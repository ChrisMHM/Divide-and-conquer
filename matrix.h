
typedef int MATRIX_ELEMENT_TYPE;



typedef void * Matrix;

void add(Matrix *_matrix, int position, MATRIX_ELEMENT_TYPE _data);

void createMatrix(Matrix *matrix, int _size);

void fillMatrixWithRandom(Matrix *_matrix);

int getSize (Matrix _matrix);

