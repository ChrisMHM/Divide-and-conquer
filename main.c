//
//  main.c
//  p5
//
//  Created by Saúl on 22/04/14.
//  Copyright (c) 2014 Saúl. All rights reserved.
//

#include <stdio.h>
#include "matrix.h"

void printSquareMatrix(Matrix _matrix);


Matrix matrix1 = NULL;
Matrix matrix2 = NULL;

void printMenu() {
    printf("\n\nDivide and Conquer\n\n");
    printf("1) Create Matrix\n");
    printf("2) Assign value\n");
    printf("3) Get value\n");
    printf("4) Multiply matrix\n");
    printf("9) Destroy Matrix\n\n");
    printf("0) Exit\n\n");
}


/*
 * This method asks to the user for a size to create two matrix
 * and are filled with random numbers, after that prints both matrix
 * on the console
 */
void startMatrix() {
    int squareMatrixSize = 0;
    int validateFlag = 1;
    
    // Validation metodology, the matrix size must be greater than 1 and the size must be power of 2
    while (validateFlag == 1) {
    // while (((squareMatrixSize & (squareMatrixSize - 1)) == 0) || squareMatrixSize < 2) {
        
        printf("\nEnter the size of your square matrix:\n>");
        scanf("%d", &squareMatrixSize);
    
        if (squareMatrixSize < 2) {
            printf("[ERROR] The matrix smaller size is 2\n");
    
        } else if ((squareMatrixSize & (squareMatrixSize - 1)) != 0) {
            printf("[ERROR] The matrix size must be power of two\n");
        
        } else {
            validateFlag = 0;
        }
    }
    
    
    

    int created1 = createSquareMatrix(&matrix1, squareMatrixSize);
    int created2 = createSquareMatrix(&matrix2, squareMatrixSize);
    
    if (created1 == 1 && created2 == 1) {
        fillSquareMatrixWithRandom(&matrix1);
        fillSquareMatrixWithRandom(&matrix2);

        printf("\n\nMatrix 1: \n\n");
        printSquareMatrix(matrix1);
    
        printf("\n\nMatrix 2: \n\n");
        printSquareMatrix(matrix2);
    
    } else {
        printf("[ERROR] There has been a problem creating the Matrix\n");
    }
}


/*
 * This method destroys both matrix
 */
void stopMatrix() {
    destroyMatrix(&matrix1);
    destroyMatrix(&matrix2);
}

void manageAssignOrGetOption(int mode) {
    
    if(matrix1 != NULL && matrix2 != NULL) {
        MATRIX_ELEMENT_TYPE data;
        Matrix selectedMatrix;
        int row, column;
        int choice = 0;

        if(mode == 1) {
            printf("\nInsert the data to assign:\n>");
            scanf("%d", &data);
        }
        
        while(choice <= 0 || choice >= 3) {
            printf("\n\n1:\n\n");
            printSquareMatrix(matrix1);
            
            printf("\n\n2:\n\n");
            printSquareMatrix(matrix2);

            printf("\n\nSelect the matrix\n>");
            scanf("%d", &choice);
        }
        
        selectedMatrix = (choice == 1) ? matrix1 : matrix2;
        int matrixSize = getSize(selectedMatrix);
        
    validate:
        printf("Insert the row: \n> ");
        scanf("%d", &row);
        
        printf("Insert the column: \n> ");
        scanf("%d", &column);
        

        if(row > matrixSize || column > matrixSize || row < 0 || column <= 0) {
            printf("\nInvalid row or column\n");
            goto validate;
        }
        
        if(mode == 0) {
            MATRIX_ELEMENT_TYPE toGet;
            getValue(matrix1, row, column, &toGet);
            printf("To get... %d\n", toGet);
        }
        
        printf("\nModified matrix:\n");
        printSquareMatrix(selectedMatrix);
    
    } else {
        printf("[ERROR] The matrix cannot be null");
    }
}


void manageMultiplyOption() {
    Matrix resultMatrix = NULL;
    multiplyMatrix(matrix1, matrix2, &resultMatrix);
    printf("\nMultiplied Matrix..\n");
    printSquareMatrix(resultMatrix);
}

/*
 * Function that handles the events that could occur at the menu
 */
void manageMenu() {
    int selectedOption = 1;
    
    while (selectedOption != 0) {
        printMenu();
        printf("\nEnter your option:\n> ");
        scanf("%d", &selectedOption);
        
        switch (selectedOption) {
            case 1:
                startMatrix();
                break;
                
            case 2:
                manageAssignOrGetOption(1);
                break;
                
            case 3:
                manageAssignOrGetOption(0);
                break;
                
            case 4:
                manageMultiplyOption();
                
            default:
                break;
                
            case 9:
                stopMatrix();
                break;
        }
    }
    
    printf("\nBye :D \n");
}


/*
 * Main method, first being called
 */
int main(int argc, const char * argv[]) {
    manageMenu();
    return 0;
}


