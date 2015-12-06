#pragma once

/**
 * YOU SHOULD NOT MODIFY ANY CODE IN THIS FILE.
 *
 * Comments in this file provide details on how to implement your assignment.
 */

/**
 * StandardFunctors.h provides IsLess, the default Order for a
 * DLinkedOrderedList.
 */
#include "StandardFunctors.h"

/**
 * Direction of traversal for iterators.
 */
enum Direction {FORWARD=1, BACKWARD=2};

/**
 * Class for self-ordering doubley linked list. YOU SHOULD NOT MODIFY ANYTHING
 * "INSIDE" THIS CLASS! Instead, add your own implementations of the class
 * interface to the three files that you will create -- the ones that are
 * included below: DLinkedOrderedList.template.h, Node.template.h, and
 * Iterator.template.h.
 */
template <class Item, class Order=IsLess>
class DLinkedOrderedList {
private:
    /**
     * Private class for list nodes. Node objects are dynamically allocated
     * and freed in the appropriate constructors/operators/methods of the
     * DLinkedOrderedList class.
     */
    class Node {
    public:
        /**
         * Construct a node containing val, with next = _next and prev = _prev.
         */
        Node(Item val = Item(), Node* _next = NULL, Node* _prev = NULL);

        /**
         * Public members giving DLinkedOrderedList and Iterator (see class
         * below) direct access to nodes' data.
         */
        Item  value;
        Node* next;
        Node* prev;

     };

public:
    /**
     * Public iterator class wraps node pointers and supports minimum set.
     * of operators for iterating forward and backward. Iterators store whether
     * or not they are "forward iterators" or "backward iterators".
     * Backward iterators have inverted "operator++" and "operator--" behaviour;
     * i.e., the go to the previous node in the list using "++" and go the next
     * node in the list with "--".
     */
    class Iterator {
    private:
        /**
         * A pointer to the node that this iterator refers to.
         */
        Node* m_node;

        /**
         * A reference to the list that this iterator is "iterating over".
         */
        DLinkedOrderedList<Item, Order>& m_list;

        /**
         * Defines "forward" or "backward" traversal iterator (see defnition of
         * type Direction at the top of this file).
         */
        Direction m_direction;

        /**
         * INVARIANT: m_node is EITHER an element of lst OR NULL.
         */

    public:
        /**
         * Construct an Iterator from a pointer to a Node, a reference to the
         * list, and a direction. Default to a forward iterator.
         *
         * PRECONDTION: ptr is EITHER an element of list OR NULL.
         */
        Iterator(
            Node* const node,
            DLinkedOrderedList<Item, Order>& list,
            Direction direction = FORWARD);

        /**
         * Increment an iterator; i.e., go to the "next node" according to
         * the value of m_direction. I.e.,  "++" operator on forward
         * iterators follows the NEXT pointer of the node; "++" operator on
         * backward iterators follows the PREVIOUS pointer of the node.
         *
         * PRECONDTION: m_node is non-NULL.
         */
        Iterator& operator++();


        /**
         * Decrement an iterator; i.e., go to the "previous node" according to
         * the value of m_direction. I.e.,  "--" operator on forward
         * iterators follows the PREVIOUS pointer of the node; "--" operator on
         * backward iterators follows the NEXT pointer of the node.
         *
         * PRECONDTION: m_node is non-NULL.
         */
        Iterator& operator--();

        /**
         * Answer the question: Does "this" NOT point to the same node as "b"?
         */
        bool operator!=(Iterator const& b) const;

        /**
         * Overridden dereference operator* below allows to access item value
         * contained in this iterator's node.
         *
         * HINT: "const'ness" of this function indicates that none of "this"'s
         * members are changed while the function is running. It does not mean
         * that the returned Item's reference is "const", which WOULD be a
         * problem if we want to change item's value as in expression like:
         *
         *     (*myItr) = 3; // Assuming MyItr is an iterator object.
         *
         * We DON'T have this problem because the returned Item& is NOT const.
         * Expressions such as this are a valid, useful way of changing list
         * item values.
         *
         * PRECONDTION: m_node is non-NULL.
         */
        Item& operator*() const;

        /**
         * Delete/remove an item from the position correpsonding to the
         * iterator) inside the list and returns the item value; the iterator
         * should point to the "++ position" in the list according to the
         * value of m_direction. I.e., forward iterators should
         * point to the NEXT node after the deleted node; backward iterators
         * should point to the PREVIOUS node prior to the deleted node. Note
         * that the node in the "++ position" may be NULL.
         *
         * HINT 1: You can implement this really easily by exploiting one of
         * DLinkedOrderedList's removal methods...
         *
         * HINT 2: When following HINT 1, let DLinkedOrderedList's removal method
         * do the "++"-ing; make sure you don't increment twice by mistake!
         */
        Item kill();

        /**
         * Make DLinkedOrderedList a friend. This gives it access protected and
         * private members.
         *
         * HINT 3: Access to m_node greatly simplifies the implementation of
         * DLinkedOrderedList's "Item remove(Iterator& itr)" (see below).
         */
        friend class DLinkedOrderedList;
    };

    /**
     * Construct an empty list.
     */
    DLinkedOrderedList();

    /**
     * Make a copy of a list.
     */
    DLinkedOrderedList(DLinkedOrderedList<Item, Order> const& copy);

    /**
     * Destruct a list. Delete all dynamically allocated nodes.
     */
    ~DLinkedOrderedList();

    /**
     * Return the current list size. O(1).
     */
    unsigned int size() const;

    /**
     * Answer: Is the list empty? O(1).
     */
    bool isEmpty() const;

    /**
     * Get an iterator to the "beginning" or "off the ending" of this list.
     * Default to a forward iterator. Note that the "beginning" of the list for
     * a backward iterator is the tail of the list. Both are O(1).
     */
    Iterator begin(Direction direction = FORWARD);
    Iterator end(Direction direction = FORWARD);

    /**
     * Insert an item into the correct location in the list according to the
     * ordering defined by our templated Order class. If Order::compare(a, b) is
     * true, then a must come before b in an ordered list. Return a forward
     * iterator pointing to the inserted value. Ordering of duplicate items
     * values does not matter, but each duplicate value should be included
     * exactly in the list. E.g.,
     *
     *     Inserting 2 into list: 1 <--> 2 <--> 3
     *     results in: 1 <--> 2 <--> 2 <--> 3
     *     It doesn't matter which "2 node" is the inserted node.
     *
     * This method should be O(n).
     */
    Iterator insert(Item item);

    /**
     * Remove a single "item"-valued item from the list and return true.
     * If no such item is found, return false. O(n).
     */
    bool remove(Item item);

    /**
     * Remove the specific node that "itr" refers to, and return the node's
     * value. "itr" should be adjusted to refer to the item in the "++ position"
     * with respect to the removed node (see comment under Iterator's "kill"
     * method for a detailed description). Note that this may be NULL! O(1).
     *
     * PRECONDITION: Iterator should be pointing at a valid position in the
     * list.
     */
    Item remove(Iterator& itr);

    /**
     * Remove all "item"-valued items from the list and return a count of the
     * number of such items found and removed. O(n).
     */
    unsigned int removeAll(Item item);

private:
    /**
     * Standard list data structure members: head of the list, tail of the list,
     * size of the list.
     */
    Node* m_head;
    Node* m_tail;
    unsigned int m_size;
};


/**
 * CREATE THE THREE FILES #include'd BELOW AND INSERT YOUR CODE THERE!
 * To make debugging easier, include these files in your Visual Studio project.
 */
#include "DLinkedOrderedList.template.h"
#include "Node.template.h"
#include "Iterator.template.h"
