#include <conio.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define MAX 100

struct Notebook
{
	char name[20];
	int CPU;
	int RAM;
	int HDD;
	int price;
	int visible; // 0 - ������ ��������, 1 - ������ ������
};

int menu(); // ������� ����
void add(Notebook *); // ������� ���������� ��������
void del(Notebook *); // ������� �������� ������
void edit(Notebook *); // ������� �������������� ������
void output(Notebook *); // ������� ������ ������ ��������� �������
int selectmenu(); // ������� ��������������� ����
int struct�ycle(Notebook *); // ������� ����� ��� ������� ��������
void clearmas(Notebook *);


int main()
{
	Notebook notebook[MAX];

	clearmas(notebook);

	setlocale(LC_CTYPE, ".1251");

	char choiseMenu;
	char choiseSelectMenu;

	while (exit != 0)
	{
		choiseMenu = menu();
		switch (choiseMenu)
		{
		case 1:
		{
				  add(notebook);//
				  do // do while ��� ��� ���������� choiseSelectMenu �� ���� �� ����� 
				  {
					  choiseSelectMenu = selectmenu();
					  switch (choiseSelectMenu)
					  {
					  case 1: add(notebook);
						  break;
					  case 2: choiseMenu; // ���������� choiseMenu ������������� �������� ������-�� ������ ����
						  break;
					  case 3: exit(0);
					  default: printf("������! ������ ������ ���� ���!\n");
						  break;
					  }
				  } while (choiseSelectMenu != 2);
		}
			break;
		case 2: edit(notebook);
			break;
		case 3: del(notebook);
			break;
		case 4: output(notebook);
			break;
		case 5: exit(0);
		default: printf("������! ������ ������ ���� ���!\n");
			break;
		}
	}
	_getch();
}

int menu()
{
	int n;

	printf("�������� ����� ������ ����!\n");
	printf("1. �������� ����� �������\n");
	printf("2. ������������� ������ � ��������\n");
	printf("3. ������� �������\n");
	printf("4. ������� ��� ������ � ��������\n");
	printf("5. ����� �� ���������\n");

	fflush(stdin);
	printf("\n������� ����� ������� ������ ����: ");
	scanf_s("%d", &n);

	return n;
}

int selectmenu()
{
	int n;

	printf("1. �������� ����� �������\n");
	printf("2. ��������� � ����\n");
	printf("3. ����� �� ���������\n");

	fflush(stdin);
	printf("\n������� ����� ������� ������ ����: ");
	scanf_s("%d", &n);

	return n;
}

void add(Notebook *notebook)
{
	int slot;

	slot = struct�ycle(notebook);

	printf("������� ����� � ������ ��������: ");
	fflush(stdin);
	gets_s(notebook[slot].name);
	printf("������� CPU ��������: ");
	scanf_s("%d", &notebook[slot].CPU);
	printf("������� RAM ��������: ");
	scanf_s("%d", &notebook[slot].RAM);
	printf("������� HDD ��������: ");
	scanf_s("%d", &notebook[slot].HDD);
	printf("������� ���� ��������: ");
	scanf_s("%d", &notebook[slot].price);


	(notebook + slot)->visible = 1;
}

void edit(Notebook *notebook)
{
	int slot;

	printf("������� � ������ ��� ��������������: ");
	scanf_s("%d", &slot);

	for (int t = 0; t < MAX; t++)
	{
		if ((notebook + t)->visible == 1)
		{
			slot--;
			printf("�������� ����� � ������ �������� (%s): ", notebook[slot].name);
			fflush(stdin);
			gets_s(notebook[slot].name);
			printf("�������� CPU �������� (%d): ", notebook[slot].CPU);
			scanf_s("%d", &notebook[slot].CPU);
			printf("�������� RAM �������� (%d): ", notebook[slot].RAM);
			scanf_s("%d", &notebook[slot].RAM);
			printf("�������� HDD �������� (%d): ", notebook[slot].HDD);
			scanf_s("%d", &notebook[slot].HDD);
			printf("�������� ���� �������� (%d): ", notebook[slot].price);
			scanf_s("%d", &notebook[slot].price);
			break;
		}
	}
}

void del(Notebook *notebook)
{
	int slot;

	printf("������� � ������ ��� ��������: ");
	scanf_s("%d", &slot);


	for (int t = 0; t < MAX; t++)
	{
		if ((notebook + t)->visible == 1)
		{
			slot--;
		}
		if (slot == 0)
		{
			(notebook + t)->visible = 0;
			break;
		}
	}

	if (slot == 0)
		printf("������� �����\n");
	else
		printf("�� ���������� ������ ��������\n");

}

void output(Notebook *notebook)
{
	int i = 1;
	int t;

	printf("----------------------------------------------------------------------\n");
	printf("|  �  |       ��������      |   CPU   |   RAM   |   HDD   |   ����   |\n");
	printf("----------------------------------------------------------------------\n");

	for (t = 0; t < MAX; t++)
	{
		if ((notebook + t)->visible == 1)
		{
			printf("| %3d ", i);
			i++;
			printf("|%17s    ", notebook[t].name);

			printf("| %7d |", notebook[t].CPU);
			printf(" %7d |", notebook[t].RAM);
			printf(" %7d |", notebook[t].HDD);
			printf(" %8d |\n", notebook[t].price);
		}
	}
	printf("----------------------------------------------------------------------\n");
}

int struct�ycle(Notebook *notebook)
{
	register int t;

	for (t = 0; t < MAX; t++)
	{
		if ((notebook + t)->visible == 0)  // ���� ������ ������
			return t;
	}
}

void clearmas(Notebook *notebook)
{
	register int t;

	for (t = 0; t < MAX; t++)
	{
		(notebook + t)->visible = 0;  // ���� ������ ������
	}
}