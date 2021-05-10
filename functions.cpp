#include <bits/stdc++.h>
#include "QuadMergeSort.h"
#include "TriMergeSort.h"
#include "MergeSort.h"
#include <fstream>
std::ifstream reader;
std::ofstream writer;
void print_Arr(float *A, int tam){
  for (size_t i = 0; i < tam; i++) {
    std::cout<< A[i] << " ";
  }
  std::cout  << '\n';
}
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

void experiment(float *A,int tam,int option){
  long long timeCounter = 0;
  int nCases,nCasescpy;
  long long num = 0;

  for(int i = 1; i < 11; ++i){
    nCases = nCasescpy = 10;
    while (nCases--){
      num = 0;
      while(num < tam*i){
        float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
        A[num] = r2;
        num++;
      }
      auto start = std::chrono::high_resolution_clock::now();
      switch (option) {
        case 1:
          MergeSort(A,0,num-1);
          break;
        case 2:
          Tri_MergeSort(A,0,num-1);
          break;
        case 3:
          quad_MergeSort(A,0,num-1);
          break;
        default:
          break;
      }
      auto finish = std::chrono::high_resolution_clock::now();
      auto d = std::chrono::duration_cast<std::chrono::nanoseconds> (finish - start).count();

      timeCounter += d;
      verify(A,num - 1);
    }

    std::cout << "averageTime for: "<<i*10000 << " elements: "<< ((double)timeCounter)/nCasescpy << '\n';
  }
}
void getInp(float *A,std::string in,std::string out,int option){
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
  switch (option) {
    case 1:
      MergeSort(A,0,num-1);
      break;
    case 2:
      Tri_MergeSort(A,0,num-1);
      break;
    case 3:
      quad_MergeSort(A,0,num-1);
      break;
    default:
      break;
  }
  writer.open(out);

  if(!writer){
    std::cerr<<"could not open ouput";
    exit(1);
  }
  verify(A,num-1);
  for(int i = 0; i < num - 1; ++i){
    writer << A[i] << '\t';
//    if(i%100 == 0)writer <<'\n';
  }

   writer.close();
}
void random_test(float *A, int tam,int option){
  int num = 0;
  while(num < tam){
    // float r2 = rand()%15 * 10;
    float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
    A[num] = r2;
    num++;
  }
  std::cout << "UNSORTED:" << '\n';
  print_Arr(A,num-1);
  switch (option) {
    case 1:

      MergeSort(A,0,num-1);
      break;
    case 2:
      Tri_MergeSort(A,0,num-1);
      break;
    case 3:
      quad_MergeSort(A,0,num-1);
      break;
    default:
      break;
  }
  std::cout << "Sorted" << '\n';
  print_Arr(A,num-1);
  verify(A,num);
}
