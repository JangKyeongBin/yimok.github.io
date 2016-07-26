#include <stdio.h>
#include <stdlib.h>
#include <vector> 
#include <queue>
#include <iostream>

#pragma warning(disable:4996)
#define SIZE 500 //������ ������
using namespace std;
int maxprofit;

//��� ���� ����ü
struct node
{
	int level;
	int w;
	int p;
	float bound;
};

//������ ����ü
struct item
{
	int id;
	float w;
	float p;
};

//�켱���� ť�� 3��° ���� �� ���۷�����
struct cmp{
	bool operator()(node x, node y) 
	{
		return y.bound > x.bound;
		
	}
};


//ť��Ʈ�� ���Լ�
int compare(const void *x, const void *y)
{
	if ((*(item *)y).p / (*(item *)y).w > (*(item *)x).p / (*(item *)x).w)
		return 1;
	else if ((*(item *)y).p / (*(item *)y).w < (*(item *)x).p / (*(item *)x).w)
		return -1;
	else
		return 0;
}

// ����ġ,���� ������ �о�� ���� 1���� �迭�� �����Ű�� �Լ�.
// parameter : ���� ���� �����ų vector 1�� �迭 , ���ϸ�1, ���ϸ�2
// return : ����
void ArrayInit(item  Item[], char * fname1, char *fname2)
{
	FILE *fin1, *fin2;
	fin1 = fopen(fname1, "rb");
	fin2 = fopen(fname2, "rb");
	int idx = 0, temp = 0;

	if (fin1 == NULL || fin2 == NULL)
	{
		printf("���ϸ��� �����ϴ�.\n");
		return;
	}

	//���ϼӿ� ����� �������� ���� Ȯ���ϱ����� �ݺ���  idx�� �� ����
	while (1)
	{
		if (feof(fin1) != 0 || feof(fin2) != 0)
			break;
		fscanf(fin1, "%d\n", &temp);
		idx++;
	}
	fseek(fin1, 0L, SEEK_SET);			//���� ������ ��ġ�� ó������ ����

	//���� �迭 �Ҵ� ������ idx������ �迭ũ�� ����
	int * arr = new int[idx - 1];
	int * arr2 = new int[idx - 1];
	idx = 0;

	//������ �̾Ƽ� arr �����迭�� ���� ��Ű��
	while (1)
	{
		if (feof(fin1) != 0 || feof(fin2) != 0)
			break;
		fscanf(fin1, "%d\n", &temp);
		arr[idx] = temp;
		fscanf(fin2, "%d\n", &temp);
		arr2[idx] = temp;
		idx++;
	}
	fclose(fin1);
	fclose(fin2);

	
	for (int i = 0; i < SIZE; i++)
	{
		//arr�� �о�� �����͵���  ����
		//id��, arr�迭�� ������ price,weight��
		//�ε����� �°� ����ü ������ ������
		Item[i].id = i+1;
		Item[i].p = arr[i];
		Item[i].w = arr2[i];
	}


}


// �Ѱ谪�� ���ϴ� �Լ�
// parameter : �����ǹ���, ������ ��, ���, ������
// return : ���� �Ѱ谪
float bound(int Weight, int n, node u, item ITEM[])
{
	int j, k;
	int totweight;
	float result;

	if (u.w >= Weight)
		return 0;
	else
	{
		result = u.p;
		j = u.level + 1;
		totweight = u.w;
		while (j <= n && totweight + ITEM[j-1].w <= Weight)
		{
			totweight = totweight + ITEM[j-1].w;
			result = result + ITEM[j-1].p;
			j++;
		}
		k = j;
		if (k <= n)
			result = result + (Weight - totweight) * ITEM[k-1].p / ITEM[k-1].w;

		return result;
	}


}

//�켱���� ť �ʱ�ȭ �Լ�
void clear(std::priority_queue<node, vector<node>, cmp > &q)
{
	std::priority_queue<node, vector<node>, cmp > empty;
	std::swap(q, empty);
}


// �б����� ����ġ�� �ְ�켱�˻� �˰���
// parameter : ����, ������, ������ ��
// return : ����
void Branch_and_bound_Knapsack_0_1(int Weight, item ITEM[], int n)
{
	priority_queue <node, vector<node> , cmp > Q;
	node u, v;
	
	//ť �ʱ�ȭ
	clear(Q);

	//��Ʈ ��� ����
	v.level = 0;
	v.p = 0;
	v.w = 0;
	v.bound = bound(Weight, n, v, ITEM);
	
	maxprofit = 0;
	Q.push(v);

	while (!Q.empty())
	{

		v = Q.top();
		
		
		//�ְ��� �Ѱ谪�� ���� ���� ����
		Q.pop();

		//���� ���� ���������� �˻��Ѵ�.
		if (v.bound > maxprofit)
		{
			//��� u�� ���� �������� �����ϴ� �ڽĸ���� ���´�.
			u.level = v.level + 1;
			u.w = v.w + ITEM[u.level-1].w;
			u.p = v.p + ITEM[u.level-1].p;
			
		

			if (u.w <= Weight && u.p > maxprofit)
			{
				maxprofit = u.p;
				//�����ظ� ��� ��� ���� ���
				printf("[level:%3d   price:%d  weight:%d ]\n", u.level, u.p, u.w);
			}
			u.bound = bound(Weight, n, u, ITEM);
			if (u.bound >maxprofit)
				Q.push(u);

			//��� u�� ���� �������� ���������ʴ� �ڽ� ����� ���´�.
			u.w = v.w;
			u.p = v.p;

			u.bound = bound(Weight, n, u, ITEM);
			if (u.bound > maxprofit)
				Q.push(u);

		}

	}

}

// ������ȹ�� ������� ������ 0-1�賶ä���
// parameter : �����ǹ���, �����۵��� ����� ����ü �迭, ������ ��, �����ظ� ������ K, ����Ҷ� �ʿ��� Check�迭
// return : ����
void Dynamic_Knapsack_0_1(int Weight, item ITEM[], int n, vector < vector<int> > &K)
{
	int i, u;
	vector < vector<int> > Check(SIZE + 1, vector<int>(Weight + 1, 0));
	vector<item> Print;
	vector<item>::iterator it;
	//�������� �� i�� ���������� ������Ŵ
	for (i = 0; i <= n; i++)
	{
		//������ ���� u�� �������Ѱ�
		for (u = 0; u <= Weight; u++)
		{
			//Check[i][u] : � �������� �ԷµǾ����� ����� �ϱ����� üũ�ϴ� �迭
			//K[i][u] : ���� <1,...,i>�� �뷮 u kg�� �賶�� ���� �� �ִ� �������� �� ��ġ.
			//���������� i�� n���� ����, u�� weight���� ���� �츮�� ���ϴ� �������� �� ��ġ�� ���� �� �ִ�.
			//��������� ����ذ��鼭 �������� ���� ���Ѵ�.
			//��ȭ�� 3���� ���� �Ʒ�ó�� ǥ���Ѵ�.
			//���� �������� ���ų�, �����ǳ��� ���԰� 0�̸�
			if (i == 0 || u == 0)
			{
				K[i][u] = 0;

			}
			//�������� ���԰� ������ �������Ժ��� Ŀ�� ������� ���Ұ��
			//������n�� ������ �ȿ� ���Ե��� �����Ƿ� �Ʒ��İ� ����.
			else if (ITEM[i - 1].w > u)
			{
				K[i][u] = K[i - 1][u];
				Check[i][u] = 0;
			}

			//�� ������ �ִ°�� �� ����ؼ� �ִ밪�� �����ؾ��Ѵ�.
			//i�� ,u ���� �������Ѱ��鼭 ������ ����Ȱ���, ������ ���� ���غ��鼭 
			//��ġ�� ���� ���� K�� ������Ѽ� �����ظ� ���Ѵ�.
			else if (K[i - 1][u] > ITEM[i - 1].p + K[i - 1][u - ITEM[i - 1].w])
			{
				K[i][u] = K[i - 1][u];
				Check[i][u] = 0;
			}

			//���������� ����������� ���� ��ġ�� �ľ��ϱ�����
			//�ش� �ε�����ġ�� Check �迭�� ���� 1�ιٲ�
			else
			{
				K[i][u] = ITEM[i - 1].p + K[i - 1][u - ITEM[i - 1].w];
				Check[i][u] = 1;
			}
		}
	}
	
	
	//���濡 � �������� �־����� ����ϴ� ����
	u = Weight;
	it = Print.begin();
	
		for (i = n; i >= 1; i--)
		{
			if (Check[i][u] == 1)
			{
				//Check �迭�� �����ϸ鼭 �������� ���� ������
				//�ٽ� Print vector�� �ִµ� Print.begin() �� �迭�� ���� �տ����� �ִ´�.
				//�ᱹ �������������� ������������ ���ĵȻ��·� Print vector�� �����
				it = Print.insert(it, ITEM[i-1]); 
				u = u - ITEM[i-1].w;
			}
		}

		for (int i = 0; i < Print.size(); i++)
			printf("[ID:%3d   price:%3.0f  weight:%3.0f]\n", Print[i].id, Print[i].p, Print[i].w);


}

int main()
{

	char fname1[50], fname2[50];
	int c;
	int itemnum = SIZE, W;
	item ITEM[SIZE];
	
	ArrayInit(ITEM, "price.txt", "weight.txt");
	printf("������ȹ���� �б����� ����ġ�� �ְ�켱�˻� ������� 0/1 �賶ä��⸦ �ϴ�  �˰��� �Դϴ�.\n");
	printf("������ �ִ빫�Ը� �Է��ϼ���\n");
	scanf("%d", &W);
	
	vector < vector<int> > K(itemnum + 1, vector<int>(W + 1, 0));
	vector<item> Print;
	
	//��ġ������ ����
	qsort(ITEM, SIZE, sizeof(item), compare);
	
	printf("������ȹ���� ����� 0-1�賶ä��� �����ذ� �˰���\n");
	Dynamic_Knapsack_0_1(W, ITEM, itemnum, K);
	printf("maxprice : %d \n\n", K[itemnum][W]);

	printf("�б����� ����ġ�� �ְ�켱�˻� ����� ����� 0-1�賶ä��� �����ذ� �˰���\n");
	Branch_and_bound_Knapsack_0_1(W,ITEM,itemnum);
	printf("maxprice : %d \n", maxprofit);

	return 0;

}





