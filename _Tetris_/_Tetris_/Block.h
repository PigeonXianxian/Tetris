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
	void drop(); // ����
	void moveLeftRight(int offset); // �����ƶ�
	void rotate(); // ��ת
	void draw(int leftMargin,int topMargin); // ���Ʒ���(���Ҳ�߽�)
	int getBlockType(); // ��÷�������
	Block& operator=(const Block& other);

	bool blockInMap(const vector<vector<int>>&map); // �жϷ����Ƿ��ڵ�ͼ��
	void solidify(vector<vector<int>>& map); // �̶�����

private:
	int blockType; // ��������,1-7
	Point smallBlocks[4];
};

