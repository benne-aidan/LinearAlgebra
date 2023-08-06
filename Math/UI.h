#include "linkedList.h"
#include "matrix.h"
#ifndef MENU_H
#define MENU_H

void Menu_main();                                   // Main menu
void Menu_createMatrix(MatNode* listHead);          // Menu for creating new matrices
void Menu_displayMatrix(MatNode* listHead);         // Menu for displaying existing matrices
void Menu_destroyMatrix(MatNode* listHead);         // Menu for deleting matrices
void Menu_operations(MatNode* listHead);            // Menu for performing math operations
void Menu_multiplyMatrices(MatNode* listHead);      // Menu for multiplying matrices
void Menu_determinant(MatNode* listHead);           // Menu for finding determinants

#endif