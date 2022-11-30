#include "matrix.h"

void gaussj(Matrix<double> &a, Matrix<double> &b);
void tridag(Vector<double> &a, Vector<double> &b, Vector<double> &c, Vector<double> &r, Vector<double> &u);
void cyclic(Vector<double> &a, Vector<double> &b, Vector<double> &c, const double alpha, const double beta, Vector<double> &r, Vector<double> &x);
void banmul(Matrix<double> &a, const int m1, const int m2, Vector<double> &x, Vector<double> &b);
