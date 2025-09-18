//
// Created by Miguel on 11/09/2025. sorteo makiaaaaa
//
#include <iostream>
#include <ctime>

using namespace std;

int main(){

  srand(time(NULL));
  int num = (rand() % 100)+1;

  cout<<num<<endl;

  string resultado;
    resultado = num == 23 ? "ganaste" : "vales monda";
  cout<<resultado<<endl;






  return 0;
  }
