#pragma once

// Iterator constructor
template <class Item, class Order>
DLinkedOrderedList<Item, Order>::Iterator::Iterator(Node* const node, DLinkedOrderedList<Item, Order>& list, Direction direction) : m_node(node), m_list(list), m_direction(direction) {
}

// Increment operator
template <class Item, class Order>
typename DLinkedOrderedList<Item, Order>::Iterator& DLinkedOrderedList<Item, Order>::Iterator::operator++() {
	// Procedure: Check that the iterator is valid, then set the m_node pointer to the next node in the chain (direction-dependent). Return this (now incremented) iterator back.
	_ASSERT(m_node != NULL); // Only works when running with debugger
	m_node = (m_direction == FORWARD) ? m_node->next : m_node->prev;
	return *this;
}

// Decrement operator
template <class Item, class Order>
typename DLinkedOrderedList<Item, Order>::Iterator& DLinkedOrderedList<Item, Order>::Iterator::operator--() {
	// Procedure: Check that the iterator is valid, then set the m_node pointer to the next node in the chain (direction-dependent). Return this (now decremented) iterator back.
	_ASSERT(m_node != NULL); // Screw-up check; only works when running with debugger
	m_node = (m_direction == FORWARD) ? m_node->prev : m_node->next;
	return *this;
}

// Not-equals operator
template <class Item, class Order>
bool DLinkedOrderedList<Item, Order>::Iterator::operator!=(Iterator const& b) const {
	return (m_node != b.m_node);
}

// Dereference operator
template <class Item, class Order>
Item& DLinkedOrderedList<Item, Order>::Iterator::operator*() const {
	_ASSERT(m_node != NULL); // Screw-up check; only works when running with debugger
	return m_node->value;
}

// Kill method
template <class Item, class Order>
Item DLinkedOrderedList<Item, Order>::Iterator::kill() {
	// Procedure: Check that iterator is valid, then call the containing list's remove function on this pointer, and return the deleted node's value. This iterator will be automatically incremented by "remove".
	_ASSERT(m_node != NULL); // Screw up check; only works when running with debugger
	return m_list.remove(*this); // Destroy original, return copy
}