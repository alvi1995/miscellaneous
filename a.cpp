#include <iostream>
#include <iomanip>

using namespace std;

template<class T>
inline const T &MIN(const T &a, const T &b)
        {return b < a ? (b) : (a);}

inline float MIN(const double &a, const float &b)
        {return b < a ? (b) : float(a);}

inline float MIN(const float &a, const double &b)
        {return b < a ? float(b) : (a);}

template<class T>
inline const T &MAX(const T &a, const T &b)
        {return b > a ? (b) : (a);}

inline float MAX(const double &a, const float &b)
        {return b > a ? (b) : float(a);}

inline float MAX(const float &a, const double &b)
        {return b > a ? float(b) : (a);}

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
class bandMatrix {
private:
	int nn, mm;
	T **v;
	int *d;
public:
	bandMatrix();
	bandMatrix(int n, int m, const T *a, const int *diag_indx);	// Initialize to array
	bandMatrix(const bandMatrix &rhs);		// Copy constructor
	bandMatrix &operator=(const bandMatrix &rhs);	//assignment
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
bandMatrix<T>::bandMatrix() : nn(0), mm(0), v(NULL), d(NULL) {}

template <class T>
bandMatrix<T>::bandMatrix(int n, int m, const T *a, const int *diag_indx) : nn(n), mm(m), v(n>0 ? new T*[n] : NULL), d(mm>0 ? new int[mm] : NULL)
{
	int i,j,k = 0,nel=m*n, step, ar = m;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1; i< n; i++) v[i] = v[i-1] + m;
	for (i = 0; i < m; i++) d[i] = diag_indx[i];
	

	for  (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			if (d[i] < 0){
				if (j < abs(d[i])){
					v[j][i] = 0.;
				} else {
					v[j][i] = a[k];
					k++;
				}
			}
			else if (d[i] > 0){
				if (j < n-abs(d[i])){
					v[j][i] = a[k];
					k++;
				} else {
					v[j][i] = 0.;
				}
			} else {
				v[j][i] = a[k];
				k++;
			}	
		}
	}
}

template <class T>
bandMatrix<T>::bandMatrix(const bandMatrix &rhs) : nn(rhs.nn), mm(rhs.mm), v(nn>0 ? new T*[nn] : NULL), d(mm>0 ? new int[mm] : NULL)
{
	int i,j,nel=mm*nn;
	if (v) v[0] = nel>0 ? new T[nel] : NULL;
	for (i=1; i< nn; i++) v[i] = v[i-1] + mm;
	for (i=0; i< nn; i++) for (j=0; j<mm; j++) v[i][j] = rhs[i][j];
	for (i = 0; i < mm; i++) d[i] = rhs.d[i];
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
	if (d != NULL)
	{
		delete []d;
	}
	
}

template<class T>
ostream& operator<<(ostream &o, bandMatrix<T> mat)
{
	for (int i = 0; i < mat.nrows(); i++)
	{
		for (int j = 0; j < mat.ncols(); j++)
		{
			o << right << setw(15) << mat[i][j] << "\t";
		}
		o << "\n";
	}
	return o;
}

// void banmul(bandMatrix<double> &a, const int m1, const int m2, Vector<double> &x, Vector<double> &b)
// {
// 	int i,j,k,tmploop,n=a.nrows();
// 	for (i=0;i<n;i++) {
// 		k=i-m1;
// 		tmploop=MIN(m1+m2+1, int(n-k));
// 		b[i]=0.0;
// 		for (j=MAX(0,-k);j<tmploop;j++) b[i] += a[i][j]*x[j+k];
// 	}
// }

void banmul(bandMatrix<double> &a, Vector<double> &x, Vector<double> &b)
{
	int i, j, n = a.nrows();
	for (i = 0; i < n; i++)
	{
		
	}
	
}

void banmul(bandMatrix<double> &a, Vector<double> &x, Vector<double> &b)
{
	int i,j,k = 0,loopStart,loopEnd,n=a.nrows();
	for (i = 0; a.diag_indx(i) < 0; i++) {	}
	int m1 = i, m2 = a.no_diag() - 1 - m1;

	for (i = 0; i < n; i++)
	{
		b[i] = 0.0;
		loopStart = (i < m1 ? abs(a.diag_indx(i)) : 0);
		loopEnd = i+m2 < n ? a.no_diag() : (a.no_diag()-(n-(i+m2)));
		for (j = loopStart; j < loopEnd; j++)
		{
			b[i] = b[i] + a[i][j]*x[j];
		}
	}
}

int main()
{
    double element[] = { -2,   1,   3,   2,  -1,   2,
                          1,   2,   4,   3,  -1,  -2,   2,
                         -1,   1,   1,   2,  -1,   4,
                          3,   1,   2,  -3,   5				};

    int diag_indx[] = { -1, 0, 1, 2 };

    const int M1=1,  M2=2,   NP=7,  MP=(M1+1+M2);
    int i,  j,  k;
    Vector<double> b(NP),   x(NP);

    for (i=0;i<NP;i++) x[i]=(i+1)/10.0;

    bandMatrix<double> bm(7,sizeof(diag_indx)/sizeof(int),element,diag_indx);
    cout << bm << endl;
    banmul(bm,x,b);

	cout << x << endl;
	cout << b << endl;
	bandMatrix<double> cm(bm);

	cout << "ok" << endl;
    return 0;
}
