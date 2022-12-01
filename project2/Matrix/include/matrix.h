#include <fstream>
#include <cmath>
#include <complex>
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

using namespace std;

// macro-like inline functions

template<class T>
inline T SQR(const T a) {return a*a;}

template<class T>
inline const T &MAX(const T &a, const T &b)
        {return b > a ? (b) : (a);}

inline float MAX(const double &a, const float &b)
        {return b > a ? (b) : float(a);}

inline float MAX(const float &a, const double &b)
        {return b > a ? float(b) : (a);}

template<class T>
inline const T &MIN(const T &a, const T &b)
        {return b < a ? (b) : (a);}

inline float MIN(const double &a, const float &b)
        {return b < a ? (b) : float(a);}

inline float MIN(const float &a, const double &b)
        {return b < a ? float(b) : (a);}

template<class T>
inline T SIGN(const T &a, const T &b)
	{return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);}

inline float SIGN(const float &a, const double &b)
	{return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);}

inline float SIGN(const double &a, const float &b)
	{return (float)(b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a));}

template<class T>
inline void SWAP(T &a, T &b)
	{T dum=a; a=b; b=dum;}

// exception handling

#define throw(message) \
{printf("ERROR: %s\n     in file %s at line %d\n", message,__FILE__,__LINE__); throw(1);}


template <class T>
class Vector {
private:
	int nn;	// size of array. upper index is nn-1
	T *v;
public:
	Vector();
	explicit Vector(int n);		// Zero-based array
	Vector(int n, const T &a);	//initialize to constant value
	Vector(int n, const T *a);	// Initialize to array
	Vector(const Vector &rhs);	// Copy constructor
	Vector & operator=(const Vector &rhs);	//assignment
	typedef T value_type; // make T available externally
	inline T & operator[](const int i)
    {
        #ifdef _CHECKBOUNDS_
        if (i<0 || i>=nn) {
	        throw("Vector subscript out of bounds");
        }
        #endif
	        return v[i];
    }	//i'th element
	inline const T & operator[](const int i) const
    {
        #ifdef _CHECKBOUNDS_
        if (i<0 || i>=nn) {
	        throw("Vector subscript out of bounds");
        }
        #endif
	        return v[i];
    }
	inline int size() const
    {
        return nn;
    }
	void resize(int newn); // resize (contents not preserved)
	void assign(int newn, const T &a); // resize and assign a constant value
	template<class U>
	friend ostream& operator<<(ostream &o, Vector<U> vec);
	~Vector();
};

template <class T>
Vector<T>::Vector() : nn(0), v(NULL) {}

template <class T>
Vector<T>::Vector(int n) : nn(n), v(n>0 ? new T[n] : NULL) {}

template <class T>
Vector<T>::Vector(int n, const T& a) : nn(n), v(n>0 ? new T[n] : NULL)
{
	for(int i=0; i<n; i++) v[i] = a;
}

template <class T>
Vector<T>::Vector(int n, const T *a) : nn(n), v(n>0 ? new T[n] : NULL)
{
	for(int i=0; i<n; i++) v[i] = *a++;
}

template <class T>
Vector<T>::Vector(const Vector<T> &rhs) : nn(rhs.nn), v(nn>0 ? new T[nn] : NULL)
{
	for(int i=0; i<nn; i++) v[i] = rhs[i];
}

template <class T>
Vector<T> & Vector<T>::operator=(const Vector<T> &rhs)
// postcondition: normal assignment via copying has been performed;
//		if vector and rhs were different sizes, vector
//		has been resized to match the size of rhs
{
	if (this != &rhs)
	{
		if (nn != rhs.nn) {
			if (v != NULL) delete [] (v);
			nn=rhs.nn;
			v= nn>0 ? new T[nn] : NULL;
		}
		for (int i=0; i<nn; i++)
			v[i]=rhs[i];
	}
	return *this;
}

template <class T>
Vector<T>::~Vector()
{
	if (v != NULL) delete[] (v);
}

template<class T>
ostream& operator<<(ostream &o, Vector<T> vec)
{
	for (int i = 0; i < vec.nn; i++)
	{
		o << vec[i] << "\t";
	}

	return o;
}

template <class T>
class Matrix {
private:
	int nn;
	int mm;
	T **v;
public:
	Matrix();
	Matrix(int n, int m);			// Zero-based array
	Matrix(int n, int m, const T &a);	//Initialize to constant
	Matrix(int n, int m, const T *a);	// Initialize to array
	Matrix(const Matrix &rhs);		// Copy constructor
	Matrix & operator=(const Matrix &rhs);	//assignment
	typedef T value_type; // make T available externally
	inline T* operator[](const int i)	//subscripting: pointer to row i
    {
        #ifdef _CHECKBOUNDS_
        if (i<0 || i>=nn) {
	        throw("Matrix subscript out of bounds");
        }
        #endif
	        return v[i];
    }
	inline const T* operator[](const int i) const
    {
        #ifdef _CHECKBOUNDS_
        if (i<0 || i>=nn) {
	        throw("Matrix subscript out of bounds");
        }
        #endif
	        return v[i];
    }
	inline int nrows() const
    {
	    return nn;
    }
	inline int ncols() const
    {
	    return mm;
    }
	void resize(int newn, int newm); // resize (contents not preserved)
	void assign(int newn, int newm, const T &a); // resize and assign a constant value
	template <class U>
	friend ostream& operator<<(ostream &o, Matrix<U> mat);
	~Matrix();
};

template <class T>
Matrix<T>::Matrix() : nn(0), mm(0), v(NULL) {}

template <class T>
Matrix<T>::Matrix(int n, int m) : nn(n), mm(m), v(n>0 ? new T*[n] : NULL)
{
	int i,nel=m*n;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1;i<n;i++) v[i] = v[i-1] + m;
}

template <class T>
Matrix<T>::Matrix(int n, int m, const T &a) : nn(n), mm(m), v(n>0 ? new T*[n] : NULL)
{
	int i,j,nel=m*n;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1; i< n; i++) v[i] = v[i-1] + m;
	for (i=0; i< n; i++) for (j=0; j<m; j++) v[i][j] = a;
}

template <class T>
Matrix<T>::Matrix(int n, int m, const T *a) : nn(n), mm(m), v(n>0 ? new T*[n] : NULL)
{
	int i,j,nel=m*n;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1; i< n; i++) v[i] = v[i-1] + m;
	for (i=0; i< n; i++) for (j=0; j<m; j++) v[i][j] = *a++;
}

template <class T>
Matrix<T>::Matrix(const Matrix &rhs) : nn(rhs.nn), mm(rhs.mm), v(nn>0 ? new T*[nn] : NULL)
{
	int i,j,nel=mm*nn;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1; i< nn; i++) v[i] = v[i-1] + mm;
	for (i=0; i< nn; i++) for (j=0; j<mm; j++) v[i][j] = rhs[i][j];
}

template <class T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> &rhs)
{
	if (this != &rhs) {
		int i,j,nel;
		if (nn != rhs.nn || mm != rhs.mm) {
			if (v != NULL) {
				delete[] (v[0]);
				delete[] (v);
			}
			nn=rhs.nn;
			mm=rhs.mm;
			v = nn>0 ? new T*[nn] : NULL;
			nel = mm*nn;
			if (v) v[0] = nel>0 ? new T[nel] : NULL;
			for (i=1; i< nn; i++) v[i] = v[i-1] + mm;
		}
		for (i=0; i< nn; i++) for (j=0; j<mm; j++) v[i][j] = rhs[i][j];
	}
	return *this;
}

template <class T>
void Matrix<T>::resize(int newn, int newm)
{
	int i,nel;
	if (newn != nn || newm != mm) {
		if (v != NULL) {
			delete[] (v[0]);
			delete[] (v);
		}
		nn = newn;
		mm = newm;
		v = nn>0 ? new T*[nn] : NULL;
		nel = mm*nn;
		if (v) v[0] = nel>0 ? new T[nel] : NULL;
		for (i=1; i< nn; i++) v[i] = v[i-1] + mm;
	}
}

template <class T>
void Matrix<T>::assign(int newn, int newm, const T& a)
{
	int i,j,nel;
	if (newn != nn || newm != mm) {
		if (v != NULL) {
			delete[] (v[0]);
			delete[] (v);
		}
		nn = newn;
		mm = newm;
		v = nn>0 ? new T*[nn] : NULL;
		nel = mm*nn;
		if (v) v[0] = nel>0 ? new T[nel] : NULL;
		for (i=1; i< nn; i++) v[i] = v[i-1] + mm;
	}
	for (i=0; i< nn; i++) for (j=0; j<mm; j++) v[i][j] = a;
}

template <class T>
Matrix<T>::~Matrix()
{
	if (v != NULL) {
		delete[] (v[0]);
		delete[] (v);
	}
}


template<class T>
ostream& operator<<(ostream &o, Matrix<T> mat)
{
	for (int i = 0; i < mat.nrows(); i++)
	{
		for (int j = 0; j < mat.ncols(); j++)
		{
			o << mat[i][j] << "\t";
		}
		o << "\n";
	}

	return o;
}

// 2   1   0   0   0   0   0   0   0   0           1
// 1   3   2   0   0   0   0   0   0   0           2
// 0   1   3   1   0   0   0   0   0   0           6
// 0   0   7   2   6   0   0   0   0   0          34
// 0   0   0   6   2   1   0   0   0   0          10
// 0   0   0   0   3   4   3   0   0   0           1
// 0   0   0   0   0   8   1   5   0   0           4
// 0   0   0   0   0   0   6   2   7   0          22
// 0   0   0   0   0   0   0   5   4   3          25
// 0   0   0   0   0   0   0   0   4   5           3

template <class T>
class bandMatrix {
private:
	int nn;
	int mm;
	T **v;
public:
	bandMatrix();
	bandMatrix(int n, int m, const T *a, const int *pos_indx);	// Initialize to array
	bandMatrix(const bandMatrix &rhs);		// Copy constructor
	bandMatrix & operator=(const bandMatrix &rhs);	//assignment
	inline T* operator[](const int i)	//subscripting: pointer to row i
    {
	    return v[i];
    }
	inline const T* operator[](const int i) const
    {
	    return v[i];
    }
	inline int nrows() const
    {
	    return nn;
    }
	inline int ncols() const
    {
	    return mm;
    }
	template <class U>
	friend ostream& operator<<(ostream &o, bandMatrix<U> mat);
	~bandMatrix();
};

template <class T>
bandMatrix<T>::bandMatrix() : nn(0), mm(0), v(NULL) {}

template <class T>
bandMatrix<T>::bandMatrix(int n, int m, const T *a, const int *pos_indx) : nn(n), mm(m), v(n>0 ? new T*[n] : NULL)
{
	int i,j,k = 0,nel=m*n;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1; i< n; i++) v[i] = v[i-1] + m;
	for (i=0; i< n; i++) for (j=0; j<m; j++) v[i][j] = *a++;

	for (i = 0; i < m; i++)
	{
		if (pos_indx[i] < 0)
		{
			for (j = abs(pos_indx[i]); j < nn; j++, k++)
			{
				v[j][i] = a[k] + n;
			}
			
		} else if (pos_indx[i] > 0)
		{
			for (j = 0; j < n - abs(pos_indx[i]); j++)
			{
				/* code */
			}
			
		} else
		{
			
		}
		
		
		
	}
	
}

template <class T>
bandMatrix<T>::bandMatrix(const bandMatrix &rhs) : nn(rhs.nn), mm(rhs.mm), v(nn>0 ? new T*[nn] : NULL)
{
	int i,j,nel=mm*nn;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1; i< nn; i++) v[i] = v[i-1] + mm;
	for (i=0; i< nn; i++) for (j=0; j<mm; j++) v[i][j] = rhs[i][j];
}

template <class T>
bandMatrix<T> & bandMatrix<T>::operator=(const bandMatrix<T> &rhs)
{
	if (this != &rhs) {
		int i,j,nel;
		if (nn != rhs.nn || mm != rhs.mm) {
			if (v != NULL) {
				delete[] (v[0]);
				delete[] (v);
			}
			nn=rhs.nn;
			mm=rhs.mm;
			v = nn>0 ? new T*[nn] : NULL;
			nel = mm*nn;
			if (v) v[0] = nel>0 ? new T[nel] : NULL;
			for (i=1; i< nn; i++) v[i] = v[i-1] + mm;
		}
		for (i=0; i< nn; i++) for (j=0; j<mm; j++) v[i][j] = rhs[i][j];
	}
	return *this;
}

template <class T>
bandMatrix<T>::~bandMatrix()
{
	if (v != NULL) {
		delete[] (v[0]);
		delete[] (v);
	}
}


template<class T>
ostream& operator<<(ostream &o, bandMatrix<T> mat)
{
	for (int i = 0; i < mat.nrows(); i++)
	{
		for (int j = 0; j < mat.ncols(); j++)
		{
			o << mat[i][j] << "\t";
		}
		o << "\n";
	}

	return o;
}