#include "matrix.h"

class Bandec 
{
    private:
        int n,m1,m2;
        double d;
    public:
	    Matrix<double> au,al;
	    Vector<int> indx;
	    Bandec(Matrix<double> &a, const int mm1, const int mm2);
	    void solve(Vector<double> &b, Vector<double> &x);
	    double det();
};

Bandec::Bandec(Matrix<double> &a, const int mm1, const int mm2) : n(a.nrows()), au(a), m1(mm1), m2(mm2), al(n,m1), indx(n)
{
	const double TINY=1.0e-40;
	int i,j,k,l,mm;
	double dum;
	mm=m1+m2+1;
	l=m1;
	for (i=0;i<m1;i++) {
		for (j=m1-i;j<mm;j++) au[i][j-l]=au[i][j];
		l--;
		for (j=mm-l-1;j<mm;j++) au[i][j]=0.0;
	}
	d=1.0;
	l=m1;
	for (k=0;k<n;k++) {
		dum=au[k][0];
		i=k;
		if (l<n) l++;
		for (j=k+1;j<l;j++) {
			if (abs(au[j][0]) > abs(dum)) {
				dum=au[j][0];
				i=j;
			}
		}
		indx[k]=i+1;
		if (dum == 0.0) au[k][0]=TINY;
		if (i != k) {
			d = -d;
			for (j=0;j<mm;j++) SWAP(au[k][j],au[i][j]);
		}
		for (i=k+1;i<l;i++) {
			dum=au[i][0]/au[k][0];
			al[k][i-k-1]=dum;
			for (j=1;j<mm;j++) au[i][j-1]=au[i][j]-dum*au[k][j];
			au[i][mm-1]=0.0;
		}
	}
}

void Bandec::solve(Vector<double> &b, Vector<double> &x)
{
	int i,j,k,l,mm;
	double dum;
	mm=m1+m2+1;
	l=m1;
	for (k=0;k<n;k++) x[k] = b[k];
	for (k=0;k<n;k++) {
		j=indx[k]-1;
		if (j!=k) SWAP(x[k],x[j]);
		if (l<n) l++;
		for (j=k+1;j<l;j++) x[j] -= al[k][j-k-1]*x[k];
	}
	l=1;
	for (i=n-1;i>=0;i--) {
		dum=x[i];
		for (k=1;k<l;k++) dum -= au[i][k]*x[k+i];
		x[i]=dum/au[i][0];
		if (l<mm) l++;
	}
}

double Bandec::det() 
{
	double dd = d;
	for (int i=0;i<n;i++) dd *= au[i][0];
	return dd;
}
