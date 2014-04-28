
typedef int MATRIX_ELEMENT_TYPE;

typedef void * Matrix;

void add(Matrix *_matrix, int position, MATRIX_ELEMENT_TYPE _data);

int createSquareMatrix(Matrix *matrix, int _size);

void fillSquareMatrixWithRandom(Matrix *_matrix);

int getSize (Matrix _matrix);

void destroyMatrix(Matrix *matrix);

void assingValue(Matrix *matrix, int row, int column, MATRIX_ELEMENT_TYPE data);

void getValue(Matrix matrix, int row, int column, MATRIX_ELEMENT_TYPE *data);

void multiplyMatrix(Matrix matrix1, Matrix matrix2, Matrix* matrixResult);

void multiplyCoolMatrix(Matrix matrixA, Matrix matrixB, Matrix* matrixResult);

void printSquareMatrix(Matrix _matrix);
