# Catalog_Shamir-s-Secret

# Shamir's Secret Sharing Implementation

## Overview
This project implements a simplified version of Shamir's Secret Sharing algorithm, focusing on reading points from a JSON file, converting them from various bases to base 10, and using Lagrange interpolation to determine the constant term of a polynomial. 

## Features
- Read points from a JSON file.
- Convert numerical values from various bases (binary, decimal, etc.) to base 10.
- Use Lagrange interpolation to compute the constant term of a polynomial based on the given points.

### Requirements
- C++ compiler (e.g., g++, MSVC)
- CMake (for building the project)
- NMake (included with Visual Studio installation)

### Approach to Implementing Shamir's Secret Sharing Algorithm
**1. Input Handling**
  - Read a JSON file containing points for polynomial interpolation.
  - Each point specifies a base and a corresponding value.
    
**2. Base Conversion**
  - Convert each numerical value from its specified base to base 10.
  - Utilize a helper function to handle different bases (e.g., binary, decimal).

**3. Lagrange Interpolation**
  - Implement the Lagrange interpolation method to compute the polynomial's constant term (f(0)).
  - Construct Lagrange basis polynomials for each point to determine the overall polynomial value at x = 0.

**4. Output**
  - Print the computed constant term, representing the polynomial's value at x = 0.
