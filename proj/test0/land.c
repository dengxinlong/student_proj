#include <stdio.h>
#include "land.h"
#include "config.h"

void usr_land(char *usr_name, char * usr_pwd)
{
	printf("----------please land--------\n");
	printf("usr_name��");
	scanf("%s", usr_name);

	//�ܴaݔ�����
	printf("pwd��");
	char c = 0;
	/*int i = 0;*/
	for (int i = 0; (c = getch()) != '\r'; )					//�І��}
	{
		if (c == '\b')
		{
			if (i > 0 && i < USR_PWD_LEN)
			{
				printf("\b \b");
				usr_pwd[--i] = 0;
			}
		}
		else
		{
			usr_pwd[i] = c;
			printf("*");
			++i;
		}
	}
}