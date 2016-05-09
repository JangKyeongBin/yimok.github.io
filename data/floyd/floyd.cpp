#include <stdio.h>
#include <stdlib.h>
#include <vector> //vector�� �������� ���̺귯��
#include <math.h> //log,floor ���
#include <time.h> //clock()
#include <iterator> // back_inserter
using std::vector;

#pragma warning(disable:4996)
#define SIZE 100 //��� ������

// �׷����� ������� W, �ִܰ�θ� ������ D, �� ������ ������ ���̿� �������� ������ ���� ū �ε����� ����� P  
// parameter : W,D,P 2���� ���� �ּ�
// return : ����
void floyd(vector< vector<int> > &matrixW, vector< vector<int> > &matrixD, vector< vector<int> > &matrixP)
{
	int i, j, k;
	
	std::copy(matrixW.begin(), matrixW.end(), matrixD.begin());  //�迭 ī�� D = W
	
	for (i = 0; i < (int)matrixW.size(); i++)     //�迭�� �����ŭ �ݺ����� ������.
	{
		for (j = 0; j < (int)matrixW.size(); j++)
		{
			matrixP[i][j] = 0;    //0���� �ʱ�ȭ�� ������ 
		}
	}


	for (k = 0; k < (int)matrixW.size(); k++)   // ��λ����� ���İ��� ����
	{
		for (i = 0; i < (int)matrixW.size(); i++)  // ��� ����
		{
			for (j = 0; j < (int)matrixW.size(); j++)  // ���� ����
			{
				if (matrixD[i][k] + matrixD[k][j] < matrixD[i][j]) // ���� ���� ����ġ ������ ���� ���
				{
					matrixP[i][j] = k;  //P�� ���� �������� ������ ���� �� k�� ����(���� ū �ε���)
					matrixD[i][j] = matrixD[i][k] + matrixD[k][j]; //k�� ���İ��� ����ġ�� �� ������� ���ο��� ����ġ�� �Է�
				}
			}
		}
	}




}

// ���̳ʸ� ������ �о�� ���� 2���� �迭�� �����Ű�� �Լ�.
// parameter : ���� ���� �����ų vector �ּ� , ���ϸ�, , �������, �������� 
// return : ����
void MatrixInit(vector< vector<int> > &matrix, char * fname, int Row, int Col)
{
	FILE *fin;
	fin = fopen(fname, "rb");
	char * arr = new char[Row*Col*3];
	int idx = 2;
	int j = 1;

	if (fin == NULL)
	{
		printf("���ϸ��� �����ϴ�.\n");
		return;
	}

	if (fread(arr, Row*Col * 3, 1, fin) != 1)
	{
		printf("����");
		exit(1);
	}

	int count = 0;
	

	//���̳ʸ� ������ �о�� �����Ͱ� �迭�� ��, ��, ����ġ ������ �� 3������ ������ 
	//�� 100x100 �迭�� ǥ���� �� �ִ� �����Ͱ� ����
	for (int i = 0; i <= Row*Col*3 - 1; i=i+3)
	{

		//fread�� arr�� �о�� �����͵��� ù��°�� ��, �ι�°�� ��, �׸��� 3��°�� ����ġ�̹Ƿ� 
		//matrix[arr[i]][arr[j]] = arr[idx]; �� ���� �迭�� �����Ų��.
		matrix[arr[i]][arr[j]] = arr[idx];
		j = j + 3;
		idx=idx + 3;
	}
	fclose(fin);

}


// ���� ������ �� ���� ������ ������ ������ ǥ�����ֱ����� ����Լ� 
// parameter : ���� ������ fout, ���� P�ּ�, �������� q, ������ r 
// return : ����
void OutFilePath(FILE *fout, vector< vector<int> > &P, int q, int r)
{
	if (P[q][r] != 0)
	{	
		OutFilePath(fout, P, q, P[q][r]);
		fprintf(fout, "%d->", P[q][r]);
		OutFilePath(fout, P, P[q][r], r);
	}

}


// OutFilePath �Լ��� ȣ���Ͽ� �� ���� ������ ������ �������� �����Ű�� �Լ�
// parameter : ���ϸ� , ���� P �ּ�
// return : ����
void PathOutput(char *fname, vector< vector<int> > &P)
{
	FILE *fout;
	fout = fopen(fname, "wt");

	for (int i = 0; i < (int)P.size(); i++)
	{
		for (int j = 0; j < (int)P.size(); j++)
		{
			fprintf(fout, "[����:%d]->", i);
			OutFilePath(fout, P, i, j);
			fprintf(fout, "[����:%d]  ", j);
			fprintf(fout, "\n"	);
		}

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
	vector < vector<int> > W1(Row, vector<int>(Col, 0)); // W1[Row][Col] �� ���� �迭
	vector < vector<int> > D1(Row, vector<int>(Col, 0)); // D1[Row][Col] �� ���� �迭
	vector < vector<int> > P1(Row, vector<int>(Col, 0)); // P1[Row][Col] �� ���� �迭
	
	vector < vector<int> > W2(Row, vector<int>(Col, 0)); 
	vector < vector<int> > D2(Row, vector<int>(Col, 0)); 
	vector < vector<int> > P2(Row, vector<int>(Col, 0)); 


	printf("Floyd �˰����� ����Ͽ� �ִܰ�θ� Ž���մϴ�.  \n");

	MatrixInit(W1, "denseG.txt", Row, Col);
	MatrixInit(W2, "sparseG.txt", Row, Col);
	printf("deseG �� sparseG �ִܰ�� Ž���� ....\n");
	floyd(W1, D1, P1);
	floyd(W2, D2, P2);

	PathOutput("result denseG.txt", P1);
	PathOutput("result sparseG.txt", P2);

	printf("�ִܰ�� Ž���� �Ϸ�Ǿ����ϴ�.\n����� result denseG.txt , result sparseG.txt �� ����Ǿ����ϴ�. \n\n");

	return 0;
}