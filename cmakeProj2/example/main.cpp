#include "solvers.h"

int main()
{
    // double a[] = {3, 2, -1, 2, -3, 1, 5, 1, -2};
    // double b[] = {11, 7, 12};

    // Matrix<double> A(3,3,a);
    // Matrix<double> B(3,1,b);

    // gaussj(A,B);

    // double a[] = {2,  1,  0,  0,  0,  0,  0,  0,  0,  0,
    //               1,  3,  2,  0,  0,  0,  0,  0,  0,  0,
    //               0,  1,  3,  1,  0,  0,  0,  0,  0,  0,
    //               0,  0,  7,  2,  6,  0,  0,  0,  0,  0,
    //               0,  0,  0,  6,  2,  1,  0,  0,  0,  0,
    //               0,  0,  0,  0,  3,  4,  3,  0,  0,  0,
    //               0,  0,  0,  0,  0,  8,  1,  5,  0,  0,
    //               0,  0,  0,  0,  0,  0,  6,  2,  7,  0,
    //               0,  0,  0,  0,  0,  0,  0,  5,  4,  3,
    //               0,  0,  0,  0,  0,  0,  0,  0,  4,  5};

    // double b[] = {1,  2,  6,  34,  10,  1,  4,  22,  25,  3};

    // Matrix<double> A(10,10,a);
    // Vector<double> B(10,b);

    const int M1=2,M2=1,NP=7,MP=(M1+1+M2);
    int i,j,k;
    Vector<double> ax(NP),b(NP),x(NP);
    Matrix<double> a(NP,MP),aa(NP,NP);

    // Lower band
    for (i=0;i<M1;i++)
        for (j=i;j<NP;j++)
        a[j][i]=10.0*(j+1)+(i+1);
    // Diagonal
    for (j=0;j<NP;j++) a[j][M1]=j+1;
    // Upper band
    for (i=0;i<M2;i++)
        for (j=0;j<NP;j++) a[j][M1+i+1]=0.1*(j+1)+(i+1);
    for (i=0;i<NP;i++) {
        for (j=0;j<NP;j++) {
            k=i-M1;
            if (j>=MAX(0,k) && j<=MIN(M1+M2+k,NP-1))
              aa[i][j]=a[i][j-k];
            else aa[i][j]=0.0;
        }
    }
    for (i=0;i<NP;i++) x[i]=(i+1)/10.0;
    banmul(a,M1,M2,x,b);
    for (i=0;i<NP;i++) {
        for (ax[i]=0.0,j=0;j<NP;j++) ax[i] += aa[i][j]*x[j];
    }
    cout << fixed << setprecision(4) << "Reference vector";
    cout << setw(18) << "banmul vector" << endl << endl;
    for (i=0;i<NP;i++)
        cout << setw(12) << ax[i] << setw(18) << b[i] << endl;
    
    cout << aa << endl;
    cout << a << endl;
    return 0;
}