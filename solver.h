#ifndef SOLVER_H
#define SOLVER_H

#include <fstream>
#include "type.h"

void write(string filename, Vector<double> &vec)
{
	std::fstream solution(filename, std::ios::out | std::ios::app);

	for (ui i = 0; i < vec.size(); i++)
	{
		solution << std::setw(12) << vec[i];
		solution << "\n";
	}

	solution << "\n\n";
	solution.close();
}

void write(string filename, Matrix<double> &mat)
{
	std::fstream solution(filename, std::ios::out | std::ios::app);
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
	solution.close();
}

bool logger(Matrix<double> &A)
{
    write("log.txt", A);
    return true;
}

bool logger(Matrix<double> &A, Vector<double> &b)
{
    write("log.txt", A);
    write("log.txt", b);

    return true;
}

class solver
{
private:
    struct track
    {
        ui row_operation[2];
        ui column_operation[2];
        double pivot;
        bool done = false;
    };

    class pivot
    {
        public:
            double *s = nullptr;
        public:
            pivot();
            void pcomplete(Matrix<double> &m, struct track *h, ui index);
            void pcomplete(Matrix<double> &m, struct track *h, ui index, Vector<double> &n);
            void ppartial(Matrix<double> &m, struct track *h, ui index, Vector<double> &n);
            void prook(Matrix<double> &m, struct track *h, ui index, Vector<double> &n);
            void scaled_partial(Matrix<double> &m, struct track *h, ui index, double *s, Vector<double> &n);
            ~pivot();
    };

    bool complete = false;
    bool partial = false;
    bool rook = false;
    bool scaled_partial = false;

    void row_reduction(Matrix<double> &m, Vector<double> &n, ui prow);
    void gaussj(Matrix<double> &m, Vector<double> &b);

    friend bool logger(Matrix<double> &A, Vector<double> &b);
public:

    solver();

    class inverse
    {
        private:
            void row_reduction(Matrix<double> &m, ui prow);
            friend bool logger(Matrix<double> &A);
            double mult = 0.0;
        public:
            inverse();
            void gaussj(Matrix<double> &A);
    };

    solver(Matrix<double> &m, Vector<double> &b);
    solver(Matrix<double> &m, Matrix<double> &B);
    
    ~solver();
};

solver::pivot::pivot() { }

solver::pivot::~pivot() { }

void solver::pivot::pcomplete(Matrix<double> &A, struct track *h, ui index)
{
    double big = 0.;
    ui ilarge = 0, jlarge = 0;
    for (ui i = 0; i < A.nrows(); i++)
    {
        if (!h[i].done)
        {
            for (ui j = 0; j < A.ncols(); j++)
            {
                if (fabs(A[i][j]) >= fabs(big) && !h[j].done)
                {
                    big = A[i][j];
                    ilarge = i;
                    jlarge = j;
                }
            }
        }
    }
    h[index].pivot = big;
    h[index].row_operation[0] = ilarge;
    h[index].row_operation[1] = index;
    h[index].column_operation[0] = jlarge;
    h[index].column_operation[1] = index;
}

void solver::pivot::pcomplete(Matrix<double> &A, struct track *h, ui index, Vector<double> &n)
{
    double big = 0.;
    pcomplete(A, h, index);

    big = n[h[index].row_operation[0]];
    n[h[index].row_operation[0]] = n[index];
    n[index] = big;
}

void solver::pivot::ppartial(Matrix<double> &A, struct track *h, ui index, Vector<double> &n)
{
    double big = 0.;
    ui ilarge = 0;

    for (ui i = index; i < A.nrows(); i++)
    {
        if (fabs(A[i][index]) >= fabs(big))
        {
            big = A[i][index];
            ilarge = i;
        }
    }
    h[index].pivot = big;

    h[index].row_operation[0] = ilarge;
    h[index].row_operation[1] = index;

    big = n[h[index].row_operation[0]];
    n[h[index].row_operation[0]] = n[index];
    n[index] = big;
}

void solver::pivot::prook(Matrix<double> &A, struct track *h, ui index, Vector<double> &n)
{
    bool found = false;
    ui rlarge = 0, clarge = 0;
    double big = 0.0;
    
    while(!found)
    {
        for (ui i = index; i < A.nrows() && !found; i++) 
        {
            big = 0.0;
            for (ui j = index; j < A.ncols(); j++) 
            {
                if(fabs(A[i][j]) > fabs(big))
                {
                    big = A[i][j];
                    rlarge = i;
                    clarge = j;
                }
            }
            for (ui j = index; j < A.nrows(); j++) 
            {
                if(fabs(A[j][clarge]) > fabs(big))
                {
                    found = false;
                    break;
                } else
                {
                    found = true;
                }
            }
        }
    }
    h[index].pivot = big;
    h[index].row_operation[0] = rlarge;
    h[index].row_operation[1] = index;
    h[index].column_operation[0] = clarge;
    h[index].column_operation[1] = index;

    big = n[h[index].row_operation[0]];
    n[h[index].row_operation[0]] = n[index];
    n[index] = big;
}

void solver::pivot::scaled_partial(Matrix<double> &A, struct track *h, ui index, double *s, Vector<double> &n)
{
    for (ui i = 0; i < A.nrows(); i++)
    {
        
    }
    
}

void solver::inverse::row_reduction(Matrix<double> &m, ui prow)
{
    for (ui j = 0; j < m.nrows(); j++)
    {
        if(prow != j)
        {
            mult = m[j][prow] / m[prow][prow];
            for (ui k = 0; k < m.ncols(); k++)
            {
                m[j][k] = m[j][k] - mult * m[prow][k];
            }
            m[j][prow] = -1.0 * mult;
        }
    }
}

solver::inverse::inverse() { }

void solver::inverse::gaussj(Matrix<double> &A)
{
    ui r = A.nrows();
    ui c = A.ncols();

    pivot g;

    struct track *history = new struct track[A.nrows()];

    for (ui i = 0; i < r; i++)
    {
        g.pcomplete(A, history, i);
        A.row_exchange(history[i].column_operation[0], history[i].row_operation[0]);
        history[history[i].column_operation[0]].done = true;

        row_reduction(A, history[i].column_operation[0]);
        for (ui j = 0; j < r; j++)
        {
            A[history[i].column_operation[0]][j] = j != history[i].column_operation[0] ? A[history[i].column_operation[0]][j] / history[i].pivot : 1.0 / history[i].pivot;
        }
    }

    for (ui i = A.nrows() - 1; i >= 0 && i < UINT_MAX; i--)
    {
        A.column_exchange(history[i].row_operation[0], history[i].column_operation[0]);
    }
    
    delete []history;
}

void solver::row_reduction(Matrix<double> &m, Vector<double> &n, ui prow)
{
    for (ui j = 0; j < m.nrows(); j++)
    {
        if(prow != j)
        {
            double mult = m[j][prow] / m[prow][prow];
            for (ui k = 0; k < m.ncols(); k++)
            {
                m[j][k] = m[j][k] - mult * m[prow][k];
            }
            n[j] = n[j] - n[prow] * mult;
        }
    }
}

void solver::gaussj(Matrix<double> &m, Vector<double> &n)
{
    ui r = m.nrows();
    ui c = m.ncols();

    double big = 0.0;

    pivot g;

    struct track *history = new struct track[r];

    if (scaled_partial)
    {
        g.s = new double[r];
        for (ui i = 0; i < r; i++)
        {
            big = 0.0;
            for (ui j = 0; j < c; j++)
            {
                if (fabs(m[i][j]) > fabs(big))
                {
                    big = m[i][j];
                }
            }
            g.s[i] = big;
        }
    }
    

    for (ui i = 0; i < r; i++)
    {
        if (complete)
        {
            g.pcomplete(m, history, i, n);
            m.row_exchange(history[i].row_operation[0], history[i].row_operation[1]);
            m.column_exchange(history[i].column_operation[0], history[i].column_operation[1]);
            history[history[i].row_operation[1]].done = true;
        }

        if (partial)
        {
            g.ppartial(m, history, i, n);
            m.row_exchange(history[i].row_operation[0], history[i].row_operation[1]);
            history[i].done = true;
        }

        if (rook)
        {
            g.prook(m, history, i, n);
            m.row_exchange(history[i].row_operation[0], history[i].row_operation[1]);
            m.column_exchange(history[i].column_operation[0], history[i].column_operation[1]);
            history[i].done = true;
        }
        
        if (scaled_partial)
        {
            
        }
        

        row_reduction(m, n, i);
    }
    
    for (ui i = 0; i < m.nrows(); i++)
    {
        n[i] = n[i] / m[i][i];
    }

    if (complete || rook)
    {
        double big = 0.0;
        for (ui i = m.nrows() - 1; i >= 0 && i < UINT_MAX; i--)
        {
            big = n[history[i].column_operation[0]];
            n[history[i].column_operation[0]] = n[history[i].column_operation[1]];
            n[history[i].column_operation[1]] = big;
        }
    } 

    if (scaled_partial)
    {
        delete []g.s;
    }
    
    delete []history;
}

solver::solver() { }

solver::solver(Matrix<double> &A, Vector<double> &b)
{
    unsigned short prompt = 0;

    cout << "Pivoting Strategy - \n";
    cout << "1. Complete Pivoting\n";
    cout << "2. Partial Pivoting \n";
    cout << "3. Rook Pivoting \n";
    cout << "4. Scaled Partial Pivoting\n";

    cout << "Input : ";
    cin >> prompt;

    switch (prompt)
    {
        case 1:
            complete = true;
            break;
        case 2:
            partial = true;
            break;
        case 3:
            rook = true;
            break;
        case 4:
            scaled_partial = true;
            break;
        default:
            cout << "Invalid Input. Default pivoting strategy(complete pivoting) used\n";
            complete = true;
            break;
    }

    gaussj(A, b);
}

solver::solver(Matrix<double> &m, Matrix<double> &B)
{
}

solver::~solver()
{
}


#endif