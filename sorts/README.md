# Flight Data Management System

This Flight Data Management System handles passenger information including flight numbers, passenger names, and dates. The system includes functionalities for data comparison, file operations, and sorting algorithms for managing passenger records.

## Structures

### Flight_Number
- **sym**: 2-letter symbol
- **num**: 4-digit number

### FIO (Full Name)
- **surname**: Last name
- **name**: First name
- **patronymic**: Middle name

### Date
- **number**: Day (2 digits)
- **month**: Month (2 digits)
- **year**: Year (4 digits)

### Passenger
- **flight_number**: Flight number (Flight_Number structure)
- **fio**: Passenger name (FIO structure)
- **date**: Date of travel (Date structure)

## Functions

### Comparison Functions
- `compare_flight_number`: Compares two Flight_Number objects
- `compare_FIO`: Compares two FIO objects
- `compare`: Compares Passenger objects using flight number and name

### Data Parsing Functions
- `parseDate`: Parses date string into Date structure
- `parseNumber`: Parses flight number string into Flight_Number structure

### File Operations
- `readData`: Reads passenger data from a file
- `generateFile`: Generates a file with randomly generated passenger data
- `writeData`: Writes sorted passenger data to a file

### Sorting Algorithms
- `StraightInsert`: Performs straight insertion sorting on passenger data
- `iterativeQuicksort`: Performs iterative quicksort on passenger data

## Usage

- `readData`: Read passenger data from a file
- `generateFile`: Generate a file with randomly generated passenger data
- `StraightInsert` and `iterativeQuicksort`: Sort passenger data using different algorithms
- `writeData`: Write sorted data to an output file

## How to Run

1. Compile and run the main file.
2. Modify the `main` function for specific use cases, such as changing the number of passengers.

## Acknowledgments

This Flight Data Management System is a practice project showcasing data structure handling and sorting algorithms in C++.
