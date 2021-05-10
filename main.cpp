#include <iostream>
#include "functions.h"
#include <time.h>
/*
g++ main.cpp functions.cpp mergeSort.cpp quadMergeSort.cpp triMergeSort.cpp -o ejecutable
.\ejecutable 10000 input.txt output.txt
*/
int main(int argc, char const *argv[]) {

  if(argc == 3){
  std::cout << "BIENVENIDO!: " << '\n';
  std::cout << "Por favor, digite el número de la opción a escoger: " << '\n';
  std::cout << '\n';
  std::cout << "[1]: Experimentación: Tomara el tiempo promedio de ordenar" << '\n';
  std::cout << "10 mil a 100 mil elementos con el algoritmo a escoger" << '\n';
  std::cout << '\n';
  std::cout << "[2]: Random_test: Creará un arreglo con variables de tipo float " << '\n';
  std::cout << "con el objetivo de presentarselas de manera ordenada con el " << '\n';
  std::cout << "algoritmo a escoger" << '\n';
  std::cout << '\n';
  std::cout << "[3]: getInput: Tomara un txt otorgado a través de la terminal " << '\n';
  std::cout << "y le Creará otro con las variables ordenadas " << '\n';
  std::cout << "con el algoritmo a escoger" << '\n';
  std::cout << '\n';
  int option;
  std::cin >> option;
  std::cout << "Muchas gracias!" << '\n';
  std::cout << "Por último, esgoja el algoritmo a utilizar" << '\n';
  std::cout << "[1]: Merge Sort" << '\n';
  std::cout << "[2]: Tri MergeSort" << '\n';
  std::cout << "[3]: quad MergeSort" << '\n';
  int optionAlgorithm;
  std::cin >> optionAlgorithm;
  srand(time(NULL));
  float *A = new float[10000000];
  switch (option) {
    case 1:
      experiment(A,10000,optionAlgorithm);
      break;
    case 2:
      random_test(A,10,optionAlgorithm);
      break;
    case 3:
      getInp(A,argv[1],argv[2],optionAlgorithm);
      break;
    default:
      break;
  }
} else std::cout << "número de argumentos incorrecto" << '\n';
  return 0;
}
