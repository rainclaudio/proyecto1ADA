#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
typedef std::vector<float> v;
/*
g++ triMergeSort.cpp -o ejecutable
.\ejecutable input.txt
*/

void Merge(float *A, int lb, int mid1,int mid2,int ub){
 int n1 = mid1 - lb +1; // size of Av
 int n2 = mid2 - mid1; // size of Bv
 int n3 = ub - mid2; // size of Cv
 v Av,Bv,Cv,Dv;

 int i,j;
  for(i = 0; i <  n1;++i){
    Av.push_back(A[lb + i]);
  }
  for(j = 0; j  < n2; ++j){
    Bv.push_back(A[mid1 + 1 + j]);
  }
  for(int k = 0; k < n3; ++k){
    Cv.push_back(A[mid2 + 1 + k]);
  }
  i = j = 0;
  while (i < n1 && j < n2){
    if(Av[i] <= Bv[j]){
      Dv.push_back(Av[i]);
      i++;
    }
    else {
      Dv.push_back(Bv[j]);
      j++;
    }
  }
  while (i < n1){
    Dv.push_back(Av[i]);
    i++;
  }
  while (j < n2){
    Dv.push_back(Bv[j]);
    j++;
  }
  i=j=0;
  int k = lb;
  while (i < n1 + n2 && j < n3){
    if(Dv[i] <= Cv[j]){
      A[k] = Dv[i];
      i++;
    }
    else {
      A[k] = Cv[j];
      j++;
    }
    k++;
  }
  while (i < n1 + n2){
    A[k] = Dv[i];
    i++;
    k++;
  }
  while (j < n3){
    A[k] = Cv[j];
    j++;
    k++;
  }
}

void Tri_MergeSort(float *A,int lb, int ub){
	if( ub - lb > 1){
	int mid1 = (2*lb + ub) / 3;
	int mid2 = (lb + 2*ub) / 3;

		Tri_MergeSort(A,lb,mid1);
		Tri_MergeSort(A,mid1 + 1, mid2);
		Tri_MergeSort(A,mid2 + 1,ub);

		Merge(A, lb,mid1,mid2, ub);
	} else if (ub - lb == 1){
    float n1 = A[lb];
    float n2 = A[ub];
    if(n2 <= n1){
      A[lb] = n2;
      A[ub] = n1;
    }
	}
}
