#include <stdio.h>
#include <stdlib.h>
#include <vector> //vector�� �������� ���̺귯��
#include <math.h> //log,floor ���
#include <time.h> //clock()
using std::vector;

#pragma warning(disable:4996)
#define SIZE 1024 //��� ������

// ���̳ʸ� ������ �о�� ���� 2���� �迭�� �����Ű�� �Լ�.
// parameter : ���� ���� �����ų vector �ּ� , ���ϸ�, , �������, �������� 
// return : ����
void MatrixInit(vector< vector<int> > &matrix, char * fname, int Row, int Col)
{
	FILE *fin;
	fin = fopen(fname, "rb");
	char * arr = new char[Row*Col];
	int idx = 0;

	if (fin == NULL)
	{
		printf("���ϸ��� �����ϴ�.\n");
		return;
	}

	if (fread(arr, Row*Col, 1, fin) != 1)
	{
		printf("����");
		exit(1);
	}


	for (int i = 0; i <= Row - 1; i++)
	{
		for (int j = 0; j <= Col - 1; j++)
		{
			matrix[i][j] =  arr[idx];
			idx++;
		}

	}
	fclose(fin);

}


// ��� A�� B�� ���Ͽ� C�� �����Ű�� �Լ�(A��� B��� C����� ���� ũ��)
// parameter :��� A,B,C 
// return : ����
void MatrixSum(vector< vector<int> > &matrixA, vector< vector<int> > &matrixB, vector< vector<int> > &matrixC)
{

	for (int i = 0; i < (int)matrixA.size(); i++) // matrixA.size() = �� ����
	{
		for (int j = 0; j< (int)matrixA[i].size(); j++) // matrixA.size() = �� ����
		{
			matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
		}
	}

}

// ��� A�� B�� ���� C�� �����Ű�� �Լ�(A��� B��� C����� ���� ũ��)
// parameter : ��� A,B,C 
// return : ����
void MatrixSub(vector< vector<int> > &matrixA, vector< vector<int> > &matrixB, vector< vector<int> > &matrixC)
{
	for (int i = 0; i < (int)matrixA.size(); i++) // matrixA.size() = �� ����
	{
		for (int j = 0; j< (int)matrixA[i].size(); j++) // matrixA.size() = �� ����
		{
			matrixC[i][j] = matrixA[i][j] - matrixB[i][j];
		}
	}


}

// ��� A�� B�� ���Ͽ� C�� �����Ű�� �Լ�(A��� B��� C����� ���� ũ��)
// parameter : ��� A, B, C 
// return : ����
void MatrixMul(vector< vector<int> > &matrixA, vector< vector<int> > &matrixB, vector< vector<int> > &matrixC)
{
	for (int i = 0; i < (int)matrixA.size(); i++) // matrixA.size() = �� ����
	{
		for (int j = 0; j< (int)matrixA[i].size(); j++) // matrixA.size() = �� ����
		{
			for (int k = 0; k < (int)matrixA[i].size(); k++)
			{
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}


}





// �Ӱ谪 ���ϴ� �Լ�
// parameter : ����� ���� �� ���� ���� (ex:1024)
// return : �Ӱ谪 ��ȯ
int getThreshold(int n)
{
	int th;
	double k = floor(log(n) / log(2) - 6);
	th = (int)floor(n / pow(2.0, k)) + 1;
	return th;
}


// 4���� �κ���ķ� ������ �Լ�
// parameter : ���� ���, ������ ��� ���� 4��
// return : ����
void Submatrix(vector< vector<int> > &matrixOrigin, vector< vector<int> > &matrix11, vector< vector<int> > &matrix12,
	vector< vector<int> > &matrix21, vector< vector<int> > &matrix22)
{
	int newNum = matrix11.size();  //�κ������ ������ 

	for (int i = 0; i < newNum; i++)
	{
		for (int j = 0; j < newNum; j++)
		{
			matrix11[i][j] = matrixOrigin[i][j];						//�� ������
			matrix12[i][j] = matrixOrigin[i][j + newNum];				//�� ������
			matrix21[i][j] = matrixOrigin[i + newNum][j];				//�� �ϴ����
			matrix22[i][j] = matrixOrigin[i + newNum][j + newNum];		//�� �ϴ����
		}
	}

}


// 4���� �κ���ĵ��� ����� ���ִ� �Լ�
// parameter : ��ģ ����� ������ ��� , �κ���� 11, 12, 21, 22
// return : ����
void Mergematrix(vector< vector<int> > &matrixOrigin, vector< vector<int> > &matrix11, vector< vector<int> > &matrix12,
	vector< vector<int> > &matrix21, vector< vector<int> > &matrix22)
{
	int newNum = matrix11.size();  //�κ������ ������

	for (int i = 0; i < newNum; i++)
	{
		for (int j = 0; j < newNum; j++)
		{
			matrixOrigin[i][j] = matrix11[i][j];						//�� ������
			matrixOrigin[i][j + newNum] = matrix12[i][j];				//�� ������
			matrixOrigin[i + newNum][j] = matrix21[i][j];         	    //�� �ϴ����
			matrixOrigin[i + newNum][j + newNum] = matrix22[i][j];	    //�� �ϴ����
		}
	}


}





// ��Ʈ�� �˰��� �Լ�
// parameter : ����� ������(ex: 1024x1024 -> 1024�Է�) , ��� A, B, C
// return : ����
void Strassen(int n, vector< vector<int> > &matrixA, vector< vector<int> > &matrixB, vector< vector<int> > &matrixC)
{


	if (n <= getThreshold(n))
	{
		MatrixMul(matrixA, matrixB, matrixC);
		return;
	}
	else
	{
		int newRow = n / 2;					//4����� �ϱ� ����
		vector<int> newCol(newRow, 0);

		//a11~a22 �κ����, b11~b22 �κ���� 
		vector < vector<int> > a11(newRow, newCol), a12(newRow, newCol), a21(newRow, newCol), a22(newRow, newCol);
		vector < vector<int> > b11(newRow, newCol), b12(newRow, newCol), b21(newRow, newCol), b22(newRow, newCol);

		//�κ���ĵ��� �������� m1~m7 ������
		vector < vector<int> > m1(newRow, newCol), m2(newRow, newCol), m3(newRow, newCol), m4(newRow, newCol)
			, m5(newRow, newCol), m6(newRow, newCol), m7(newRow, newCol);

		//a11~b22 �� ���������� �ӽ÷� ������ �׸�
		vector < vector<int> > tempA(newRow, newCol), tempB(newRow, newCol);

		// m1~m7 ���� ����� C�� ���ϱ� ���� ���� �� ���
		vector < vector<int> > c11(newRow, newCol), c12(newRow, newCol), c21(newRow, newCol), c22(newRow, newCol);


		//A�� �κ���� 4��, B�� �κ���� 4�� ����
		Submatrix(matrixA, a11, a12, a21, a22);
		Submatrix(matrixB, b11, b12, b21, b22);


		MatrixSum(a11, a22, tempA);		       // a11+a22
		MatrixSum(b11, b22, tempB);		       // b11+b22
		Strassen(newRow, tempA, tempB, m1);    // m1=(a11+a11)(b11+b22)
		
		MatrixSum(a21, a22, tempA);            // a21+a22
		Strassen(newRow, tempA, b11, m2);      // m2=(a21+a22)b11

		MatrixSub(b12, b22, tempB);            // b12-b22
		Strassen(newRow, a11, tempB, m3);      // m3=a11(b12-b22)

		MatrixSub(b21, b11, tempB);            // b21-b11
		Strassen(newRow, a22, tempB, m4);      // m4=a22(b21-11)

		MatrixSum(a11, a12, tempA);            //  a11+a12
		Strassen(newRow, tempA, b22, m5); 	   // m5=(a11+a12)b22

		MatrixSub(a21, a11, tempA);            // a21-a11
		MatrixSum(b11, b12, tempB);            // b11+b12
		Strassen(newRow, tempA, tempB, m6);    // m6=(a21-a11)(b11+b12)

		MatrixSub(a12, a22, tempA);            // a12-a22
		MatrixSum(b21, b22, tempB);            // b21+b22
		Strassen(newRow, tempA, tempB, m7);    // m7 = (a12 - a22)(a12 - a22)




		// ������ ���� m1~m7 �����  c11 ~ c22 �� �����.
		MatrixSum(m1, m4, tempA); //m1 + m4
		MatrixSum(tempA, m7, tempB); //m1 + m4 + m7
		MatrixSub(tempB, m5, c11); //c11 = m1 + m4 - m5 + m7

		MatrixSum(m3, m5, c12); //c12 = m3 + m5

		MatrixSum(m2, m4, c21); //c21 = m2 + m4

		MatrixSum(m1, m3, tempA); //m1 + m3
		MatrixSum(tempA, m6, tempB); //m1 + m3 + m6
		MatrixSub(tempB, m2, c22); //c22 = m1 + m3 - m2 + m6



		//�� ����
		Mergematrix(matrixC, c11, c12, c21, c22);


	}
}


void FileOutput(char *fname, vector< vector<int> > &matrix)
{
	FILE *fout;
	fout = fopen(fname, "wt");   

	for (int i = 0; i < (int)matrix.size(); i++)
	{
		for (int j = 0; j < (int)matrix.size(); j++)
		{
			fprintf(fout, "%d  ", matrix[i][j]);
		}
		fprintf(fout, "\n");
	}

}



int main()
{
	int Row = SIZE;
	int Col = SIZE;
	char fname1[50], fname2[50];
	int start, end; //�ð�����


	// ex) vector<vector<int> >  arr(6, vector<int>(5, 0));
	// ����: vector< vector<int> > �� ���� 6��(���� 6��)�� �Ҵ� �Ѵٴ� ��
	//       vector<int>(5,0) �� ��� �������� 5��¥�� 0���� �ʱ�ȭ �� �͸��� int �� ���� �迭�� ������ �ʱⰪ�� �ִ´�.

	vector < vector<int> > A(Row, vector<int>(Col, 0)); // A[Row][Col] �� ���� �迭
	vector < vector<int> > B(Row, vector<int>(Col, 0)); // B[Row][Col] �� ���� �迭
	vector < vector<int> > C(Row, vector<int>(Col, 0)); // C[Row][Col] �� ���� �迭
	vector < vector<int> > D(Row, vector<int>(Col, 0)); // D[Row][Col] �� ���� �迭

	printf("A��Ŀ� �Է��� ���ϸ��� �Է��ϼ��� \n( �Է� �� : xxx.txt )");
	scanf("%s", &fname1);
	printf("B��Ŀ� �Է��� ���ϸ��� �Է��ϼ��� \n( �Է� �� : xxx.txt )");
	scanf("%s", &fname2);


	MatrixInit(A, fname1, Row, Col);
	MatrixInit(B, fname2, Row, Col);

	start = clock();
	MatrixMul(A, B, D);
	end = clock();
	printf("Navie matrix multiplication time : %f ms \n", (double)(end - start));

	start = clock();
	Strassen(A.size(), A, B, C);
	end = clock();
	printf("Strassen matrix multiplication time : %f ms \n", (double)(end - start));

	FileOutput("Navie result.txt", D);
	FileOutput("Strassen result.txt", C);
	printf("������ ��� ����� Navie result.txt�� ����Ǿ����ϴ�. \nStrassen ����� Strassen result.txt�� ����Ǿ����ϴ�.\n\n");
	

	return 0;
}