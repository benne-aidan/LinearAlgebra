#include <stdbool.h>

#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix_struct {
    int numRows;
    int numCols;
    int* elements;
    char identifier;
} Matrix;

int* Matrix_elementAt(Matrix* mat, int row, int col);                            // Takes row and column args and returns pointer to element in that position of matrix.
void Matrix_elementChangeTo(Matrix* mat, int row, int col, int newVal);          // Updates value in (row, col) position of matrix to newVal
Matrix* Matrix_initialize(Matrix* mat, int rows, int cols, char letter);         // Initializes new matrix with specified number of rows and cols. Identifier is letter name for matrix and is used for selecting matrix from user input.
void Matrix_populate(Matrix* mat, int* elements, int listSize);                  // Populates matrix with values in list "elements". ALWAYS USE LISTSIZE VARIABLE EVERYWHERE IT APPEARS.
void Matrix_print(Matrix* mat);                                                  // Prints matrix formatted in square form (or rectangle)
int Matrix_numRows(Matrix* mat);                                                 // Gets number of rows in mat
int Matrix_numCols(Matrix* mat);                                                 // Gets number of cols in mat
char Matrix_getName(Matrix* mat);                                                // Gets name of matrix
void Matrix_checkBounds(Matrix* mat, int row, int col);                          // Checks if passed row and column values are valid. If not, exits. Else, nothing happens
void Matrix_destroy(Matrix* mat);                                                // Destroys matrix and frees all related memory
bool Matrix_isSquare(Matrix* mat);                                               // Returns true if matrix is square, false if not

#endif
