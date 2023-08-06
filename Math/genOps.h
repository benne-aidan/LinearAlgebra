#include "matrix.h"
#ifndef GENOPS_H
#define GENOPS_H

// Main functions; Functions that will be listed to the user
Matrix* Matrix_multiply(Matrix* mat1, Matrix* mat2);            // Multiplies mat1 with mat2 (in that order). Returns NULL if they cannot be multiplied
int Matrix_determinant(Matrix* mat);                            // Returns pointer with determinant of matrix. Must account for non square matrices in function call

// Sub functions; Functions that will be used solely for performing other operations
int Matrix_cofactorOf(Matrix* mat, int row, int col);          // Returns cofactor of specified element
Matrix* Matrix_minor(Matrix* mat, int row, int col);           // Returns minor of mat (by crossing out i row and j col)

#endif