//#include <iostream>
//#include <cstdlib>
//
//using namespace std;
//
//const int N = 3;
//
//void inversion(double A[][N], double E[][N])
//{
//    double temp;
//
//    for (int k = 0; k < N; k++)
//    {
//        temp = A[k][k];
//
//        for (int j = 0; j < N; j++)
//        {
//            A[k][j] /= temp;
//            E[k][j] /= temp;
//        }
//
//        for (int i = k + 1; i < N; i++)
//        {
//            temp = A[i][k];
//
//            for (int j = 0; j < N; j++)
//            {
//                A[i][j] -= A[k][j] * temp;
//                E[i][j] -= E[k][j] * temp;
//            }
//        }
//    }
//
//    for (int k = N - 1; k > 0; k--)
//    {
//        for (int i = k - 1; i >= 0; i--)
//        {
//            temp = A[i][k];
//
//            for (int j = 0; j < N; j++)
//            {
//                A[i][j] -= A[k][j] * temp;
//                E[i][j] -= E[k][j] * temp;
//
//            }
//        }
//    }
//    for (int i=0; i<3; i++)
//    {
//       
//
//            
//        
//    }
//}
//
//void multi(double A[][N], double B[N], double X[N])
//{
//    for (int i = 0; i < N; i++)
//    {
//        X[i] = 0;
//        for (int j = 0; j < N; j++)
//        {
//            X[i] += A[i][j] * B[j];
//                std::cout << X[i] << " ";
//        }
//        
//    }
//  
//}
//
//int main()
//{
//    double A[N][N] =
//    {
//        2.9992, -0.0008, 0.009,
//       -0.0008, 2.0008, 2.4163,
//        0.009, 2.4163, 5.0
//    };
//
//    double B[N] =
//    {
//        -11.802,
//        13.548,
//        26.0
//    };
//
//    double E[N][N] =
//    {
//        1.0, 0.0, 0.0,
//        0.0, 1.0, 0.0,
//        0.0, 0.0, 1.0
//    };
//
//    double X[N];
//
//    inversion(A, E);
//    multi(E, B, X);
//
//    for (int i = 0; i < N; i++)
//        cout << "X[" << i << "] = " << X[i] << endl;
//
//    cout << endl;
//    system("pause");
//    return 0;
//}