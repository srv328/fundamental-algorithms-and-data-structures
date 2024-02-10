# Passenger Pattern Matching

This C++ program implements pattern matching algorithms—Aho-Corasick and Boyer-Moore—to find specific strings within a dataset containing passenger information.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [File Structure](#file-structure)
- [How It Works](#how-it-works)

## Introduction

The code contains implementations of the Aho-Corasick and Boyer-Moore algorithms for pattern matching within a passenger dataset. It helps identify occurrences of specific strings, such as names and keywords, within the data.

## Features

- Aho-Corasick algorithm implementation
- Boyer-Moore algorithm implementation
- Reading and processing passenger data
- Random generation of passenger data for testing

## Usage

1. **Compile**: Use a C++ compiler to compile the code.
2. **Run**: Execute the compiled binary.
3. **Input**: The program reads data from the `input.txt` file (or any specified path).
4. **Output**: Results are written to output files (`AHO_CORASIK.txt` and `BOYER_MOORE.txt`).

## File Structure

- `main.cpp`: Contains the main code implementing pattern matching.
- `input.txt`: Input file with passenger data.
- `AHO_CORASIK.txt`: Output file containing results from Aho-Corasick algorithm.
- `BOYER_MOORE.txt`: Output file containing results from Boyer-Moore algorithm.

## How It Works

- `Passenger` structure holds flight information, names, and dates.
- `readData`: Reads passenger data from a file.
- `generateFile`: Generates random passenger data for testing.
- `Aho` function: Implements Aho-Corasick algorithm for pattern matching.
- `BM` function: Implements Boyer-Moore algorithm for pattern matching.
