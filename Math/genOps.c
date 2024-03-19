#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "genOps.h"

Matrix* Matrix_multiply(Matrix* mat1, Matrix* mat2) {
    Matrix* product = NULL;
    int newElement;
    int temp;
    
    if (Matrix_numCols(mat1) == Matrix_numRows(mat2)) {
        product = (Matrix*)malloc(sizeof(Matrix));

        product->numRows = Matrix_numRows(mat1);
        product->numCols = Matrix_numCols(mat2);
        product->elements = (int*)malloc(sizeof(int) * Matrix_numRows(product) * Matrix_numCols(product));
        
        // Compute element for each ith row
        for (int i = 1; i <= Matrix_numRows(product); ++i) {
            // For each jth column
            for (int j = 1; j <= Matrix_numCols(product); ++j) {
                newElement = 0;
                // Compute element for ij position
                for (int k = 1; k <= Matrix_numRows(mat2); ++k) {
                    temp = (*Matrix_elementAt(mat1, i, k)) * (*Matrix_elementAt(mat2, k, j));
                    newElement += temp;
                }
                Matrix_elementChangeTo(product, i, j, newElement);
            }
        }
    }

    return product;
}

int Matrix_determinant(Matrix* mat) {
    int determinant;

    // Base case: 1x1 matrix (determinant is the only element)
    if (Matrix_numRows(mat) == 1) {
        determinant = *(Matrix_elementAt(mat, 1, 1));
    }
    // Base case: 2x2 matrix (formula)
    else if (Matrix_numRows(mat) == 2) {
        int a = *(Matrix_elementAt(mat, 1, 1));
        int b = *(Matrix_elementAt(mat, 1, 2));
        int c = *(Matrix_elementAt(mat, 2, 1));
        int d = *(Matrix_elementAt(mat, 2, 2));

        determinant = (a * d) - (b * c);
    }
    // Recursive step: general formula
    else if (Matrix_numRows(mat) > 2) {
        determinant = 0;

        // Solve cofactor expansion for row 1
        for (int i = 1; i <= Matrix_numRows(mat); ++i) {
            determinant = determinant + (*(Matrix_elementAt(mat, 1, i)) * Matrix_cofactorOf(mat, 1, i));
        }
        
    }

    return determinant;
}


// Helper functions

// Returns cofactor of specified matrix element
int Matrix_cofactorOf(Matrix* mat, int row, int col) {
    // Check if matrix is square
    if (!(Matrix_isSquare(mat))) {
        printf("ERROR: Non square matrix passed to cofactor function\nPrinting matrix:\n");
        Matrix_print(mat);
        exit(1);
    }
    
    // Manual exponentiation rather than using math.h to avoid dealing with potential rounding errors with double to int conversion
    int power = row + col;
    int base = -1;

    for (int i = 1; i < power; ++i) {
        base *= -1;
    }

    return base * Matrix_determinant(Matrix_minor(mat, row, col));
}

// Returns minor of matrix
Matrix* Matrix_minor(Matrix* mat, int row, int col) {
    // Check if matrix is square
    if (!(Matrix_isSquare(mat))) {
        printf("ERROR: Non square matrix passed to minor function\nPrinting matrix:\n");
        Matrix_print(mat);
        exit(1);
    }
    // Check if matrix is too small
    else if (Matrix_numRows(mat) < 2) {
        printf("ERROR: Matrix too small to be passed to minor function\nPrinting matrix:\n");
        Matrix_print(mat);
        exit(1);
    }

    // Create new smaller matrix
    Matrix* minor = NULL;
    minor = Matrix_initialize(minor, Matrix_numRows(mat) - 1, Matrix_numCols(mat) - 1, 't');

    int* elements = NULL;                                                   // List of elements
    int listSize = Matrix_numRows(minor) * Matrix_numCols(minor);     // Size of list
    elements = (int*)malloc(sizeof(int) * listSize);

    // Populate array
    int k = 0;          // Index variable for inserting values into elements list
    for (int i = 1; i <= Matrix_numRows(mat); ++i) {        // For every row
        for (int j = 1; j <= Matrix_numCols(mat); ++j) {    // For every column
            // If element is not "crossed out", add to list. Else, iterate.
            if (i != row && j != col) {
                elements[k] = *(Matrix_elementAt(mat, i, j));
                ++k;
            }
        }
    }

    Matrix_populate(minor, elements, listSize);
    free(elements);

    return minor;
}