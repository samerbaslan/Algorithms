//Samer Baslan
//sbaslan
//CMPS101 Fall2017
//PA3
//List.java -- List ADT with minor adjustments from PA1

public class List{
	
	private class Node{
		// Fields
		Object data;
		Node prev;
		Node next;
		// Default Constructor
		Node(){
			this.data = null;
			next = null;
			prev = null;
		}
		// Overloaded Constructors
		Node(Object data){
			this.data = data;
			next = null;
			prev = null;
		}
		Node(Object data, Node next, Node prev){
			this.data = data;
			this.next = next;
			this.prev = prev;
		}

		public String toString(){
			return String.valueOf(data);
		}
	}

		public int hashCode(){
			return 0;
		}		




	// Fields
	private Node front;
	private Node back;
	private Node cursor;
	private int cursorindex;
	private int length;

	// Constructor
	public List(){
		front = null;
		back = null;
		cursor = null;
		cursorindex = -1;
		length = 0;
	}

	// Access Functions
	// returns the length of the List
	public int length(){
		return length;
	}
	
	public int index(){
		return cursorindex;
	}
	
	public Object get(){
		return cursorindex;
	}
	
	// returns the index of the cursor
	public int getIndex(){
		return cursorindex;
	}

	// front(): returns front element in this list
	// Pre: this.length() > 0
	public Object front(){
		if(this.length() == 0){
			throw new RuntimeException("List Error: front() called on empty List");
		}
		return front.data;
	}

	// back(): returns back element in this list
	// Pre: this.length() > 0
	public Object back(){
		if(this.length() == 0){
			throw new RuntimeException("List Error: back() called on empty List");
		}
		return back.data;
	}

	// getElement(): returns cursor element in this list
	// Pre: length() > 0, getIndex() >= 0
	public Object getElement(){
		if(this.length() == 0){
			throw new RuntimeException("List Error: getElement() called on empty List");
		}else if(this.cursorindex == -1){
			throw new RuntimeException("List Error: getElement() called with undefined cursor");
		}
		return cursor.data;
	}

	// Returns true if this List and L are the same integer
	// sequence. The cursor is ignored in both lists.
	public boolean equals(Object L){
		if(!(L instanceof List)){
			throw new RuntimeException("List Error: equals() called with non-list parameter");
		}
		List that = (List) L;
		boolean check = true;
		Node A = this.front;
		Node B = that.front;
		if(this.length == that.length){
			while(check && A != null){
				check = (A.data == B.data);
				A = A.next;
				B = B.next;
			}
			return check;
		}
		return false;
	}

	// Manipulation procedures
	// Resets this List to the empty state.
	public void clear(){
		front = null;
		back = null;
		cursor = null;
		cursorindex = -1;
		length = 0;
	}
	
	public void moveFront(){
		if(this.length() > 0){
			cursor =  front;
			cursorindex = 0;
		}
	}
	
	public void moveBack(){
		if(this.length() > 0){
			cursor = back;
			cursorindex = length - 1; //back element's cursor index = length - 1
		}
	}

	// If 0<=i<=length()-1, moves the cursor to the element
	// at index i, otherwise the cursor becomes undefined.
	public void moveTo(int i){
		if(i>=0 && i<=length-1){
			cursor = front;
			for(int j=0; j<i; j++){
				cursor = cursor.next;
			}
			cursorindex = i;
		}else{
			cursor = null;
			cursorindex = -1;
		}
	}

	// If 0<getIndex()<=length()-1, moves the cursor one step toward front
	// If getIndex()==0, cursor becomes undefined.
	// If getIndex()==-1, cursor remains undefined. 
	public void movePrev(){
		if(cursorindex>0 && cursorindex<=length-1){
			moveTo(cursorindex-1);
		}else if(cursorindex == 0 || cursorindex == -1){
			cursor = null;
			cursorindex = -1;
		}
	}

	// If 0<=getIndex()<length()-1, moves the cursor one step toward back
	// If getIndex()==length()-1, cursor becomes undefined
	// If getIndex()==-1, cursor remains undefined.
	public void moveNext(){
		if(cursorindex>=0 && cursorindex<length-1){
			moveTo(cursorindex+1);
		}else if(cursorindex == length-1 || cursorindex == -1){
			cursor = null;
			cursorindex = -1;
		}
	}

	// Inserts new element before front element in this List.
	public void prepend(Object data){
		if(this.length() == 0){
			Node node = new Node(data);
			front = node;
			back = node;
		}else{
			front = new Node(data, front, null);
			front.next.prev = front;
		}
		length++;
		if(cursorindex >= 0){
			cursorindex++;
		}
	}

	// Inserts new element after back element in this List.
	public void append(Object data){
		if(this.length() == 0){
			Node node = new Node(data);
			front = node;
			back = node;
		}else{
			back = new Node(data, null, back);
			back.prev.next = back;
		}
		length++;
	}

	// Inserts new element before cursor element in this List.
	// Pre: length()>0, getIndex()>=0
	public void insertBefore(Object data){
		if(this.length() == 0){
			throw new RuntimeException("List Error: insertBefore() called on empty List");
		}else if(this.getIndex() == -1){
			throw new RuntimeException("List Error: insertBefore() called with undefined cursor");
		}
		if(cursorindex == 0){
			prepend(data);
		}else{
			Node ins = new Node(data, cursor, cursor.prev);
			ins.prev.next = ins;
			cursor.prev = ins;
			length++;
			cursorindex++;
		}
	}

	// Inserts new element after cursor element in this List.
	// Pre: length()>0, getIndex()>=0
	public void insertAfter(Object data){
		if(this.length() == 0){
			throw new RuntimeException("List Error: insertAfter() called on empty List");
		}else if(this.getIndex() == -1){
			throw new RuntimeException("List Error: insertAfter() called with undefined cursor");
		}
		Node ins = new Node(data, cursor.next, cursor);
		cursor.next = ins;
		ins.next.prev = ins;
		length++;
	}

	// Deletes the front element in this List. Pre: length()>0
	public void deleteFront(){
		if(this.length() == 0){
			throw new RuntimeException("List Error: deleteFront() called on empty List");
		}
		if(cursor == front){
			cursor = null;
			cursorindex = -1;
		}else{
			cursorindex--;
		}
		front = front.next;
		if(length != 1){
			front.prev = null;
		}
		length--;
	}

	// Deletes the back element in this List. Pre: length()>0
	public void deleteBack(){
		if(this.length() == 0){
			throw new RuntimeException("List Error: deleteBack() called on empty List");
		}
		if(cursor == back){
			cursor = null;
			cursorindex = -1;
		}
		back = back.prev;
		if(length != 1){
			back.next = null;
		}
		length--;
	}

	// Deletes cursor element in this List. Cursor is undefined after this
	// operation. Pre: length()>0, getIndex()>=0
	public void delete(){
		if(this.getIndex() == -1){
			throw new RuntimeException("List Error: delete() called with undefined cursor");
		}else if (this.length() == 0){
			throw new RuntimeException("List Error: delete() called on empty List");
		}
		if(cursor == front){
			deleteFront();
		}else if (cursor == back){
			deleteBack();
		}else{
			Node left = cursor.prev;
			Node right = cursor.next;
			left.next = right;
			right.prev = left;
			cursor = null;
			cursorindex = -1;
			length--;
		}
	}

	// Override Object toString() method, creates a sequence of 
	// integers representing the List
	public String toString(){
		String op = "";
		Node current = front;
		for(int i=0; i<this.length(); i++){
			op = op + current.toString();
			current = current.next;
		}
		return op;
	}
}
