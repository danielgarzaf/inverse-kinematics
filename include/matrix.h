#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <math.h>
#include <stdint.h>

typedef double vec4[4];
typedef vec4 mat4[4];

typedef double vec3[3];
typedef vec3 mat3[3];

#define ROT_MAT3_X(x)                                                          \
  {                                                                            \
    {1, 0, 0}, {0, cos(x), -sin(x)}, { 0, sin(x), cos(x) }                     \
  }

#define ROT_MAT3_Y(x)                                                          \
  {                                                                            \
    {cos(x), 0, sin(x)}, {0, 1, 0}, { -sin(x), 0, cos(x) }                     \
  }

#define ROT_MAT3_Z(x)                                                          \
  {                                                                            \
    {cos(x), -sin(x), 0}, {sin(x), cos(x), 0}, { 0, 0, 1 }                     \
  }

#define MAT3_INIT_ZEROS                                                        \
  {                                                                            \
    {0, 0, 0}, {0, 0, 0}, { 0, 0, 0 }                                          \
  }

#define MAT3_IDENTITY_INIT                                                     \
  {                                                                            \
    {1, 0, 0}, {0, 1, 0}, { 0, 0, 1 }                                          \
  }

#define MAT4_IDENTITY_INIT                                                     \
  {                                                                            \
    {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, { 0, 0, 0, 1 }                   \
  }

#define MAT4_INIT_ZEROS                                                        \
  {                                                                            \
    {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, { 0, 0, 0, 0 }                   \
  }

void mult_mat3(mat3 a, mat3 b);
void mult_mat4(mat4 a, mat4 b);
void copy_mat3(mat3 src, mat3 dst);
void copy_vec3(vec3 src, vec3 dst);
void translate(mat4 m, vec3 pos);

#endif /* _MATRIX_H_ */
