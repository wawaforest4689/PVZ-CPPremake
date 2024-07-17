#include <winbase.h>
#include <graphics.h>

#pragma once
#ifndef TOOLS_H
#define TOOLS_H

int getdelay()
{
	static unsigned long long int lasttime = 0;
	unsigned long long int currenttime = GetTickCount();
	if (lasttime == 0)
	{
		lasttime = currenttime;
		return 0;
	}

	else
	{
		int interval = currenttime - lasttime;
		lasttime = currenttime;
		return interval;
	}
}

// tackle with black bg problem
void display_enhance(int n, int m, int a, int b, IMAGE input)
{
	DWORD* pmem_input = GetImageBuffer(&input);
	IMAGE temp(a, b);
	DWORD* pmem_temp = GetImageBuffer(&temp);
	for (int i = 0; i < a * b; i++)
	{
		if (pmem_input[i] >= 0 && pmem_input[i] < 0x555555)
			pmem_temp[i] = WHITE;
		else
			pmem_temp[i] = BLACK;
	}
	putimage(n, m, &temp, SRCAND);
	putimage(n, m, &input, SRCPAINT);
}


// file existence judging
bool file(const char* name)
{
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, name, "r");
	if (fp == NULL)
		return 0;
	fclose(fp);
	return 1;
}


#endif