#include<iostream>
#include <iomanip>
#include<cmath>

const double eps = 0.001;
const int N = 5;
const int ROWS = 3;

class BasisXY
{
private:
	double X;
	double Y;

public:

	double f1(double x)
	{
		return 1;
	}

	double f2(double x)
	{
		return x;
	}

	double f3(double x)
	{
		return ((3 * (x * x)) - 1);
	}

	
	BasisXY(double X, double Y)
	{
		this->X = X;
		this->Y = Y;

	}

	double GetX()
	{
		
		return X;
	}

	double SetX(double X)
	{
		this->X = X;

	}
	double GetY()
	{

		return Y;
	}

	double SetY(double Y)
	{
		this->Y = Y;

	}
	
	
};

//class creatFi
//{
//public:
//
//	BasisXY* CreatFi(BasisXY* XiYi, double Y[N], double Fi[ROWS][N])
//	{
//		for (int i = 0; i < 3; i++)
//		{
//			for (int j = 0; j < 5; j++)
//			{
//				if (i == 0)
//				{
//					Fi[i][j] = 1;
//				}
//
//				if (i == 1)
//				{
//					Fi[i][j] = XiYi.X[j];
//				}
//
//				if (i == 2)
//				{
//					Fi[i][j] = ((3 * (X[j] * X[j])) - 1);
//				}
//
//			}
//
//		}
//		return Fi[ROWS][N];
//
//};


double* iter(double a[3][3], double y[3], int n);


int main()
{
	setlocale(LC_ALL, "rus");
	BasisXY* XiYi = new BasisXY[N]
	{
		{-1.0, 0.0, ) },
		{-0.3, 0.8 },
		{ 0.4, 0.7 },
		{ 0.6, 0.4},
		{ 1.0, 0.1 }
	};

	


	/*double Fi[3][5];
	double A[3][3];
	double B[3]{ 0, 0, 0 };
	double* C;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == 0)
			{
				Fi[i][j] = 1;
			}

			if (i == 1)
			{
				Fi[i][j] = X[j];
			}

			if (i == 2)
			{
				Fi[i][j] = ((3*(X[j]* X[j]))-1);
			}
			
		}

	}
	int k = 0;
	for (int i=0; i<3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			A[i][j] = (Fi[i][k] * Fi[j][k]+
				       Fi[i][k+1] * Fi[j][k+1]+
				       Fi[i][k+2] * Fi[j][k+2]+ 
				       Fi[i][k+3] * Fi[j][k+3]+ 
				       Fi[i][k+4] * Fi[j][k+4]);
			k = 0;
		}

	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			B[i] = B[i]+ Y[j]* Fi[i][j];

		}
		
	}

	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::cout << std::endl;
			std::cout << Fi[i][j];
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << " " << A[i][j];
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < 3; i++)
	{
		std::cout << " " << B[i];

	}
	std::cout << std::endl;
	C = iter(A, B, 3);
	for (int i = 0; i < 3; i++)
	{
		std::cout << C[i] << "\t";
	}
	std::cout << std::endl;

	double Fun[5]{ 0, 0, 0 , 0, 0 };

	for (int i = 0; i < 5; i++)
	{
	
		Fun[i] = C[0] + (C[1] * Fi[1][i]) + (C[2] * Fi[2][i] );
	
	}
	std::cout << std::endl;
	for (int i = 0; i < 5; i++)
	{
	
		std::cout << Fun[i] << "\t";

	}
	std::cout << std::endl;
	double J=0;
	for (int i = 0; i < 5; i++)
	{
		J = J + pow((Y[i]-Fun[i]),2);
	
	}
	std::cout << J << "\t";*/


	return 0;

}

//Решение СЛАУ методом итераций
double* iter(double a[3][3], double y[3], int n)
{
	double* res = new double[n];
	int i, j;


	for (i = 0; i < n; i++)
	{
		res[i] = y[i] / a[i][i];
	}

	double eps = 0.0001;
	double* Xn = new double[n];

	do {
		for (i = 0; i < n; i++) {
			Xn[i] = y[i] / a[i][i];
			for (j = 0; j < n; j++) {
				if (i == j)
					continue;
				else {
					Xn[i] -= a[i][j] / a[i][i] * res[j];
				}
			}
		}

		bool flag = true;
		for (i = 0; i < n - 1; i++) {
			if (abs(Xn[i] - res[i]) > eps) {
				flag = false;
				break;
			}
		}

		for (i = 0; i < n; i++) {
			res[i] = Xn[i];
		}

		if (flag)
			break;
	} while (1);

	return res;
}