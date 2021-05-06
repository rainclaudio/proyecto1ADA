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
v merge_util(v avector, v bvector, int sizea, int sizeb){
  v dvector;
  int i=0,j=0;
  while (i < sizea && j < sizeb){
    if(avector[i] <= bvector[j]){
      dvector.push_back(avector[i]);
      i++;
    }
    else {
      dvector.push_back(bvector[j]);
      j++;
    }
  }
  while (i < sizea){
    dvector.push_back(avector[i]);
    i++;
  }

  while (j < sizeb){
    dvector.push_back(bvector[j]);
    j++;
  }
  return dvector;
}

void Merge(float *A, int lb, int midleft,int midCentral,int midright,int ub){
  v Av,Bv,Cv,Dv;
  // MODIFICAR
 int n1 = midleft - lb +1; // size of Av
 int n2 =  midCentral - midleft; // size of Bv
 int n3 =  midright - midCentral; // size of Cv
 int n4 = ub - midright;
  for(int i = 0; i <  n1;++i){
   Av.push_back(A[lb + i]);
  }
  for(int j = 0; j  < n2; ++j){
    Bv.push_back(A[midleft + 1 + j]);
  }
  for(int k = 0; k < n3; ++k){
    Cv.push_back(A[midCentral + 1 + k]);
  }
  for(int k = 0; k < n4; ++k){
    Dv.push_back(A[midright + 1 + k]);
  }

  v vecvar1 = merge_util(Av,Bv,n1,n2);
  v vecvar2 = merge_util(Cv,Dv,n3,n4);
  v answer = merge_util(vecvar1,vecvar2,n1+n2,n3+n4);

  for(int i = 0; i < answer.size(); ++i){
    A[i+lb] = answer[i];
  }

}
void compare(float *A, float n1, float n2, float n3,int lb){
  if(n1 < n2){
    if(n1 < n3){
      if(n2 < n3){
        A[lb] = n1;
        A[lb + 1] = n2;
        A[lb + 2] = n3;
      } else {
        A[lb] = n1;
        A[lb + 1] = n3;
        A[lb + 2] = n2;
      }
    } else {
      A[lb] = n3;
      A[lb + 1] = n1;
      A[lb + 2] = n2;
    }
  } else {
    if(n2 < n3){
      if(n1 < n3){
        A[lb] = n2;
        A[lb + 1] = n1;
        A[lb + 2] = n3;
      } else{
        A[lb] = n2;
        A[lb + 1] = n3;
        A[lb + 2] = n1;
      }
    } else {
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
    quad_MergeSort(A,0,num-1);
    auto finish = std::chrono::high_resolution_clock::now();
    auto d = std::chrono::duration_cast<std::chrono::nanoseconds> (finish - start).count();

    timeCounter += d;
  }
  /*std::cout <<"averageTime: "<< ((double)timeCounter)/10 << " [ns]" << " \n";
  std::cout << '\n';*/
  return ((double)timeCounter)/10;
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
int main(int argc, char const *argv[]) {

  float *A = new float[10000000];

  //double average_time =  expermient(A,i*10000);
  getInp(A,argv[1],argv[2]);

  delete A;

  return 0;
}
