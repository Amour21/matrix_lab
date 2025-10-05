// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz= 0;
  T* pMem = nullptr;
public:
  TDynamicVector() : sz(0), pMem(nullptr) {}
  explicit TDynamicVector(size_t size ) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (size >= MAX_VECTOR_SIZE) throw out_of_range("VECTOR TOO LARGE");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz (v.sz), pMem (new T[v.sz])
  {
      for (size_t i = 0; i < sz; ++i) pMem[i] = v.pMem[i];
  }
  T* data() {
      return pMem;
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    pMem = v.data (); 
    sz = v.size (); 
    v.sz = 0;
    v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this;
      T* newMem = new T[v.sz];
      for (size_t i = 0; i < v.sz; i++)
          newMem[i] = v.pMem[i];
      delete[] pMem;
      pMem = newMem;
      sz = v.sz;
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v) return *this;
      delete[] pMem;
      pMem = v.pMem;
      sz = v.sz;
      v.pMem = nullptr;
      v.sz = 0;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz || ind < 0) throw out_of_range("ERROR IND");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz || ind < 0) throw out_of_range("ERROR IND");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] + val;
      }
      return res;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - val;
      }
      return res;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] * val;
      }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw std::out_of_range("ERROR VECTORS SIZE NOT EQUAL");
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] + v.pMem[i];
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw std::out_of_range("ERROR VECTORS SIZE NOT EQUAL");
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - v.pMem[i];
      }
      return res;
  }
  T operator*(const TDynamicVector& v) 
  {
      if (sz != v.sz) throw std::out_of_range("ERROR VECTORS SIZE NOT EQUAL");
      T res=0;
      for (size_t i = 0; i < sz; i++) {
          res += pMem[i]*v.pMem[i];
      }
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }
  
  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};
template<typename T>
std::istream& operator>>(std::istream& is, TDynamicVector<T>& value) {
    is >> value;
    return is;
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const TDynamicVector<T>& value) {
    return os << value << " ";
}

// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:

  explicit  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {   
        if (s == 0 || s > MAX_MATRIX_SIZE) throw out_of_range("NOT CORRECT SIZE MATRIX");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }
   
    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::at;
    using TDynamicVector<TDynamicVector<T>>::size;
    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                if (pMem[i][j] != m.pMem[i][j]) return false;
            }
        }
        return true;
    }

    // матрично-скалярные операции
    TDynamicMatrix<T> operator*(const T& val) const
    {
        TDynamicMatrix res(*this);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                res[i][j] *= val;
            }
        }
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size()) throw std::out_of_range("ERROR SIZE CAN'T MUL VEC AND MATRIX");
        TDynamicVector<T> res(v.size());
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                res[i] += pMem[i][j] * v[j];
            }
        }
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        TDynamicMatrix res(sz);
        if (sz != m.sz) throw std::out_of_range("ERROR SIZE CAN'T ADD MATRIX AND MATRIX");
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                res[i][j] = pMem[i][j] + m.pMem[i][j];
            }
        }
        return res;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        TDynamicMatrix res(sz);
        if (sz != m.sz) throw std::out_of_range("ERROR SIZE CAN'T DIFF MATRIX AND MATRIX");
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                res[i][j] = pMem[i][j] - m.pMem[i][j];
            }
        }
        return res;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m) const
    {
        if (sz != m.sz) throw std::out_of_range("ERROR SIZE CAN'T MUL MATRIX AND MATRIX");
        TDynamicMatrix res(sz); 
        #pragma omp parallel for schedule(static)  // параллелизм по i (строки независимы)
        for (size_t i = 0; i < sz; ++i) {
            for (size_t k = 0; k < sz; ++k) {
                const T tmp = pMem[i][k];          // для чтения единожды
                #pragma omp simd                   // векторизация цикла по j
                for (size_t j = 0; j < sz; ++j) {
                    res[i][j] += tmp * m.pMem[k][j];
                }
            }
        }
        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; 
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << '\n';
        return ostr;
    }
#endif
};