
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
        printf("[ERROR] The vector has not been initalized.");
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


/**
 * Multiply two matrix and store the result into the result matrix given by parameter
 */
void multiplyMatrix(Matrix matrix1, Matrix matrix2, Matrix* matrixResult) {
    int container =0;
    int subMatrix1Value, subMatrix2Value;
    int matrixSize = getSize(matrix1);
    Matrix temporalMatrix1 = NULL;
    Matrix temporalMatrix2 = NULL;

    

    printf("Creating result matrix with a size of : %d\n", matrixSize);
    createSquareMatrix(matrixResult, matrixSize);

    if (matrixSize > 2) {
        
        int subMatrixSize = matrixSize /2;
        printf("Sub matrix size: %d\n", subMatrixSize);
        
        for (int subMatrixOffset=0; subMatrixOffset < 4; subMatrixOffset++) {
            createSquareMatrix(&temporalMatrix1, subMatrixSize);
            createSquareMatrix(&temporalMatrix2, subMatrixSize);
            
            for (int  column= 0; column < subMatrixSize; column++) {
                for (int row = 0; row < subMatrixSize; row++) {
                    getValue(matrix1, column, subMatrixOffset + row, &subMatrix1Value);
                    getValue(matrix2, column, subMatrixOffset + row, &subMatrix2Value);
                    assingValue(&temporalMatrix1, column, row, subMatrix1Value);
                    assingValue(&temporalMatrix2, column, row, subMatrix2Value);
                }
            }
            
            printf("\n\n Result matrix 1\n\n");
            printSquareMatrix(temporalMatrix1);
            
            printf("\n\n Result matrix 2\n\n");
            printSquareMatrix(temporalMatrix2);
            
        }
        
        
    } else {
        int value1, value2;
        
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






