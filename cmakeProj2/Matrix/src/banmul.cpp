#include <matrix.h>

void banmul(Matrix<double> &a, const int m1, const int m2, Vector<double> &x, Vector<double> &b)
{
	int i,j,k,tmploop,n=a.nrows();
	for (i=0;i<n;i++) {
		k=i-m1;
		tmploop=MIN(m1+m2+1, int(n-k));
		b[i]=0.0;
		for (j=MAX(0,-k);j<tmploop;j++) b[i] += a[i][j]*x[j+k];
	}
}
