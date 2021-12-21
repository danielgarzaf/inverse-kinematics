#include <matrix.h>

void matrixMult(double (&mat1)[3][3], double (&mat2)[3][3],
                double (&out)[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      out[i][j] = mat1[i][0] * mat2[0][j];
      out[i][j] += mat1[i][1] * mat2[1][j];
      out[i][j] += mat1[i][2] * mat2[2][j];
    }
  }
}
