# Hash Table Implementation in C++

This C++ program demonstrates a Hash Table implementation for storing and managing passenger data using separate chaining collision resolution.

## Features

- **Add Passenger**: Add a new passenger to the hash table.
- **Remove Passenger**: Remove a passenger from the hash table.
- **Search Passenger**: Search for a passenger in the hash table.
- **Print Hash Table**: Display the content of the hash table.
- **Set K Value**: Set the value of K used for linear probing.
- **Clear Hash Table**: Clear all entries from the hash table.

## Implementation Details

The program utilizes a Hash Table structure with separate chaining for collision resolution. It includes the following components:

- Structs for `FIO`, `Date`, `Flight_Number`, and `Passenger`.
- A `HashTable` class that manages hash table operations.
- Hash functions for key generation and collision resolution.
- Methods for adding, removing, searching, printing, and resizing the hash table.

## Usage

The `main.cpp` file contains a demonstration of how to use the `HashTable` class:

- Initialize the `HashTable` object with an initial size.
- Set the value of K for linear probing using `setKValue()`.
- Perform operations like adding, removing, searching, and printing passengers.
- Test the functionality with various scenarios and edge cases.

## Instructions

1. **Compile**: Compile the `main.cpp` file using a C++ compiler.
2. **Run**: Execute the compiled binary to observe the hash table operations.

Feel free to modify the code and adapt it to your requirements.

## Note

This implementation is for educational purposes and may not be optimized for production use.
