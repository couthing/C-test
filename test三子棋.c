#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#define ROW 3
#define COL 3

Menu(){
	printf(".......1.��Ϸ��ʼ.......\n");
	printf(".......2.������Ϸ.......\n");
	printf("���������ѡ��");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

char Map[ROW][COL];
void Init(){
	int i = 0;
	int j = 0;
	for (i = 0; i < ROW; ++i){
		for (j = 0; j < COL; ++j){
			Map[i][j] = ' ';
		}
	}
}

void print(){
	//��ӡ����
	for (int row = 0; row < ROW; ++row){
		printf("| %c  | %c  | %c  |\n", Map[row][0], Map[row][1], Map[row][2]);
		if (row != 2){
			printf("|----|----|----|\n");
		}
	}
}

void PlayerStep(){
	//��ʾ�������
	while (1){
		printf("����������Ҫ���ӵ�����ROW COL:");
		int row = -1;
		int col = -1;
		scanf("%d %d", &row, &col);
		if (row < 0 || row >= ROW || col < 0 || col >= COL){
			printf("��������Ƿ����������������꣡\n");
			continue;
		}
		if (Map[row][col] != ' '){
			printf("�˴���������,��������������!\n");
			continue;
		}
		Map[row][col] = 'o';
		break;
	}
}

void ComputerStep(){
	printf("��������\n");
	srand((unsigned int)time(NULL));
	int row = 0;
	int col = 0;
	while (1){
		row = rand() % 3;
		col = rand() % 3;
		if (Map[row][col] != ' '){
			continue;
		}
		Map[row][col] = 'x';
		break;
	}
}

//�á�o����ʾ��� �á�x����ʾ����
//ʹ��IsWin���������ء�o����ʾ���ʤ�� 
//               ���ء�x����ʾ����ʤ��
//               ���ء�q����ʾ����
//               ���ء� ����ʾʤ��δ��
int IsFull(){
	for (int row = 0; row < ROW; ++row){
		for (int col = 0; row < COL; ++col){
			if (Map[row][col] == ' ')
				return 0;
		}
	}
	return 1;
}

char IsWin(){
	//�����Ϸ�Ƿ����
	//�Ƿ����������������������
	//1.���M��
	int row = 0;
	for (row = 0; row < ROW; ++row){
		if (Map[row][0] == Map[row][1]
			&& Map[row][0] == Map[row][2]
			&& Map[row][0] != ' '){
			return Map[row][0];
		}
	}

	//2.�������
	int col = 0;
	for (col = 0; col < COL; ++col){
		if (Map[0][col] == Map[1][col]
			&& Map[0][col] == Map[2][col]
			&& Map[0][col] != ' '){
			return Map[0][col];
		}
	}

	//3.���б�� 
	if (Map[0][0] == Map[1][1]
		&& Map[0][0] == Map[2][2]
		&& Map[0][0] != ' '){
		return Map[0][0];
	}
	else if (Map[0][3] == Map[1][1]
		&& Map[0][3] == Map[2][0]
		&& Map[0][3] != ' '){
		return Map[0][3];
	}
	//����Ƿ����
	if (IsFull()){
		return 'q';
	}
	return' ';
}

int main(){
	char winner = ' ';
	Init();
	printf("\n");
	int choice = Menu();
	if (choice == 2){
		printf("���Ѿ��˳���Ϸ��!\n");
	}
	while (choice == 1){
		//�ȴ�ӡ����
		print();
		//4.��ʾ������ӣ��������Ϸ�Ƿ����
		PlayerStep();
		winner = IsWin();
		if (winner != ' '){
			break;
		}
		//5.�������ӣ�����Ƿ����
		ComputerStep();
		winner = IsWin();
		if (winner != ' '){
			break;
		}
	}
	if (winner == 'o'){
		printf("��ϲ��,ʤ������\n");
	}
	else if (winner == 'x'){
		printf("����ʤ����\n");
	}
	else if (winner == 'q'){
		printf("���壡\n");
	}
	system("pause");
	return 0;
}

