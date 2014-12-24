**Important Note: Linked List does not support type integer. This is because some functions rely on passing index positions, and have
overladed counter parts that rely on passing the type of the linked list (i.e. integers), and causes ambiguous overloaded function errors.
Honestly, I don't think anyone should be using the Linked List class for just integers.



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



