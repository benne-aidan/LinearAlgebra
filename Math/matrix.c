#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix.h"

int Matrix_numRows(Matrix* mat) {
    return mat->numRows;
}

int Matrix_numCols(Matrix* mat) {
    return mat->numCols;
}

char Matrix_getName(Matrix* mat) {
    return mat->identifier;
}

void Matrix_checkBounds(Matrix* mat, int row, int col) {
    if (row > Matrix_numRows(mat) || col > Matrix_numCols(mat) || row < 1 || col < 1) {
        printf("ERROR: requested row or column not valid.\n");
        exit(1);
    }
}

int* Matrix_elementAt(Matrix* mat, int row, int col) {
    Matrix_checkBounds(mat, row, col);                      // Check if requested element is valid
    
    int *element;
    element = &(mat->elements[(Matrix_numCols(mat) * (row - 1)) + col - 1]);         // Formula should determine desired matrix element

    return element;    
}

void Matrix_elementChangeTo(Matrix* mat, int row, int col, int newVal) {
    Matrix_checkBounds(mat, row, col);                     // Check if requested element is valid

    *(Matrix_elementAt(mat, row, col)) = newVal;           // Assign new value
}

void Matrix_populate(Matrix* mat, int* elementList, int listSize) {
    // Check to see if list sizes match
    if (listSize != Matrix_numCols(mat) * Matrix_numRows(mat)) {
        printf("ERROR: listSize does not match matrix size.\n");
        fflush(stdout);
        exit(1);
    }

    mat->elements = (int*)malloc(sizeof(int) * listSize);


    // Populate array with all values from list
    for (int i = 0; i < listSize; ++i) {
        mat->elements[i] = elementList[i];
    }

}

void Matrix_print(Matrix* mat) {
    printf("\n");
    for (int i = 0; i < Matrix_numRows(mat); ++i) {
        printf("|        ");
        for (int j = 0; j < Matrix_numCols(mat); ++j) {
            printf("%-10d", *(Matrix_elementAt(mat, i + 1, j + 1)));
        }
        printf(" |\n");
    }
}

Matrix* Matrix_initialize(Matrix* mat, int rows, int cols, char letter) {
    mat = (Matrix*)malloc(sizeof(Matrix));
    
    mat->numRows = rows;
    mat->numCols = cols;
    mat->identifier = letter;

    return mat;
}

void Matrix_destroy(Matrix* mat) {
    if (mat == NULL) {
        printf("ERROR: Matrix already NULL.\n");
        return;
    }
    
    free(mat->elements);   // Free memory allocated by populate function
    free(mat);             // Free memory allocated by initialize function
}

bool Matrix_isSquare(Matrix* mat) {
    if (Matrix_numRows(mat) == Matrix_numCols(mat)) {
        return true;
    }
    else {
        return false;
    }
}