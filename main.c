//
//  main.c
//  p5
//
//  Created by Saúl on 22/04/14.
//  Copyright (c) 2014 Saúl. All rights reserved.
//

#include <stdio.h>
#include "matrix.h"

Matrix matrix1;
Matrix matrix2;

void printMenu() {
    printf("\n1) Create Matrix\n\n0) Exit\n");
}


/*
 * This method asks to the user for a size to create two matrix
 * and are filled with random numbers, after that prints both matrix
 * on the console
 */
void startMatrix() {
    int squareMatrixSize = 0;
    
    printf("Enter the size of your square matrix:\n\n>");
    scanf("%d", &squareMatrixSize);
    
    int created1 = createSquareMatrix(&matrix1, squareMatrixSize);
    int created2 = createSquareMatrix(&matrix2, squareMatrixSize);
    
    if (created1 == 1 && created2 == 1) {
        fillSquareMatrixWithRandom(&matrix1);
        fillSquareMatrixWithRandom(&matrix2);

        printf("\nMatrix 1: \n\n");
        printSquareMatrix(matrix1);
        
        printf("\n Matrix 2: \n");
        printSquareMatrix(matrix2);
    
    } else {
        printf("[ERROR] There has been a problem creating the Matrix\n");
    }
}


void manageMenu() {
    int selectedOption = 1;
    
    while (selectedOption != 0) {
        printMenu();
        printf("\nEnter your option: \n\n> ");
        scanf("%d", &selectedOption);
        
        switch (selectedOption) {
            case 1:
                startMatrix();
                break;
                
            default:
                break;
        }
    }
    
    printf("\nBye :D \n");
}


int main(int argc, const char * argv[]) {
    manageMenu();
    return 0;
}


