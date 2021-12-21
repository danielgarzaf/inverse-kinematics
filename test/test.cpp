#include "../include/matrix.h"
#include <iostream>

void print_mat_3x3(double (&mat)[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      printf("%0.3f\t", mat[i][j]);
    printf("\n");
  }
}

void matrix_mult(double (&mat1)[3][3], double (&mat2)[3][3],
                 double (&out)[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      out[i][j] = mat1[i][0] * mat2[0][j];
      out[i][j] += mat1[i][1] * mat2[1][j];
      out[i][j] += mat1[i][2] * mat2[2][j];
    }
  }
  return;
}

int main(int argc, char *argv[]) {
  const double PI = 3.1416;
  double out[3][3] = MAT_ZEROS;
  double matX[3][3] = MAT_X(30 * PI / 180);
  double matY[3][3] = MAT_Y(30 * PI / 180);
  matrix_mult(matX, matY, out);
  print_mat_3x3(out);
  return 0;
}
