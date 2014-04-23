//
//  main.c
//  p5
//
//  Created by Saúl on 22/04/14.
//  Copyright (c) 2014 Saúl. All rights reserved.
//

#include <stdio.h>
#include "matrix.h"

Matrix matrix1 = NULL;
Matrix matrix2 = NULL;

void printMenu() {
    printf("\n\nDivide and Conquer\n\n");
    printf("1) Create Matrix\n");
    printf("2) Assign value\n");
    printf("4) Destroy Matrix\n\n");
    printf("0) Exit\n\n");
}


/*
 * This method asks to the user for a size to create two matrix
 * and are filled with random numbers, after that prints both matrix
 * on the console
 */
void startMatrix() {
    int squareMatrixSize = 0;
    
    printf("\nEnter the size of your square matrix:\n>");
    scanf("%d", &squareMatrixSize);
    
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

void stopMatrix() {
    destroyMatrix(&matrix1);
    destroyMatrix(&matrix2);
}

void manageAssignOption() {
    
    if(matrix1 != NULL && matrix2 != NULL) {
        MATRIX_ELEMENT_TYPE data;
        Matrix selectedMatrix;
        int row, column;
        int choice = 0;

        printf("\nInsert the data to assign:\n>");
        scanf("%d", &data);
        
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
        
        assingValue(&matrix1, row, column, data);
        
        printf("\nModified matrix:\n");
        printSquareMatrix(selectedMatrix);
    
    } else {
        printf("[ERROR] The matrix cannot be null");
    }
}


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
                manageAssignOption();
                break;
                
            default:
                break;
                
            case 4:
                stopMatrix();
                break;
        }
    }
    
    printf("\nBye :D \n");
}


int main(int argc, const char * argv[]) {
    manageMenu();
    return 0;
}


