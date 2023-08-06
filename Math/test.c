// Test environment to test various functions
// Edit as needed
// Kept as history to view previous methods of testing

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix.h"
#include "genOps.h"

int main(void) {
    Matrix* mat1 = NULL;
    Matrix* mat2 = NULL;
    Matrix* mat3 = NULL;   

    mat1 = Matrix_initialize(mat1, 2, 2, 'A');
    mat2 = Matrix_initialize(mat2, 2, 3, 'B');
    mat3 = Matrix_initialize(mat3, 3, 3, 'C');

    // Populate mat1
    int* elements = NULL;
    elements = (int*)malloc(sizeof(int) * 4);

    elements[0] = 1;
    elements[1] = 2;
    elements[2] = 3;
    elements[3] = 4;
    Matrix_populate(mat1, elements, 4);

    // Populate mat2
    elements = (int*)realloc(elements, sizeof(int) * 6);
    
    elements[0] = 0;
    elements[1] = 1;
    elements[2] = 2;
    elements[3] = 3;
    elements[4] = 4;
    elements[5] = 5;
    Matrix_populate(mat2, elements, 6);

    // Populate mat3
    elements = (int*)realloc(elements, sizeof(int) * 9);

    elements[0] = 2;
    elements[1] = 4;
    elements[2] = 6;
    elements[3] = 8;
    elements[4] = 10;
    elements[5] = 12;
    elements[6] = 14;
    elements[7] = 16;
    elements[8] = 18;
    Matrix_populate(mat3, elements, 9);

    // Debug checks
    Matrix_print(mat1);
    Matrix_print(mat2);
    Matrix_print(mat3);

    printf("Determinant of mat1 = %d\n", Matrix_determinant(mat1));

    return 0;
}
