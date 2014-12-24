----------Introduction----------

  What is different about this Linked List?

	This implementation has a faster system for accessing the elements contained. In a 'traditional' linked list, accessing an 
	element generally reqiures starting at the beginning (head), and going through each element, in order, until the desired element is 
	found. For example, accessing the middle element of a linked list with 100,000,000 elements requires 50,000,000 comparisons.

	This implementation allows the user to specifiy a 'reference number.' This keeps a record every n-th element added, where n is the 
	reference number specified by the user. Then, when searching, the list can automatically begin searching from the closest reference.
	For example, if the user specifies the reference number to be 10, then every element that is a multiple of 10 is added to the 
	reference list. Then, when searching for an element, we will say element 34, the list automatically begins searching from the 30th 
	element in the list, ultimately limiting the amount of comparisons from 35 (elements 0 - 34) to 5 (elements 30 - 34). 
	
	Some things to consider: the smaller the reference number, the faster searching will be, but the more memory Linked List will
	occupy. Now, Linked List only keeps a reference to each place, so the memory used is not over the top, but it can be a factor,
	especially in very large lists.



  Creating a Linked List object:
	
	A linked list object only requires one argument to be instantiated, and that is the 'type' of list you want.
	Examples:
		A list of strings: 				LinkedList<string> list;
		A list of user defined class 'Students':	LinkedList<Students> list;

	Alternatively, the user may specify a reference number. If you do not know what this is, see the above section 'what is different
	about this Linked List?'. By default, this feature is turned off, and no references are contained. The user may specifiy any number
	in unsigned integer range.
	Examples:
		A list of strings with references every 100 objects:	LinkedList<string, 100> list;
		A list of string pointers without any references: 	LinkedList<string *> list; (or LinkedList<string *, 0> list;)
	



**Important Note: Linked List does not support type integer. This is because some functions rely on passing index positions, and have
overloaded counter parts that rely on passing an object of the type of the linked list (i.e. integers), and causes ambiguous overloaded 
function errors.
Honestly, I don't think anyone should be using the Linked List class for just integers anyways.



----------Functionality----------
	-Use ctrl + F to serach this document for the funtion you are wanting more information about.

  1. Constructing
  2. push
  3. pop
  4. insertHead
  5. insertAfter
  6. insertBefore





















----------Descriptions----------

Constructing:

	LinkedList()
	LinkedList(_T info)

	The Linked List class has two constructors, one if the user is passing in an element to add to the list, and a default constructor
	(no element to add). Therefore, it is possible to have an object of the Linked List class that contains no elements. Attempting to
	perform certain functionality on an empty list will throw various errors. Because of this, it is recommended to us try and catch
	blocks when it is not guaranteed that the list contains elements. For the specific errors, see the descriptions of the functions
	that throw the respective error.




push:
	
	void push(_T info)
	
	This function takes an object of the type of the linked list, and appends it to the end of the list. Note: the function takes the
	element to be added by VALUE, so it is recommended that the user provide overloaded assignment operators / copy constructors for
	user defined classes.




pop:

	_T pop()

	This function removes the last element to be added (e.g. the 'tail' of the list). It returns the data that was contained at the 
	location. This will throw an out_of_range exception if the current list has 0 elements.




insertHead:

	void insertHead(_T info)

	This will insert the new data as the 'head' of the list (i.e. the first element in the list). This is guaranteed to execute, 
	regardless if the list is empty or not.




insertAfter:

	void insertAfter(unsigned int index, _T info)
	bool insertAfter(const _T &key, _T info)

	This allows the user to inset the new data AFTER the element specified. The user may either choose to identify the element by index
	value, or by a key value (of the same type as the Linked List). If an index value that is larger than the largest possible index
	value is passed, and out_of_range error is thrown. Note: calling insertAfter and passing in the largest possible index value
	for the current list is equivalent to calling the 'push' function.

	If the user passes in a 'key' value to insert after, the function will return true if the operation was successful, or false 
	otherwise. If it returns false, this can only mean that the 'key' value does not currently exist in the Linked List.



insertBefore:

	void insertBefore(unsigned int index, _T info)
	bool insertBefore(const _T &key, _T info)

	These have the same functionality as the insertAfter functions, but instead of inserting after the element specified, the new data
	is inserted before the element specified. Note: calling insertBefore and passing 0 as the index value is eqivalent to calling
	the 'insertHead' function.



