#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <math.h>

#define MAT_X(x)                                                               \
  { 1, 0, 0, 0, cos(x), -sin(x), 0, sin(x), cos(x) }

#define MAT_Y(x)                                                               \
  { cos(x), 0, sin(x), 0, 1, 0, -sin(x), 0, cos(x) }

#define MAT_Z(x)                                                               \
  { cos(x), -sin(x), 0, sin(x), cos(x), 0, 0, 0, 1 }

#define MAT_ZEROS                                                              \
  { 0, 0, 0, 0, 0, 0, 0, 0, 0 }

void matrixMult(double (&mat1)[3][3], double (&mat2)[3][3],
                double (&out)[3][3]);

#endif /* _MATRIX_H_ */
