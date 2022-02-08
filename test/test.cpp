#include "../include/matrix.h"
#include <iostream>

void print_mat_3x3(double (&mat)[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      printf("%0.3f\t", mat[i][j]);
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  const double PI = 3.1416;
  mat3 matX = ROT_MAT3_X(30 * PI / 180);
  mat3 matY = ROT_MAT3_Y(30 * PI / 180);
  mult_mat3(matX, matY);
  print_mat_3x3(matY);
  return 0;
}
