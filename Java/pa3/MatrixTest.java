//Samer Baslan
//sbaslan
//CMPS101 Fall 2017
//PA3
//MatrixTest.java -- Test client for Matrix.java


public class MatrixTest {
	public static void main(String[] args) {
		int i, j, n=100;
		Matrix A = new Matrix(n);
		Matrix B = new Matrix(n);

		// Test Matrices
		A.changeEntry(1, 1, 1); B.changeEntry(1, 1, 0);
		A.changeEntry(1, 2, 0); B.changeEntry(1, 2, 1);
		A.changeEntry(1, 3, 1); B.changeEntry(1, 3, 0);
		A.changeEntry(2, 1, 0); B.changeEntry(2, 1, 1);
		A.changeEntry(2, 2, 1); B.changeEntry(2, 2, 0);
		A.changeEntry(2, 3, 0); B.changeEntry(2, 3, 1);
		A.changeEntry(3, 1, 1); B.changeEntry(3, 1, 0);
		A.changeEntry(3, 2, 0); B.changeEntry(3, 2, 1);
		A.changeEntry(3, 3, 1); B.changeEntry(3, 3, 0);

		// Expected output: 
		// 5
		// 1: (1, 1.0) (3, 1.0)
		// 2: (2, 1.0)
		// 3: (1, 1.0) (3, 1.0)
		System.out.println(A.getNNZ());
		System.out.println(A);

		// Expected output:
		// 4
		// 1: (2, 1.0)
		// 2: (1, 1.0) (3, 1.0)
		// 3: (2, 1.0)
		System.out.println(B.getNNZ());
		System.out.println(B);

		// Expected output:
		// 5
		// 1: (1, 2.0) (3, 2.0)
		// 2: (2, 2.0)
		// 3: (1, 2.0) (3, 2.0)
		Matrix C = A.scalarMult(2.0);
		System.out.println(C.getNNZ());
		System.out.println(C);

		// Expected output: (should be same as previous matrix)
		// 5
		// 1: (1, 2.0) (3, 2.0)
		// 2: (2, 2.0)
		// 3: (1, 2.0) (3, 2.0)
		Matrix D = A.add(A);
		System.out.println(D.getNNZ());
		System.out.println(D);

		// Expected output: 
		// 0
		Matrix E = A.sub(A);
		System.out.println(E.getNNZ());
		System.out.println(E);

		// Expected output: (same as Matrix B)
		// 4
		// 1: (2, 1.0)
		// 2: (1, 1.0) (3, 1.0)
		// 3: (2, 1.0)
		Matrix F = B.transpose();
		System.out.println(F.getNNZ());
		System.out.println(F);

		// Identity Matrix
		// Expected output:
		// 3 
		// 1: (1, 1.0)
		// 2: (2, 1.0)
		// 3: (3, 1.0)
		Matrix G = new Matrix(n);
		G.changeEntry(1, 1, 1);
		G.changeEntry(2, 2, 1);
		G.changeEntry(3, 3, 1);
		System.out.println(G.getNNZ());
		System.out.println(G);

		// Fill Matrix with 1-9
		Matrix H = new Matrix(n);
		H.changeEntry(1,1,1);
		H.changeEntry(1,2,2);
		H.changeEntry(1,3,3);
		H.changeEntry(2,1,4);
		H.changeEntry(2,2,5);
		H.changeEntry(2,3,6);
		H.changeEntry(3,1,7);
		H.changeEntry(3,2,8);
		H.changeEntry(3,3,9);

		// Expected output:
		// 9
		// 1: (1, 1.0) (2, 4.0) (3, 7.0)
		// 2: (1, 2.0) (2, 5.0) (3, 8.0)
		// 3: (1, 3.0) (2, 6.0) (3, 9.0)
		Matrix I = H.transpose();
		System.out.println(H.getNNZ());
		System.out.println(I);


		// Expected output:
		// 3
		// 1: (1, 14.0) (2, 32.0) (3, 50.0)
		// 2: (1, 32.0) (2, 77.0) (3, 122.0)
		// 3: (1, 50.0) (2, 122.0) (3, 194.0)
		Matrix J = H.mult(I);
		System.out.println(J.getNNZ());
		System.out.println(J);
		System.out.println("hello");

		// Expected output:
		// 9
		// 1: (1, 14.0) (2, 32.0) (3, 50.0)
		// 2: (1, 32.0) (2, 77.0) (3, 122.0)
		// 3: (1, 50.0) (2, 122.0) (3, 194.0)
		// true
		// false
		// true
		// false
		Matrix K = J.copy();
		System.out.println(K.getNNZ());
		System.out.println(K);
		System.out.println(K.equals(J));
		System.out.println(K.equals(B));
		System.out.println(K.equals(K));
		System.out.println(J.equals(G));

		// Initialize an empty matrix
		Matrix L = new Matrix(n);

		// Expected output: (any matrix multiplied by 0 matrix is 0, 
		// regardless of which matrix is on the left)
		// 0
		// 0
		Matrix M = L.mult(K);
		System.out.println(M.getNNZ());
		System.out.println(M);
		Matrix N = K.mult(L);
		System.out.println(N.getNNZ());
		System.out.println(N);

		// Expected output: 
		// 9
		// 1: (1, 1.0) (2, -1.0) (3, 1.0)
		// 2: (1, -1.0) (2, 1.0) (3, -1.0)
		// 3: (1, 1.0) (2, -1.0) (3, 1.0)
		Matrix O = A.sub(B);
		System.out.println(O.getNNZ());
		System.out.println(O);

		// Expected output: 
		// 1: (1, -1.0) (2, 1.0) (3, -1.0)
		// 2: (1, 1.0) (2, -1.0) (3, 1.0)
		// 3: (1, -1.0) (2, 1.0) (3, -1.0)
		Matrix P = B.sub(A);
		System.out.println(P.getNNZ());
		System.out.println(P);
		
		// Expected output:
		// 9
		// 1: (1, 1.0) (2, 1.0) (3, 1.0)
		// 2: (1, 1.0) (2, 1.0) (3, 1.0)
		// 3: (1, 1.0) (2, 1.0) (3, 1.0)
		Matrix Q = A.add(B);
		System.out.println(Q.getNNZ());
		System.out.println(Q);
		
		// Expected output: 
		// 9
		// 1: (1, 1.0) (2, 1.0) (3, 1.0)
		// 2: (1, 1.0) (2, 1.0) (3, 1.0)
		// 3: (1, 1.0) (2, 1.0) (3, 1.0)
		Matrix R = B.add(A);
		System.out.println(R.getNNZ());
		System.out.println(R);

		// Expected Output:
		// 9
		// 1: (1, 15.0) (2, 32.0) (3, 51.0)
		// 2: (1, 32.0) (2, 78.0) (3, 122.0)
		// 3: (1, 51.0) (2, 122.0) (3, 195.0) 
		Matrix S = K.add(A);
		System.out.println(S.getNNZ());
		System.out.println(S);

		// Expected Output:
		// 9
		// 1: (1, 7.5) (2, 16.0) (3, 25.5)
		// 2: (1, 16.0) (2, 39.0) (3, 61.0)
		// 3: (1, 25.5) (2, 61.0) (3, 97.5)
		Matrix T = S.scalarMult(0.5);
		System.out.println(T.getNNZ());
		System.out.println(T);

		// Expected Output: 
		// 0
		A.makeZero();
		System.out.println(A.getNNZ());
		System.out.println(A);

		// Try and change a values that equal zero to zero
		// Expected output:
		// 0
		A.changeEntry(50, 50, 0);
		A.changeEntry(20, 50, 0);
		A.changeEntry(99, 99, 0);
		A.changeEntry(100, 100, 0);
		System.out.println(A.getNNZ());
		System.out.println(A);
	}
}