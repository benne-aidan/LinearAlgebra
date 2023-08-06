#include "matrix.h"
#ifndef LLIST_H
#define LLIST_H

typedef struct MatNode_struct {
    Matrix* matPtr;
    struct MatNode_struct *next;
} MatNode;

MatNode* MatNode_create(MatNode* newNode, Matrix* mat);                         // Create new node
void MatNode_append(MatNode* head, MatNode* newNode);                           // Add node to end of list (useful if we decide not to sort the list)
void MatNode_insertAfter(MatNode* node, MatNode* newNode);                      // Add node after other node (useful if we decide to sort the list)
void MatNode_insertSorted(MatNode* head, MatNode* newNode);                     // Adds node while maintaining the sort (alphabetially by identifier)
Matrix* MatNode_searchList(MatNode* head, char letter);                         // Search list for a matrix with matching identifier. Returns NULL if not found.
void MatNode_printNode(MatNode* node);                                          // Prints matrix in node
void MatNode_printList(MatNode* head);                                          // Prints identifiers of all matrices in list
char MatNode_getIdentifier(MatNode* node);                                      // Returns identifier of matrix in node
Matrix* MatNode_getMatrix(MatNode* node);                                       // Returns pointer to matrix in node
void MatNode_destroy(MatNode* head, char identifier);                           // Destroys node and frees all related memory
void MatNode_printIdentifiers(MatNode* head);                                   // Prints names of all stored matrices

// Have not been implemented
// None as of yet

/***
 * Possible additions:
 * 
 *  Sort List
 * 
***/


#endif