#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
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

int main(int argc, char const *argv[]) {
  reader.open(argv[1]);
  if(!reader){
    std::cerr<<"could not open input";
    exit(1);
  }
  float *A = new float(10000000);
  float var = 0;
  long long num = 0;
  while(reader >> A[num]){
    num++;
  }
  std::cout << "hola?" << '\n';
  std::cout << var << '\n';
  auto start = std::chrono::high_resolution_clock::now();
  Tri_MergeSort(A,0,num-1);
  auto finish = std::chrono::high_resolution_clock::now();
  for(int i = 0; i < num; ++i){
    std::cout << A[i] << ' ';
  }
  std::cout << '\n';


  auto d = std::chrono::duration_cast<std::chrono::nanoseconds> (finish - start).count();
  std::cout <<"total time "<< d << " [ns]" << " \n";

  reader.close();
  writer.close();
  return 0;
}
