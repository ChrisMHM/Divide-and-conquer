

#include <stdio.h>
#include <time.h>

typedef int MATRIX_ELEMENT_TYPE;

typedef struct {
    MATRIX_ELEMENT_TYPE *data;
    int size;
    
} _MATRIX;


typedef _MATRIX * Matrix;


void createMatrix(Matrix *matrix, int _size) {

    unsigned long i = 0;
    
    if(*matrix == NULL) {
        *matrix = (Matrix) malloc (sizeof(Matrix));
        
        (*matrix) -> data = (MATRIX_ELEMENT_TYPE*) malloc(_size * sizeof(MATRIX_ELEMENT_TYPE));
        (*matrix) -> size = _size;
        
        for (i = 0; i < _size; ++i) {
            *((*matrix) -> data + i) = 0;
        }
        
    } else {
        printf("[ERROR] El vector ya ha sido inicializado, liberelo antes.");
    }
}


void add(Matrix *_matrix, int position, MATRIX_ELEMENT_TYPE _data) {
    
    if (*_matrix != NULL) {
        *((*_matrix) -> data + position) = _data;
        
    } else {
        printf("[ERROR] El vector no ha sido inicializado.");
    }
}


void fillMatrixWithRandom(Matrix *_matrix) {
    int vectorSize = getSize(*_matrix);
//    srand(time(NULL));
    
    for (unsigned long i = 0; i < vectorSize; i++) {
        MATRIX_ELEMENT_TYPE randomNumber = rand() % vectorSize + 1;
        add(_matrix, i, randomNumber);
        
    }
}


int getSize (Matrix _matrix) {
    int _size = -1;
    
    if(_matrix != NULL)
        _size = (_matrix) -> size;
    
    return _size;
}

