// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "utmatrix.h"
using namespace std;
//---------------------------------------------------------------------------

void main()
{
	TVector<int> v(5), res(5);
	for (int i = 0; i < 5; i++) {
		v[i] = 0;
		res[i] = 1;
	}
	//v = v + 1;
	cout << v << endl;
	/*
	  TMatrix<int> a(5), b(5), c(5);
	 int i, j;

	  setlocale(LC_ALL, "Russian");
	  cout << "Тестирование программ поддержки представления треугольных матриц" << endl;
	  cout << "Matrix a = " << endl << a << endl;
	  for (i = 0; i < 5; i++)
	    for (j = i; j < 5; j++ )
	    {
	      a[i][j] =  i * 10 + j;
	      b[i][j] = (i * 10 + j) * 100;
	    }
	  c = a + b;
	  cout << "Matrix a = " << endl << a << endl;
	  cout << "Matrix b = " << endl << b << endl;
	  cout << "Matrix c = a + b" << endl << c << endl;
	*/
}
//---------------------------------------------------------------------------
