Circular Doubly Linked List Implementation in C++
=================================================

This C++ code implements a circular doubly linked list data structure along with basic operations such as insertion, removal, erasure, and printing of the list.

Code Structure
--------------

*   `list_elem`: Structure representing an element in the circular doubly linked list.
    *   `key`: Integer value stored in each node.
    *   `next`: Pointer to the next node in the list.
    *   `prev`: Pointer to the previous node in the list.

### Functions

*   `list_init()`: Initializes an empty circular doubly linked list.
*   `list_insert(list_elem*& head)`: Inserts a new node at the end of the list.
*   `remove(list_elem*& head)`: Removes the last node from the list.
*   `list_erase(list_elem*& head)`: Removes all nodes from the list.
*   `print_list(list_elem* root)`: Prints the keys of elements in the circular linked list.

Usage
-----

1.  **Initialization**: Use `list_init()` to create an empty circular doubly linked list.
2.  **Insertion**: Add nodes using `list_insert()`.
3.  **Removal**: Remove the last node with `remove()`.
4.  **Erasure**: Clear the entire list using `list_erase()`.
5.  **Printing**: Visualize the content of the list with `print_list()`.

Note
----

*   This implementation serves as a basic example. Adjustments may be necessary for specific use cases.

Feel free to explore the code and adapt it as needed.