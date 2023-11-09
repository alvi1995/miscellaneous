#ifndef TYPE_H
#define TYPE_H

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>

using namespace std;
typedef unsigned int ui;

template <class T>
class Vector
{
private:
	int ne;	// size of array. upper index is nn-1
	T* v;
public:
	Vector();
	explicit Vector(ui n);		// Zero-based array
	Vector(ui n, const T& a);	//initialize to constant value
	Vector(ui n, const T* a);	// Initialize to array
	Vector(const Vector& rhs);	// Copy constructor
	Vector& operator=(const Vector& rhs);	//assignment
	typedef T value_type; // make T available externally
	inline T& operator[](const ui i);	//i'th element
	inline const T& operator[](const ui i) const;
	inline int size() const;
	void resize(ui newn); // resize (contents not preserved)
	void assign(ui newn, const T& a); // resize and assign a constant value
	void interchange(ui i1, ui i2);
	template<typename U>
	friend ostream& operator<<(ostream& o, Vector<U>& vec);
	~Vector();
};

template <class T>
Vector<T>::Vector() : ne(0), v(NULL) {}

template <class T>
Vector<T>::Vector(ui n) : ne(n), v(n > 0 ? new T[n] : NULL) {}

template <class T>
Vector<T>::Vector(ui n, const T& a) : ne(n), v(n > 0 ? new T[n] : NULL)
{
	for (int i = 0; i < n; i++) v[i] = a;
}

template <class T>
Vector<T>::Vector(ui n, const T* a) : ne(n), v(n > 0 ? new T[n] : NULL)
{
	for (int i = 0; i < n; i++) v[i] = *a++;
}

template <class T>
Vector<T>::Vector(const Vector<T>& rhs) : ne(rhs.ne), v(ne > 0 ? new T[ne] : NULL)
{
	for (int i = 0; i < ne; i++) v[i] = rhs[i];
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
	if (this != &rhs)
	{
		if (ne != rhs.ne)
		{
			if (v != NULL) delete[](v);
			ne = rhs.ne;
			v = ne > 0 ? new T[ne] : NULL;
		}
		for (int i = 0; i < ne; i++)
		{
			v[i] = rhs[i];
		}
	}
	return *this;
}

template <class T>
inline T& Vector<T>::operator[](const ui i)	//subscripting
{

	return v[i];
}

template <class T>
inline const T& Vector<T>::operator[](const ui i) const	//subscripting
{
	return v[i];
}

template <class T>
inline int Vector<T>::size() const
{
	return ne;
}

template <class T>
void Vector<T>::resize(ui newn)
{
	if (newn != ne)
	{
		if (v != NULL) delete[](v);
		ne = newn;
		v = ne > 0 ? new T[ne] : NULL;
	}
}

template <class T>
void Vector<T>::assign(ui newn, const T& a)
{
	if (newn != ne)
	{
		if (v != NULL) delete[](v);
		ne = newn;
		v = ne > 0 ? new T[ne] : NULL;
	}
	for (int i = 0; i < ne; i++) v[i] = a;
}

template <class T>
void Vector<T>::interchange(ui i1, ui i2)
{
	ui big = 0;
	big = v[i1];
	v[i1] = v[i2];
	v[i2] = big;
}

template<typename T>
ostream& operator<<(ostream& o, Vector<T>& vec)
{
	for (ui i = 0; i < vec.ne; i++)
	{
		o << std::setw(15) << vec[i] << "\n";
	}
	o << endl;
	return o;
}

template <class T>
Vector<T>::~Vector()
{
	if (v != NULL) delete[](v);
}

template <typename T>
class Matrix {
private:
	ui r;
	ui c;
	T** m;
public:
	Matrix();
	Matrix(ui nr, ui mc);			// Zero-based array
	Matrix(ui nr, ui mc, const T& a);	//Initialize to constant
	Matrix(ui nr, ui mc, const T* a);	// Initialize to array
	void Eye();
	Matrix(const Matrix& rhs);		// Copy constructor
	Matrix& operator=(const Matrix& rhs);	//assignment
	typedef T value_type; // make T available externally
	inline T* operator[](const ui i);	//subscripting: pointer to row i
	inline const T* operator[](const ui i) const;
	inline ui nrows() const;
	inline ui ncols() const;
	void resize(ui newr, ui newc); // resize (contents not preserved)
	void assign(ui newr, ui newc, const T& a); // resize and assign a constant value
	void row_exchange(ui r1, ui r2);
	void column_exchange(ui c1, ui c2);
	template<typename U>
	friend ostream& operator<<(ostream& o, Matrix<U>& mat);
	~Matrix();
};

template <typename T>
Matrix<T>::Matrix() : r(0), c(0), m(NULL) {}

template <typename T>
Matrix<T>::Matrix(ui nr, ui mc) : r(nr), c(mc), m(r > 0 ? new T * [nr] : NULL)
{
	int i, nel = nr * mc;
	if (m) m[0] = nel > 0 ? new T[nel] : NULL;
	for (i = 1; i < nr; i++) m[i] = m[i - 1] + mc;
}

template <typename T>
Matrix<T>::Matrix(ui nr, ui mc, const T& a) : r(nr), c(mc), m(r > 0 ? new T * [nr] : NULL)
{
	int i, j, nel = nr * mc;
	if (m) m[0] = nel > 0 ? new T[nel] : NULL;
	for (i = 1; i < nr; i++) m[i] = m[i - 1] + mc;
	for (i = 0; i < nr; i++) for (j = 0; j < mc; j++) m[i][j] = a;
}

template <typename T>
Matrix<T>::Matrix(ui nr, ui mc, const T* a) : r(nr), c(mc), m(r > 0 ? new T * [nr] : NULL)
{
	int i, j, nel = nr * mc;
	if (m) m[0] = nel > 0 ? new T[nel] : NULL;
	for (i = 1; i < nr; i++) m[i] = m[i - 1] + mc;
	for (i = 0; i < nr; i++) for (j = 0; j < mc; j++) m[i][j] = *a++;
}

template <typename T>
void Matrix<T>::Eye()
{
	for (ui i = 0; i < r; i++)
	{
		for (ui j = 0; j < c; j++)
		{
			m[i][j] = i == j ? 1 : 0;
		}
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix& rhs) : r(rhs.r), c(rhs.c), m(r > 0 ? new T * [r] : NULL)
{
	int i, j, nel = r * c;
	if (m) m[0] = nel > 0 ? new T[nel] : NULL;
	for (i = 1; i < r; i++) m[i] = m[i - 1] + c;
	for (i = 0; i < r; i++) for (j = 0; j < c; j++) m[i][j] = rhs[i][j];
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
	if (this != &rhs)
	{
		int i, j, nel;
		if (r != rhs.r || c != rhs.c)
		{
			if (m != NULL)
			{
				delete[](m[0]);
				delete[](m);
			}
			r = rhs.r;
			c = rhs.c;
			m = r > 0 ? new T * [r] : NULL;
			nel = r * c;
			if (m) m[0] = nel > 0 ? new T[nel] : NULL;
			for (i = 1; i < r; i++) m[i] = m[i - 1] + c;
		}
		for (i = 0; i < r; i++) for (j = 0; j < c; j++) m[i][j] = rhs[i][j];
	}
	return *this;
}

template <typename T>
inline T* Matrix<T>::operator[](const ui i)	//subscripting: pointer to row i
{
	return m[i];
}

template <typename T>
inline const T* Matrix<T>::operator[](const ui i) const
{
	return m[i];
}

template <typename T>
inline ui Matrix<T>::nrows() const
{
	return r;
}

template <typename T>
inline ui Matrix<T>::ncols() const
{
	return c;
}

template <typename T>
void Matrix<T>::resize(ui newr, ui newc)
{
	ui i, nel;
	if (newr != r || newc != c)
	{
		if (m != NULL)
		{
			delete[](m[0]);
			delete[](m);
		}
		r = newr;
		c = newc;
		m = r > 0 ? new T * [r] : NULL;
		nel = r * c;
		if (m) m[0] = nel > 0 ? new T[nel] : NULL;
		for (i = 1; i < r; i++) m[i] = m[i - 1] + c;
	}
}

template <typename T>
void Matrix<T>::assign(ui newr, ui newc, const T& a)
{
	int i, j, nel;
	if (newr != r || newc != c)
	{
		if (m != NULL)
		{
			delete[](m[0]);
			delete[](m);
		}
		r = newr;
		c = newc;
		m = r > 0 ? new T * [r] : NULL;
		nel = r * c;
		if (m) m[0] = nel > 0 ? new T[nel] : NULL;
		for (i = 1; i < r; i++) m[i] = m[i - 1] + c;
	}
	for (i = 0; i < r; i++) for (j = 0; j < c; j++) m[i][j] = a;
}

template <typename T>
void Matrix<T>::row_exchange(ui r1, ui r2)
{
    double temp = 0.;
    for (ui i = 0; i < c; i++)
    {
        temp = m[r1][i];
        m[r1][i] = m[r2][i];
        m[r2][i] = temp;
    }
}

template <typename T>
void Matrix<T>::column_exchange(ui c1, ui c2)
{
    double temp = 0.;
    for (ui i = 0; i < r; i++)
    {
        temp = m[i][c1];
        m[i][c1] = m[i][c2];
        m[i][c2] = temp;
    }
}

template <typename T>
Matrix<T>::~Matrix()
{
	if (m != NULL)
	{
		delete[](m[0]);
		delete[](m);
	}
}

template<typename T>
ostream& operator<<(ostream& o, Matrix<T>& mat)
{
	o << std::fixed << std::setprecision(4);
	for (ui i = 0; i < mat.r; i++)
	{
		for (ui j = 0; j < mat.c; j++)
		{
			o << std::setw(15) << mat[i][j];
		}
		o << endl;
	}

	return o;
}

#endif