#include "Tetris.h"
#include "Block.h"
#include "winFunction.h"
#include <stdlib.h>
#include <iostream>

#include <graphics.h>
#include <conio.h>
#include <stdio.h>

using namespace std;

const int SPEED_NORMAL = 500; // ms
const int SPEED_QUICK = 50;

Tetris::Tetris(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;

	for (int i = 0; i < rows; i++)
	{
		vector<int> mapRow;
		for (int j = 0; j < cols; j++)
		{
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
}

void Tetris::init()
{
	initgraph((cols+10)*blockSize, rows * blockSize); // 创建新画面

	delay = SPEED_NORMAL;
	gameOver = false;
	score = 0;

	for (int i = 0; i < rows; i++) // 初始化游戏数据
	{
		for (int j = 0; j < cols; j++)
		{
			map[i][j] = 0;
		}
	}

	// 配置随机种子
	srand(time(NULL));
}

void Tetris::play()
{
	init();

	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

	int timer = 0;
	while (1)
	{
		keyEvent(); // 接受用户输入

		timer += getDelay();
		if (timer > delay)
		{
			timer = 0;
			drop();
			update = true;
		}

		if (update)
		{
			update = false;
			updateWindow(); // 更新画面
			clearLine(); // 更新数据
		}

		if (gameOver)
		{
			// 保存分数
			saveScore();

			// 更新游戏结束界面
			// displayOver();

			system("pause");
			init(); // 重新开局
		}
	}
}

void Tetris::keyEvent()
{
	unsigned char ch; // 接收输入
	bool rotateFlag = false;
	int dx = 0; // 偏移量

	if (_kbhit()) // 如果有按键输入
	{
		ch = _getch();
		if (ch == 224) // 按下了上下左右
		{
			ch = _getch();
			switch (ch)
			{
			case 72: // 上
				rotateFlag = true;
				break;
			case 80: // 下
				delay = SPEED_QUICK;
				break;
			case 75: // 左
				dx = -1;
				break;
			case 77: // 右
				dx = 1;
				break;
			default:
				break;
			}
		}
	}

	if (rotateFlag)
	{
		rotate();
		update = true;
	}

	if (dx != 0)
	{
		moveLeftRight(dx); // 实现左右移动
		update = true;
	}
}

void Tetris::updateWindow()
{
	BeginBatchDraw();
	// 绘制地图
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			setlinecolor(RGB(0,0,0));
			if (map[i][j] > 0) // 如果有方块
				setfillcolor(HSVtoRGB(map[i][j] * 10, 0.9, 1)); // 根据数值设置方块颜色
			else
				setfillcolor(RGB(0, 0, 0));
			fillrectangle(j * blockSize, i * blockSize, (j + 1) * blockSize, (i + 1) * blockSize);
		}
	}

	//擦除旧的预告方块
	setfillcolor(RGB(0, 0, 0));
	fillrectangle((cols + 5) * blockSize, blockSize, (cols + 7) * blockSize, 5 * blockSize);
	
	curBlock->draw(0,0);
	nextBlock->draw(cols+5, 1);

	drawScore(); // 绘制分数

	EndBatchDraw();
}

void Tetris::drop()
{
	bakBlock = *curBlock;
	curBlock->drop();

	if (!(curBlock->blockInMap(map))) // 方块不可再移动，固定方块
	{
		bakBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;

		// 检查游戏是否结束
		checkover();
	}

	delay = SPEED_NORMAL;
}

void Tetris::clearLine()
{
	int lines = 0;
	int k = rows - 1; // 存储数据的行数
	for (int i = rows - 1; i >= 0; i--)
	{
		// 检查第i行是否满行
		int count = 0;
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j])
				count++;
			map[k][j] = map[i][j]; // 一边扫描一边存储
		}

		if (count < cols)
		{
			// 不是满行
			k--;
		}
		else
		{
			// 满行
			lines++;
		}
	}

	if (lines > 0)
	{
		int addScore[4] = { 10,30,60,80 };
		score += addScore[lines - 1];
		update = true;
	}
}

// 第一次调用，返回0
// 返回距离上一次调用间隔了多少ms
int Tetris::getDelay()
{
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();

	if (lastTime == 0)
	{
		lastTime = currentTime;
		return 0;
	}
	else
	{
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}

	return 0;
}

void Tetris::moveLeftRight(int offset)
{
	bakBlock = *curBlock;
	curBlock->moveLeftRight(offset);

	if (!(curBlock->blockInMap(map))) // 检测位置是否合法
	{
		*curBlock = bakBlock;
	}
}

void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7)
		return;
	bakBlock = *curBlock;
	curBlock->rotate();

	if (!(curBlock->blockInMap(map))) // 检测位置是否合法
	{
		*curBlock = bakBlock;
	}
}

void Tetris::checkover()
{
	gameOver = (curBlock->blockInMap(map) == false);

}

void Tetris::saveScore()
{
	/*if (score > highestScore)
	{
		highestScore = score;

		ofstream file(RECORDER_FILE);
	}*/
}

void Tetris::drawScore()
{
	TCHAR scoreText[32];
	_itow_s(score, scoreText, 10);
	settextcolor(RGB(255, 255, 255)); // 设置字体颜色
	settextstyle(40, 0, _T("微软雅黑")); // 设置字体大小、样式
	outtextxy((cols + 6) * blockSize, (rows - 5) * blockSize, scoreText);// 输出字体
	settextstyle(30, 0, _T("微软雅黑"));
	outtextxy((cols + 4.5) * blockSize, (rows - 7) * blockSize, _T("SCORE"));
}

