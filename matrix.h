
typedef int MATRIX_ELEMENT_TYPE;

typedef void * Matrix;

void add(Matrix *_matrix, int position, MATRIX_ELEMENT_TYPE _data);

int createSquareMatrix(Matrix *matrix, int _size);

void fillSquareMatrixWithRandom(Matrix *_matrix);

int getSize (Matrix _matrix);

void printSquareMatrix(Matrix _matrix);



