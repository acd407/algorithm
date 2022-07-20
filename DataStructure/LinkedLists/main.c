#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#pragma GCC diagnostic ignored "-Wint-conversion"
struct line *hCurrent = NULL;

struct line
{
	int data;
	struct line *Next;
	struct line *Last;
};

int CreatOne(void)
{
	int LastBak = hCurrent->Next;				//保存下一个链节的位置
	hCurrent->Next = malloc(3*4);				//创建下一个链节
	if(hCurrent->Next == NULL)return 1;
	
	hCurrent->Next->Last = hCurrent;			//完善新建的链节信息
	hCurrent->Next->Next = LastBak;
	
	hCurrent->Next->Next->Last = hCurrent->Next;
	return 0;
}

int Delete(void)	//自动移到下一个链节
{
	hCurrent = hCurrent->Next;
	int LastBak = hCurrent->Last->Last;	

	free((struct line *)hCurrent->Last);
	
	hCurrent->Last = LastBak;
	hCurrent->Last->Next = hCurrent;
	return 0;
}

int PrintAllData(void)
{
	printf("int : %d\n", hCurrent->data);
	int Start = hCurrent;
	hCurrent = hCurrent->Next;
	while(hCurrent!=Start)
	{
		printf("int : %d\n", hCurrent->data);
		hCurrent = hCurrent->Next;
	}
	return 0;
}

int InputData(void)
{
	printf("Input : ");
	scanf("%d", &(hCurrent->data));
	return 0;
}

int Init(void)
{
	struct line *hpn = NULL, *hpl = NULL;
	hCurrent = (struct line *)malloc(3*4);
	hpn = (struct line *)malloc(3*4);
	hpl = (struct line *)malloc(3*4);
	hCurrent->Next = hpn;
	hCurrent->Last = hpl;
	hpn->Next = hpl;
	hpn->Last = hCurrent;
	hpl->Next = hCurrent;
	hpl->Last = hpn;
	return 0;	
}

int main()
{
	
	int choice = 0;
	Init();
	puts("[C]: Creat One");
	puts("[D]: Delete One");
	puts("[P]: Print Current Data");
	puts("[A]: Print All Data");
	puts("[S]: Set Current Data");
	puts("[N]: Go to Next");
	puts("[L]: Go to Last");
	while(1)
	{
		printf("Input choice : ");
		choice = _getch();
		if(choice == 3)exit(0);
		printf("%c\n", choice);
		switch(choice)
		{
			case 'c' :
				if(CreatOne())puts("Failed!");
				break;
			case 'd' :
				Delete();
				break;
			case 'p' :
				printf("int : %d\n", hCurrent->data);
				break;
			case 'a' :
				PrintAllData();
				break;
			case 's' :
				InputData();
				break;
			case 'n' :
				hCurrent = hCurrent->Next;
				break;
			case 'l' :
				hCurrent = hCurrent->Last;
				break;
			default :
				puts("Input error!");
		}
	}
	return 0;
}