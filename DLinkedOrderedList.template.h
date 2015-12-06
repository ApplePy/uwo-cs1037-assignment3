#pragma once

// Default constructor
template <class Item, class Order>
DLinkedOrderedList<Item, Order>::DLinkedOrderedList() {
	m_head = NULL;
	m_tail = NULL;
	m_size = 0;
}

// Copy constructor
template <class Item, class Order>
DLinkedOrderedList<Item, Order>::DLinkedOrderedList(DLinkedOrderedList<Item, Order> const& copy) {
	// Optimization Opportunity: Going backwards so that insertions don't have to iterate through the entire structure each time - they're simply inserted at the front of the chain.

	//Procedure: Start from the end node of the source list (can't use iterators, they're not const-safe), and insert it to this list, then move the node pointer forward one in the source list.
	Node* nodeIter = copy.m_tail;
	while (nodeIter != NULL) {
		insert(nodeIter->value);
		nodeIter = nodeIter->prev;
	}
}

// Destructor
template <class Item, class Order>
DLinkedOrderedList<Item, Order>::~DLinkedOrderedList() {
	// Procedure: start an iterator at the beginning of the list, and continuously call kill() to delete each node until there are none left
	Iterator destroyer = begin();
	while (destroyer != end()) {
		destroyer.kill(); // Auto-iterates; could have also used remove(destroyer), but this way is more amusing
	}
	// stack-allocated members don't need to be cleared. They'll die gracefully.
}

// List size checker
template <class Item, class Order>
unsigned int DLinkedOrderedList<Item, Order>::size() const {
	return m_size;
}

// Checks if list is empty
template <class Item, class Order>
bool DLinkedOrderedList<Item, Order>::isEmpty() const {
	return (m_size == 0) ? true : false; // Conditional operator, better than the long if-block
}

// Returns an iterator to the first item in the list
template <class Item, class Order>
typename DLinkedOrderedList<Item, Order>::Iterator DLinkedOrderedList<Item, Order>::begin(Direction direction) {
	// Procedure: if list is empty, return NULL iterator. Otherwise, return an iterator pointing to the first or last node, depending on direction.
	if (isEmpty())
		return end(direction); // Equal to NULL operator
	else
		return Iterator((direction == FORWARD) ? m_head : m_tail, *this, direction);
}

// Returns an iterator to the null pointer - one past the last item in the list
template <class Item, class Order>
typename DLinkedOrderedList<Item, Order>::Iterator DLinkedOrderedList<Item, Order>::end(Direction direction) {
	return Iterator(NULL, *this, direction);
}

// Inserts items into the ordered list
template <class Item, class Order>
typename DLinkedOrderedList<Item, Order>::Iterator DLinkedOrderedList<Item, Order>::insert(Item item) {
	// Procedure: if the list is empty, create the new node and link the m_head and m_tail as appropriate. Otherwise, iterate through the list until you find the appropriate insertion place, or you hit the end. Then create a new node, relink the nodes on either side and increase the size. Return an iterator to the new node.
	if (isEmpty()) {
		m_head = new Node(item);
		m_tail = m_head;
		m_size++;
		return begin(); // Returns an iterator to this node
	}
	else {
		// Use iterators to go crawling through the list until you find the apropriate insertion place, then insert as appropriate
		Iterator search = begin();
		while (search.m_node != NULL && !Order::compare(item, *search)) {
			++search;
		}

		// This is the end of the chain
		if (search.m_node == NULL) {
			Node* newNode = new Node(item, NULL, m_tail); // Create new end node
			m_tail->next = newNode; // Relink old end node to new one
			m_tail = newNode; // Officially designate new end node as canonical end node
			m_size++;
			return Iterator(newNode, *this);
		}
		// Node is to be inserted in the front, or somewhere in the middle of the chain
		else {
			Node* newNode = new Node(item, search.m_node, search.m_node->prev); // Create new node

			// Relink bordering nodes
			if (search.m_node->prev != NULL)
				search.m_node->prev->next = newNode;
			else
				m_head = newNode; //Insertion is to be at the front of the list

			search.m_node->prev = newNode;
			--search; // Move the iterator back onto the new node, to save time having to create a new one
			m_size++;
			return search;
		}
	}
}

// Removes first matching item found from the ordered list
template <class Item, class Order>
bool DLinkedOrderedList<Item, Order>::remove(Item item) {
	// Procedure: Iterate through the list, when a match is found, delete it and return true. Else, return false.
	for (auto iter = begin(); iter != end(); ++iter) {
		if (*iter == item) {
			remove(iter); // Using the iterator version of "remove" to save coding time
			return true;
		}
	}
	return false;
}

// Removes item pointed to by iterator from ordered list
template <class Item, class Order>
Item DLinkedOrderedList<Item, Order>::remove(Iterator& itr) {
	// Procedure: After confirming that the iterator is valid, store the Item it points to, create a new Iterator to point to the node to be deleted (so that the iterator passed in by reference can be moved forward in order to stay valid), then relink the nodes adjacent to the soon-to-be-deleted node, and then delete the node and decrease the size, returning the value deleted.

	_ASSERT(itr.m_node != NULL); // Screw-up check, only works when you run with debugger
	Item returnNode = *itr; // Store item
	Iterator copy = itr; // Copy iterator to node to be deleted
	++itr; // Move the node (leave it to ++ to figure out direction)


	// Re-link adjacent nodes
	if (copy.m_node->prev != NULL)
		copy.m_node->prev->next = copy.m_node->next;
	else
		m_head = copy.m_node->next; // Move the head forward one if deleting from front of list

	if (copy.m_node->next != NULL)
		copy.m_node->next->prev = copy.m_node->prev;
	else
		m_tail = copy.m_node->prev; // Move the tail back one if deleting from the end of the list


	delete copy.m_node; // delete now-detached node

	m_size--;

	return returnNode; // Return value
}

// Removes all specifed items from ordered list
template <class Item, class Order>
unsigned int DLinkedOrderedList<Item, Order>::removeAll(Item item) {
	// Procedure: iterate through the list, and every time the item to be deleted is found, remove that node and increment the counter that counts how many nodes were deleted. Return deleted node count.
	unsigned int count = 0; // Contains the number of nodes deleted
	for (auto iter = begin(); iter != end(); ++iter) {
		if (*iter == item) {
			remove(iter); // iter.kill() is also valid
			count++;
		}
	}
	return count;
}