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
void mergeVector(v& Av, v& Bv, v& Ev, int n1, int n2){
  int i,j;
  i = j = 0;
  while (i < n1 && j < n2){
    if(Av[i] <= Bv[j]){
      Ev.push_back(Av[i]);
      i++;
    }
    else {
      Ev.push_back(Bv[j]);
      j++;
    }
  }
  while (i < n1){
    Ev.push_back(Av[i]);
    i++;
  }
  while (j < n2){
    Ev.push_back(Bv[j]);
    j++;
  }
}
void Merge(float *A, int lb, int midleft,int midCentral,int midright,int ub){
  v Av,Bv,Cv,Dv,Ev,Fv;
  // MODIFICAR
 int n1 =  midleft - lb +1; // size of Av
 int n2 =  midCentral - midleft; // size of Bv
 int n3 =  midright - midCentral; // size of Cv
 int n4 =  ub - midright;
 int i,j,k;
  for(i = 0; i <  n1;++i){
   Av.push_back(A[lb + i]);
  }
  for(j = 0; j  < n2; ++j){
    Bv.push_back(A[midleft + 1 + j]);
  }
  for(k = 0; k < n3; ++k){
    Dv.push_back(A[midCentral + 1 + k]);
  }
  for(k = 0; k < n4; ++k){
    Ev.push_back(A[midright + 1 + k]);
  }

  mergeVector(Av,Bv,Cv,n1,n2);
  mergeVector(Dv,Ev,Fv,n3,n4);

  i = j = 0;
  k = lb;
  while (i < n1 + n2 && j < n3 + n4){
    if(Cv[i] <= Fv[j]){
      A[k] = Cv[i];
      i++;
    }
    else {
      A[k] = Fv[j];
      j++;
    }
    k++;
  }
  while (i < n1 + n2){
    A[k] = Cv[i];
    i++;
    k++;
  }
  while (j < n3 + n4){
    A[k] = Fv[j];
    j++;
    k++;
  }

}
void compare(float *A, float n1, float n2, float n3,int lb){
  if(n1 < n2){
    if(n1 < n3){
      if(n2 < n3){
        // swap
        A[lb] = n1;
        A[lb + 1] = n2;
        A[lb + 2] = n3;
      } else {
        // swap
        A[lb] = n1;
        A[lb + 1] = n3;
        A[lb + 2] = n2;
      }
    } else {
      // swap
      A[lb] = n3;
      A[lb + 1] = n1;
      A[lb + 2] = n2;
    }
  } else {
    if(n2 < n3){
      if(n1 < n3){
        // swap
        A[lb] = n2;
        A[lb + 1] = n1;
        A[lb + 2] = n3;
      } else{
        // swap
        A[lb] = n2;
        A[lb + 1] = n3;
        A[lb + 2] = n1;
      }
    } else {
      // swap
      A[lb] = n3;
      A[lb + 1] = n2;
      A[lb + 2] = n1;
    }
  }
}
void util_sort(float *A, int lb, int ub){
  float n1 = A[lb];
  float n2 = A[lb + 1];
  float n3 = A[ub];

  switch (ub-lb) {
    case 1:
      if(n3 < n1){
        A[lb] = n3;
        A[ub] = n1;
      }
      break;
    case 2:
      compare(A,n1,n2,n3,lb);
      break;

    default: break;
  }
}
void quad_MergeSort(float *A,int lb, int ub){
	if( ub - lb > 2){

	int midCentral = (ub + lb)/2;
	int midleft =  (lb + midCentral)/2;
  int midright = (midCentral + ub)/2;

		quad_MergeSort(A,lb,midleft);
		quad_MergeSort(A,midleft + 1, midCentral);
		quad_MergeSort(A,midCentral + 1,midright);
    quad_MergeSort(A,midright + 1,ub);
		Merge(A, lb,midleft,midCentral,midright, ub);

	} else {
      util_sort(A,lb,ub);
    }
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

void print_Arr(float *A, int tam){
  for (size_t i = 0; i < tam; i++) {
    std::cout<< A[i] << " ";
  }
  std::cout  << '\n';
}

void random_test(float *A, int tam){
  int num = 0;
  while(num < tam){
    float r2 = rand()%15 * 10;
    float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
    A[num] = r2;
    num++;
  }
  quad_MergeSort(A,0,num-1);
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
