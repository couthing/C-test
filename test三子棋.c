#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#define ROW 3
#define COL 3

Menu(){
	printf(".......1.游戏开始.......\n");
	printf(".......2.结束游戏.......\n");
	printf("请输入你的选择：");
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
	//打印棋盘
	for (int row = 0; row < ROW; ++row){
		printf("| %c  | %c  | %c  |\n", Map[row][0], Map[row][1], Map[row][2]);
		if (row != 2){
			printf("|----|----|----|\n");
		}
	}
}

void PlayerStep(){
	//提示玩家落子
	while (1){
		printf("请您输入想要落子的坐标ROW COL:");
		int row = -1;
		int col = -1;
		scanf("%d %d", &row, &col);
		if (row < 0 || row >= ROW || col < 0 || col >= COL){
			printf("输入坐标非法，请重新输入坐标！\n");
			continue;
		}
		if (Map[row][col] != ' '){
			printf("此处已有棋子,请重新输入坐标!\n");
			continue;
		}
		Map[row][col] = 'o';
		break;
	}
}

void ComputerStep(){
	printf("电脑落子\n");
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

//用‘o’表示玩家 用‘x’表示电脑
//使用IsWin函数，返回‘o’表示玩家胜利 
//               返回‘x’表示电脑胜利
//               返回‘q’表示和棋
//               返回‘ ’表示胜负未分
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
	//检查游戏是否结束
	//是否有三个子相连的情况出现
	//1.检查橫行
	int row = 0;
	for (row = 0; row < ROW; ++row){
		if (Map[row][0] == Map[row][1]
			&& Map[row][0] == Map[row][2]
			&& Map[row][0] != ' '){
			return Map[row][0];
		}
	}

	//2.检查竖行
	int col = 0;
	for (col = 0; col < COL; ++col){
		if (Map[0][col] == Map[1][col]
			&& Map[0][col] == Map[2][col]
			&& Map[0][col] != ' '){
			return Map[0][col];
		}
	}

	//3.检查斜行 
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
	//检查是否和棋
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
		printf("您已经退出游戏啦!\n");
	}
	while (choice == 1){
		//先打印棋盘
		print();
		//4.提示玩家落子，并检查游戏是否结束
		PlayerStep();
		winner = IsWin();
		if (winner != ' '){
			break;
		}
		//5.电脑落子，检查是否结束
		ComputerStep();
		winner = IsWin();
		if (winner != ' '){
			break;
		}
	}
	if (winner == 'o'){
		printf("恭喜您,胜利啦！\n");
	}
	else if (winner == 'x'){
		printf("电脑胜利！\n");
	}
	else if (winner == 'q'){
		printf("和棋！\n");
	}
	system("pause");
	return 0;
}

