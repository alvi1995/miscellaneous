#include <iostream>
#include <iomanip>
#include <fstream>
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
	T** v;
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
	template<typename U>
	friend ostream& operator<<(ostream& o, Matrix<U>& mat);
	~Matrix();
};

template <typename T>
Matrix<T>::Matrix() : r(0), c(0), v(NULL) {}

template <typename T>
Matrix<T>::Matrix(ui nr, ui mc) : r(nr), c(mc), v(r > 0 ? new T * [nr] : NULL)
{
	int i, nel = nr * mc;
	if (v) v[0] = nel > 0 ? new T[nel] : NULL;
	for (i = 1; i < nr; i++) v[i] = v[i - 1] + mc;
}

template <typename T>
Matrix<T>::Matrix(ui nr, ui mc, const T& a) : r(nr), c(mc), v(r > 0 ? new T * [nr] : NULL)
{
	int i, j, nel = nr * mc;
	if (v) v[0] = nel > 0 ? new T[nel] : NULL;
	for (i = 1; i < nr; i++) v[i] = v[i - 1] + mc;
	for (i = 0; i < nr; i++) for (j = 0; j < mc; j++) v[i][j] = a;
}

template <typename T>
Matrix<T>::Matrix(ui nr, ui mc, const T* a) : r(nr), c(mc), v(r > 0 ? new T * [nr] : NULL)
{
	int i, j, nel = nr * mc;
	if (v) v[0] = nel > 0 ? new T[nel] : NULL;
	for (i = 1; i < nr; i++) v[i] = v[i - 1] + mc;
	for (i = 0; i < nr; i++) for (j = 0; j < mc; j++) v[i][j] = *a++;
}

template <typename T>
void Matrix<T>::Eye()
{
	for (ui i = 0; i < r; i++)
	{
		for (ui j = 0; j < c; j++)
		{
			v[i][j] = i == j ? 1 : 0;
		}
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix& rhs) : r(rhs.r), c(rhs.c), v(r > 0 ? new T * [r] : NULL)
{
	int i, j, nel = r * c;
	if (v) v[0] = nel > 0 ? new T[nel] : NULL;
	for (i = 1; i < r; i++) v[i] = v[i - 1] + c;
	for (i = 0; i < r; i++) for (j = 0; j < c; j++) v[i][j] = rhs[i][j];
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
	if (this != &rhs)
	{
		int i, j, nel;
		if (r != rhs.r || c != rhs.c)
		{
			if (v != NULL)
			{
				delete[](v[0]);
				delete[](v);
			}
			r = rhs.r;
			c = rhs.c;
			v = r > 0 ? new T * [r] : NULL;
			nel = r * c;
			if (v) v[0] = nel > 0 ? new T[nel] : NULL;
			for (i = 1; i < r; i++) v[i] = v[i - 1] + c;
		}
		for (i = 0; i < r; i++) for (j = 0; j < c; j++) v[i][j] = rhs[i][j];
	}
	return *this;
}

template <typename T>
inline T* Matrix<T>::operator[](const ui i)	//subscripting: pointer to row i
{
	return v[i];
}

template <typename T>
inline const T* Matrix<T>::operator[](const ui i) const
{
	return v[i];
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
		if (v != NULL)
		{
			delete[](v[0]);
			delete[](v);
		}
		r = newr;
		c = newc;
		v = r > 0 ? new T * [r] : NULL;
		nel = r * c;
		if (v) v[0] = nel > 0 ? new T[nel] : NULL;
		for (i = 1; i < r; i++) v[i] = v[i - 1] + c;
	}
}

template <typename T>
void Matrix<T>::assign(ui newr, ui newc, const T& a)
{
	int i, j, nel;
	if (newr != r || newc != c)
	{
		if (v != NULL)
		{
			delete[](v[0]);
			delete[](v);
		}
		r = newr;
		c = newc;
		v = r > 0 ? new T * [r] : NULL;
		nel = r * c;
		if (v) v[0] = nel > 0 ? new T[nel] : NULL;
		for (i = 1; i < r; i++) v[i] = v[i - 1] + c;
	}
	for (i = 0; i < r; i++) for (j = 0; j < c; j++) v[i][j] = a;
}


template <typename T>
Matrix<T>::~Matrix()
{
	if (v != NULL)
	{
		delete[](v[0]);
		delete[](v);
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

struct track{
	ui row_op[2];
	bool done = false;
};

void read_matrix(string filename, Matrix<double>& mat)
{
    std::ifstream file(filename, std::ios::in);
    std::string line;
    char *token = nullptr;
    ui i = 0, j = 0;
    while (std::getline(file, line)) 
    {
        token = strtok((char *)line.c_str(), ",");
        while (token  != NULL)
        {
            mat[i][j] = stod(token);
            j++;
            token = strtok(NULL, ",");
        }
        j = 0;
        i++;
    }
    file.close();
}

void read_vector(string filename, Vector<double>& vec)
{
	std::ifstream file(filename, std::ios::in);
    std::string line;
	char *token = nullptr;
	ui i = 0;
	while (std::getline(file, line))
	{
		token = strtok((char *)line.c_str(), ",");
		vec[i] = stod(token);
		i++;
	}
}

void write(Matrix<double> &mat, Vector<double> &vec)
{
	std::fstream solution("solution.txt", std::ios::out | std::ios::app);
	for (ui i = 0; i < mat.nrows(); i++)
	{
		for (ui j = 0; j < mat.ncols(); j++)
		{
			solution << std::setprecision(6) << std::fixed;
			solution << std::setw(10) << mat[i][j];
		}
		solution << "\n";
	}

	solution << "\n\n";

	for (ui i = 0; i < vec.size(); i++)
	{
		solution << std::setw(12) << vec[i];
		solution << "\n";
	}
	solution << "\n\n";
	solution.close();
}

void gaussj(Matrix<double> &A, Vector<double> &b)
{
	struct track *history = new struct track[A.nrows()];
	Vector<double> rowM(A.nrows());

	for (ui k = 0; k < A.nrows(); k++)
	{
		double big = 0.0;
		ui ilarge = 0, jlarge = 0;
		for (ui i = 0; i < A.nrows(); i++)
		{
			if (!history[i].done)
			{
				for (ui j = 0; j < A.nrows(); j++)
				{
					if (fabs(A[i][j]) >= fabs(big) && !history[j].done)
					{
						big = A[i][j];
						ilarge = i;
						jlarge = j;
					}
				}
			}
		}

		history[k].row_op[0] = ilarge;
		history[k].row_op[1] = jlarge;
		history[jlarge].done = true;

		if (ilarge != jlarge)
		{
			double temp = 0.0;
			for (ui i = 0; i < A.nrows(); i++)
			{
				temp = A[ilarge][i];
				A[ilarge][i] = A[jlarge][i];
				A[jlarge][i] = temp;
				rowM[i] = A[jlarge][i];
			}
			temp = b[ilarge];
			b[ilarge] = b[jlarge];
			b[jlarge] = temp;	
		} else
		{
			for (ui i = 0; i < A.nrows(); i++)
			{
				rowM[i] = A[jlarge][i];
			}
		}
 
		for (ui i = 0; i < A.nrows(); i++)
		{
			if (i != jlarge)
			{
				double mult = (A[i][jlarge] / (double)rowM[jlarge]);
				for (ui j = 0; j < A.nrows(); j++)
				{
					A[i][j] = A[i][j] - rowM[j] * mult;
				}
				A[i][jlarge] = -1.0 * mult;
				b[i] = b[i] - mult * b[jlarge];
			} else
			{
				for (ui j = 0; j < A.nrows(); j++)
				{
					A[jlarge][j] = rowM[j] / rowM[jlarge];
				}
			}
		}

		A[jlarge][jlarge] = A[jlarge][jlarge] / rowM[jlarge];
		b[jlarge] = b[jlarge] / rowM[jlarge];
	}

	for (ui i = A.nrows() - 1; i >= 0 && i < A.nrows(); i--)
	{
		double temp = 0.0;
		for (ui j = 0; j < A.nrows(); j++)
		{
			temp = A[j][history[i].row_op[0]];
			A[j][history[i].row_op[0]] = A[j][history[i].row_op[1]];
			A[j][history[i].row_op[1]] = temp;
		}
	}

	delete []history;
}

int main(int argc, char** argv)
{
	if (argc != 5)
	{
		std::cout << "<program_name.exe> <matrix_file_name.txt> <row_of_matrix> <column of matrix> <rhs_vector.txt>" << "\n";
		return -1;
	} else
	{
		ui dim_r = stoul(argv[2]);
		ui dim_c = stoul(argv[3]);
		if (dim_r != dim_c)
		{
			std::cout << "number of variable is not equal to number of equation" << "\n";
			return -1;
		} else
		{
			Matrix<double> A(dim_r,dim_c);
    		Vector<double> b(dim_r);

    		read_matrix(argv[1], A);
			read_vector(argv[4], b);
			write(A, b);

			gaussj(A, b);
			write(A, b);
		}
	}

	std::cout << "Solved" << "\n";
	return 0;
}