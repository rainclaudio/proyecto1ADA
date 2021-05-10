#include <iostream>
#include <vector>
typedef std::vector<float> v;
void mergeVector(v& Av, v& Bv, v& Ev, int n1, int n2);
void Merge(float *A, int lb, int midleft,int midCentral,int midright,int ub);
void compare(float *A, float n1, float n2, float n3,int lb);
void util_sort(float *A, int lb, int ub);
void quad_MergeSort(float *A,int lb, int ub);
