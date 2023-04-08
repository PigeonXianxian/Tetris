#ifndef _winFunction_h
#define _winFunction_h

#include <Windows.h>

void Gotoxy(int x, int y); // 1）控制台运行中，可以将光标移动到指定位置(x,y)，之后cout输出的内容将在(x,y)开始输出
void Setcolor(int color);  // 2）控制台运行中，可以设置输出的字符的颜色，颜色号包括：0黑色1蓝色2绿色3青色 4红色5紫色6黄色7白
void HideCursor(); // 3）控制台运行中，如果不希望看到光标闪烁，可以隐藏光标

#endif // !_winFunction_h

