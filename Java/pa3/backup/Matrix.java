//Samer Baslan
//sbaslan
//CMPS101 Fall2017
//PA3
//Matrix.java -- Matrix ADT



public class Matrix{

	private class Entry{
		// Fields
		int column;
		double value;
		// Default Constructor
		Entry(){
			column = 0;
			value = 0;
		}
		// Overloaded Constructor
		Entry(int column, double value){
			this.column = column;
			this.value = value;
		}

		public boolean equals(Object o){
			Entry other = (Entry) o;
			return (this.column==other.column && this.value==other.value);
		}

		// toString(): 
		public String toString(){
			return " ("+column+", "+value+")";
		}
	}

		//error fix
		public int hashCode(){
			return 0;
		}


	// Fields
	private List[] row;
	private int size;
	private int NNZ;

	// Constructor
	// Makes a new n x n zero Matrix. pre: n>=1
	public Matrix(int n){
		row = new List[n+1];
		size = n;
		NNZ = 0;
		for(int i=1; i<=size; i++){
			row[i] = new List();
		}
	} // no List at row[0]

	// Access Functions
	// getSize(): Returns n, the number of rows and columns of this Matrix
	public int getSize(){
		return size;
	}

	// getNNZ(): Returns the number of non-zero entries in this Matrix
	public int getNNZ(){
		return NNZ;
	}

	// overrides Object's equals() method
	public boolean equals(Object M){
		if(!(M instanceof Matrix)){
			throw new RuntimeException("Matrix Error: equals() called with non-matrix parameter");
		}
		Matrix other = (Matrix) M;
		// Check for equivalent size and same number of non-zero entries
		if(size == other.getSize() && NNZ == other.getNNZ()){
			for(int i=1; i<=size; i++){
				if(row[i].length() > 0){
					row[i].moveTo(0);
					other.row[i].moveTo(0);
					while(row[i].getIndex() >= 0){
						Entry x = (Entry)row[i].getElement();
						Entry y = (Entry)other.row[i].getElement();
						if(!x.equals(y)){
							return false;
						}
						row[i].moveNext();
						other.row[i].moveNext();
					}
				}
			}
			return true;
		}
		return false;
	}

	// Manipulation Procedures
	// makeZero(): sets this Matrix to the zero state 
	// Assuming zero state means a matrix of all zeroes (lists initialized but are empty)
	public void makeZero(){
		row = new List[size+1];
		NNZ = 0;
		for(int i=1; i<=size; i++){
			row[i] = new List();
		}
	}

	// copy(): returns a new Matrix having the same entries as this Matrix
	public Matrix copy(){
		Matrix copym = new Matrix(size);
		for(int i=1; i<=copym.getSize(); i++){
			row[i].moveTo(0);
			while(row[i].getIndex() >= 0){
				Entry data = (Entry)row[i].getElement();
				copym.changeEntry(i, data.column, data.value);
				row[i].moveNext();
			}
		}
		return copym;
	}

	// changeEntry():
	// Mij=0, x=0 -> do nothing
	// Mij=0, x!=0 -> insert x at row i column j
	// Mij!=0, x=0 -> delete value at row i column j
	// Mij!=0, x!=0 -> changes ith row, jth column of this Matrix to x 
	// Pre: 1<=i<=getSize(), 1<=j<=getSize()
	public void changeEntry(int i, int j, double x){
		if(i<1 || i>size || j<1 || j>size){
			throw new RuntimeException("Matrix Error: changeEntry() called with out of bounds indexes");
		}
		boolean check = true;
		if(row[i].length() != 0){
			row[i].moveTo(0);
			while(check && row[i].getIndex()>=0){
				Entry data = (Entry)row[i].getElement();
				if(data.column < j){
					row[i].moveNext();
				}else if(data.column == j){
					if(x == 0){
						row[i].delete();
						NNZ--;
					}else{
						data.value = x;
					}
					check = false;
				}else{
					if(x != 0){
						row[i].insertBefore(new Entry(j,x));
						NNZ++;
						check = false;
					}
				}
			}
		}
		if(check && x != 0){
			row[i].append(new Entry(j,x));
			NNZ++;
		}
	}

	// scalarMult() returns a new Matrix that is the scalar 
	// product of this Matrix with x
	public Matrix scalarMult(double x){
		Matrix mult = new Matrix(this.size);
		for(int i=1; i<=mult.getSize(); i++){
			row[i].moveTo(0);
			while(row[i].getIndex() != -1){
				Entry data = (Entry)row[i].getElement();
				mult.changeEntry(i, data.column, data.value*x);
				row[i].moveNext();
			}
		}
		return mult;
	}

	// add(): returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize()==M.getSize()
	public Matrix add(Matrix M){
		if(getSize() != M.getSize()){
			throw new RuntimeException("Matrix Error: add() called on matrices with different sizes");
		}
		return addsub(this, M, true);
	}

	// returns a new Matrix that is the difference of this Matrix with M
 	// pre: getSize()==M.getSize()
	public Matrix sub(Matrix M){
		if(getSize() != M.getSize()){
			throw new RuntimeException("Matrix Error: sub() called on matrices with different sizes");
		}
		return addsub(this, M, false);
	}

	// private helper function for add() and sub()
	private Matrix addsub(Matrix N, Matrix M, boolean add){
		Matrix ds = new Matrix(N.size);
		// If the matrices reference the same object
		if(N == M){
			if(add){
				return N.scalarMult(2);
			}else{
				return ds; // return empty matrix
			}
		}else{
			for(int i=1; i<=N.size; i++){
				// If both lists not empty
				if(N.row[i].length() > 0 && M.row[i].length() > 0){
					N.row[i].moveTo(0);
					M.row[i].moveTo(0);
					Entry eN = (Entry)N.row[i].getElement();
					Entry eM = (Entry)M.row[i].getElement();
					
					int iter = N.row[i].length() + M.row[i].length();
					for(int j=1; j<=iter; j++){
						// If the operation is subtract, then negate the 2nd value
						double mValue = add ? eM.value : -eM.value;
						if(eN.column < eM.column){
							// First case is standard insert of one element before the other
							// Special case where one list has finished iterating while the other
							// still has more elements that need to be inserted (add/sub to 0)
							if(N.row[i].getIndex()>=0 && M.row[i].getIndex()>=0){
								ds.changeEntry(i, eN.column, eN.value);
							}else{
								ds.changeEntry(i, eM.column, mValue);
								M.row[i].moveNext();
							}
							N.row[i].moveNext();
						}else if (eN.column > eM.column){
							if(N.row[i].getIndex()>=0 && M.row[i].getIndex()>=0){
								ds.changeEntry(i, eM.column, mValue);
							}else{
								ds.changeEntry(i, eN.column, eN.value);
								N.row[i].moveNext();
							}
							M.row[i].moveNext();
						}else{
							ds.changeEntry(i, eN.column, eN.value + mValue);
							N.row[i].moveNext();
							M.row[i].moveNext();
							j++; 
						}
						// Update eN and eM if the cursor still points to an element
						// This fixes the edge case where one list has no more non zero elements
						// to insert while the other list still has elements
						if(N.row[i].getIndex()>=0){
							eN = (Entry)N.row[i].getElement();
						}
						if(M.row[i].getIndex()>=0){
							eM = (Entry)M.row[i].getElement();
						}
					}
				// If only the first list has elements, copy those elements into the matrix
				}else if (N.row[i].length() > 0 && M.row[i].length() == 0){
					N.row[i].moveTo(0);
					for(int j=1; j<=N.row[i].length(); j++){
						Entry eN = (Entry)N.row[i].getElement();
						ds.changeEntry(i, eN.column, eN.value);
						N.row[i].moveNext();
					}
				// If only the second list has elements, copy those elements into the matrix
				}else if(N.row[i].length() == 0 && M.row[i].length() > 0){
					M.row[i].moveTo(0);
					for(int j=1; j<=M.row[i].length(); j++){
						Entry eM = (Entry)M.row[i].getElement();
						double mValue = add ? eM.value : -eM.value;
						ds.changeEntry(i, eM.column, mValue);
						M.row[i].moveNext();
					}
				}
			}
		}
		return ds;
	}

	// returns a new Matrix that is the transpose of this Matrix
	public Matrix transpose(){
		Matrix trans = new Matrix(this.size);
		for(int i=1; i<=trans.getSize(); i++){
			row[i].moveTo(0);
			while(row[i].getIndex() != -1){
				Entry data = (Entry)row[i].getElement();
				trans.changeEntry(data.column, i, data.value);
				row[i].moveNext();
			}
		}
		return trans;
	}

	// returns a new Matrix that is the product of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix mult(Matrix M){
		if(size != M.getSize()){
			throw new RuntimeException("Matrix Error: mult() called on matrices with different sizes");
		}
		Matrix mult = new Matrix(this.size);
		Matrix trans = M.transpose();
		for(int i=1; i<=size; i++){
			// check row[i].length >= 0
			// since a row of zeroes does not contribute to the dot product
			if(row[i].length() > 0){
				for(int j=1; j<=size; j++){
					// check that the length of col j is greater than zero
					if(trans.row[j].length() > 0){
						double result = dot(row[i], trans.row[j]);
						mult.changeEntry(i, j, result);
					}
				}
			}
		}
		return mult;
	}

	// helper method that takes two Lists and calculates the dot product
	private static double dot(List P, List Q){
		P.moveTo(0);
		Q.moveTo(0);
		double sum = 0;
		while(P.getIndex()!=-1 && Q.getIndex()!=-1){
			Entry eP = (Entry)P.getElement();
			Entry eQ = (Entry)Q.getElement();
			if(eP.column < eQ.column){
				P.moveNext();
			}else if (eP.column > eQ.column){
				Q.moveNext();
			}else{
				sum = sum + (eP.value * eQ.value);
				P.moveNext();
				Q.moveNext();
			}
		}
		return sum;
	}

	// toString(): overrides Object's toString() method
	// prints a matrix in the form [line#]: [(column, data)...]
	public String toString(){
		String matrixString = "";
		for(int i=1; i<=size; i++){
			if(row[i].length() > 0){
				matrixString = matrixString + i + ":" + row[i].toString();
				matrixString += "\n";
			}
		}
		return matrixString;
	}
}
