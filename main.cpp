#include "type.h"
//#include "solver.h"
#include <fstream>

struct track
{
    ui rowop[2];
    ui colop[2];
    double pivot;
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

void complete(Matrix<double> &A, struct track *h, ui index)
{
    double big = 0.;
    ui ilarge = 0, jlarge = 0;

    for (ui i = 0; i < A.nrows(); i++)
    {
        if (!h[i].done)
        {
            for (ui j = 0; j < A.ncols(); j++)
            {
                if(fabs(A[i][j]) >= fabs(big) && !h[j].done)
                {
                    big = A[i][j];
                    ilarge = i;
                    jlarge = j;
                }
            }
        }
    }

    
}

void gaussj(Matrix<double> &A, Vector<double> &b)
{
    ui r = A.nrows();
    ui c = A.ncols();

    
    ui p[] = { 0, 1, 2, 3, 4, 5, 6 };

    Vector<ui> rowp(r, p), columnp(c, p);
    struct track *h = new struct track[r];


    for (ui i = 0; i < r; i++)
    {
        

        for (ui j = 0; j < c; j++)
        {
            
        }
        
    }
    
    

    

}

int main()
{
    Matrix<double> A(7,7);
    read_matrix("A.txt", A);

    Vector<double> b(7);
    read_vector("b.txt", b);



    cout << A << "\n" << b;
    cout << "successfull\n";

    return 0;
}