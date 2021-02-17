#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void handle_fill_Matrix(int n, int m, int** M) {
	for (int i = 0; i < n; i++) {
		cout << "Заполнение " << i << " строки матрицы\n\n";
		for (int j = 0; j < m; j++)
			cin >> M[i][j];
	}
}

void random_fill_Matrix(int n, int m, int** M) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			M[i][j] = rand() % 10;
}

void showMatrix(int n, int m, int** M) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << M[i][j] << " ";
		cout << endl;
	}
}

int** createNullMatrix(int n, int m){
    int** M = new int* [n];
	for (int i = 0; i < n; i++)
	{
		M[i] = new int[m];
		for (int j = 0; j < m; j++)
			M[i][j] = 0;
	}
	return M;
}

void copyMatrix(int** copyM, int** mainM, int n ,int m) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			copyM[i][j] = mainM[i][j];
	}
}

int*** splitMatrixOn4parts(int** M, int n, int m) {
	int*** resMat = new int** [4];
	resMat[0] = new int* [n / 2];
	for (int i = 0; i < n / 2; i++)
	{
		resMat[0][i] = new int[m / 2];
		for (int j = 0; j < m / 2; j++)
			resMat[0][i][j] = M[i][j];
	}

	resMat[1] = new int* [n / 2];
	for (int i = 0; i < n / 2; i++)
	{
		resMat[1][i] = new int[m / 2];
		for (int j = 0; j < m / 2; j++)
			resMat[1][i][j] = M[i][j + m / 2];
	}

	resMat[2] = new int* [n / 2];
	for (int i = 0; i < n / 2; i++)
	{
		resMat[2][i] = new int[m / 2];
		for (int j = 0; j < m / 2; j++)
			resMat[2][i][j] = M[i + n / 2][j];
	}

	resMat[3] = new int* [n / 2];
	for (int i = 0; i < n / 2; i++)
	{
		resMat[3][i] = new int[m / 2];
		for (int j = 0; j < m / 2; j++)
			resMat[3][i][j] = M[i + n / 2][j + m / 2];
	}
	return resMat;
}

void deleteArrayLinks(int** M, int len) {
	for (int i = len; i < len; i++) {
		delete[] M[i];
	}
}
void main()
{
	srand(time(NULL));
	int n1, m1, n2, m2, k, l = 2;
	system("chcp 1251");
	cout << "Вас приветствует программа" << endl <<
		"быстрого перемножения матриц методом Штрассена\n\n";

	///////////////////////////////////////////////////////////////////////////////
	////////////////////Ввод размеров матрицы пользователем////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	do
	{
		cout << "Введите размеры первой матрицы\n";
		cin >> n1 >> m1;
	} while (n1 <= 0 || m1 <= 0);
	do
	{
		cout << "Введите размеры второй матрицы\n";
		cin >> n2 >> m2;
	} while (n2 <= 0 || m2 <= 0);

	int** M1 = new int* [n1];
	for (int i = 0; i < n1; i++)
		M1[i] = new int[m1];
	int** M2 = new int* [n2];
	for (int i = 0; i < n2; i++)
		M2[i] = new int[m2];

	///////////////////////////////////////////////////////////////////////////////
	////////////////Выбор способа заполнения и заполнение матриц///////////////////
	///////////////////////////////////////////////////////////////////////////////

	do
	{
		cout << "Выберите способ заполнения матриц\n" <<
			"1 - Вручную \n2 - Случайным образом\n";
		cin >> k;
	} while (k < 1 || k > 2);
	switch (k)
	{
	case 1:
		cout << "\nЗаполнение Матрицы 1\n\n";
		handle_fill_Matrix(n1, m1, M1);
		cout << "\nЗаполнение Матрицы 2\n\n";
		handle_fill_Matrix(n2, m2, M2);

		break;
	case 2:
		random_fill_Matrix(n1, m1, M1);
		random_fill_Matrix(n2, m2, M2);
		break;
	}

	cout << "\nМатрица 1\n\n";
	showMatrix(n1, m1, M1);
	cout << "\nМатрица 2\n\n";
	showMatrix(n2, m2, M2);

	///////////////////////////////////////////////////////////////////////////////
	/////////////////Приведение матриц к требуемому размеру////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	while (l < n1 || l < n2 || l < m1 || l < m2)
		l *= 2;
	
	l += 1; // Теперь для квадратных матриц размерностями равным степеням 2, кроме 0 степеи будет вычислятся произведени матриц без ошибок

	int** M3;
	M3=createNullMatrix(l, l);
	int** M4;
	M4=createNullMatrix(l, l);

	copyMatrix(M3, M1, n1, m1);
	copyMatrix(M4, M2, n2, m2);
	cout << "Приведенные матрицы\n";
	cout << "\nМатрица 1\n\n";
	showMatrix(l, l, M3);
	cout << "\nМатрица 2\n\n";
	showMatrix(l, l, M4);

	///////////////////////////////////////////////////////////////////////////////
	///////////////Разбиение матриц на подматрицы и их заполнение//////////////////
	///////////////////////////////////////////////////////////////////////////////

	int*** splitM3;
	splitM3 = splitMatrixOn4parts(M3, l, l);

	int** subMat1_Mat3 = splitM3[0];
	int** subMat2_Mat3 = splitM3[1];
	int** subMat3_Mat3 = splitM3[2];
	int** subMat4_Mat3 = splitM3[3];

	int*** splitM4;
	splitM4 = splitMatrixOn4parts(M4, l, l);
	int** subMat1_Mat4 = splitM4[0];
	int** subMat2_Mat4 = splitM4[1];
	int** subMat3_Mat4 = splitM4[2];
	int** subMat4_Mat4 = splitM4[3];
	//int** mat1 = new int* [l / 2];
	//for (int i = 0; i < l / 2; i++)
	//{
	//	mat1[i] = new int[l / 2];
	//	for (int j = 0; j < l / 2; j++)
	//		mat1[i][j] = M3[i][j];
	//}
	//int** mat2 = new int* [l / 2];
	//for (int i = 0; i < l / 2; i++)
	//{
	//	mat2[i] = new int[l / 2];
	//	for (int j = 0; j < l / 2; j++)
	//		mat2[i][j] = M3[i][j + l / 2];
	//}
	//int** mat3 = new int* [l / 2];
	//for (int i = 0; i < l / 2; i++)
	//{
	//	mat3[i] = new int[l / 2];
	//	for (int j = 0; j < l / 2; j++)
	//		mat3[i][j] = M3[i + l / 2][j];
	//}
	//int** mat4 = new int* [l / 2];
	//for (int i = 0; i < l / 2; i++)
	//{
	//	mat4[i] = new int[l / 2];
	//	for (int j = 0; j < l / 2; j++)
	//		mat4[i][j] = M3[i + l / 2][j + l / 2];
	//}
	//int** mat5 = new int* [l / 2];
	//for (int i = 0; i < l / 2; i++)
	//{
	//	mat5[i] = new int[l / 2];
	//	for (int j = 0; j < l / 2; j++)
	//		mat5[i][j] = M4[i][j];
	//}
	//int** mat6 = new int* [l / 2];
	//for (int i = 0; i < l / 2; i++)
	//{
	//	mat6[i] = new int[l / 2];
	//	for (int j = 0; j < l / 2; j++)
	//		mat6[i][j] = M4[i][j + l / 2];
	//}
	//int** mat7 = new int* [l / 2];
	//for (int i = 0; i < l / 2; i++)
	//{
	//	mat7[i] = new int[l / 2];
	//	for (int j = 0; j < l / 2; j++)
	//		mat7[i][j] = M4[i + l / 2][j];
	//}
	//int** mat8 = new int* [l / 2];
	//for (int i = 0; i < l / 2; i++)
	//{
	//	mat8[i] = new int[l / 2];
	//	for (int j = 0; j < l / 2; j++)
	//		mat8[i][j] = M4[i + l / 2][j + l / 2];
	//}

	///////////////////////////////////////////////////////////////////////////////
	////////////////////////Создание промежуточных матриц//////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** p1 = createNullMatrix(l / 2, l / 2);
	int** p2 = createNullMatrix(l / 2, l / 2);
	int** p3 = createNullMatrix(l / 2, l / 2);
	int** p4 = createNullMatrix(l / 2, l / 2);
	int** p5 = createNullMatrix(l / 2, l / 2);
	int** p6 = createNullMatrix(l / 2, l / 2);
	int** p7 = createNullMatrix(l / 2, l / 2);

	///////////////////////////////////////////////////////////////////////////////
	////////////////////Вычисление значений промежуточных матриц///////////////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			for (int z = 0; z < l / 2; z++)
			{
				p1[i][j] += (subMat1_Mat3[i][z] + subMat4_Mat3[i][z]) * (subMat1_Mat4[z][j] + subMat4_Mat4[z][j]);
			}

			for (int z = 0; z < l / 2; z++)
			{
				p2[i][j] += (subMat3_Mat3[i][z] + subMat4_Mat3[i][z]) * subMat1_Mat4[z][j];
			}

			for (int z = 0; z < l / 2; z++)
			{
				p3[i][j] += subMat1_Mat3[i][z] * (subMat2_Mat4[z][j] - subMat4_Mat4[z][j]);
			}

			for (int z = 0; z < l / 2; z++)
			{
				p4[i][j] += subMat4_Mat3[i][z] * (subMat3_Mat4[z][j] - subMat1_Mat4[z][j]);
			}

			for (int z = 0; z < l / 2; z++)
			{
				p5[i][j] += (subMat1_Mat3[i][z] + subMat2_Mat3[i][z]) * subMat4_Mat4[z][j];
			}

			for (int z = 0; z < l / 2; z++)
			{
				p6[i][j] += (subMat3_Mat3[i][z] - subMat1_Mat3[i][z]) * (subMat1_Mat4[z][j] + subMat2_Mat4[z][j]);
			}

			for (int z = 0; z < l / 2; z++)
			{
				p7[i][j] += (subMat2_Mat3[i][z] - subMat4_Mat3[i][z]) * (subMat3_Mat4[z][j] + subMat4_Mat4[z][j]);
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////Создание вспомогательных матриц/////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** mat9 = createNullMatrix(l / 2, l / 2);
	int** mat10 = createNullMatrix(l / 2, l / 2);
	int** mat11 = createNullMatrix(l / 2, l / 2);
	int** mat12 = createNullMatrix(l / 2, l / 2);

	///////////////////////////////////////////////////////////////////////////////
	////////////Подсчет значений вспомогательных матриц из промежуточных///////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			mat9[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
			mat10[i][j] = p3[i][j] + p5[i][j];
			mat11[i][j] = p2[i][j] + p4[i][j];
			mat12[i][j] = p1[i][j] - p2[i][j] + p3[i][j] + p6[i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////Создание результирующей матрицы/////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** M5 = createNullMatrix(l , l);

	///////////////////////////////////////////////////////////////////////////////
	///////Занесение информации из вспомогательных матриц в результирующую/////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			M5[i][j] = mat9[i][j];
			M5[i][j + l / 2] = mat10[i][j];
			M5[i + l / 2][j] = mat11[i][j];
			M5[i + l / 2][j + l / 2] = mat12[i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	////////////////Выравнивание границ результирующей матрицы/////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int x = 0, f = 100, s = 100;
	for (int i = 0; i < l; i++)
	{
		x = 0;
		for (int j = 0; j < l; j++)
		{
			if (M5[i][j] != 0)
			{
				x++;
				f = 100;
			}
		}
		if (x == 0 && i < f)
		{
			f = i;
		}
	}
	for (int i = 0; i < l; i++)
	{
		x = 0;
		for (int j = 0; j < l; j++)
		{
			if (M5[j][i] != 0)
			{
				x++;
				s = 100;
			}
		}
		if (x == 0 && i < s)
		{
			s = i;
		}
	}

	int** ResultMatrix = new int* [f];
	for (int i = 0; i < f; i++)
	{
		ResultMatrix[i] = new int[s];
		for (int j = 0; j < s; j++)
			ResultMatrix[i][j] = M5[i][j];
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////Вывод результирующей матрицы////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	cout << "\nРезультирующая матрица\n\n";
	showMatrix(f, s, ResultMatrix);

	system("pause");

	///////////////////////////////////////////////////////////////////////////////
	/////////////////////Очистка динамической памяти///////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 4; i++) {
		deleteArrayLinks(splitM3[i], l);
		deleteArrayLinks(splitM4[i], l);
	}
	deleteArrayLinks(M1, n1);
	deleteArrayLinks(M2, n2);
	deleteArrayLinks(M3, l);
	deleteArrayLinks(M4, l);
	deleteArrayLinks(M5, l);
	deleteArrayLinks(ResultMatrix, f);
	deleteArrayLinks(subMat1_Mat3,l/2);
	deleteArrayLinks(subMat2_Mat3, l / 2);
	deleteArrayLinks(subMat3_Mat3, l / 2);
	deleteArrayLinks(subMat4_Mat3, l / 2);
	deleteArrayLinks(subMat1_Mat4, l / 2);
	deleteArrayLinks(subMat2_Mat4, l / 2);
	deleteArrayLinks(subMat3_Mat4, l / 2);
	deleteArrayLinks(subMat4_Mat4, l / 2);
	deleteArrayLinks(mat9, l / 2);
	deleteArrayLinks(mat10, l / 2);
	deleteArrayLinks(mat11, l / 2);
	deleteArrayLinks(mat12, l / 2);
	deleteArrayLinks(p1, l / 2);
	deleteArrayLinks(p2, l / 2);
	deleteArrayLinks(p3, l / 2);
	deleteArrayLinks(p4, l / 2);
	deleteArrayLinks(p5, l / 2);
	deleteArrayLinks(p6, l / 2);
	deleteArrayLinks(p7, l / 2);

	delete[] M1, M2, M3, M4, M5, ResultMatrix;
	delete[] subMat1_Mat3, subMat2_Mat3, subMat3_Mat3, subMat4_Mat3, subMat1_Mat4, subMat2_Mat4, subMat3_Mat4, subMat4_Mat4, mat9, mat10, mat11, mat12;
	delete[] p1, p2, p3, p4, p5, p6, p7;
	delete[] splitM3, splitM4;
}