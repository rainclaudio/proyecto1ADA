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
std::ifstream reader;
std::ofstream writer;
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

void verify(float *A, int tam){
  bool isTrue = true;
  for (size_t i = 1; i < tam; i++) {
    if(A[i] < A[i - 1]){
      std::cout << "CATCH ERROR EXEPTION" << '\n';
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
    MergeSort(A,0,num-1);
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

  MergeSort(A,0,num-1);
  writer.open(out);

  if(!writer){
    std::cerr<<"could not open ouput";
    exit(1);
  }

  for(int i = 0; i < num - 1; ++i){
    writer << A[i] << '\t';
  }

   writer.close();
}

void print_Arr(float *A, int tam){
  for (size_t i = 0; i < tam; i++) {
    std::cout<< A[i] << " ";
  }
  std::cout  << '\n';
}

void random_test(float *A, int tam){
  int num = 0;
  while(num < tam){
     float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
    A[num] = r2;
    num++;
  }
  MergeSort(A,0,num-1);
   verify(A,num);
}

int main(int argc, char const *argv[]) {

  float *A = new float[10000000];
  srand(time(NULL));

   for(int i = 1; i < 11; ++i){
     double average_time =  expermient(A,i*10000);
     std::cout << "averageTime for: "<<i*10000 << "elements: "<< average_time << '\n';
  }
  delete A;

  return 0;
}
