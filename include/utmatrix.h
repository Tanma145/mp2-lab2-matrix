﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
	for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si){
	if ((s < 0) || (si < 0)) {
		throw "negative length";
	}
	if (s > MAX_VECTOR_SIZE) {
		throw "large index";
	}
	Size = s;
	StartIndex = si;
	pVector = new ValType[s];
}

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v){
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = v.pVector[i];
}

template <class ValType>
TVector<ValType>::~TVector(){
	delete[] pVector;
}

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos){
	if ((pos > MAX_VECTOR_SIZE) || (pos - StartIndex > Size) || (pos - StartIndex < 0))
		throw pos;
	return pVector[pos - StartIndex];
}

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (Size != v.Size)
		return false;
	else {
		for (int i = 0; i < Size; i++)
			if (pVector[i] != v.pVector[i])
				return false;
	}
	return true;
}

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return !(*this == v);
}

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v){
	if (this != &v) {
		delete[] pVector;
		Size = v.Size;
		StartIndex = v.StartIndex;
		pVector = new ValType[v.Size];
		for (int i = 0; i < v.Size; i++)
			pVector[i] = v.pVector[i];
	}
	return *this;
}

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val){
	TVector<ValType> v(*this);
	for (int i = 0; i < Size; i++)
		v.pVector[i] = v.pVector[i] + val;
	return v;
}

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val){
	TVector<ValType> v(*this);
	for (int i = 0; i < Size; i++)
		v.pVector[i] = v.pVector[i] - val;
	return v;
}

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val){
	TVector<ValType> v(*this);
	for (int i = 0; i < Size; i++)
		v.pVector[i] = v.pVector[i] * val;
	return v;
}

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v){
	if (Size != v.Size) 
		throw Size - v.Size;
	TVector<ValType> w(Size);
	for (int i = 0; i < Size; i++)
		w.pVector[i] = pVector[i] + v.pVector[i];
	return w;
}

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v){
	if (Size != v.Size)
		throw Size - v.Size;
	TVector<ValType> w(Size);
	for (int i = 0; i < Size; i++)
		w.pVector[i] = pVector[i] - v.pVector[i];
	return w;
}

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v){
	if (Size != v.Size)
		throw Size - v.Size;
	int sum = 0;
	for (int i = 0; i < Size; i++)
		sum += pVector[i] * v.pVector[i];
	return sum;
}


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType>>
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int _Size):TVector<TVector<ValType>>(_Size){
	if (_Size > MAX_MATRIX_SIZE)
		throw "large index";
	if (_Size < 0)
		throw "negative length";
	for (int i = 0; i < _Size; i++)
		pVector[i] = TVector<ValType>(_Size - i, i);
}

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):TVector<TVector<ValType>>(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):TVector<TVector<ValType>>(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt)const{
	return TVector<TVector<ValType>>::operator==(mt);
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const{
	return TVector<TVector<ValType>>::operator!=(mt);
} 

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt){
	TVector<TVector<ValType>>::operator=(mt);
	return *this;
} 

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt){
	if (Size == mt.Size)
		return TVector<TVector<ValType>>::operator+(mt);
	else
		throw Size - mt.Size;
} 

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt){
	if (Size == mt.Size)
		return TVector<TVector<ValType>>::operator-(mt);
	else
		throw Size - mt.Size;
}

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
