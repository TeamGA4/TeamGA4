#include "Header.h"

//60fps‚Å“®ì‚·‚é‚æ‚¤‚É‚·‚éŠÖ”
void wait_flame()
{
	static int time = 0;
	int term = GetNowCount() - time;

	if (16 - term > 0)
		Sleep(16 - term);
	time = GetNowCount();

	return;
}