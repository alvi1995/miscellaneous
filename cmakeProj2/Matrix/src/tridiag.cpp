#include <matrix.h>

void tridag(Vector<double> &a, Vector<double> &b, Vector<double> &c, Vector<double> &r, Vector<double> &u)
{
	int j,n=a.size();
	double bet;
	Vector<double> gam(n);
	if (b[0] == 0.0) throw("Error 1 in tridag");
	u[0]=r[0]/(bet=b[0]);
	for (j=1;j<n;j++) {
		gam[j]=c[j-1]/bet;
		bet=b[j]-a[j]*gam[j];
		if (bet == 0.0) throw("Error 2 in tridag");
		u[j]=(r[j]-a[j]*u[j-1])/bet;
	}
	for (j=(n-2);j>=0;j--)
		u[j] -= gam[j+1]*u[j+1];
}

void cyclic(Vector<double> &a, Vector<double> &b, Vector<double> &c, const double alpha, const double beta, Vector<double> &r, Vector<double> &x)
{
	int i,n=a.size();
	double fact,gamma;
	if (n <= 2) throw("n too small in cyclic");
	Vector<double> bb(n),u(n),z(n);
	gamma = -b[0];
	bb[0]=b[0]-gamma;
	bb[n-1]=b[n-1]-alpha*beta/gamma;
	for (i=1;i<n-1;i++) bb[i]=b[i];
	tridag(a,bb,c,r,x);
	u[0]=gamma;
	u[n-1]=alpha;
	for (i=1;i<n-1;i++) u[i]=0.0;
	tridag(a,bb,c,u,z);
	fact=(x[0]+beta*x[n-1]/gamma)/
		(1.0+z[0]+beta*z[n-1]/gamma);
	for (i=0;i<n;i++) x[i] -= fact*z[i];
}