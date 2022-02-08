#include "matrix.h"

void mult_mat3(mat3 a, mat3 b) {
  mat3 tmp = MAT3_INIT_ZEROS;
  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t j = 0; j < 3; j++) {
      tmp[i][j] = a[i][0] * b[0][j];
      tmp[i][j] += a[i][1] * b[1][j];
      tmp[i][j] += a[i][2] * b[2][j];
    }
  }
  copy_mat3(tmp, b);
}

void mult_mat4(mat4 a, mat4 b) {
  mat4 tmp = MAT4_INIT_ZEROS;
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      tmp[i][j] = a[i][0] * b[0][j];
      tmp[i][j] += a[i][1] * b[1][j];
      tmp[i][j] += a[i][2] * b[2][j];
      tmp[i][j] += a[i][3] * b[3][j];
    }
  }
}

void copy_mat3(mat3 src, mat3 dst) {
  for (uint8_t i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      dst[i][j] = src[i][j];
    }
  }
}

void copy_vec3(vec3 src, vec3 dst) {
  for (uint8_t i = 0; i < 3; i++)
    dst[i] = src[i];
}

void translate(mat4 m, vec3 pos) {
  for (uint8_t i = 0; i < 3; i++) {
    m[i][3] += pos[i];
  }
}
