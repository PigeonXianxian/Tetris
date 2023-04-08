#pragma once
#include <vector>
#include "Block.h"

#define blockSize 20

using namespace std;

class Tetris
{
public:
	Tetris(int rows,int cols); // 行数，列数，左侧间距，上部间距，方块大小
	void init(); // 初始化
	void play(); // 开始游戏

private:
	void keyEvent(); // 接受用户输入
	void updateWindow(); // 渲染界面
	void drop(); // 下落
	void clearLine(); // 清行
	int getDelay(); // 获取延时
	void moveLeftRight(int offset); // 实现方块的左右移动
	void rotate(); // 旋转
	void checkover(); // 检查游戏是否结束
	void saveScore(); // 保存分数
	void drawScore(); // 绘制分数

private:
	int delay; // 刷新延时
	bool update; // 判断是否更新

	// 0：空白
	// 5：第五种俄罗斯方块
	vector<vector<int>> map; // 存储地图数据
	int rows; // 行数
	int cols; // 列数

	Block* curBlock; // 当前方块
	Block* nextBlock; // 预告方块
	Block bakBlock; // 当前方块降落过程中用来备份上一个合法位置的备用方块

	int score; // 当前的分数
	bool gameOver; // 游戏是否结束
};

