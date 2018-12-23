//Samer Baslan
//sbaslan
//CMPS101 Fall 2017
//10-06-2017
//List.java


class List{

	private class Node{
		//Fields
		int data;
		Node next;
		Node prev;

		//Constructor
		Node(int data){
			this.data = data;
			next = null;
			prev = null;
		}

		//toString(): overrides Object's toString() method
		public String toString(){
			return String.valueOf(data);
		}

		//equals(): overrides Object's equals() method
		public boolean equals(Object x){
			boolean eq = false;
			Node that;
			if(x instanceof Node){
				that = (Node) x;
				eq = (this.data==that.data);
			}
			return eq;
		}
	}


	//Fields

	private Node front;
	private Node back;
	private Node cursor;
	private int length;
	private int cursorindex;

	//Constructor
	List(){
	front = null;
	back = null;
	cursor = null;
	length = 0;
	cursorindex = -1;
	}

//Access Functions

	// length()
	// Returns the number of elements in the list
	int length(){
		return length;
	}

	// index()
	// If the cursor is undefined, returns the index of the cursor element, otherwise returns -1
	int index(){
		return cursorindex;
	}

	// front()
	// Retruns front element. Pre: length() > 0
	int front(){
		if(this.length() <= 0){
			throw new RuntimeException("List Error: front() called on empty list");
		}
		return front.data;
	}

	// back()
	// Returns back element. Pre: length() > 0
	int back(){
		if(this.length() <= 0){
			throw new RuntimeException("List Error: back() called on empty list");
		}
		return back.data;
	}

	// get()
	// Returns the cursor element. Pre: length() > 0, index() >= 0
	int get(){
		if(this.length() <= 0){
			throw new RuntimeException("List Error: get() called on empty list");
		}
		if(this.index() < 0){
			throw new RuntimeException("List Error: get() called on undefined cursor");
		}
		return cursor.data;
	}

	// equals()
	// Returns true if and only if this List and L are the same integer sequence.
	// The states of the cursors in the two lists are not used in determining equality.
	boolean equals(List L){
		if(L.length == this.length){
			Node tempfront = L.front;
			Node tempfront2 = this.front;
			while(tempfront.next != null && tempfront2.next != null){
				if(tempfront.data == tempfront2.data){
					tempfront = tempfront.next;
					tempfront2 = tempfront2.next;
				}
				else{
					return false;
				}
			}
			return true;
		}
		return false;
	}


//Manipulation procedures


	// clear
	// Resets this List to its original empty state.
	void clear(){
		front = back = cursor = null;
		length = 0;
		cursorindex = -1;
	}


	// moveFront()
	// If List is nonempty, places the cursor under the front element, otherwise does nothing
	void moveFront(){
		if(this.length() > 0){
			cursor =  front;
			cursorindex = 0;
		}
	}


	// moveBack()
	// If List is nonempty, places the cursor under the back element, otherwise does nothing
	void moveBack(){
		if(this.length() > 0){
			cursor = back;
			cursorindex = length - 1;
		}
	}

	// movePrev()
	// If cursor is defined and not at front, moves cursor one step toward
	// front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void movePrev(){
		if(cursor != null && this.index() != 0){
			cursor = cursor.prev;
			cursorindex = cursorindex - 1;
		}
		else if(cursor != null && this.index() <= 0){
			cursor = null;
			cursorindex = -1;
		}
		else{ //do nothing
		}
	}


	// moveNext()
	// If cursor is defined and not at back, moves cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void moveNext(){
		if(cursor != null && this.index() != this.length() - 1){
		cursor = cursor.next;
		cursorindex = cursorindex + 1;
		}
		else if(cursor != null && this.index() == this.length() - 1){
			cursor = null;
			cursorindex = -1;
	}
	else{
	}
	}
	
	
	// prepend()
	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element.
	void prepend(int data){
		Node N = new Node(data);
		if(this.length() == 0){
			front = back = N;
		}
		else{
			front.prev = N;
			N.next = front;
			front = N;
		}
		length++;
	} 
	
	// append()
	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	void append(int data){
		Node N = new Node(data);
		if(this.length == 0){
			front = back = N;
		}
		else{
			back.next = N;
			N.prev = back;
			back = N;
		}
		length++;
	} 
	
	// insertBefore()
	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	void insertBefore(int data){
		if(this.length() <= 0){
			throw new RuntimeException("List Error: insertBefore() called on empty list");
		}
		if(this.index() < 0){
			throw new RuntimeException("List Error: insertBefore() called on undefined cursor");
		}
		Node N = new Node(data);
		if(cursor.prev == null){
			cursor.prev = N;
			N.next = cursor;
			front = N;
		}else{
			N.prev = cursor.prev;
			cursor.prev.next = N;
			N.next = cursor;
			cursor.prev = N;
		}
		length++;
		cursorindex++;
	}
	
	// insertAfter()
	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	void insertAfter(int data){
		if(this.length() <= 0){
			throw new RuntimeException("List Error: insertAfter() called on empty list");
		}
		if(this.index() < 0){
			throw new RuntimeException("List Error: insertAfter() called on undefined cursor");
		}
		
		Node N = new Node(data);
		if(cursor.next == null){
			cursor.next = N;
			N.prev = cursor;
			back = N;
		}
		else{
			cursor.next.prev = N;
			N.next = cursor.next;
			N.prev = cursor;
			cursor.next = N;
		}
		length++;
	}
 
	// deleteFront()
	// Deletes the front element. 
	// Pre: length()>0
	void deleteFront(){
		if(this.length() <= 0){
			throw new RuntimeException("List Error: deleteFront() called on empty list");
		}
		front = front.next;
		front.prev = null;
		length--;
		}
	
	// deleteBack()
	// Deletes the back element. 
	// Pre: length()>0
	void deleteBack(){
		if(this.length() <= 0){
			throw new RuntimeException("List Error: deleteBack() called on empty list");
		}
		back = back.prev;
		back.next = null;
		length--;
		}
	
	
	//delete()
	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	void delete(){
		if(this.length() <= 0){
			throw new RuntimeException("List Error: delete() called on empty list");
		}
		if(this.index() < 0){
			throw new RuntimeException("List Error: delete() called on undefined cursor");
		}
		if(cursor == front){
			deleteFront();
		}
		else if(cursor == back){
			deleteBack();
		}
		else{
			cursor.next.prev = cursor.prev;
			cursor.prev.next = cursor.next;
			length--;
			cursor = null;
			cursorindex = -1;
		}
	}
	
	
	
// Other methods

	// toString()
	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
	public String toString(){
		StringBuffer sb = new StringBuffer();
		Node N = front;
		while(N!=null){
			sb.append(N.toString());
			sb.append(" ");
			N = N.next;
		}
		return new String(sb);
	}
	
	// copy()
	// Returns a new List representing the same integer sequence as this
	// List. The cursor in the new list is undefined, regardless of the
	// state of the cursor in this List. This List is unchanged.
	List copy(){
		List Q = new List();
		Node N = this.front;

		while( N!=null ){
			Q.append(N.data);
			N = N.next;
		}
		return Q;
	}
}
















	
