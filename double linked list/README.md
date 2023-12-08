# Doubly Linked List Operations in Pascal

This Pascal code demonstrates operations on a doubly linked list.

## Overview

The provided code showcases the following functionalities:

- **Creation and Management of Doubly Linked List**
  - Definition of a `List_Elem` structure that includes fields for previous and next elements, integer data, and a count.
  - Three head pointers `head1`, `head2`, and `head3` for different lists.
  
- **List Manipulation Procedures**
  - `PrintList`: Displays the elements of a given linked list.
  - `Free`: Deallocates memory for the entire linked list.
  - `Delete_Element`: Removes an element from the list based on the provided data.
  - `Union`: Merges two lists, storing the union in a new list (`head3`).
  - `Add`: Inserts an element into the list in sorted order.
  - `Find_Element`: Searches for an element in the list based on the provided data.

## Usage

The code demonstrates the usage of the mentioned procedures through a series of operations:
- Adding elements to `head1` and `head2` lists.
- Checking the presence of specific elements using `Find_Element`.
- Printing the content of `head1` and `head2`.
- Performing a union operation on `head1` and `head2` and displaying the resulting `head3` list.

This code serves as an illustrative example of basic doubly linked list operations in Pascal.
