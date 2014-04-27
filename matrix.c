
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef int MATRIX_ELEMENT_TYPE;

typedef struct {
    MATRIX_ELEMENT_TYPE *data;
    int size;
    
} _MATRIX;


typedef _MATRIX * Matrix;


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

/**
 * Multiply two matrix and store the result into the result matrix given by parameter
 */
void multiplyMatrix(Matrix matrix1, Matrix matrix2, Matrix* matrixResult) {
    int matrixSize = getSize(matrix1);
        createSquareMatrix(matrixResult, matrixSize);
    
    if (matrixSize > 2) {
        Matrix a1 = NULL, a2 = NULL, a3 = NULL, a4 = NULL, b1 = NULL, b2 = NULL, b3 = NULL, b4 = NULL, sol1 = NULL, sol2 = NULL, sol3 = NULL, sol4 = NULL, temporalMatrix1 = NULL, temporalMatrix2 = NULL;

        int subMatrixSize = matrixSize / 2;
        createSquareMatrix(&temporalMatrix1, subMatrixSize);
        createSquareMatrix(&temporalMatrix2, subMatrixSize);
        
        createSquareMatrix(&sol1, subMatrixSize);
        createSquareMatrix(&sol2, subMatrixSize);
        createSquareMatrix(&sol3, subMatrixSize);
        createSquareMatrix(&sol4, subMatrixSize);
        
        // A submatrix creation
        createSquareMatrix(&a1, subMatrixSize);
        copyQuadrant(matrix1, &a1, 0);
        
        createSquareMatrix(&a2, subMatrixSize);
        copyQuadrant(matrix1, &a2, 1);
        
        createSquareMatrix(&a3, subMatrixSize);
        copyQuadrant(matrix1, &a3, 2);
        
        createSquareMatrix(&a4, subMatrixSize);
        copyQuadrant(matrix1, &a4, 3);
        
        // B submatrix creation
        createSquareMatrix(&b1, subMatrixSize);
        copyQuadrant(matrix2, &b1, 0);
        
        createSquareMatrix(&b2, subMatrixSize);
        copyQuadrant(matrix2, &b2, 1);
        
        createSquareMatrix(&b3, subMatrixSize);
        copyQuadrant(matrix2, &b3, 2);
        
        createSquareMatrix(&b4, subMatrixSize);
        copyQuadrant(matrix2, &b4, 3);
   

        multiplyMatrix(a1, b1, &temporalMatrix1);
        multiplyMatrix(a2, b3, &temporalMatrix2);
        sumMatrix(temporalMatrix1, temporalMatrix2, &sol1);
        
        multiplyMatrix(a1, b2, &temporalMatrix1);
        multiplyMatrix(a2, b4, &temporalMatrix2);
        sumMatrix(temporalMatrix1, temporalMatrix2, &sol2);
        
        multiplyMatrix(a3, b1, &temporalMatrix1);
        multiplyMatrix(a4, b3, &temporalMatrix2);
        sumMatrix(temporalMatrix1, temporalMatrix2, &sol3);
        
        multiplyMatrix(a3, b2, &temporalMatrix1);
        multiplyMatrix(a4, b4, &temporalMatrix2);
        sumMatrix(temporalMatrix1, temporalMatrix2, &sol4);
        

        printf("\nSol 1\n");
        printSquareMatrix(sol1);

        printf("\nSol 2\n");
        printSquareMatrix(sol2);

        
        printf("\nSol 3\n");
        printSquareMatrix(sol3);

        printf("\nSol 4\n");
        printSquareMatrix(sol4);

        
        int c1, c2, c3, c4;
        for(int row=0; row < subMatrixSize; row++) {
            for(int column=0;column < subMatrixSize ; column++) {
                
                getValue(sol1, row, column, &c1);
                assingValue(matrixResult, row, column, c1);
                
                getValue(sol3, row, column, &c3);
                assingValue(matrixResult, row + subMatrixSize, column, c3);
                

                getValue(sol2, row, column, &c2);
                assingValue(matrixResult, row, column + subMatrixSize, c2);
                

                getValue(sol4, row, column, &c4);
                assingValue(matrixResult, row + subMatrixSize, column + subMatrixSize, c4);
            }
        }
        
        
    } else {
        int value1, value2, container = 0;
        int matrixSize = getSize(matrix1);
        
        
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                for (int k= 0; k < matrixSize; k++) {
                    getValue(matrix1, j, k, &value1);
                    getValue(matrix2, k, i, &value2);
                    container += value1 * value2;
                }
                
                assingValue(matrixResult, j, i, container);
                container = 0;
            }
        }
    }
}







