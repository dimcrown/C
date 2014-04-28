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
	int visible; // 0 - ячейка свободна, 1 - ячейка занята
};

int menu(); // функция меню
void add(Notebook *); // функция добавления ноутбука
void del(Notebook *); // функция удаления записи
void edit(Notebook *); // функция редактирования записи
void outputfile(Notebook *); // функция вывода данных в текстовый файл
void outputview(Notebook *); // функция вывода данных на экран
void outputfileb(Notebook *); // функция вывода данных в бинарный файл
int selectmenu(); // функция дополнительного меню
int structСycle(Notebook *); // функция цикла для массива структур
void clearmas(Notebook *);
int selectMenuOut();


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
				  do // do while так как переменная choiseSelectMenu ни чему не равна 
				  {
					  choiseSelectMenu = selectmenu();
					  switch (choiseSelectMenu)
					  {
					  case 1: add(notebook);
						  break;
					  case 2: choiseMenu; // переменной choiseMenu присваевается значение какого-то пункта меню
						  break;
					  case 3: exit(0);
					  default: printf("Ошибка! Такого пункта меню нет!\n");
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
			choiseSelectMenu = selectMenuOut();
			switch (choiseSelectMenu)
			{
			case 1: outputfile(notebook);
				break;
			case 2: outputview(notebook);
				break;
			case 3: outputfileb(notebook);
				break;
			default: printf("Ошибка! Такого пункта меню нет!\n");
				break;
			}
		}
			break;
		case 5: exit(0);
		default: printf("Ошибка! Такого пункта меню нет!\n");
			break;
		}
	}
	_getch();
}

int menu()
{
	int n;

	printf("Выберите цифру пункта меню!\n");
	printf("1. Добавить новый ноутбук\n");
	printf("2. Редактировать данные о ноутбуке\n");
	printf("3. Удалить ноутбук\n");
	printf("4. Вывести все данные о ноутбуке\n");
	printf("5. Выйти из программы\n");

	fflush(stdin);
	printf("\nВведите номер нужного пункта меню: ");
	scanf_s("%d", &n);

	return n;
}

int selectmenu()
{
	int n;

	printf("1. Добавить новый ноутбук\n");
	printf("2. Вернуться в меню\n");
	printf("3. Выйти из программы\n");

	fflush(stdin);
	printf("\nВведите номер нужного пункта меню: ");
	scanf_s("%d", &n);

	return n;
}

int selectMenuOut()
{
	int n;

	printf("1. Сохранить все данные в файл\n");
	printf("2. Вывести все данные на экран\n");
	printf("3. Вывести все данные в бинарный файл\n");

	fflush(stdin);
	printf("\nВведите номер нужного пункта меню: ");
	scanf_s("%d", &n);

	return n;
}

void add(Notebook *notebook)
{
	int slot;

	slot = structСycle(notebook);

	printf("Введите марку и модель ноутбука: ");
	fflush(stdin);
	gets_s(notebook[slot].name);
	printf("Введите CPU ноутбука: ");
	scanf_s("%d", &notebook[slot].CPU);
	printf("Введите RAM ноутбука: ");
	scanf_s("%d", &notebook[slot].RAM);
	printf("Введите HDD ноутбука: ");
	scanf_s("%d", &notebook[slot].HDD);
	printf("Введите цену ноутбука: ");
	scanf_s("%d", &notebook[slot].price);


	(notebook + slot)->visible = 1;
}

void edit(Notebook *notebook)
{
	int slot;

	printf("Введите № записи для редактирования: ");
	scanf_s("%d", &slot);

	for (int t = 0; t < MAX; t++)
	{
		if ((notebook + t)->visible == 1)
		{
			slot--;
			printf("Измените марку и модель ноутбука (%s): ", notebook[slot].name);
			fflush(stdin);
			gets_s(notebook[slot].name);
			printf("Измените CPU ноутбука (%d): ", notebook[slot].CPU);
			scanf_s("%d", &notebook[slot].CPU);
			printf("Измените RAM ноутбука (%d): ", notebook[slot].RAM);
			scanf_s("%d", &notebook[slot].RAM);
			printf("Измените HDD ноутбука (%d): ", notebook[slot].HDD);
			scanf_s("%d", &notebook[slot].HDD);
			printf("Измените цену ноутбука (%d): ", notebook[slot].price);
			scanf_s("%d", &notebook[slot].price);
			break;
		}
	}
}

void del(Notebook *notebook)
{
	int slot;

	printf("Введите № записи для удаления: ");
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
		printf("Ноутбук удалён\n");
	else
		printf("Не существует такого ноутбука\n");

}

void outputfile(Notebook *notebook)
{
	int i = 1;
	int t;

	FILE *f;

	fopen_s(&f, "Список ноутбуков.txt", "w");

	fprintf(f, "----------------------------------------------------------------------\n");
	fprintf(f, "|  №  |       Название      |   CPU   |   RAM   |   HDD   |   цена   |\n");
	fprintf(f, "----------------------------------------------------------------------\n");
	
	for (t = 0; t < MAX; t++)
	{
		if ((notebook + t)->visible == 1)
		{
			fprintf(f, "%d;%17s;%7d;%7d;%7d;%8d \n", i, notebook[t].name, notebook[t].CPU, notebook[t].RAM, notebook[t].HDD, notebook[t].price);
		}
		i++;
	}

	fprintf(f, "----------------------------------------------------------------------\n");

	fclose(f);
}

void outputview(Notebook *notebook)
{
	int i = 1;
	int t;

	FILE *f;

	f = stdout;

	fprintf(f, "----------------------------------------------------------------------\n");
	fprintf(f, "|  №  |       Название      |   CPU   |   RAM   |   HDD   |   цена   |\n");
	fprintf(f, "----------------------------------------------------------------------\n");

	for (t = 0; t < MAX; t++)
	{
		if ((notebook + t)->visible == 1)
		{
			fprintf(f, "%d;%17s;%7d;%7d;%7d;%8d \n", i, notebook[t].name, notebook[t].CPU, notebook[t].RAM, notebook[t].HDD, notebook[t].price);
		}
	}

	fprintf(f, "----------------------------------------------------------------------\n");
}

void outputfileb(Notebook *notebook)
{
	int i = 1;
	int t;

	FILE *f;

	fopen_s(&f, "Список ноутбуков.bd", "wb");

	for (t = 0; t < MAX; t++)
	{
		if ((notebook + t)->visible == 1)
		{
			fwrite(&notebook[t], sizeof(Notebook), 1, f);
		}
	}

	fclose(f);

	//// ОПЕРАЦИЯ ЧТЕНИЯ
	//Notebook readmas[20];

	//fopen_s(&f, "Список ноутбуков.bd", "rb");
	//int count;
	//int N = 0;

	//do
	//{
	//	count = fread(&readmas[N], sizeof(notebook), 1, f);
	//	N++;
	//} while (count == 1);
	//N--;	

	//fclose(f);

	//fprintf(f, "----------------------------------------------------------------------\n");
	//fprintf(f, "|  №  |       Название      |   CPU   |   RAM   |   HDD   |   цена   |\n");
	//fprintf(f, "----------------------------------------------------------------------\n");

	//for (t = 0; t < MAX; t++)
	//{
	//	if ((notebook + t)->visible == 1)
	//	{
	//		fprintf(f, "%d;%17s;%7d;%7d;%7d;%8d \n", i, readmas[t].name, readmas[t].CPU, readmas[t].RAM, readmas[t].HDD, readmas[t].price);
	//	}
	//	i++;
	//}

	//fprintf(f, "----------------------------------------------------------------------\n");
}

int structСycle(Notebook *notebook)
{
	register int t;

	for (t = 0; t < MAX; t++)
	{
		if ((notebook + t)->visible == 0)  // если ячейка пустая
			return t;
	}
}

void clearmas(Notebook *notebook)
{
	register int t;

	for (t = 0; t < MAX; t++)
	{
		(notebook + t)->visible = 0;  // если ячейка пустая
	}
}
