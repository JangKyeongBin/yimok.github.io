
#include <stdio.h>
#include <stdlib.h>
#include <vector> //vector�� �������� ���̺귯��
using std::vector;

//1. Ʈ������ �������� �� ��ӸԴ´�
//2. Ʈ�� ���ʳ����� �Ѵܰ� ��Ʈ��ŷ�ؼ� �����ʰ� �ٸ��� �Դ´�.
//3. ���� �ö󰡸鼭 �ٲ㰡�鼭 �ִ´�.

#pragma warning(disable:4996)
#define SIZE 500 //������ ������

int maxprice, itemnum=SIZE, W, totprice;
int numbest=0; // ���캻 ���ǵ�(���� ���� ���� ���� ����)
vector<char> bestset(SIZE+1, 0); // �ִ� �����϶� ������ ���ǵ�
vector<char> include(SIZE+1, 0); // ���� ������ ���� (������ y, �ȸ����� n )



struct item
{
	int id;
	float w;
	float p;

};



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

	Item[0].p = 0;
	Item[0].w = 0;
	
	for (int i = 1; i <=SIZE; i++)
	{
		//arr�� �о�� �����͵���  ����
		//id��, arr�迭�� ������ price,weight��
		//�ε����� �°� ����ü ������ ������
		Item[i].id = i;
		Item[i].p = arr[i-1];
		Item[i].w = arr2[i-1];
	}



}

//qsort ���Լ�
//���Դ� ��ġ�� ����
int compare(const void *x, const void *y)
{
	if ((*(item *)y).p / (*(item *)y).w > (*(item *)x).p / (*(item *)x).w)
		return 1;
	else if ((*(item *)y).p / (*(item *)y).w < (*(item *)x).p / (*(item *)x).w)
		return -1;
	else
		return 0;
}



// �ش� �������� �����Ѱ��� �Ǵ��ϴ� �Լ�
// parameter : �������� ��, weight , ITEM ����ü �迭 ���� �����ּ�
// return : true / false
bool promising(int i, int weight, item ITEM[])
{
	int j, k;
	int totweight;
	float bound;
	static int o = 1;

	//���̻� �������� �� weight�� ������ ��ġ�� ���Ż��
	if (weight >= W)
		return false;

	else
	{
		//���� �������� �Դ´ٰ� ����������
		//���� �������� �ǹ��ϴ� j��
		//bound �� ���ݱ����� price���� �����Ѵ�
		//totweight�� �켱 ��������� ���Է� �ʱ�ȭ �Ѵ�.
		j = i + 1;     
		bound = totprice;  
		totweight = weight;   

		// ���԰� ����ϴµ� ���� ���� �������� ���Խ�Ų��
		while (j <= itemnum && totweight + ITEM[j].w <= W)
		{       
			totweight = totweight + ITEM[j].w;
			bound = bound + ITEM[j].p;
			j++;
		}

		k = j;  

		// bound�� ����	
		if (k <= itemnum)         
			bound = bound + (W - totweight) * ITEM[k].p / ITEM[k].w;

		return bound > maxprice;
	}
}

// 01 �賶ä��� ������ �˰��� ���� �Լ�
// parameter : �������� ��, price, weight , ITEM ����ü �迭 ���� �����ּ�
// return : ����
void knapsack(int i, int price, int weight, item ITEM[])
{
	// W�� ������ �Ѱ� ����
	// ���԰� ����ϰ� price�� maxprice���� ũ��
	// maxprice �ִ� ������ ���� �������� ����
	if (weight <= W && price > maxprice)
	{
		maxprice = price;    
		numbest = i;
		
		// y, n ���� ����� include ���� bestset�� ������
		// �� ����� �ߴ� ���ߴٸ� ǥ���ϱ� ���� 
		bestset = include;

	}
	
	// ���� �������� ���� �ϴٸ�
	if (promising(i, weight, ITEM))  
	{

		// ���� �������� ���Խ�Ų��
		// Ʈ���� �����ϸ� �ڽĳ���� ���ʳ�����
		include[i + 1] = 'y';     
		
		totprice = price + ITEM[i+1].p;
		knapsack(i + 1, price + ITEM[i + 1].p, weight + ITEM[i + 1].w, ITEM);
		
		// ���� �� ����Լ����� ������ �˻縦 ���� �������� ������ �ǴܵǸ�
		// ���� �������� ���Խ�Ű�� �ʴ´�
		// Ʈ���� ġ�� �ڽĳ���� �����ʳ����� 
		include[i + 1] = 'n';                 
		totprice = price;
		knapsack(i + 1, price, weight, ITEM);
	}
}





int main()
{

	char fname1[50], fname2[50];
	int c;
	item ITEM[SIZE+1];

	
	ArrayInit(ITEM, "price.txt", "weight.txt");
	printf("��Ʈ��ŷ 0/1 �賶ä��� �˰��� �Դϴ�.\n");
	printf("������ �ִ빫�Ը� �Է��ϼ���\n");
	scanf("%d", &W);

	//0��° �ε����� �����ϹǷ�
	//1��° �ε������� ������
	qsort(&ITEM[1], SIZE, sizeof(item), compare);

	knapsack(0, 0, 0, ITEM);
	
	for (int i = 1; i <= SIZE; i++)
	{
		if (bestset[i] == 'y')
			printf("[ID:%3d   price:%3.0f weight:%3.0f]\n", ITEM[i].id,  ITEM[i].p, ITEM[i].w);
	}
	printf("maxprice : %d    \n", maxprice );


	return 0;


}


// ��Ʈ��ŷ: ���̿켱 Ž��
// branch and bound ���� �������� ������ �˻�� ������ -> ���� �켱 Ž��(�ڽĳ�� 2������ ���� �� �ڽĳ���� �ڽĳ��2���� ���� ..)->��,��ť�� ��������