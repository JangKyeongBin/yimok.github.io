#include <stdio.h>
#include <stdlib.h>
#include <vector> //vector�� �������� ���̺귯��
#include <math.h> //log,floor ���
#include <time.h> //clock()
#include <iterator> // back_inserter
using std::vector;
int count1 = 0;
int count2 = 0;
#pragma warning(disable:4996)
#define SIZE 502//��� ������ 0�ε����� �����ҰŶ� +1

//�ּ� ���� �˰���
//param : 2�� ���� �迭 M,d,P
//return : ����
void minmult(vector< vector<int> > &M, vector<int> &d, vector< vector<int> > &P)
{
	int i, j, k, diagonal;
	int temp = 0;
	int min,minidx;


	//���� ������ M�迭�� 0���� �̹� �ʱ�ȭ������
	//�迭�ε����� 1���� �����Ѵٰ� �����Ѵ�
	//diagonal������ �밢���� ��ġ�� �ľ��ϱ� ���� �����̴�.
	//���� diagonal�� 1�̶�� ���߾ӿ� �ִ� �밢�� �Ѵܰ� �� �밢���� ���Ѵ�.
	//�� diagonal ���� ����� ������� �E���Ͽ� i�� ������ ���ϰ�, j���� ���� i�� ���� diagonal�� ���Ͽ� 
	//�밢����ġ�� �迭�� �ǵ帱 �� �ְ� �����.
	//�ٽø��ؼ� ��ﰢ��ĸ� �ʿ��ϹǷ� �߾� �밢�� �Ʒ��� ���� �ʿ����.
	for (diagonal = 1; diagonal <= d.size() - 1; diagonal++)
	{
		for (i = 1; i < d.size() - diagonal; i++)
		{
			j = i + diagonal;
			// ��ó�� min���� ������ �ֱ����� ū������ �ʱ�ȭ
			min = 100000000;  



			//M[i][j] = minimum(M[i][k] + M[k+1][j] + di-1 * dk * dj) ����  ���� i <= k <= j-1 
			//i�� j�� �� �������� k���� ���Ѵ�.
			//���� M[1][4] �� ������ Ƚ���� ���Ͽ� �����Ϸ���
			//temp = M[1][1]+M[2][4] + d[0]*d[1]*d[4]
			//temp = M[1][2]+M[3][4] + d[0]*d[2]*d[4]
			//temp = M[1][3]+M[4][4] + d[0]*d[3]*d[4]
		    //�� k���� �����ϸ鼭 ���� ���� Ƚ���� temp �� �����Ͽ� 
			//min ������ �񱳸��ϸ鼭 ������� min�� �����ϰ�
			//���������� for���� �ٵ��� �ּҰ���Ƚ����, �ּҰ��� �ִ� k�� ��ġ�� �����Ѵ�.
			for (k = i; k <= j - 1; k++)
			{
				//�� �μ��� ���ϴ� ���� Ƚ�� ,+ �� �μ��� ���ϴµ� �ʿ��� ������ Ƚ��
				temp  = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];


				
				if (min > temp)
				{
					min = temp;     //���� Ƚ�� ����
					minidx = k; 	//�ּҰ��� �ִ� k�� ��ġ�� �����Ѵ�
				
				}
			}
			
		
			M[i][j] = min;
			P[i][j] = minidx;
		}
	}
}
	


// ���̳ʸ� ������ �о�� ���� 1���� �迭�� �����Ű�� �Լ�.
// parameter : ���� ���� �����ų vector �ּ� , ���ϸ�, ������
// return : ����
void MatrixInit(vector<int> &matrix, char * fname, int num)
{
	FILE *fin;
	fin = fopen(fname, "rb");
	int idx = 0;
	int temp = 0;

	if (fin == NULL)
	{
		printf("���ϸ��� �����ϴ�.\n");
		return ;
	}

	//���ϼӿ� ����� �������� ���� Ȯ���ϱ����� �ݺ���  idx�� �� ����
	while (1)
	{
		if (feof(fin) != 0)
			break;
		fscanf(fin, "%d\n", &temp);
		idx++;
	}
	fseek(fin, 0L, SEEK_SET);			//���� ������ ��ġ�� ó������ ����


	int * arr = new int[idx - 1];		//���� �迭 �Ҵ� ������ idx������ �迭ũ�� ����
	idx = 0;

	//������ �̾Ƽ� arr �����迭�� ���� ��Ű��
	while (1)
	{
		if (feof(fin) != 0)
			break;
		fscanf(fin, "%d\n", &temp);
		arr[idx] = temp;
		idx++;
	}
	fclose(fin);
	
	idx = 0;
	//�� 501���� �����͸� ����
	for (int i = 0; i <= num-1; i++)
	{

		//arr�� �о�� �����͵��� ���� �迭�� ����
		matrix[i] = arr[idx];
		idx++;
	}


	fclose(fin);

}



// ������ ������ ������ִ� �Լ� 
// parameter : ���� ������ fout, ���� P�ּ�, �� p, �� r 
// return : ����
void Order(FILE *fout, vector< vector<int> > &P, int q, int r)
{
	int k;

	if (q == r)
		fprintf(fout, "A%d", q);
	else
	{	
		k = P[q][r];
		fprintf(fout, "(");
		Order(fout, P, q, k);
		Order(fout, P, k+1, r);
		fprintf(fout, ")");
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
	vector < vector<int> > M(Row, vector<int>(Col, 0)); 
	vector < vector<int> > P(Row, vector<int>(Col, 0)); 
	vector<int>  d(SIZE - 1, 0); 

	
	printf("������� �ּҰ����� ���ϴ� �˰����Դϴ�.\n");
	printf("����� .... \n");
	MatrixInit(d, "arr.txt", 501);
    minmult(M, d, P);
	FILE *fout;
	fout = fopen("result.txt", "wt");

	Order(fout, P, 1, 500);
	printf("����� �Ϸ�Ǿ����ϴ�. ����� result.txt�� ����Ǿ����ϴ�.\n\n");
	
	return 0 ;
}