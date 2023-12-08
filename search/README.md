# Flight Passenger Data Management

This C++ program manages flight passenger data, including functionalities to read, search, and sort passenger information.

## Implementation Details

The program consists of various functions and structures:

- `clearFile`: Clears the content of a file.
- `Passenger` struct: Stores details of a passenger including flight number, names, dates, and commander's name.
- `parseDate`: Parses date information from a string.
- `readData`: Reads and extracts passenger data from a file.
- `generateFile`: Generates a file with randomly generated passenger information.
- `writeData`: Writes specific data information into a file.
- `compare`: Compares two `Passenger` objects based on flight number and record number.
- `partition`: Implements the partition function for quicksort.
- `linear_search`: Performs a linear search on the passenger data.
- `iterativeQuicksort`: Implements quicksort iteratively.
- `WriteData`: Writes sorted passenger data into a file.
- `interpolationSearch`: Implements interpolation search on the sorted data.
- `main`: Demonstrates functionality by generating data, reading it, and performing linear and interpolation searches.

## Usage

1. **File Generation**: Modify the `main()` function to adjust the number of passengers to generate (`n`) and the search key (`key`).
2. **Compilation**: Compile the code using a C++ compiler.
3. **Execution**: Run the compiled binary file to observe the passenger data management functionalities.

Feel free to explore and adapt the code to suit your specific requirements or data structures.

## Note

This code is for educational purposes and may require further optimization for production-level use. Consider additional error handling and input validation for real-world applications.

