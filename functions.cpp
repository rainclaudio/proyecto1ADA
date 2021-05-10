#include <bits/stdc++.h>
#include "QuadMergeSort.h"
#include "TriMergeSort.h"
#include "MergeSort.h"
#include <fstream>
std::ifstream reader;
std::ofstream writer;

void verify(float *A, int tam){
  bool isTrue = true;
  for (size_t i = 1; i < tam; i++) {
    if(A[i] < A[i - 1]){
      std::cout << "CATCH ERROR EXCEPTION" << '\n';
      std::cout << "A[i - 1] A[i]: "<<A[i - 1]<<" "<<A[i] << '\n';
      break;
    }
  }

}

double expermient(float *A,int tam){
  int nCases = 10;
  int nCasescpy = nCases;
  long long num = 0;
  long long timeCounter = 0;
  while (nCases--){
    num = 0;
    while(num < tam){
      float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
      A[num] = r2;
      num++;
    }

    auto start = std::chrono::high_resolution_clock::now();
    quad_MergeSort(A,0,num-1);
    auto finish = std::chrono::high_resolution_clock::now();
    auto d = std::chrono::duration_cast<std::chrono::nanoseconds> (finish - start).count();

    timeCounter += d;
    verify(A,num - 1);
  }
  return ((double)timeCounter)/nCasescpy;
}
void getInp(float *A,std::string in,std::string out){
  reader.open(in);
  if(!reader){
    std::cerr<<"could not open input";
    exit(1);
  }
  long long num = 0;
  while(reader >> A[num]){
    num++;
  }
  reader.close();

  quad_MergeSort(A,0,num-1);
  writer.open(out);

  if(!writer){
    std::cerr<<"could not open ouput";
    exit(1);
  }

  for(int i = 0; i < num - 1; ++i){
    writer << A[i] << '\t';
//    if(i%100 == 0)writer <<'\n';
  }

   writer.close();
}
void random_test(float *A, int tam){
  int num = 0;
  while(num < tam){
    // float r2 = rand()%15 * 10;
    float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
    A[num] = r2;
    num++;
  }
  quad_MergeSort(A,0,num-1);
  verify(A,num);
}

void print_Arr(float *A, int tam){
  for (size_t i = 0; i < tam; i++) {
    std::cout<< A[i] << " ";
  }
  std::cout  << '\n';
}
