//
//  main.c
//  p5
//
//  Created by Saúl on 22/04/14.
//  Copyright (c) 2014 Saúl. All rights reserved.
//

#include <stdio.h>
#include "matrix.h"

int main(int argc, const char * argv[])
{
    Matrix myMatrix;
    createMatrix(&myMatrix, 10);
    fillMatrixWithRandom(&myMatrix);
    
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

