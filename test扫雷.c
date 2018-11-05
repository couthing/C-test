#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MINE_COUNT 5
#define ROW 5
#define COL 5

//游戏菜单
Menu(){
	printf(".......1.游戏开始.......\n");
	printf(".......2.游戏结束.......\n");
	printf("请输入你的选择：");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

//使用二维数组来表示扫雷的地图，此处需要使用两个二维数组
//（1.显示给玩家的-->show_map 2.真实雷的分布-->real_map）
//扫雷的大小为 5 * 5 ，但是把这个数组定义为 7 * 7
//地图有效范围[1,ROW] 和 [1,COL]

//对于 real_map,用'0'表示不是地雷，使用'1'表示是地雷
char real_map[ROW + 2][COL + 2];
//对于 show_map,用'*'表示未打开的方块，打开的方块用具体数字表示（周围8个方块中所含雷的个数）
char show_map[ROW + 2][COL + 2];

void Init(char real_map[ROW + 2][COL + 2], char show_map[ROW + 2][COL + 2]){
	memset(real_map, '0', (ROW + 2)*(COL + 2));
	memset(show_map, '*', (ROW + 2)*(COL + 2));
	//随机布置雷阵，需要引用srand(time(0))作为随机种子
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
	//打印第一行的内容
	printf("    ");
	for (int col = 1; col <= COL; ++col){
		printf(" %d", col);
	}
	printf("\n");
	//打印具体的地图
	//打印第二行，地图上的边框
	for (int col = 1; col <= COL; ++col){
		printf("---");
	}
	printf("\n");
	//按行打印地图
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
	//1.初始化地图(real_map,show_map) 2.随机布置雷阵
	int not_mine_count = 0;
	Init(real_map, show_map);
	//3.打印show_map
	DisplayShowMap(show_map);
	while (choice == 1){
		//4.提示用户输入坐标(ROW,COL)
		printf("请输入您要翻开方块的坐标：");
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		//5.判定用户输入是否合法：
		if (row < 1 || row > ROW || col < 1 || col > COL){
			//    [1]如果不合法，提示用户重新输入 
			printf("输入非法，请重新输入!\n");
			continue;
		}
		//	[2]如果合法，打开show_map上对应坐标的方块，判定此方块是否是雷
		if (real_map[row][col] == '1'){
			//(1)如果是雷，结束游戏  
			printf("踩到雷啦！游戏结束&_&\n");
			DisplayShowMap(real_map);
			break;
		}
		//(2)如果不是雷，需要判定这个方块是不是地图上最后一个非雷方块
		++not_mine_count;
		//<1>如果是输出“恭喜您通关啦！”   
		if (not_mine_count == ROW*COL - MINE_COUNT){
			printf("恭喜您游戏通关啦！\n");
			//<2>如果不是，则继续循环
		}
		//统计当前位置有几个雷，
		UpdateShowMap(show_map, real_map, row, col);
		DisplayShowMap(show_map);
	}
	if (choice == 2){
		printf("您已退出游戏！\n");
	}
	system("pause");
	return 0;
}


