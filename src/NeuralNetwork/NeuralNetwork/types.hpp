#ifndef types_h
#define types_h

// Standard types, vectors and matrices etc.
typedef Tensor<0> Scalar;

typedef Tensor<1> Vector;
#define VECTOR_LENGTH       (0)

typedef Tensor<2> Matrix;
#define MATRIX_ROWS         (0)
#define MATRIX_COLUMNS      (1)

// Convolutional Neural Network types
typedef Tensor<3> Volume;
#define VOLUME_WIDTH      (0)
#define VOLUME_HEIGHT     (1)
#define VOLUME_DEPTH      (2)

typedef Tensor<4> FilterSet;
#define FILTERSET_WIDTH     (0)
#define FILTERSET_HEIGHT    (1)
#define FILTERSET_DEPTH     (2)
#define FILTERSET_AMOUNT    (3)

#endif
