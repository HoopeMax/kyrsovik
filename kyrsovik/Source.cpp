#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <initializer_list>

const int QUANTITY_Y = 5;
const int QUANTITY_X = 3;
double* iter(double** a,  int n);
void AproksimFunction();
class Matrix
{
	double Y[QUANTITY_Y] = { 0.0f, 0.8f, 0.7f, 0.4f, 0.1f };
	double CalcElement(unsigned int n, unsigned int m);
	double CalcB(unsigned short n, double Y[QUANTITY_Y]);
public:
	double** mat;
	Matrix(unsigned short height = 3, unsigned short width = 3)
	{
		mat = new double* [height];
		for (unsigned short step(0); step < width; step++)
		{
			mat[step] = new double[width];
		}
		FillMatrix();
	}

	~Matrix()
	{
		delete[] mat;
	}
	void FillMatrix();
	void Show();
};

class BazF
{
	double f1(double);
	double f2(double);
	double f3(double);
public:
	double** basic_f;
	BazF(std::initializer_list<double> x_arr)
	{
		basic_f = new double* [QUANTITY_Y];

		for (unsigned short step(0); step < QUANTITY_Y; step++)
		{
			basic_f[step] = new double[QUANTITY_X];
		}
		for (unsigned short step_y(0); step_y < QUANTITY_Y; step_y++)
		{
			for (unsigned short step_x(0); step_x < QUANTITY_X; step_x++)
			{
				if (step_x == 0)
				{
					basic_f[step_y][step_x] = f1(*(x_arr.begin() + step_y));
				}
				else if (step_x == 1)
				{
					basic_f[step_y][step_x] = f2(*(x_arr.begin() + step_y));
				}
				else
				{
					basic_f[step_y][step_x] = f3(*(x_arr.begin() + step_y));
				}
			}
		}
	}
	~BazF()
	{
		delete[] basic_f;
	}
};

int main()
{
	setlocale(LC_ALL, "russian");
	AproksimFunction();
	system("pause");
}

double BazF::f1(double x)
{
	return 1;
}

double BazF::f2(double x)
{
	return x;
}

double BazF::f3(double x)
{
	return 3*pow(x,2)-1;
}

double Matrix::CalcElement(unsigned int n, unsigned int m)
{
	BazF basic_f({-1.0f,-0.3f,0.4f,0.6f,1.0f });
	double result = 0;
	for (unsigned short i(0); i < QUANTITY_Y; i++)
	{
		result += (basic_f.basic_f[i][n - 1] * basic_f.basic_f[i][m - 1]);
	}
	return result;
}

double Matrix::CalcB(unsigned short n, double Y[QUANTITY_Y])
{
	BazF basic_f({ -1.0f,-0.3f,0.4f,0.6f,1.0f });
	double result = 0;
	for (unsigned short i(0); i < QUANTITY_Y; i++)
	{
		result += (Y[i] * basic_f.basic_f[i][n - 1]);
	}
	return result;
}

void Matrix::FillMatrix()
{
	for (unsigned short i(0); i < 3; i++)
	{
		for (unsigned short j(0); j < 3; j++)
		{
			mat[i][j] = CalcElement(i + 1, j + 1);
		}
		mat[i][3] = CalcB(i + 1, Y);
	}
}

void Matrix::Show()
{
	for (unsigned short i(0); i < 3; i++)
	{
		for (unsigned short j(0); j < 4; j++)
		{
			std::cout << mat[i][j] << " ";
		}
		std::cout << "\n";
	}
}

double* iter(double** a, int n)
{
	double* y= new double [3];
	double* res = new double[n];
	int i, j;

	for (i = 0; i < n; i++)
	{
		y[i]=a[i][3];
	}

	for (i = 0; i < n; i++)
	{
		res[i] = y[i] / a[i][i];
	}


	double eps = 0.0001;
	double* Xn = new double[n];

	do {
		for (i = 0; i < 3; i++) {
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

void AproksimFunction()
{
	double Y[QUANTITY_Y] = { 0.0f, 0.8f, 0.7f, 0.4f, 0.1f };
	Matrix mat_object;
	BazF basic_f({ -1.0f,-0.3f,0.4f,0.6f,1.0f });
	//Вывод изначальной матрицы
	std::cout << "Изначальная матрица\n";
	for (unsigned short i(0); i < 3; i++)
	{
		for (unsigned short j(0); j < 4; j++)
		{
			std::cout << mat_object.mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
	double* answers = iter(mat_object.mat,3);
	double f[QUANTITY_Y] = {};
	double sigma[QUANTITY_Y] = {};
	double J = 0;
	for (unsigned short i(0); i < QUANTITY_Y; i++)
	{
		f[i] = *answers * basic_f.basic_f[i][0] + *(answers + 1) * basic_f.basic_f[i][1] + *(answers + 2) * basic_f.basic_f[i][2];
		sigma[i] = abs(f[i] - Y[i]);
		J += pow(sigma[i], 2);
	}


	std::cout << "\nX,Y и Z в результате выполнения метода Гаусса\n";
	for (unsigned short i(0); i < 3; i++)
	{
		std::cout << *(answers + i) << " ";
	}
	std::cout << "\n";
	std::cout << "\nЗначения апрокс. функций\n";
	for (unsigned short i(0); i < QUANTITY_Y; i++)
	{
		std::cout << f[i] << " ";
	}
	std::cout << "\n";
	std::cout << "\nЗначения сигмы\n";
	for (unsigned short i(0); i < QUANTITY_Y; i++)
	{
		std::cout << sigma[i] << " ";
	}
	std::cout << "\n";
	std::cout << "\nJ = " << J << "\n";
	delete[] answers;
}