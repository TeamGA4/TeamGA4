#include "Header.h"

//60fpsで動作するようにする関数
void wait_flame()
{
	static int time = 0;
	int term = GetNowCount() - time;

	if (16 - term > 0)
		Sleep(16 - term);
	time = GetNowCount();

	return;
}