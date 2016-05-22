#include <stdio.h>
#include <stdlib.h>
#include <vector> //vector�� �������� ���̺귯��
#include <math.h> //log,floor ���
#include <time.h> //clock()
#include <Windows.h>
using std::vector;

#pragma warning(disable:4996)
#define SIZE 100 //��� ������

//vi - vj ���� ����ġ ���� ����ü
typedef struct edge
{
	int i;    // vi
	int j;    // vj
	int cost;
}edge;

// ����ġ�� �ӽ÷� ������ ����ü
typedef struct distance
{
	int start;
	int length;

}Distance;


//qsort �񱳸� ���� �Լ�
int compare(const void * x, const void * y)
{
	return (*(edge *)x).cost - (*(edge *)y).cost;
}

//�׷��� W���� �����鰣�� ����ġ���� �̾ƿ��� ���� �Լ�
void EdgeInit(edge E[], vector< vector<int> > &W)
{
	int count=0;
	for (int i = 1; i < W.size(); i++)
	{
		for (int j = i; j < W.size(); j++)
		{
			if (i != j)
			{
				E[count].cost = W[i][j];
				E[count].i = i;
				E[count].j = j;
				count++;
			}
		}


	}

}

//���μ� ���յ��� �����ϱ����� �迭������ �ʱ�ȭ
void initial(vector<int>  &Prime)
{
	int i = 0;
	for (i = 0; i < (int)Prime.size(); i++)
	{
		Prime[i] = i;
	}

}

//����ġ�� ���� ��������i�� ���μ� ���տ��� ã�´�.
int find(int i, vector<int>  &Prime)    
{
	int j;
	j = i;
	while (Prime[j] != j)
		j = Prime[j];
	return j;
}


//find �Լ��� ���� p,q ���� ����Ͽ� �񱳸� �ϰ� �� �Լ��� �����Ͽ�
//Prime �迭�� ��ģ��.
void merge(int p, int q, vector<int>  &Prime)   
{
	if (p < q)     
		Prime[q] = p;  
	else
		Prime[p] = q;
}

// kruskal �˰���
// parameter : 2���� �迭 vector, edge ����ü ���� E, edge ����ü ���� F, E 
// return : ����
void kruskal(vector< vector<int> > &W, edge E[], edge F[] ,int Esize)
{
	int i, j, count = 0, num = 0;
	int p, q; // ���μ� üũ
	double start, end; // �ð�����
	edge e;
	vector<int>  Prime((int)W.size(),0);

	//qsort ����, ������ �迭 �����ּ�, �迭 ����� ����, �迭 ��� �ϳ��� ũ��, ���Լ�
	//edge�� cost�� ���� ������������ �����Ѵ�
	qsort(E, Esize, sizeof(edge), compare);
	initial(Prime);  //���μ� ���� �ʱ�ȭ
	
	//���� n�ϋ� n-1 ���� �� �� ���� �ݺ����� ��������
	//�迭�ε��� 1���ͽ����ϹǷ� -2�� ��
	while (count < W.size() - 2)  
	{
		

		e = E[num];
		i = E[num].i;
		j = E[num].j;

		p = find(i, Prime);
		q = find(j, Prime);
		
		if (p != q)
		{
			merge(p, q, Prime);
			F[count] = e;
			count++;

		}

		num++;
	}

}


// Prim �˰���
// parameter : 2���� �迭 vector, edge ����ü ���� F 
// return : ����
void prim(vector< vector<int> > &W, edge F[])
{
	int i, vnear;
	int min;
	edge e;
	//int* nearest = new int[(int)W.size()];  
	vector<int>  nearest((int)W.size(), 0);
	Distance* distance = new Distance[(int)W.size()];
	for (i = 2; i < (int)W.size(); i++)
	{
		nearest[i] = 1;                 // ù ���� v1���� �켱 �ʱ�ȭ
		distance[i].length = W[1][i];   // v1���� vi �� �����ϴ� �������� ����ġ�� �ʱ�ȭ
		distance[i].start = 1;          // �ʱ� v1���� �����ϹǷ� 1�� �ʱ�ȭ �� ����Y = {v1}
	}


	//������ ����ŭ for���� ������.
	for (int i = 2; i < (int)W.size(); i++)
	{
		
		min = 1000;             

		for (int j = 2; j < (int)W.size(); j++)
		{
			//���� ����ġ�� 0�̻��̰�, min ���� �۴ٸ�
			//�� ����ġ�� �ּ��̹Ƿ� min�� �ٽ� �����Ѵ�.
			//�ݺ����� ���� ���� �������ִ� ������ ã�´�.
			if (distance[j].length >= 0 && distance[j].length < min)
			{ 
				min = distance[j].length;  // ����ġ�� min�� �����Ѵ�.
				vnear = j;                 // ������ ����
			}
		}

		F[i - 2].i = distance[vnear].start;    // ���� ���� ����
		F[i - 2].j = vnear;                    // ���� ����� ���� ����
		F[i - 2].cost = min;                   // ����ġ ����	

		distance[vnear].length = -1;

		for (int j = 2; j < (int)W.size(); j++)
		{

			// ������ �����ߴ� ���� Y�� 
			// ������ ���� �����鿡�� vnear ������ ����ġ�� 
			// ����� �ּ� ����ġ�� ���Ѵ�.
			if (W[j][vnear] < distance[j].length)
			{  
				//���� �� ����ġ�� �� ������� 
				// Y�� ������ �Ÿ�(distance[i])�� �ٽ� �����Ѵ�.
				distance[j].length = W[j][vnear];  
				distance[j].start = vnear;          
				nearest[j] = vnear;
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
	char * arr = new char[Row*Col * 3];
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
	for (int i = 0; i <= Row*Col * 3 - 1; i = i + 3)
	{

		//fread�� arr�� �о�� �����͵��� ù��°�� ��, �ι�°�� ��, �׸��� 3��°�� ����ġ�̹Ƿ� 
		//matrix[arr[i]][arr[j]] = arr[idx]; �� ���� �迭�� �����Ų��.
		//�迭�� 0��° �ε����� ������� �����Ƿ� +1�� ����
		matrix[arr[i]+1][arr[j]+1] = arr[idx];
		j = j + 3;
		idx = idx + 3;
	}
	fclose(fin);

}

// �ּҺ�� ����Ʈ�� ���� ���Ϸ� ������ִ� �Լ�
// parameter : ����ü �迭���� F, ���ϸ�, ũ�� 
// return : ����
void MatrixOut(edge F[], char * fname, int size)
{
	FILE *fout;

	fout = fopen(fname, "wt");
	
	for (int i = 0; i < size-1; i++)  //������ ������ -1 �� �ؾ���
	{
			fprintf(fout, "%2d (%3d - %3d  : %3d )",i+1, F[i].i , F[i].j , F[i].cost);
			fprintf(fout, "\n");
	
	}

}
int main()
{

	char fname1[50], fname2[50];

	//�ð������� ���� ����
	LARGE_INTEGER timecheck1, timecheck2, timecheck3, timecheck4;
	LARGE_INTEGER start, end;
	double time1, time2, time3, time4;
	

	// ex) vector<vector<int> >  arr(6, vector<int>(5, 0));
	// ����: vector< vector<int> > �� ���� 6��(���� 6��)�� �Ҵ� �Ѵٴ� ��
	//       vector<int>(5,0) �� ��� �������� 5��¥�� 0���� �ʱ�ȭ �� �͸��� int �� ���� �迭�� ������ �ʱⰪ�� �ִ´�.
	
	
	vector < vector<int> > W1(SIZE + 1, vector<int>(SIZE + 1, 0)); // W1[SIZE][SIZE] �� ���� �迭
	vector < vector<int> > W2(SIZE + 1, vector<int>(SIZE + 1, 0));

	// E �迭 ������ ���ϱ� => ��ﰢ��� 
	int Esize = ( (W1.size()-1 ) * (W1.size()-1 )) / 2 - (W1.size()-1)/2;   
	edge *F1 = new edge[W1.size() -1];       //prim �˰��� 
	edge *F2 = new edge[W2.size() - 1];      //prim �˰���  
	edge *F3 = new edge[W1.size() - 1];      //kruskal �˰���
	edge *F4 = new edge[W2.size() - 1];      //kruskal �˰���
	edge *E1 = new edge[Esize]; // kruskal �˰��� ��� ������ ����
	edge *E2 = new edge[Esize]; // kruskal �˰��� ��� ������ ����                                                                    
	

	printf("Prim �˰���� , Kruskal �˰����� ����Ͽ�  �ּҺ�� ����Ʈ���� ���մϴ�.)\n");
	printf("��������Ʈ�� ǥ���� �׷����� �Է��ϼ���(�Է¼���: denseUdiT.txt -> ���� -> sparseUdiT.txt -> ����) \n");
	scanf("%s %s", fname1,fname2);
	MatrixInit(W1, fname1 , SIZE, SIZE);
	MatrixInit(W2, fname2, SIZE, SIZE);

	printf("�˰��� ����� ...\n\n\n");
	

	//�ð������Լ�, Prim �˰��� ����
	QueryPerformanceFrequency(&timecheck1);
	QueryPerformanceCounter(&start);
	prim(W1, F1);
	QueryPerformanceCounter(&end);
	time1 = (double(end.QuadPart - start.QuadPart) / timecheck1.QuadPart);
	
	//�ð������Լ�, Prim �˰��� ����
	QueryPerformanceFrequency(&timecheck2);
	QueryPerformanceCounter(&start);
	prim(W2, F2);
	QueryPerformanceCounter(&end);
	time2 = (double(end.QuadPart - start.QuadPart) / timecheck2.QuadPart);

	//�ð������Լ�, Kruskal �˰��� ����
	
	EdgeInit(E1, W1);
	QueryPerformanceFrequency(&timecheck3);
	QueryPerformanceCounter(&start);
	kruskal(W1, E1, F3, Esize);
	QueryPerformanceCounter(&end);
	time3 = (double(end.QuadPart - start.QuadPart) / timecheck3.QuadPart);


	//�ð������Լ�, Kruskal �˰��� ����

	EdgeInit(E2, W2);
	QueryPerformanceFrequency(&timecheck4);
	QueryPerformanceCounter(&start);
	kruskal(W2, E2, F4, Esize);
	QueryPerformanceCounter(&end);
	time4 = (double(end.QuadPart - start.QuadPart) / timecheck4.QuadPart);


	//������, �ð����
	printf(" prim %s \t    prim %s\t     kruskal %s \t  kruskal %s  \n",fname1,fname2,fname1,fname2);
	for (int i = 0; i < (int)W1.size() - 2 ; i++)
	{
		printf("%2d (%3d - %3d  : %3d )\t ", i + 1, F1[i].i, F1[i].j, F1[i].cost);
		printf("%2d (%3d - %3d  : %3d )\t    ", i + 1, F2[i].i, F2[i].j, F2[i].cost);
		printf("%2d (%3d - %3d  : %3d )\t  ", i + 1, F3[i].i, F3[i].j, F3[i].cost);
		printf("%2d (%3d - %3d  : %3d )\t ", i + 1, F4[i].i, F4[i].j, F4[i].cost);
		printf("\n");
	}
	printf("Time : %f ns \t Time : %f ns  \t    Time : %f ns  \t   Time : %f ns  \n\n",time1,time2,time3,time4);
	



	//���Ϸ� ����
	MatrixOut(F1, "prim result(dense).txt", W1.size() - 1);
	MatrixOut(F2, "prim result(sparse).txt", W2.size() - 1);
	MatrixOut(F3, "kruskal result(dense).txt", W1.size() - 1);
	MatrixOut(F4, "kruskal result(sprase).txt", W2.size() - 1);
	
	



	// å���ִ� ����Ʈ�� ���ϱ� ////
	vector<vector<int> > W3({
		vector<int>({ 0, 0, 0, 0, 0, 0 }),
		vector<int>({ 0, 0, 1, 3, 101, 101 }),
		vector<int>({ 0, 1, 0, 3, 6, 101 }),
		vector<int>({ 0, 3, 3, 0, 4, 2 }),
		vector<int>({ 0, 101, 6, 4, 0, 5 }),
		vector<int>({ 0, 101, 101, 2, 5, 0 })
	});

	// E �迭 ������ ���ϱ� => ��ﰢ���
	int Esize2 = ((W3.size() - 1) * (W3.size() - 1)) / 2 - (W3.size() - 1) / 2;    
	edge *E3 = new edge[Esize];             // kruskal �˰��� ��� ������ ����  
	edge *F5 = new edge[W1.size() - 1];     //prim �˰���
	edge *F6 = new edge[W2.size() - 1];     //kruskal �˰���

	prim(W3, F5);
	EdgeInit(E3, W3);
	kruskal(W3, E3, F6, Esize2);

	MatrixOut(F5, "prime result(book).txt", W3.size() - 1);
	MatrixOut(F6, "kruskal result(book).txt", W3.size() - 1);
	
	return 0;
	

}