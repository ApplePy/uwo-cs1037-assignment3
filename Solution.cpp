#define NULL 0 // for XCode
#include <assert.h>
#define _ASSERT(expr) assert(expr)
#include "DLinkedOrderedList.h"
#include <iostream>

int main() {
	// NOTE: This testing code is missing a lot of couts (see NOTE at the bottom). Fill in cout lines in this file as you need.

	DLinkedOrderedList<int> test;
	test.isEmpty(); // Test isEmpty function
	test.insert(5); // Test insertion
	test.insert(5); // Test non-unique front insertion(s)
	test.insert(5);
	test.insert(5);
	test.insert(3); // Test front insertion
	test.insert(8); // Test back insertion
	test.insert(8); // Test non-unique back insertion
	test.insert(7); // Test unique insertion in the middle
	test.insert(7); // Test non-unique insertion in the middle
	test.isEmpty(); // Another isEmpty test
	
	auto lastIter = test.begin(); // Holds pointer to last node, since --test.end() doesn't work due to implementation issues.

	// Tests iterator forward begin, end, incrementing, size, not-equals comparison, and overloaded dereferencing
	for (auto iter = test.begin(); iter != test.end(); ++iter) {
		std::cout << *iter << std::endl;
		//lastIter = iter; // WHY IS ASSIGNMENT GONE???...
		
		// Assignment operator missing workaround below...
		static int counter = 0;
		if (counter++ != test.size() - 1)
			++lastIter; 

	}

	std::cout << std::endl;

	// Tests iterator foward decrementing
	for (auto iter = lastIter; iter != test.end(); --iter) {
		std::cout << *iter << std::endl;
	}

	std::cout << std::endl << std::endl; // Spacing

	// Tests iterator backward begin, end, incrementing, size, not-equals comparison, and overloaded dereferencing
	auto lastIter2 = test.begin(BACKWARD);
	for (auto iter = test.begin(BACKWARD); iter != test.end(BACKWARD); ++iter) {
		std::cout << *iter << std::endl;

		// Assignment operator missing workaround below...
		static int counter2 = 0;
		if (counter2++ != test.size() - 1)
			++lastIter2;

	}

	std::cout << std::endl;

	// Tests iterator backward decrementing
	for (auto iter = lastIter2; iter != test.end(BACKWARD); --iter) {
		std::cout << *iter << std::endl;
	}

	lastIter.kill();						//Test destruction of an end node
	(--lastIter2).kill();					//Test destruction of an inside node
	test.begin().kill();					//Test destruction of a beginning node

	DLinkedOrderedList<int>copier(test);	//Test copy constructor
	for (auto iter = copier.begin(); iter != copier.end(); ++iter) {
		std::cout << *iter << std::endl;
	}
	test.remove(test.insert(6));	//Test removal by pointer
	test.insert(10);
	test.remove(10);				//Test removal by value
	test.removeAll(5);				//Test removeAll

	return 0;						//Tests destructors

	//NOTE: Although there is little output being sent to the screen, most of this was debugged by using the watch lists at the bottom of the Visual Studio IDE to check the state of the stack and heap memory, as well as the state of the linked list(s) after each line was executed. Particualarly useful as direct access to node prev/next pointers are inaccessible from this file - printing out the state of the linked list after each and every function call test would have been tedious to read through and decipher.
}