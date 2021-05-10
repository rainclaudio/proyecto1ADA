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

void Merge(float *A, int lb, int mid, int ub){
  v Av,Bv;
  // MODIFICAR
 int n1 =  mid - lb +1; // size of Av
 int n2 =  ub - mid;
 int i,j,k;
  for(i = 0; i <  n1;++i){
   Av.push_back(A[lb + i]);
  }
  for(j = 0; j  < n2; ++j){
   Bv.push_back(A[mid + 1 + j]);
  }
  i = j = 0;
  k = lb;
  while (i < n1&& j < n2){
    if(Av[i] <= Bv[j]){
      A[k] = Av[i];
      i++;
    }
    else {
      A[k] = Bv[j];
      j++;
    }
    k++;
  }
  while (i < n1 ){
    A[k] = Av[i];
    i++;
    k++;
  }
  while (j < n2){
    A[k] = Bv[j];
    j++;
    k++;
  }

}
void MergeSort(float *A,int lb, int ub){
	if( ub  > lb){

	int mid = (ub + lb)/2;
	MergeSort(A,lb,mid);
	MergeSort(A,mid + 1, ub);
	Merge(A,lb,mid,ub);
	}
}
