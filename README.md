# Matrix Operations System

### Author: Nichita-Adrian Bunu, 323CA Facultatea de Automatica si Calculatoare UNSTPB 
**Contact:** [nichita_adrian.bunu@stud.acs.upb.ro](mailto:nichita_adrian.bunu@stud.acs.upb.ro)

---

## Overview

This project is a C-based system for performing operations on dynamically allocated matrices, supporting commands for loading, modifying, multiplying, sorting, and transposing matrices. The system uses defensive programming practices to ensure robust memory allocation and error handling. 

---

## Features and Functionality

### Commands

1. **Load Matrix (L)**:
   - Allocates a new layer in a 3D matrix and populates it with data provided by the user.
   - Computes and stores the matrix sum for future sorting operations.

2. **Display Matrix Dimensions (D)**:
   - Prints the number of rows and columns of a specified matrix.

3. **Print Matrix (P)**:
   - Prints all elements of a specified matrix.

4. **Resize Matrix (C)**:
   - Changes the dimensions of a specified matrix, preserving data within the new dimensions.

5. **Matrix Multiplication (M)**:
   - Multiplies two compatible matrices and stores the result in a new layer.

6. **Sort Matrices by Sum (O)**:
   - Sorts matrices based on their precomputed sums.

7. **Transpose Matrix (T)**:
   - Transposes the specified matrix in-place.

8. **Matrix Power (R)**:
   - Raises a square matrix to a specified power using a logarithmic approach.

9. **Free Matrix (F)**:
   - Deallocates memory for a specified matrix.

10. **Quit Program (Q)**:
    - Releases all allocated memory and exits the program.

---

## Code Structure

### `my_octave.c`

- **Matrix Allocation and Memory Management**:
  - The `alocare` function dynamically allocates memory for each new matrix layer.
  - The `dealocare` function deallocates all allocated memory for matrix layers, rows, columns, and sum arrays.

- **Matrix Operations**:
  - **`citire`**: Reads a matrix from input and calculates its sum.
  - **`inmultire`**: Multiplies two square matrices.
  - **`suma`**: Calculates the sum of a specified matrix layer.
  - **`comanda_2` to `comanda_9`**: Functions that implement commands like displaying matrix dimensions, printing matrices, resizing, transposing, raising to power, and freeing matrices.
  
### `Makefile`

Automates compilation and cleanup processes:
- **`build`**: Compiles `my_octave.c` into an executable `my_octave`.
- **`pack`**: Packages source files into a zip archive.
- **`clean`**: Deletes compiled executables.

---

## How to Compile and Run

1. **Compile the project**:
   ```bash
   make build
   ```

2. **Run the executable**:
   ```bash
   ./my_octave
   ```

3. **Clean up compiled files**:
   ```bash
   make clean
   ```

---
