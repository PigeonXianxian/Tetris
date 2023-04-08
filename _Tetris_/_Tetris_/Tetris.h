#pragma once
#include <vector>
#include "Block.h"

#define blockSize 20

using namespace std;

class Tetris
{
public:
	Tetris(int rows,int cols); // ����������������࣬�ϲ���࣬�����С
	void init(); // ��ʼ��
	void play(); // ��ʼ��Ϸ

private:
	void keyEvent(); // �����û�����
	void updateWindow(); // ��Ⱦ����
	void drop(); // ����
	void clearLine(); // ����
	int getDelay(); // ��ȡ��ʱ
	void moveLeftRight(int offset); // ʵ�ַ���������ƶ�
	void rotate(); // ��ת
	void checkover(); // �����Ϸ�Ƿ����
	void saveScore(); // �������
	void drawScore(); // ���Ʒ���

private:
	int delay; // ˢ����ʱ
	bool update; // �ж��Ƿ����

	// 0���հ�
	// 5�������ֶ���˹����
	vector<vector<int>> map; // �洢��ͼ����
	int rows; // ����
	int cols; // ����

	Block* curBlock; // ��ǰ����
	Block* nextBlock; // Ԥ�淽��
	Block bakBlock; // ��ǰ���齵�����������������һ���Ϸ�λ�õı��÷���

	int score; // ��ǰ�ķ���
	bool gameOver; // ��Ϸ�Ƿ����
};

