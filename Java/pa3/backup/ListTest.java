//Samer Baslan
//sbaslan
//CMPS101 Fall 2017
//PA3
//Listsb.java -- sb client for List.java





public class ListTest{
	
	public static void main(String[] args){
		
		List sb = new List();
		
		// Empty list toString
		sb.toString();
		
		// print length of sb and index of cursor to console
		// expected - Length: 0 Index: -1
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("Append '1'");
		
		//sb append/front/back on 1 element list
		sb.append(1);
		
		// current state of list
		System.out.println("Front: " + sb.front());
		System.out.println("Back: " + sb.back());
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("sb toString: " + sb.toString());
		
		System.out.println("Append '2'");
		sb.append(2);
		System.out.println("Front: " + sb.front());
		System.out.println("Back: " + sb.back());
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("sb toString: " + sb.toString());
		
		System.out.println("Prepend '3'");
		sb.prepend(3);
		System.out.println("Front: " + sb.front());
		System.out.println("Back: " + sb.back());
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("sb toString: " + sb.toString());
		
		System.out.println("Move cursor to index '1'");
		sb.moveTo(1);
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("sb toString: " + sb.toString());
		
		System.out.println("Insert 4 before current cursor");
		sb.insertBefore(4);
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("sb toString: " + sb.toString());
		
		System.out.println("Inser 5 after current cursor");
		sb.insertAfter(5);
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("sb toString: " + sb.toString());

		// Create a list that's supposedly the same as sb
		// output should be TRUE
		List sb2 = new List();
		sb2.append(3);
		sb2.append(4);
		sb2.append(1);
		sb2.append(5);
		sb2.append(2);
		System.out.println("sb2 Length: " + sb2.length() + " sb2 Index: " + sb2.getIndex());
		System.out.println("sb2 toString: " + sb2.toString());
		System.out.print("sb and sb2 are equal ");
		if(sb.equals(sb2)) {
			System.out.println("TRUE");
		} else {
			System.out.println("FALSE");
		}

		// output after appending should be FALSE
		sb2.append(100);
		System.out.println("sb Length: " + sb.length() + " sb Index: " + sb.getIndex());
		System.out.println("sb toString: " + sb.toString());
		System.out.println("sb2 Length: " + sb2.length() + " sb2 Index: " + sb2.getIndex());
		System.out.println("sb2 toString: " + sb2.toString());
		System.out.print("COMPARE sb AND sb2: ");
		if(sb.equals(sb2)) {
			System.out.println("TRUE");
		} else {
			System.out.println("FALSE");
		}

		System.out.println("moveNext()");
		sb.moveNext();
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("sb toString: " + sb.toString());
		System.out.println("Current index element: " + sb.getElement());
		
		System.out.println("moveNext()");
		sb.moveNext();
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("sb toString: " + sb.toString());
		System.out.println("Current index element: " + sb.getElement());
		
		System.out.println("movePrev()");
		sb.movePrev();
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("sb toString: " + sb.toString());
		System.out.println("Current index element: " + sb.getElement());
		
		System.out.println("deleteFront()");
		sb.deleteFront();
		sb.deleteBack();
		System.out.println("sb toString after deletions: " + sb.toString());
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("Current index element: " + sb.getElement());
		System.out.println("Front: " + sb.front());
		System.out.println("Back: " + sb.back());

		System.out.println("delete()");
		sb.delete();
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("sb toString: " + sb.toString());
		
		System.out.println("moveTo(0)");
		sb.moveTo(0);
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("sb toString: " + sb.toString());
		
		System.out.println("delete()");
		sb.delete();
		System.out.println("Length: " + sb.length() + " Index: " + sb.getIndex());
		System.out.println("sb toString: " + sb.toString());
	}
}
