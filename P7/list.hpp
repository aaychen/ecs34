#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

/**
 * Represents a node in a linked list.
 *
 * I see no reason why you would need to modify this class,
 * but if you find yourself with a potential reason to modify it,
 * feel free to check with me first; it could be a sign that you're
 * on the wrong track.
 */
template<typename T>
class Node
{
public:
    /**
     * Constructor.
     *
     * Tip: It's possible to pass nullptr as the second argument.
     */
    Node(const T& data, Node* next);

    /**
     * Accessor methods (including const overloads) and mutator methods.
     */
    T& getData() { return data; }
    const T& getData() const { return data; }
    void setData(const T& newData) { data = newData; }
    Node* getNext() { return next; }
    const Node* getNext() const { return next; }
    void setNext(Node* newNext) { next = newNext; }

private:
    T data;
    /**
     * You could put Node<T> instead of Node here (and in the methods'
     * signatures); doesn't make a difference.
     * This can't be a reference since it could be nullptr.
     */
    Node* next;
};

template<typename T>
class List
{
public:
    /**
     * Constructor. Creates an empty list.
     */
    List();

    /**
     * Copy constructor. Creates an independent clone of this list.
     */
    List(const List<T>& other);

    /**
     * Destructor.
     */
    ~List();

    /**
     * Copy assignment operator.
     */
    List<T>& operator=(const List<T>& other);

    /**
     * Returns the number of nodes in the list.
     * 
     * MUST run in constant time.
     */
    unsigned length() const;

    /**
     * Adds a new node with the given data to the front of the list.
     *
     * MUST run in constant time.
     */
    void pushFront(const T& data);

    /**
     * Adds a new node with the given data to the back of the list.
     *
     * MUST run in constant time.
     */
    void pushBack(const T& data);

    /**
     * Adds a new node with the given data to the back of the list.
     *
     * MUST run in constant time.
     */
    void operator+=(const T& data);

    /**
     * Accesses the element that is @index nodes past the first node in
     * the list.
     *
     * Throws std::out_of_range exception (the message doesn't matter) if
     * given an out-of-range index.
     */
    T& operator[](unsigned index);
    const T& operator[](unsigned index) const;

    /**
     * Returns true if a node that contains the given data exists in the list.
     * Returns false otherwise.
     */
    bool contains(const T& data) const;

    /**
     * Removes the FIRST occurrence (starting from the front of the list)
     * of a node that contains the given data.
     * Returns true if a node was removed; returns false otherwise.
     */
    bool remove(const T& data);

    /**
     * Removes the FIRST occurrence (starting from the front of the list)
     * of a node that contains the given data.
     */
    void operator-=(const T& data);
    
    /**
     * Prints the contents of this list.
     */
    friend std::ostream& operator<<(std::ostream& os, const List<T>& list) {
        Node<T>* temp = list.head;
        while (temp != nullptr) {
            os << temp->getData() << " ";
            temp = temp->getNext();
        }
        os << std::endl;
        return os;
    }

private:
    // TODO: Any helper methods that you add should be declared or defined
    // in here.

private:
    // TODO: Insert member variables here.
    Node<T>* head;
    Node<T>* tail;
    unsigned numItems;
};

#include "list.inl"
#endif // LIST_HPP
