
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
    printf("matrix size: %d\n", matrixSize);
    
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
    }

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
        MATRIX_ELEMENT_TYPE randomNumber = rand() % vectorSize + 1;
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
    int index = getSize(*matrix) * (row - 1) + column;
    add(matrix, (index - 1), data);
}


/*
 * Get the given value in the given matrix at the given row and column
 */
void getValue(Matrix matrix, int row, int column, MATRIX_ELEMENT_TYPE *data) {
    int index = getSize(matrix) * (row - 1) + column;
    *data = get(matrix, (index - 1));
}

