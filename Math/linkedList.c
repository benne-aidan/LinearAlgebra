#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedList.h"
#include "matrix.h"

MatNode* MatNode_create(MatNode* newNode, Matrix* mat) {    
    newNode = (MatNode*)malloc(sizeof(MatNode));
    newNode->matPtr = mat;
    newNode->next = NULL;

    return newNode;
}

void MatNode_insertAfter(MatNode* node, MatNode* newNode) {
    if (node->next != NULL) {
        newNode->next = node->next;
    }
    else {
        newNode->next = NULL;
    }

    node->next = newNode;
}

void MatNode_insertSorted(MatNode* head, MatNode* newNode) {    
    MatNode* currNode = head;

    // Loop to find correct position if not at start
    // Loop condition for if end of list is reached
    while (currNode->next != NULL) {
        // Case: position found
        if (MatNode_getIdentifier(newNode) < MatNode_getIdentifier(currNode->next)) {
            MatNode_insertAfter(currNode, newNode);
            return;
        }
        // Case: duplicate name
        else if (MatNode_getIdentifier(newNode) == MatNode_getIdentifier(currNode->next)) {
            // Check for this case in all use cases. If this case is reached in this function, throw error
            printf("ERROR: matrix %c passed to function already exists\n", MatNode_getIdentifier(newNode));
            exit(1);
        }
        // Case: continue through list
        else {
            currNode = currNode->next;
        }
    }
    // If position not found, append to list
    MatNode_insertAfter(currNode, newNode);
}


void MatNode_append(MatNode* head, MatNode* newNode) {
    MatNode* currNode = head;

    while (currNode->next != NULL) {
        currNode = currNode->next;
    }

    MatNode_insertAfter(currNode, newNode);
}

Matrix* MatNode_searchList(MatNode* head, char letter) {
    MatNode* currNode = head;
    Matrix* retMat;
    retMat = NULL;

    if (head->next == NULL) return NULL;

    while (currNode != NULL) {
        
        if (MatNode_getMatrix(currNode) != NULL && MatNode_getIdentifier(currNode) == letter) {
            retMat = currNode->matPtr;
            break;          // Exit loop once we find the matrix with matching identifier.
        }
        currNode = currNode->next;
    }

    return retMat;
}


void MatNode_printNode(MatNode* node) {
    if (node->matPtr != NULL) {
        printf("Matrix %c:\n", MatNode_getIdentifier(node));
        Matrix_print(node->matPtr);
    }
    else {
        printf("ERROR: Requested printNode is NULL.\nQuitting program.\n");
        exit(1);
    }
}


void MatNode_printList(MatNode* head) {
    MatNode* currNode = head;

    while (currNode->next != NULL) {
        currNode = currNode->next;
        MatNode_printNode(currNode);
    }
}

char MatNode_getIdentifier(MatNode* node) {
    return Matrix_getName(node->matPtr);
}

Matrix* MatNode_getMatrix(MatNode* node) {
    return node->matPtr;
}

void MatNode_destroy(MatNode* head, char identifier) {
    // Iterate through list until next element matches passed argument (by identifier)
    MatNode* currNode = head;

    if (head->next == NULL) {
        printf("ERROR: list empty, node cannot be deleted.\n");
        exit(1);
    }

    // Skip head node
    currNode = currNode->next;
    MatNode* prevNode = head;

    while (MatNode_getIdentifier(currNode) != identifier) {
        if (currNode->next == NULL) {
            printf("Matrix could not be found.\n");
            return;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }

    prevNode->next = currNode->next;
    Matrix_destroy(currNode->matPtr);
    free(currNode);
}

void MatNode_printIdentifiers(MatNode* head) {
    MatNode* currNode = head;
    
    if (currNode->next == NULL) {
        printf("No matrices have been created.\n");
    }
    else {
        printf("Matrices: ");
        while (currNode->next != NULL) {
            currNode = currNode->next;
            printf("%c, ", MatNode_getIdentifier(currNode));
        }
        printf("\b\b \n");  // Remove trailing comma and space from output.
    }
}