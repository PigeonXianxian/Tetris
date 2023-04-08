#include "Block.h"
#include "winFunction.h"
#include "Tetris.h"
#include <stdlib.h>
#include <iostream>

#include <graphics.h>
#include <conio.h>
#include <stdio.h>

using namespace std;

Block::Block()
{
	// 用一个二维数组表示俄罗斯方块
	int blocks[7][4] =
	{
		1,3,5,7, // 1形方块
		2,4,5,7, // Z 1形
		3,5,4,6, // Z2
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // 田
	};

	// 随机生成一种俄罗斯方块
	blockType = 1 + rand() % 7; // 1-7

	// 初始化 smallBlocks
	for (int i = 0; i < 4; i++)
	{
		int value = blocks[blockType - 1][i];
		smallBlocks[i].row = value / 2;
		smallBlocks[i].col = value % 2;
	}
}

void Block::drop()
{
	for (int i = 0; i < 4; i++)
	{
		smallBlocks[i].row++;
	}
}

void Block::moveLeftRight(int offset)
{
	for (int i = 0; i < 4; i++)
	{
		smallBlocks[i].col += offset;
	}
}

void Block::rotate()
{
	Point p = smallBlocks[1]; // 旋转中心
	
	for (int i = 0; i < 4; i++)
	{
		Point tmp = smallBlocks[i]; // 准备旋转的点
		smallBlocks[i].col = p.col - tmp.row + p.row;
		smallBlocks[i].row = p.row + tmp.col - p.col;
	}
}

void Block::draw(int leftMargin, int topMargin)
{
	for (int i = 0; i < 4; i++)
	{
		int x_ = leftMargin + smallBlocks[i].col;
		int y_ = topMargin + smallBlocks[i].row;
		setlinecolor(RGB(0, 0, 0));
		setfillcolor(HSVtoRGB(blockType * 10, 0.9, 1)); // 根据数值设置方块颜色
		fillrectangle(x_ * blockSize, y_ * blockSize, (x_ + 1) * blockSize, (y_ + 1) * blockSize);
	}
}

int Block::getBlockType()
{
	return blockType;
}

Block& Block::operator=(const Block& other)
{
	if (this == &other) return *this;

	this->blockType = other.blockType;

	for (int i = 0; i < 4; i++)
	{
		this->smallBlocks[i] = other.smallBlocks[i];
	}
	return *this;
}

bool Block::blockInMap(const vector<vector<int>>& map)
{
	int rows = map.size();
	int cols = map[0].size();
	for (int i = 0; i < 4; i++)
	{
		if (smallBlocks[i].col < 0
			|| smallBlocks[i].col >= cols
			|| smallBlocks[i].row < 0
			|| smallBlocks[i].row >= rows
			|| map[smallBlocks[i].row][smallBlocks[i].col])
			return false;
	}
	return true;
}

void Block::solidify(vector<vector<int>>& map)
{
	for (int i = 0; i < 4; i++)
	{
		// 修改地图数据以固定方块
		map[smallBlocks[i].row][smallBlocks[i].col] = blockType;
	}
}
