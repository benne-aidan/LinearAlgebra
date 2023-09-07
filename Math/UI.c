#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <Windows.h>
#include "matrix.h"
#include "UI.h"
#include "linkedList.h"
#include "genOps.h"

void Menu_main() {
    // Linked list to hold matrices
    MatNode* head = NULL;
    head = MatNode_create(head, NULL);

    // Main menu
    bool keepRunning = true;

    while (keepRunning) {
        char* menuSelection;
        menuSelection = (char*)malloc(sizeof(char));

        printf("What would you like to do?\n\n");
        printf("Create new matrix (m)\nShow matrix (s)\nDelete matrix (d)\nPerform operations (o)\nQuit Program (q)\n\n");
    
        scanf("%c", menuSelection);
        fflush(stdin);

        switch (*menuSelection) {
            case 'm':
                free(menuSelection);
                Menu_createMatrix(head);
                break;
            case 's':
                free(menuSelection);
                Menu_displayMatrix(head);
                break;
            case 'q':
                free(menuSelection);
                printf("Goodbye!\n");
                Sleep(1000);
                keepRunning = false;
                break;
            case 'd':
                free(menuSelection);
                Menu_destroyMatrix(head);
                break;
            case 'o':
                free(menuSelection);
                Menu_operations(head);
                break;
            default:
                free(menuSelection);
                printf("Invalid input. Please select one of the options.\n\n");
                break;
        }
    }
}

void Menu_createMatrix(MatNode* listHead) {
    fflush(stdin);
    int numRows;
    int numCols;
    char letter;
    bool doNotAdvance = true;
    
    while (doNotAdvance) {
        printf("Enter number of rows: ");

        // Condition met if valid input is entered
        if ((scanf("%d", &numRows) == 1) && numRows < 51 && numRows > 0) {      // TODO: this exact condition is repeated several times in this file, could be abstracted to a function isValidInput
            doNotAdvance = false;
        }
        else {
            printf("Input must be integer between 1-50 (inclusive)\n");
        }
        fflush(stdin);
    }

    doNotAdvance = true;
    while (doNotAdvance) {
        printf("Enter number of columns: ");

        // Condition met if valid input is entered
        if ((scanf("%d", &numCols) == 1) && numCols < 51 && numCols > 0) {
            doNotAdvance = false;
        }
        else {
            printf("Input must be integer between 1-50 (inclusive)\n");
        }
        fflush(stdin);
    }

    // Variables for array to be passed into matrix
    int listSize = numRows * numCols;
    int* matrixElements;
    matrixElements = (int*)malloc(sizeof(int) * listSize);
    
    printf("Enter values for your matrix from left to right, then top to bottom, separated by spaces.\nEX: 3 1 6 8 for a 2x2 matrix\n\n");

    for (int i = 0; i < listSize; ++i) {
        while (scanf("%d", &(matrixElements[i])) != 1) {
            // Loop is only entered if incorrect input is given
            printf("Input must be an integer.\n");
            fflush(stdin);
        }
    }
    fflush(stdin);
    
    doNotAdvance = true;
    while (doNotAdvance) {
        printf("Enter capital letter to name matrix: ");

        // Condition met if valid input is entered
        if ((scanf("%c", &letter) == 1) && letter >= 65 && letter <= 90) {   // Use ascii codes here to ensure it's a capital letter
            
            // Check if letter has already been used
            if (MatNode_searchList(listHead, letter) != NULL) {
                printf("Matrix %c already exists.\n", letter);
            }
            else {
                // If letter hasn't been used, end loop
                doNotAdvance = false;
            }

        }
        else {
            printf("Name must be a capital letter.\n");
        }
        fflush(stdin);
    }

    // Create and initialize matrix
    Matrix* newMat = NULL;

    newMat = Matrix_initialize(newMat, numRows, numCols, letter);

    Matrix_populate(newMat, matrixElements, listSize);
    
    printf("Matrix %c:\n", Matrix_getName(newMat));
    Matrix_print(newMat);

    // Add matrix to linked list
    MatNode* newNode = NULL;
    newNode = MatNode_create(newNode, newMat);

    MatNode_insertSorted(listHead, newNode);
}

void Menu_displayMatrix(MatNode* listHead) {
    fflush(stdin);
    char userChoice;
    bool doNotAdvance = true;
    Matrix* displayMat = NULL;

    while (doNotAdvance) {
        printf("Enter matrix you would like to display (or \'e\' to exit, or \'l\' to list options): ");
        if (scanf("%c", &userChoice) == 1 && userChoice >= 65 && userChoice <= 90) {
            // Search list for chosen matrix
            displayMat = MatNode_searchList(listHead, userChoice);

            // If found, then print
            if (displayMat != NULL) {
                printf("\nMatrix %c:\n\n", userChoice);
                Matrix_print(displayMat);
                printf("\n");
                doNotAdvance = false;
            }
            else {
                printf("Matrix %c does not exist.\n", userChoice);
            }
        }
        else if (userChoice == 'e') {
            doNotAdvance = false;
        }
        else if (userChoice == 'l') {
            MatNode_printIdentifiers(listHead);
        }
        else {
            printf("Invalid input. Matrices are named with single capital letters.\n");
        }
        fflush(stdin);
    }    
}

void Menu_destroyMatrix(MatNode* listHead) {
    fflush(stdin);
    char userChoice;
    Matrix* destMat = NULL;
    bool doNotAdvance = true;

    while (doNotAdvance) {
        printf("Enter matrix to be deleted (or \'e\' to exit, or \'l\' to list options): ");
        // Check for valid input
        if (scanf("%c", &userChoice) == 1 && userChoice >= 65 && userChoice <= 90) {
            destMat = MatNode_searchList(listHead, userChoice);

            if (destMat != NULL) {
                MatNode_destroy(listHead, userChoice);
                printf("Matrix %c successfully deleted.\n", userChoice);
                doNotAdvance = false;
            }
            else {
                printf("Matrix %c does not exist or has already been deleted.\n", userChoice);
            }
        }
        else if (userChoice == 'e') {
            doNotAdvance = false;
        }
        else if (userChoice == 'l') {
            MatNode_printIdentifiers(listHead);
        }
        else {
            printf("Invalid input. Matrices are named with single capital letters.\n");
        }
        fflush(stdin);
    }
}

void Menu_operations(MatNode* listHead) {
    char userChoice;
    bool doNotAdvance = true;

    while (doNotAdvance) {
        printf("What operation would you like to perform?\nMatrix multiplication (m)\nDeterminant (d)\nQuit to main menu (q)\n\n");

        scanf("%c", &userChoice);
        fflush(stdin);
        switch (userChoice) {
            case 'd':
                Menu_determinant(listHead);
                doNotAdvance = false;
                break;
            case 'm':
                Menu_multiplyMatrices(listHead);
                doNotAdvance = false;
                break;
            case 'q':
                doNotAdvance = false;
                break;
            default:
                printf("Invalid input. Please select one of the options.\n");
                break;
        }
    }
}

void Menu_multiplyMatrices(MatNode* listHead) {
    char matName1, matName2;
    Matrix* mat1 = NULL;
    Matrix* mat2 = NULL;
    Matrix* product = NULL;
    bool doNotAdvance = true;

    // TODO: Entering first matrix and entering second matrix use nearly identical code, could be abstracted to function to improve readability

    // Enter first matrix
    fflush(stdin);
    while (doNotAdvance) {
        printf("Enter the name of the first matrix you would like to multiply (or \'e\' to exit, or \'l\' to list options): ");

        // Check for valid input
        if ((scanf("%c", &matName1) == 1) && matName1 >= 65 && matName1 <= 90) {
            fflush(stdin);
            // Check to see if matrix exists
            mat1 = MatNode_searchList(listHead, matName1);
            if (mat1 != NULL) {
                doNotAdvance = false;
            }
            else {
                printf("Matrix %c does not exist.\n", matName1);
            }
        }
        else if (matName1 == 'e') {
            fflush(stdin);
            return;
        }
        else if (matName1 == 'l') {
            MatNode_printIdentifiers(listHead);
            fflush(stdin);
        }
        else {
            printf("Invalid input. Matrices are named with single capital letters.\n");
            fflush(stdin);
        }
    }

    // Enter second matrix
    doNotAdvance = true;
    fflush(stdin);
    while (doNotAdvance) {
        printf("Enter the second matrix you would like to multiply (or \'e\' to exit, or \'l\' to list options): ");

        // Check for valid input
        if ((scanf("%c", &matName2) == 1) && matName2 >= 65 && matName2 <= 90) {
            fflush(stdin);
            // Check to see if matrix exists
            mat2 = MatNode_searchList(listHead, matName2);
            if (mat2 != NULL) {
                doNotAdvance = false;
            }
            else {
                printf("Matrix %c does not exist.\n", matName2);
            }
        }
        else if (matName2 == 'e') {
            fflush(stdin);
            return;
        }
        else if (matName1 == 'l') {
            fflush(stdin);
            MatNode_printIdentifiers(listHead);
        }
        else {
            printf("Invalid input. Matrices are named with single capital letters.\n");
            fflush(stdin);
        }
    }

    // Initialize product matrix
    product = (Matrix*)malloc(sizeof(Matrix));
    product = Matrix_multiply(mat1, mat2);
    
    // If matrices could not be multiplied, end function
    if (product == NULL) {
        printf("Matrices %c and %c are of incompatible dimensions to be multiplied.\n", matName1, matName2);
        return;
    }
    // If matrices were multiplied successfully, output result
    else {
        printf("%c x %c =\n", matName1, matName2);
        Matrix_print(product);
    }

    char userChoice;
    char productName;
    doNotAdvance = true;
    // Save Matrix
    while (doNotAdvance) {
        printf("Would you like to save this matrix (y/n)?\n");

        // Check if valid input is passed
        if (scanf("%c", &userChoice) == 1) {
            fflush(stdin);
            switch (tolower(userChoice)) {
                case 'y':
                    // Prompt for name of new matrix
                    while (doNotAdvance) {
                        printf("Enter a name for the new matrix: ");
                        // Check if valid input is passed
                        if (scanf("%c", &productName) == 1 && productName >= 65 && productName <= 90) {
                            // Check for duplicate name
                            Matrix* temp = MatNode_searchList(listHead, productName);
                            if (temp != NULL) {
                                printf("Matrix %c already exists. Please choose another letter.\n", productName);
                                Matrix_destroy(temp);
                                fflush(stdin);
                            }
                            else {
                                product->identifier = productName;
                                MatNode* newNode = NULL;
                                newNode = MatNode_create(newNode, product);
                                MatNode_insertSorted(listHead, newNode);
                                printf("Matrix %c saved successfully.\n", productName);
                                doNotAdvance = false;
                                fflush(stdin);
                            }
                            
                        }
                        else {
                            printf("Invalid input. Matrices are named with single capital letters.\n");
                            fflush(stdin);
                        }
                    }
                    break;
                case 'n':
                    Matrix_destroy(product);
                    doNotAdvance = false;
                    fflush(stdin);
                    break;
                default:
                    printf("Invalid input. Please chose \'y\' or \'n\'\n");
                    fflush(stdin);
                    break;
            }
        }
    }
}

void Menu_determinant(MatNode* listHead) {
    char userChoice;
    bool doNotAdvance = true;
    Matrix* detMat = NULL;

    while (doNotAdvance) {
        printf("Enter the name of the matrix you would like the determinant of (or \'e\' to exit, or \'l\' to list options): ");
        
        fflush(stdin);
        // Check for valid input
        if (scanf("%c", &userChoice) == 1 && userChoice >= 65 && userChoice <= 90) {
            detMat = MatNode_searchList(listHead, userChoice);

            // Check if matrix exists
            if (detMat == NULL) {
                printf("Matrix %c does not exist.\n", userChoice);
                fflush(stdin);
            }
            // If matrix does exist:
            else {
                // Check if matrix has computable determinant (is square)
                if (Matrix_isSquare(detMat)) {
                    printf("det(%c) = %d\n", userChoice, Matrix_determinant(detMat));
                    doNotAdvance = false;
                }
                else {
                    printf("Non-square matrices do not have determinants.\n");
                }
            }
        }
        else if (userChoice == 'e') {
            fflush(stdin);
            return;
        }
        else if (userChoice == 'l') {
            MatNode_printIdentifiers(listHead);
        }
        else {
            printf("Invalid input. Matrices are named with single capital letters.\n");
        }
        fflush(stdin);
    }
}