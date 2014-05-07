#include <conio.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>

#define MAX 10

struct Notebook
{
	char name[20];
	int CPU;
	int RAM;
	int HDD;
	int price;
	int visible; // 0 - ������ ��������, 1 - ������ ������
	//Notebook *prev; // ��������� �� ���������� �������
	//Notebook *next; // ��������� �� ��������� �������
};

int menu(); // ������� ����
void add(Notebook *); // ������� ���������� ������
void edit(Notebook *); // ������� �������������� ������
void del(Notebook *); // ������� �������� ������
void outputfile(Notebook *); // ������� ������ ������ � ��������� ����
void outputview(Notebook *); // ������� ������ ��������� ������ �� �����
void outputfileb(Notebook *); // ������� ������ ������ � �������� ����
void outputviewb(Notebook *); // ������� ������ �� ����� ���������� �� ��������� �����
int selectmenuAdd(); // ������� ��������������� ���� ��� ���������� ��������
int selectMenuOut(); // ������� ��������������� ���� ��� ������ ���������� � ���� ��� �� �����
int struct�ycle(Notebook *); // ������� ����� ��� ������� ��������
void clearmas(Notebook *); // ������� ����������� ���� ��������� ������� � 0 ��� ����������� ���������
int selectmenuOutInfo();
void outputscreen(Notebook *); // test


int main()
{
	Notebook notebook[MAX];
	Notebook readmas[MAX];

	clearmas(notebook);

	setlocale(LC_CTYPE, ".1251");

	char choiseMenu;
	char choiseSelectMenu;
	char choiseSelectFile;

	while (exit != 0)
	{
		choiseMenu = menu();
		switch (choiseMenu)
		{
		case 1:
		{
				  add(notebook);
				  do // do while ��� ��� ���������� choiseSelectMenu �� ���� �� ����� 
				  {
					  choiseSelectMenu = selectmenuAdd();
					  switch (choiseSelectMenu)
					  {
					  case 1: add(notebook);
						  break;
					  case 2: choiseMenu; // ���������� choiseMenu ������������� �������� ������-�� ������ ����
						  break;
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
		case 4:
		{
				  do
				  {
					  choiseSelectFile = selectmenuOutInfo();
					  switch (choiseSelectFile)
					  {
					  case 1: outputscreen(readmas);
						  break;
					  case 2: outputfile(notebook);
						  break;
					  case 3: choiseMenu;
						  break;
					  default: printf("������! ������ ������ ���� ���!\n");
						  break;
					  }
				  } while (choiseSelectFile != 3);
		}
			break;
		case 5:
		{
				  choiseSelectMenu = selectMenuOut();
				  switch (choiseSelectMenu)
				  {
				  case 1: outputfile(notebook);
					  break;
				  case 2: outputview(readmas);
					  break;
				  case 3: outputfileb(notebook);
					  break;
				  case 4: outputviewb(readmas);
					  break;
				  default: printf("������! ������ ������ ���� ���!\n");
					  break;
				  }
		}
			break;
		case 6: exit(0);
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
	printf("5. ������ � ������\n");
	printf("6. ����� �� ���������\n");

	fflush(stdin);
	printf("\n������� ����� ������� ������ ����: ");
	scanf_s("%d", &n);

	return n;
}

int selectmenuAdd()
{
	int n;

	printf("1. �������� ����� �������\n");
	printf("2. ��������� � ����\n");

	fflush(stdin);
	printf("\n������� ����� ������� ������ ����: ");
	scanf_s("%d", &n);

	return n;
}

int selectmenuOutInfo()
{
	int n;

	printf("1. ������� �� �����\n");
	printf("2. ������� � ����\n");
	printf("3. ��������� � ������� ����\n");

	fflush(stdin);
	printf("\n������� ����� ������� ������ ����: ");
	scanf_s("%d", &n);

	return n;
}

int selectMenuOut()
{
	int n;

	printf("1. ��������� ��� ������ � ��������� ����\n");
	printf("2. ��������� ��� ������ �� ���������� �����\n");
	printf("3. ��������� ��� ������ � �������� ����\n");
	printf("4. ��������� ��� ������ �� ��������� �����\n");

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

void outputfile(Notebook *notebook) // ��������� ��� ������ � ��������� ����
{
	int i = 1;
	int t;

	FILE *f;

	fopen_s(&f, "������ ���������.txt", "w");

	for (t = 0; t < MAX; t++)
	{
		if ((notebook + t)->visible == 1)
		{
			fprintf(f, "%d;%s;%d;%d;%d;%d \n", i, notebook[t].name, notebook[t].CPU, notebook[t].RAM, notebook[t].HDD, notebook[t].price);
		}
		i++;
	}

	fclose(f);
}

void outputview(Notebook *readmas) // ��������� ��� ������ �� ���������� �����
{
	int i = 1;
	int t;

	FILE *f;

	fopen_s(&f, "������ ���������.txt", "r");

	for (t = 0; t < MAX; t++)
	{
		if ((readmas + t)->visible == 1)
		{
			fscanf_s(f, "%d;%s;%d;%d;%d;%d \n", i, readmas[t].name, readmas[t].CPU, readmas[t].RAM, readmas[t].HDD, readmas[t].price);
		}
		i++;
	}

	fclose(f);
}

void outputfileb(Notebook *notebook) // ��������� ��� ������ � �������� ����
{
	int i = 1;
	int t;

	FILE *f;

	fopen_s(&f, "������ ���������.bd", "wb");

	for (t = 0; t < MAX; t++)
	{
		if ((notebook + t)->visible == 1)
		{
			fwrite(&notebook[t], sizeof(Notebook), 1, f);
		}
	}

	fclose(f);
}

void outputviewb(Notebook *readmas) // ��������� ��� ������ �� ��������� �����
{
	int i = 1;
	int t;

	FILE *f;

	fopen_s(&f, "������ ���������.bd", "rb");
	int count;
	int N = 0;

	do
	{
		count = fread(&readmas[N], sizeof(Notebook), 1, f);
		N++;
	} while (count == 1);
	N--;

	//for (t = 0; t < MAX; t++)
	//{
	//	if ((readmas + t)->visible == 1)
	//	{
	//		fprintf(f, "%d;%s;%d;%d;%d;%d \n", i, readmas[t].name, readmas[t].CPU, readmas[t].RAM, readmas[t].HDD, readmas[t].price);
	//	}
	//	i++;
	//}

	fclose(f);
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

//void outputfile(Notebook *readmas)
//{
//	int i = 1;
//	int t;
//
//	FILE *f;
//
//	fopen_s(&f, "������ ���������.txt", "w");
//
//	fprintf(f, "----------------------------------------------------------------------\n");
//	fprintf(f, "|  �  |       ��������      |   CPU   |   RAM   |   HDD   |   ����   |\n");
//	fprintf(f, "----------------------------------------------------------------------\n");
//
//	for (t = 0; t < MAX; t++)
//	{
//		if ((readmas + t)->visible == 1)
//		{
//			fprintf(f, "%d;%17s;%7d;%7d;%7d;%8d \n", i, readmas[t].name, readmas[t].CPU, readmas[t].RAM, readmas[t].HDD, readmas[t].price);
//		}
//		i++;
//	}
//
//	fprintf(f, "----------------------------------------------------------------------\n");
//
//	fclose(f);
//}

void outputscreen(Notebook *readmas)
{
	int i = 1;
	int t;

	FILE *f;

	f = stdout;

	fprintf(f, "----------------------------------------------------------------------\n");
	fprintf(f, "|  �  |       ��������      |   CPU   |   RAM   |   HDD   |   ����   |\n");
	fprintf(f, "----------------------------------------------------------------------\n");

	//if (outputview)
	//{
		for (t = 0; t < MAX; t++)
		{
			if ((readmas + t)->visible == 1)
			{
				fprintf(f, "%d;%17s;%7d;%7d;%7d;%8d\n", i, readmas[t].name, readmas[t].CPU, readmas[t].RAM, readmas[t].HDD, readmas[t].price);
			}
		}
	//} 
	//else
	//	if (outputviewb)
	//	{

	//	}

	fprintf(f, "----------------------------------------------------------------------\n");
}