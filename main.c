#include <Tchar.h>
#include <windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <conio.h>
#include <dirent.h>

void xclear(void);

int main(){}

void xclear(void)
{
	int x = 0, y = 0; char ch;

	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &coninfo);
	coninfo.dwCursorPosition.Y = 0;
	coninfo.dwCursorPosition.X = 0;
	SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);

	int counter, i;

	for (counter = 0; counter < 2000; counter++)
	{
		GetConsoleScreenBufferInfo(hConsole, &coninfo);
		coninfo.dwCursorPosition.Y = y;
		coninfo.dwCursorPosition.X = x;
		SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
jump:
			if (ch = fgetc(stdout) == '\n')
		{
			printf("%c", NULL);
			x = 0;
			y++;
		}
		else
		{ 
			printf("%c", NULL);
			x++;
		}
	}

	GetConsoleScreenBufferInfo(hConsole, &coninfo);
	coninfo.dwCursorPosition.Y = 0;
	coninfo.dwCursorPosition.X = 0;
	SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);

}