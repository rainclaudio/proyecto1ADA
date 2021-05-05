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

void Merge(float *A, int lb, int mid1,int mid2,int ub){
  v Av,Bv,Cv;
 int n1 = mid1 - lb +1; // size of Av
 int n2 =  mid2 - mid1; // size of Bv
 int n3 =  ub - mid2; // size of Cv
  for(int i = 0; i <  n1;++i){
   Av.push_back(A[lb + i]);
  }
  for(int j = 0; j  < n2; ++j){
    Bv.push_back(A[mid1 + 1 + j]);
  }
  for(int k = 0; k < n3; ++k){
    Cv.push_back(A[mid2 + 1 + k]);
  }

  v vecvar = merge_util(Av,Bv,n1,n2);
  v answer = merge_util(Cv,vecvar,n3,n1+n2);
  for(int i = 0; i < answer.size(); ++i){
    A[i+lb] = answer[i];
  }

}

void quad_MergeSort(float *A,int lb, int ub){
	if( ub - lb > 1){
	int mid1 = lb + ((ub - lb) / 3);
	int mid2 = lb + 2 * ((ub - lb) / 3) + 1;

		quad_MergeSort(A,lb,mid1);
		quad_MergeSort(A,mid1 + 1, mid2);
		quad_MergeSort(A,mid2 + 1,ub);

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
