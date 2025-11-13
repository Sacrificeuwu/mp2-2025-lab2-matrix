// MyMStrix.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0 || size > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size should be greater than zero");
        pMem = new T[sz]();
        if (pMem == nullptr) {
            throw std::string("No memory allocated");
        }
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        //assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v) : sz(v.sz), pMem(nullptr)
    {
        if (sz > 0) {
            pMem = new T[sz];
            std::copy(v.pMem, v.pMem + sz, pMem);
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
    {
        v.sz = 0;
        v.pMem = nullptr;
    }
    ~TDynamicVector()
    {
        delete[] pMem;
        pMem = nullptr;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {
            TDynamicVector temp(v); 
            this->swap(temp);     
        }                          
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            TDynamicVector temp(std::move(v)); 
            this->swap(temp);                  
        }
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
        if (ind <= sz) return pMem[ind];
        throw std::string("Index out of range");
    }
    const T& at(size_t ind) const
    {
        if (ind <= sz) return pMem[ind];
        throw std::string("Index out of range");
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz == v.sz) {
            for (int i = 0; i < sz; ++i) {
                if !(*this == v) return false;
            }
            return true;
        }
        return false;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (sz == v.sz) {
            for (int i = 0; i < sz; ++i) {
                if (pMem[i] != v.pMem[i]) return true;
            }
            return false;
        }
        return true;
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] + val;
        }
        return res;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] - val;
        }
        return res;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] * val;
        }
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw std::string("LOGIC ERROR");
        }
        TDynamicVector<T> res(*this);
        for (int i = 0; i < sz; i++) {
            res.pMem[i] += v.pMem[i];
        }
        return res;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        TDynamicVector<T> res(*this);
        if (res.sz != v.sz) {
            throw std::string("LOGIC ERROR");
        }
        for (int i = 0; i < sz; i++) {
            res.pMem[i] -= v.pMem[i];
        }
        return res;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        T sum = T();
        if (this->sz != v.sz) {
            return sum;
        }
        for (int i = 0; i < sz; i++) {
            sum += pMem[i] * v.pMem[i];
        }
        return sum;
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
    friend std::ostream& operator<<(std::ostream& os, const TDynamicVector<T>& v)
    {
        os << "[";
        for (size_t i = 0; i < v.sz; ++i) {
            os << v.pMem[i];
            if (i != v.sz - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
};

template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  { 
      if (s > MAX_MATRIX_SIZE) {
          throw std::string("ERROR");
      }
      for (size_t i = 0; i < s; i++) {
          (*this)[i] = TDynamicVector<T>(s);
      }
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      for (int i = 0; i < sz; ++i) {
          for (int j = 0; j < sz; j++) {
              if (pMem[i][j] != m.pMem[i][j]) {
                  return false;
              }
          }
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
        TDynamicMatrix<T> res(sz);
        if (sz != v.sz) {
            throw std::string("LOGIC ERROR")
        }
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; j++) {
                res.pMem[i][j] = pMem[i][j] * val;
            }
        }
      
        return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicVector<T> res(sz);
      if (sz != v.sz) {
          throw std::string("LOGIC ERROR")
      }
      for (int i = 0; i < sz; ++i) {
          T sum = T();
          for (int j = 0; j < sz; j++) {
              sum += pMem[i][j] * v[j];
          }
          res[i] = sum;
      }
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> res(sz);
      if (sz != m.sz) {
          throw std::string("LOGIC ERROR");
      }
      for (int i = 0; i < sz; ++i) {
          for (int j = 0; j < sz; j++) {
              res.pMem[i][j] = pMem[i][j] + m.pMem[i][j];
          }
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> res(sz);
      if (sz != m.sz) {
          throw std::string("LOGIC ERROR");
      }
      for (int i = 0; i < sz; ++i) {
          for (int j = 0; j < sz; j++) {
              res.pMem[i][j] = pMem[i][j] - m.pMem[i][j];
          }
      }
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> res(sz);
      if (sz != v.sz) {
          throw std::string("LOGIC ERROR")
      }
      for (int i = 0; i < sz; ++i) {
          for (int j = 0; j < sz; j++) {
              T sum = T();
              for (int k = 0; k < sz; k++) {
                  sum += pMem[i][k] * m.pMem[k][j];
              }
              res.pMem[i][j] = sum;
          }
      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; i++) {
          for (size_t j = 0; j < m.sz; j++) {
              istr >> m.pMem[i][j];
          }
      }
      return istr;
  }
  friend ostream& operator<<(ostream& os, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; ++i) {
          os << v[i] << std::endl;
      }

      return os;
  }
};

#endif
