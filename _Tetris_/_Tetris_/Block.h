#pragma once
#include <graphics.h>
#include <vector>
using namespace std;

struct  Point
{
	int row;
	int col;
};

class Block
{
public:
	Block();
	void drop(); // 降落
	void moveLeftRight(int offset); // 左右移动
	void rotate(); // 旋转
	void draw(int leftMargin,int topMargin); // 绘制方块(左右侧边界)
	int getBlockType(); // 获得方块类型
	Block& operator=(const Block& other);

	bool blockInMap(const vector<vector<int>>&map); // 判断方块是否在地图内
	void solidify(vector<vector<int>>& map); // 固定方块

private:
	int blockType; // 方块类型,1-7
	Point smallBlocks[4];
};

