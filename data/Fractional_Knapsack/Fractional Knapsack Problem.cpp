#include <stdio.h>
#include <stdlib.h>
#include <vector> //vector�� �������� ���̺귯��
#include <time.h>
using std::vector;
#pragma warning(disable:4996)
#define SIZE 500 //���� ������


// ����ġ,���� ������ �о�� ���� 1���� �迭�� �����Ű�� �Լ�.
// parameter : ���� ���� �����ų vector 1�� �迭 , ���ϸ�
// return : ����
void ArrayInit(vector<int>  &array, char * fname)
{
	FILE *fin;
	fin = fopen(fname, "rb");
	int idx=0, temp = 0;

	if (fin == NULL)
	{
		printf("���ϸ��� �����ϴ�.\n");
		return;
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

	
	
	for (int i = 0; i < SIZE ; i++)
	{

		//arr�� �о�� �����͵��� ���� �迭�� ����
		array[i] = arr[i];

	}


	fclose(fin);

}



// ��ƴ���� ����ä��� �˰��� �Լ�
// parameter : price�� ����� �迭, weight�� ����� �迭 , ������ �뷮
// return : ����
void Fractional_Knapsack(vector<int> &price, vector<int> &weight, int capacity)
{
	int i, max;
	int *used = new int[price.size()];     //������ �ε�����ġ�� �������� ����ߴ��� ���ߴ��� �Ǵ�
	int current_weight;
	double total_value=0;


	//��� ������ �뷮
	current_weight = capacity;
	
	//���� ������̱� ������ 0���� ��� �ʱ�ȭ 
	for (i = 0; i < (int)price.size(); i++)
	{
		used[i] = 0; 
	}
	
	
	//Item�� �����鼭 current_weight�� ��ư���
	//�ִ� ���뷮���� �ݺ����� ����
	while (current_weight > 0) 
	{ 
		
		max = -1;
		
		//���Դ� ��� ������ ���� ���� ������ ��ã�´�.
		for (i = 0; i < (int)price.size(); ++i)
		{
			//���� �������� ������ �� used[i]�� 0�̰� 
			//max�� -1(��ó�� ������) �̰ų�
			//������ ���Է� ���� ������ �������� max �ε����� �������� ū��� 
			//max�� i�� ��ħ
			if ((used[i] == 0) && ((max == -1) || ((double)price[i] / weight[i] >(double)price[max] / weight[max])))
			{
				max = i;
			}
		}

		//�� �ݺ������� ���� ��ȿ���� �������� ���� �˾����Ƿ�
		//�� �ε����� 1�� �Ͽ� ��뿩�θ� ǥ����
		used[max] = 1; 

		//max �������� �ε����� ����Ͽ� ���Կ� ������ �ҷ���
		//current_weight ���� total_value ���� ������
		current_weight -= weight[max]; 
		total_value += price[max];

		//�߰��� �������� �����
		if (current_weight >= 0)
			printf("%3d ��° Item (��ġ:%3d, ����:%3d) �߰� ���� , ���� ���� ���� %d.\n", 
				max , price[max], weight[max], current_weight);
		
		
		//���� �������� �߰��� �������� ����뷮�� �ʰ��ϴ� ���Ը� ������ �ִٸ�
		//�뷮�� �°� ������ ���� ���� �����Ѵ�.
		else 
		{
			printf("%3d ��° Item (��ġ:%3d, ����:%3d)  %2d%% ������ �߰� ���� \n", 
				max, price[max], weight[max],(int)(( 1+(double)current_weight / weight[max]) * 100));
			
			total_value -= price[max];
			total_value += (1+(double)current_weight / weight[max]) * price[max];
		}
	}

	printf("�������� �� ��ġ�� %.0f �Դϴ�.\n", total_value);

}


int main()
{

	char fname1[50], fname2[50];
	int c;

	vector<int>  Price(SIZE , 0); // Price[SIZE] �� ���� �迭
	vector<int>  Weight(SIZE, 0); // Weight[SIZE] �� ���� �迭
	ArrayInit(Price, "price.txt");
	ArrayInit(Weight, "weight.txt");
	
	printf("��ƴ���� �賶ä��� �˰��� �Դϴ�.\n");
	printf("������ �ִ빫�Ը� �Է��ϼ���\n");
	scanf("%d", &c);
	
	Fractional_Knapsack(Price, Weight, (int)c);

	return 0;


}