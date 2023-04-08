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
	initgraph((cols+10)*blockSize, rows * blockSize); // �����»���

	delay = SPEED_NORMAL;
	gameOver = false;
	score = 0;

	for (int i = 0; i < rows; i++) // ��ʼ����Ϸ����
	{
		for (int j = 0; j < cols; j++)
		{
			map[i][j] = 0;
		}
	}

	// �����������
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
		keyEvent(); // �����û�����

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
			updateWindow(); // ���»���
			clearLine(); // ��������
		}

		if (gameOver)
		{
			// �������
			saveScore();

			// ������Ϸ��������
			// displayOver();

			system("pause");
			init(); // ���¿���
		}
	}
}

void Tetris::keyEvent()
{
	unsigned char ch; // ��������
	bool rotateFlag = false;
	int dx = 0; // ƫ����

	if (_kbhit()) // ����а�������
	{
		ch = _getch();
		if (ch == 224) // ��������������
		{
			ch = _getch();
			switch (ch)
			{
			case 72: // ��
				rotateFlag = true;
				break;
			case 80: // ��
				delay = SPEED_QUICK;
				break;
			case 75: // ��
				dx = -1;
				break;
			case 77: // ��
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
		moveLeftRight(dx); // ʵ�������ƶ�
		update = true;
	}
}

void Tetris::updateWindow()
{
	BeginBatchDraw();
	// ���Ƶ�ͼ
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			setlinecolor(RGB(0,0,0));
			if (map[i][j] > 0) // ����з���
				setfillcolor(HSVtoRGB(map[i][j] * 10, 0.9, 1)); // ������ֵ���÷�����ɫ
			else
				setfillcolor(RGB(0, 0, 0));
			fillrectangle(j * blockSize, i * blockSize, (j + 1) * blockSize, (i + 1) * blockSize);
		}
	}

	//�����ɵ�Ԥ�淽��
	setfillcolor(RGB(0, 0, 0));
	fillrectangle((cols + 5) * blockSize, blockSize, (cols + 7) * blockSize, 5 * blockSize);
	
	curBlock->draw(0,0);
	nextBlock->draw(cols+5, 1);

	drawScore(); // ���Ʒ���

	EndBatchDraw();
}

void Tetris::drop()
{
	bakBlock = *curBlock;
	curBlock->drop();

	if (!(curBlock->blockInMap(map))) // ���鲻�����ƶ����̶�����
	{
		bakBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;

		// �����Ϸ�Ƿ����
		checkover();
	}

	delay = SPEED_NORMAL;
}

void Tetris::clearLine()
{
	int lines = 0;
	int k = rows - 1; // �洢���ݵ�����
	for (int i = rows - 1; i >= 0; i--)
	{
		// ����i���Ƿ�����
		int count = 0;
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j])
				count++;
			map[k][j] = map[i][j]; // һ��ɨ��һ�ߴ洢
		}

		if (count < cols)
		{
			// ��������
			k--;
		}
		else
		{
			// ����
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

// ��һ�ε��ã�����0
// ���ؾ�����һ�ε��ü���˶���ms
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

	if (!(curBlock->blockInMap(map))) // ���λ���Ƿ�Ϸ�
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

	if (!(curBlock->blockInMap(map))) // ���λ���Ƿ�Ϸ�
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
	settextcolor(RGB(255, 255, 255)); // ����������ɫ
	settextstyle(40, 0, _T("΢���ź�")); // ���������С����ʽ
	outtextxy((cols + 6) * blockSize, (rows - 5) * blockSize, scoreText);// �������
	settextstyle(30, 0, _T("΢���ź�"));
	outtextxy((cols + 4.5) * blockSize, (rows - 7) * blockSize, _T("SCORE"));
}

