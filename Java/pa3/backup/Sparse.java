//Samer Baslan
//sbaslan
//CMPS101 Fall2017
//PA3
//Sparse.java -- Top level client module. Takes two command line arguments 'input output'

import java.io.*;
import java.util.Scanner;

public class Sparse {
	public static void main(String[] args) throws IOException {
		if(args.length != 2) {
			System.err.println("Usage: Sparse inputfile outputfile");
			System.exit(1);
		}

		Scanner in = new Scanner(new File(args[0]));
		PrintWriter out = new PrintWriter(new FileWriter(args[1]));

		int n = Integer.valueOf(in.next());
		int a = Integer.valueOf(in.next()); 
		int b = Integer.valueOf(in.next());

		Matrix A = new Matrix(n);
		Matrix B = new Matrix(n);

		for(int i=0; i<a; i++) {
			int x = Integer.valueOf(in.next());
			int y = Integer.valueOf(in.next());
			double z = Double.valueOf(in.next());
			A.changeEntry(x, y, z);
		}

		for(int i=0; i<b; i++) {
			int x = Integer.valueOf(in.next());
			int y = Integer.valueOf(in.next());
			double z = Double.valueOf(in.next());
			B.changeEntry(x, y, z);
		}

		// Print A
		out.println("A has " + A.getNNZ() + " non-zero entries:");
		out.println(A);

		// Print B
		out.println("B has " + B.getNNZ() + " non-zero entries:");
		out.println(B);

		// Print (1.5)A
		out.println("(1.5)*A =");
		Matrix C = A.scalarMult(1.5);
		out.println(C);

		// Print A+B
		out.println("A+B =");
		Matrix D = A.add(B);
		out.println(D);

		// Print A+A
		out.println("A+A =");
		Matrix E = A.add(A);
		out.println(E);

		// Print B-A
		out.println("B-A =");
		Matrix F = B.sub(A);
		out.println(F);

		// Print A-A
		out.println("A-A =");
		Matrix G = A.sub(A);
		out.println(G);

		// Print transpose(A)
		out.println("Transpose(A) =");
		Matrix H = A.transpose();
		out.println(H);

		// Print AB
		out.println("A*B =");
		Matrix I = A.mult(B);
		out.println(I);

		// Print B^2
		out.println("B*B =");
		Matrix J = B.mult(B);
		out.println(J);

		// Close scanner and printwriter
		in.close();
		out.close();
	}
}
