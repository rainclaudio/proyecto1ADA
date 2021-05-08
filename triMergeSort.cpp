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
void printVector(v A, int tam){
  for (size_t i = 0; i < tam; i++) {
    std::cout<< A[i] << " ";
  }
  std::cout << '\n';
}

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
      Dv.push_back(Bv[i]);
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
	int mid1 = lb + ((ub - lb) / 3);
	int mid2 = lb + 2 * ((ub - lb) / 3) + 1;

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

double expermient(float *A,int tam){
  int nCases = 20;
  long long num = 0;
  long long timeCounter = 0;
  while (nCases--){
    num = 0;
    while(num < tam){
      float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
      A[num] = r2;
      num++;
    }

    // std::cout << "comenzando" << '\n';
    auto start = std::chrono::high_resolution_clock::now();
    Tri_MergeSort(A,0,num-1);
    auto finish = std::chrono::high_resolution_clock::now();
    auto d = std::chrono::duration_cast<std::chrono::nanoseconds> (finish - start).count();

    timeCounter += d;
  }
  /*std::cout <<"averageTime: "<< ((double)timeCounter)/10 << " [ns]" << " \n";
  std::cout << '\n';*/
  return ((double)timeCounter)/10;
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
    float r2 = ((float)rand() * 10);
    A[num] = r2;
    num++;
  }
  std::cout << "UNSORTED" << '\n';
  print_Arr(A,num-1);
  std::cout << '\n';
  std::cout << "SORTED" << '\n';
  Tri_MergeSort(A,0,num-1);
  print_Arr(A,num-1);
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
  std::cout << "previous: " << '\n';
  print_Arr(A,num-1);
  Tri_MergeSort(A,0,num-1);
  std::cout << "merged: " << '\n';
  print_Arr(A,num-1);
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
int main(int argc, char const *argv[]) {

  // srand(time(NULL));
  float *A = new float[10000000];
  for(int i = 1; i < 11; ++i){
    double average_time =  expermient(A,i*10000);
    std::cout << "averageTime for: "<<i*10000 << "elements: "<< average_time << '\n';
  }
//getInp(A,argv[1],argv[2]);
  //random_test(A,20);
  delete A;

  return 0;
}
