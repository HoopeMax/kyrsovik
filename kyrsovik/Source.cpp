#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <initializer_list>
//Задаем колиество переменных и функций
const int COLLS = 5;
const int ROWS = 3;

//Функция метода простых итераций
double* Itera(double** Matrix, int n);
//Главная апроксимурующая функция
void AproksimFun();

//Класс матрица
class Mat
{
private:
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

	//Создаем матрицу полную А
	void FullMatA()
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

	//Выводим матрицу А
	void Show_MatA()
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
};

//Класс базисных функций
class BazisFunction
{
public:
	//Методы, котрые возвращают значения базмсных функций
	double fun1(double x)
	{
		return 1;
	}

	double fun2(double x)
	{
		return 3*x;
	}

	double fun3(double x)
	{
		return x*x;
	}

	double** bas_x;

	//Конструктор BazisFunction
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

	//Деструктор
	~BazisFunction()
	{
		delete[] bas_x;
	}
};

//Главная функция
int main()
{
	setlocale(LC_ALL, "rus");
	AproksimFun();
	system("pause");
}

//Создаем элементы базисов
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

//Создаем Вектор В
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


//Метод простых  Итераций
double* Itera(double** MatA, int n)
{
	double* res = new double[n];
	double* y = new double[n];
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			y[i] = MatA[i][n];
		}

		res[i] = y[i] / MatA[i][i];
	}


	for (i = 0; i < n; i++)
	{
		res[i] = y[i] / MatA[i][i];
	}

	double eps = 0.0001;
	double* Xn = new double[n];

	do 
	{
		for (i = 0; i < n; i++)
		{
			Xn[i] = y[i] / MatA[i][i];
			for (j = 0; j < n; j++)
			{
				if (i == j)
					continue;
				else 
				{
					Xn[i] -= MatA[i][j] / MatA[i][i] * res[j];
				}
			}
		}

		bool flag = true;
		for (i = 0; i < n - 1; i++) 
		{
			if (abs(Xn[i] - res[i]) > eps)
			{
				flag = false;
				break;
			}
		}

		for (i = 0; i < n; i++) 
		{
			res[i] = Xn[i];
		}

		if (flag)
			break;
	} while (1);

	return res;
}

//Апркосимация
void AproksimFun()
{
	double Y[COLLS] = { 0.0f, 0.8f, 0.7f, 0.4f, 0.1f };
	Mat mat_A;
	BazisFunction basic_f({ -1.0f,-0.3f,0.4f,0.6f,1.0f });
	//Вывод изначальной матрицы
	std::cout << "Матрица AC= B\n";
	mat_A.Show_MatA();
	double* OutPut_C = Itera(mat_A.mat_A, ROWS);
	double f[COLLS] = {};
	double sigm[COLLS] = {};
	double J = 0;
	for (int i(0); i < COLLS; i++)
	{
		f[i] = *OutPut_C * basic_f.bas_x[i][0] + *(OutPut_C + 1) * basic_f.bas_x[i][1] + *(OutPut_C + 2) * basic_f.bas_x[i][2];
		sigm[i] = abs(f[i] - Y[i]);
		J += pow(sigm[i], 2);
	}

	//Вывод результатов работы метода
	std::cout << "\n\n Метод простых итераций \n\n";
	for (int i(0); i < 3; i++)
	{
		std::cout << *(OutPut_C + i) << " ";
	}

	std::cout << "\n \n Значения апрокс. функций\n\n";
	for (int i(0); i < COLLS; i++)
	{
		std::cout << f[i] << " ";
	}

	std::cout << "\n\nЗначения фи\n\n";
	for (int i(0); i < COLLS; i++)
	{
		std::cout << sigm[i] << " ";
	}

	std::cout << "\n\nJ = " << J << "\n\n";
	delete[] OutPut_C;
}