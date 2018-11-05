#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MINE_COUNT 5
#define ROW 5
#define COL 5

//��Ϸ�˵�
Menu(){
	printf(".......1.��Ϸ��ʼ.......\n");
	printf(".......2.��Ϸ����.......\n");
	printf("���������ѡ��");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

//ʹ�ö�ά��������ʾɨ�׵ĵ�ͼ���˴���Ҫʹ��������ά����
//��1.��ʾ����ҵ�-->show_map 2.��ʵ�׵ķֲ�-->real_map��
//ɨ�׵Ĵ�СΪ 5 * 5 �����ǰ�������鶨��Ϊ 7 * 7
//��ͼ��Ч��Χ[1,ROW] �� [1,COL]

//���� real_map,��'0'��ʾ���ǵ��ף�ʹ��'1'��ʾ�ǵ���
char real_map[ROW + 2][COL + 2];
//���� show_map,��'*'��ʾδ�򿪵ķ��飬�򿪵ķ����þ������ֱ�ʾ����Χ8�������������׵ĸ�����
char show_map[ROW + 2][COL + 2];

void Init(char real_map[ROW + 2][COL + 2], char show_map[ROW + 2][COL + 2]){
	memset(real_map, '0', (ROW + 2)*(COL + 2));
	memset(show_map, '*', (ROW + 2)*(COL + 2));
	//�������������Ҫ����srand(time(0))��Ϊ�������
	srand((unsigned int)time(NULL));
	int mine_count = MINE_COUNT;
	while (mine_count > 0){
		int row = rand() % 5 + 1;
		int col = rand() % 5 + 1;
		if (real_map[ROW][COL] == '0'){
			real_map[row][col] = '1';
			--mine_count;
		}
	}
}

void DisplayShowMap(char map[ROW + 2][COL + 2]){
	//��ӡ��һ�е�����
	printf("    ");
	for (int col = 1; col <= COL; ++col){
		printf(" %d", col);
	}
	printf("\n");
	//��ӡ����ĵ�ͼ
	//��ӡ�ڶ��У���ͼ�ϵı߿�
	for (int col = 1; col <= COL; ++col){
		printf("---");
	}
	printf("\n");
	//���д�ӡ��ͼ
	for (int row = 1; row <= ROW; ++row){
		printf("  %d|", row);
		for (int col = 1; col <= COL; ++col){
			printf(" %c", map[row][col]);
		}
		printf("\n");
	}
}

void UpdateShowMap(char show_map[ROW + 2][COL + 2], char real_map[ROW + 2][COL + 2], int row, int col){
	int mine_count = 0;
	if (real_map[row - 1][col - 1] == '1'){
		++mine_count;
	}
	if (real_map[row - 1][col] == '1'){
		++mine_count;
	}
	if (real_map[row - 1][col + 1] == '1'){
		++mine_count;
	}
	if (real_map[row][col - 1] == '1'){
		++mine_count;
	}
	if (real_map[row][col] == '1'){
		++mine_count;
	}
	if (real_map[row][col + 1] == '1'){
		++mine_count;
	}
	if (real_map[row + 1][col - 1] == '1'){
		++mine_count;
	}
	if (real_map[row + 1][col] == '1'){
		++mine_count;
	}
	if (real_map[row + 1][col + 1] == '1'){
		++mine_count;
	}
	show_map[row][col] = '0' + mine_count;
}

int main(){
	int choice = Menu();
	//1.��ʼ����ͼ(real_map,show_map) 2.�����������
	int not_mine_count = 0;
	Init(real_map, show_map);
	//3.��ӡshow_map
	DisplayShowMap(show_map);
	while (choice == 1){
		//4.��ʾ�û���������(ROW,COL)
		printf("��������Ҫ������������꣺");
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		//5.�ж��û������Ƿ�Ϸ���
		if (row < 1 || row > ROW || col < 1 || col > COL){
			//    [1]������Ϸ�����ʾ�û��������� 
			printf("����Ƿ�������������!\n");
			continue;
		}
		//	[2]����Ϸ�����show_map�϶�Ӧ����ķ��飬�ж��˷����Ƿ�����
		if (real_map[row][col] == '1'){
			//(1)������ף�������Ϸ  
			printf("�ȵ���������Ϸ����&_&\n");
			DisplayShowMap(real_map);
			break;
		}
		//(2)��������ף���Ҫ�ж���������ǲ��ǵ�ͼ�����һ�����׷���
		++not_mine_count;
		//<1>������������ϲ��ͨ��������   
		if (not_mine_count == ROW*COL - MINE_COUNT){
			printf("��ϲ����Ϸͨ������\n");
			//<2>������ǣ������ѭ��
		}
		//ͳ�Ƶ�ǰλ���м����ף�
		UpdateShowMap(show_map, real_map, row, col);
		DisplayShowMap(show_map);
	}
	if (choice == 2){
		printf("�����˳���Ϸ��\n");
	}
	system("pause");
	return 0;
}


