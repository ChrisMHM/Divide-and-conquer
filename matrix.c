
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef int MATRIX_ELEMENT_TYPE;

typedef struct {
    MATRIX_ELEMENT_TYPE *data;
    int size;
    
} _MATRIX;


typedef _MATRIX * Matrix;

// Matrix multiplication Divide & conquer order
int operations[16] = {1, 1, 2, 3, 1, 2, 2, 4, 3, 1, 4, 3, 3, 2, 4 ,4};

/**
 * Creates a square Matrix
 */
int createSquareMatrix(Matrix *matrix, int rowSize) {
    unsigned long i = 0;
    int matrixSize = rowSize * rowSize;
    
    if(*matrix == NULL) {
        *matrix = (Matrix) malloc (sizeof(Matrix));
        
        (*matrix) -> data = (MATRIX_ELEMENT_TYPE*) malloc(matrixSize * sizeof(MATRIX_ELEMENT_TYPE));
        (*matrix) -> size = rowSize;
        
        for (i = 0; i < matrixSize; ++i) {
            *((*matrix) -> data + i) = 0;
        }
        
        return 1;
        
    } else {
        return 0;
    }
}



/*
 * Add an element into the matrix at the giving position
 */
void add(Matrix *_matrix, int position, MATRIX_ELEMENT_TYPE _data) {

    if (*_matrix != NULL) {
        *((*_matrix) -> data + position) = _data;
        
    } else {
        printf("[ERROR] The matrix has not been initalized.\n");
    }
}


/*
* Fills a square matrix with random numbers
*/
void fillSquareMatrixWithRandom(Matrix *_matrix) {
    int vectorSize = getSize(*_matrix);
    vectorSize *= vectorSize;
//    srand(time(NULL));
    
    for (int i = 0; i < vectorSize; i++) {
        MATRIX_ELEMENT_TYPE randomNumber = rand() % 9;
        add(_matrix, i, randomNumber);
    }
}

/*
* Returns the rowSize of a square matrix
*/
int getSize (Matrix _matrix) {
    int _size = -1;
    
    if(_matrix != NULL)
        _size = (_matrix) -> size;
    
    return _size;
}


/*
* Destroys the given matrix
*/
void destroyMatrix(Matrix *matrix) {
    if (*matrix != NULL) {
        free((*matrix) -> data);
        free(*matrix);
        
        *matrix = NULL;
        
    } else
        printf("[ERROR] The matrix has not been initialized.");
}


/*
 * Prints a square matrix on console
 */
void printSquareMatrix(Matrix _matrix) {
    int rowSize = getSize(_matrix);
    int matrixSize = rowSize * rowSize;
    
    if (_matrix != NULL) {
        for (int i = 0; i < (matrixSize); i++) {
            
            if(i != 0 && i % rowSize == 0)
                printf("\n");
            
            
            printf("%d\t", get(_matrix, i));
        }
        
    } else {
        printf("[ERROR] The matrix has not been initialized.\n");
    }
}



/*
 * Returns the element of the matrix at the position given at parameter
 */
MATRIX_ELEMENT_TYPE get(Matrix _matrix, int index) {
    int output = -1;
    int matrixSize = getSize(_matrix) * getSize(_matrix);
    
    if (_matrix != NULL) {
        if(index < matrixSize) {
            output = *((_matrix) -> data + index);
            
        } else {
            printf("[ERROR] There is not data at the position: %d.\n", index);
        }
        
    } else {
        printf("[ERROR] The matrix has not been initalized.\n");
    }
    
    return output;
}


/*
 * Assing the given value in the given matrix at the given row and column
 */
void assingValue(Matrix *matrix, int row, int column, MATRIX_ELEMENT_TYPE data) {
    int index = getSize(*matrix) * row + column;
    add(matrix, index, data);
}


/*
 * Get the given value in the given matrix at the given row and column
 */
void getValue(Matrix matrix, int row, int column, MATRIX_ELEMENT_TYPE *data) {
    int index = getSize(matrix) * (row) + column;
    *data = get(matrix, (index));
}


void sumMatrix(Matrix matrix1, Matrix matrix2, Matrix *resultMatrix){
    int matrixSize= getSize(matrix1);
    int container;
    int m1Value, m2Value;
    
    for(int row=0; row < matrixSize; row++){

        for(int column = 0; column < matrixSize; column++) {
            getValue(matrix1, row, column, &m1Value);
            getValue(matrix2, row, column, &m2Value);
            container = m1Value + m2Value;
            
            assingValue(resultMatrix, row, column, container);
        }
    }
}


void copyQuadrant(Matrix bigMatrix, Matrix * subMatrix, int quadrant) {
    int subMatrixSize = getSize(*subMatrix);
    int matrixValue;
    
    for (int  row= 0; row < subMatrixSize; row++) {
        for (int column = 0; column < subMatrixSize; column++) {
            int isDiagonalSubMatrix = quadrant % 2;
            int isBottomSubMatrix = quadrant > 1;
            
            int rowPos = row + (subMatrixSize * isBottomSubMatrix);
            int columnPos = column + (subMatrixSize * isDiagonalSubMatrix);
            
            getValue(bigMatrix, rowPos, columnPos, &matrixValue);
            assingValue(subMatrix, row, column, matrixValue);
        }
    }
}


void assignCuadrant(Matrix subMatrix, Matrix * bigMatrix, int quadrant) {
    int subMatrixSize = getSize(subMatrix);
    int matrixValue;
    
    for (int  row= 0; row < subMatrixSize; row++) {
        for (int column = 0; column < subMatrixSize; column++) {
            int isDiagonalSubMatrix = quadrant % 2;
            int isBottomSubMatrix = quadrant > 1;
            
            int rowPos = row + (subMatrixSize * isBottomSubMatrix);
            int columnPos = column + (subMatrixSize * isDiagonalSubMatrix);
            
            getValue(subMatrix, row, column, &matrixValue);
            assingValue(bigMatrix, rowPos, columnPos, matrixValue);
        }
    }
}


/**
 * Multiply two matrix and store the result into the result matrix given by parameter
 */
void multiplyCoolMatrix(Matrix matrixA, Matrix matrixB, Matrix* matrixResult) {

    int matrixSize = getSize(matrixA);
    createSquareMatrix(matrixResult, matrixSize);
    
    if (matrixSize > 2) {
        int subMatrixSize = matrixSize / 2;
        
        // Auxiliar variables
        Matrix auxMatrixA1 = NULL, auxMatrixB1 = NULL, auxMatrixA2 = NULL, auxMatrixB2 = NULL;
        Matrix auxContainer1 = NULL, auxContainer2 = NULL, solutionContainer = NULL;
        
        createSquareMatrix(&solutionContainer, subMatrixSize);
        createSquareMatrix(&auxMatrixA1, subMatrixSize);
        createSquareMatrix(&auxMatrixB1, subMatrixSize);
        createSquareMatrix(&auxMatrixA2, subMatrixSize);
        createSquareMatrix(&auxMatrixB2, subMatrixSize);
        createSquareMatrix(&auxContainer1, subMatrixSize);
        createSquareMatrix(&auxContainer2, subMatrixSize);

        int operation1Index = 0;
        for(short quadrant = 0; quadrant < 4; quadrant++) {
            operation1Index += 4;
 
            copyQuadrant(matrixA, &auxMatrixA1, operations[operation1Index -4]);
            copyQuadrant(matrixB, &auxMatrixB1, operations[operation1Index -3]);
            multiplyCoolMatrix(auxMatrixA1, auxMatrixB1, &auxContainer1);
            
            copyQuadrant(matrixA, &auxMatrixA2, operations[operation1Index -2]);
            copyQuadrant(matrixB, &auxMatrixB2, operations[operation1Index -1]);
            multiplyCoolMatrix(auxMatrixA2, auxMatrixB2, &auxContainer2);
            
            sumMatrix(auxContainer1, auxContainer2, &solutionContainer);
            assignCuadrant(solutionContainer, matrixResult, quadrant);

        }
        
        destroyMatrix(&auxMatrixA1);
        destroyMatrix(&auxMatrixB1);
        destroyMatrix(&auxMatrixA2);
        destroyMatrix(&auxMatrixB2);
        destroyMatrix(&auxContainer1);
        destroyMatrix(&auxContainer2);
        destroyMatrix(&solutionContainer);
    
    } else {
        int value1, value2, container = 0;
        int matrixSize = getSize(matrixA);
        
        
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                for (int k= 0; k < matrixSize; k++) {
                    getValue(matrixA, j, k, &value1);
                    getValue(matrixB, k, i, &value2);
                    container += value1 * value2;
                }
                
                assingValue(matrixResult, j, i, container);
                container = 0;
            }
        }
    }
    
}








