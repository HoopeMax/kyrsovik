#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <initializer_list>

const int COLLS = 5;
const int ROWS = 3;

double* Itera(double** Matrix);
void AproksimFun();

class Mat
{
	double Y[COLLS] = { 0.0f, 0.8f, 0.7f, 0.4f, 0.1f };
	double CreatElem(int n, int m);
	double CalcB(int n, double Y[COLLS]);
public:
	double** mat_A;
	Mat(int colls = 3, int rows = 3)
	{
		mat_A = new double* [colls];
		for (int step(0); step < rows; step++)
		{
			mat_A[step] = new double[rows];
		}
		FullMatA();
	}

	~Mat()
	{
		delete[] mat_A;
	}
	void FullMatA();
	void Show_MatA();
};

class BazisFunction
{
	double fun1(double);
	double fun2(double);
	double fun3(double);
public:
	double** bas_x;
	BazisFunction(std::initializer_list<double> x_arr)
	{
		bas_x = new double* [COLLS];

		for (int step(0); step < COLLS; step++)
		{
			bas_x[step] = new double[ROWS];
		}
		for (int step_y(0); step_y < COLLS; step_y++)
		{
			for (int step_x(0); step_x < ROWS; step_x++)
			{
				if (step_x == 0)
				{
					bas_x[step_y][step_x] = fun1(*(x_arr.begin() + step_y));
				}
				else if (step_x == 1)
				{
					bas_x[step_y][step_x] = fun2(*(x_arr.begin() + step_y));
				}
				else
				{
					bas_x[step_y][step_x] = fun3(*(x_arr.begin() + step_y));
				}
			}
		}
	}
	~BazisFunction()
	{
		delete[] bas_x;
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	AproksimFun();
	system("pause");
}

double BazisFunction::fun1(double x)
{
	return 1;
}

double BazisFunction::fun2(double x)
{
	return x;
}

double BazisFunction::fun3(double x)
{
	return 3*pow(x,2)-1;
}

double Mat::CreatElem(int n, int m)
{
	BazisFunction bas_f({-1.0f,-0.3f,0.4f,0.6f,1.0f });
	double ansv = 0;
	for (int i(0); i < COLLS; i++)
	{
		ansv += (bas_f.bas_x[i][n - 1] * bas_f.bas_x[i][m - 1]);
	}
	return ansv;
}

double Mat::CalcB(int n, double Y[COLLS])
{
	BazisFunction basic_f({ -1.0f,-0.3f,0.4f,0.6f,1.0f });
	double ansv = 0;
	for (int i(0); i < COLLS; i++)
	{
		ansv += (Y[i] * basic_f.bas_x[i][n - 1]);
	}
	return ansv;
}

void Mat::FullMatA()
{
	for (int i(0); i < 3; i++)
	{
		for (int j(0); j < 3; j++)
		{
			mat_A[i][j] = CreatElem(i + 1, j + 1);
		}
		mat_A[i][3] = CalcB(i + 1, Y);
	}
}

void Mat::Show_MatA()
{
	for (int i(0); i < 3; i++)
	{
		for (int j(0); j < 4; j++)
		{
			std::cout << mat_A[i][j] << " ";
		}
		std::cout << "\n";
	}
}

double* Itera(double** MatA)
{
	double* result = new double[3];
	for (int j(1); j < 3; j++)
	{
		double subdiv = MatA[j][0] / MatA[0][0];
		for (int i(0); i < 4; i++)
		{
			MatA[j][i] = MatA[j][i] - (MatA[0][i] * subdiv);
		}
	}
	for (int j(2); j < 3; j++)
	{
		double subdiv = MatA[j][1] / MatA[1][1];
		for (int i(1); i < 4; i++)
		{
			MatA[j][i] = MatA[j][i] - (MatA[1][i] * subdiv);
		}
	}

	result[2] = MatA[2][3] / MatA[2][2];
	result[1] = (MatA[1][3] - MatA[1][2] * result[2]) / MatA[1][1];
	result[0] = (MatA[0][3] - MatA[0][1] * result[1] - MatA[0][2] * result[2]) / MatA[0][0];
	return result;
}

void AproksimFun()
{
	double Y[COLLS] = { 0.0f, 0.8f, 0.7f, 0.4f, 0.1f };
	Mat mat_A;
	BazisFunction basic_f({ -1.0f,-0.3f,0.4f,0.6f,1.0f });
	//Вывод изначальной матрицы
	std::cout << "Матрица AC= B\n";
	for (int i(0); i < 3; i++)
	{
		for (int j(0); j < 4; j++)
		{
			std::cout << mat_A.mat_A[i][j] << " ";
		}
		std::cout << std::endl;
	}
	double* OutPut_C = Itera(mat_A.mat_A);
	double f[COLLS] = {};
	double sigm[COLLS] = {};
	double J = 0;
	for (int i(0); i < COLLS; i++)
	{
		f[i] = *OutPut_C * basic_f.bas_x[i][0] + *(OutPut_C + 1) * basic_f.bas_x[i][1] + *(OutPut_C + 2) * basic_f.bas_x[i][2];
		sigm[i] = abs(f[i] - Y[i]);
		J += pow(sigm[i], 2);
	}

	//Начало паботы метода

	std::cout << "\n Метод простых итераций \n";
	for (int i(0); i < 3; i++)
	{
		std::cout << *(OutPut_C + i) << " ";
	}
	std::cout << "\n";
	std::cout << "\nЗначения апрокс. функций\n";
	for (int i(0); i < COLLS; i++)
	{
		std::cout << f[i] << " ";
	}
	std::cout << "\n";
	std::cout << "\nЗначения фи\n";
	for (int i(0); i < COLLS; i++)
	{
		std::cout << sigm[i] << " ";
	}
	std::cout << "\n";
	std::cout << "\nJ = " << J << "\n";
	delete[] OutPut_C;
}