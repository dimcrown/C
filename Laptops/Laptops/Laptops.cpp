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
	//Notebook *prev; // указатель на предыдущий ноутбук
	//Notebook *next; // указатель на следующий ноутбук
};

int menu(); // функция меню
void add(Notebook *); // функция добавления записи
void edit(Notebook *); // функция редактирования записи
void del(Notebook *); // функция удаления записи
void outputfile(Notebook *); // функция вывода данных в текстовый файл
void outputview(Notebook *); // функция вывода текстовых данных на экран
void outputfileb(Notebook *); // функция вывода данных в бинарный файл
void outputviewb(Notebook *); // функция вывода на экран информации из бинарного файла
int selectmenuAdd(); // функция дополнительного меню при добавлении ноутбука
int selectMenuOut(); // функция дополнительного меню при выводе информации в файл или на экран
int structСycle(Notebook *); // функция цикла для массива структур
void clearmas(Notebook *); // функция превращения всех элементов массива в 0 для возможности сравнения
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
				  do // do while так как переменная choiseSelectMenu ни чему не равна 
				  {
					  choiseSelectMenu = selectmenuAdd();
					  switch (choiseSelectMenu)
					  {
					  case 1: add(notebook);
						  break;
					  case 2: choiseMenu; // переменной choiseMenu присваевается значение какого-то пункта меню
						  break;
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
					  default: printf("Ошибка! Такого пункта меню нет!\n");
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
				  default: printf("Ошибка! Такого пункта меню нет!\n");
					  break;
				  }
		}
			break;
		case 6: exit(0);
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
	printf("5. Работа с файлом\n");
	printf("6. Выйти из программы\n");

	fflush(stdin);
	printf("\nВведите номер нужного пункта меню: ");
	scanf_s("%d", &n);

	return n;
}

int selectmenuAdd()
{
	int n;

	printf("1. Добавить новый ноутбук\n");
	printf("2. Вернуться в меню\n");

	fflush(stdin);
	printf("\nВведите номер нужного пункта меню: ");
	scanf_s("%d", &n);

	return n;
}

int selectmenuOutInfo()
{
	int n;

	printf("1. Вывести на экран\n");
	printf("2. Вывести в файл\n");
	printf("3. Вернуться в главное меню\n");

	fflush(stdin);
	printf("\nВведите номер нужного пункта меню: ");
	scanf_s("%d", &n);

	return n;
}

int selectMenuOut()
{
	int n;

	printf("1. Сохранить все данные в текстовый файл\n");
	printf("2. Загрузить все данные из текстового файла\n");
	printf("3. Сохранить все данные в бинарный файл\n");
	printf("4. Загрузить все данные из бинарного файла\n");

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

void outputfile(Notebook *notebook) // Сохранить все данные в текстовый файл
{
	int i = 1;
	int t;

	FILE *f;

	fopen_s(&f, "Список ноутбуков.txt", "w");

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

void outputview(Notebook *readmas) // Загрузить все данные из текстового файла
{
	int i = 1;
	int t;

	FILE *f;

	fopen_s(&f, "Список ноутбуков.txt", "r");

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

void outputfileb(Notebook *notebook) // Сохранить все данные в бинарный файл
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
}

void outputviewb(Notebook *readmas) // Загрузить все данные из бинарного файла
{
	int i = 1;
	int t;

	FILE *f;

	fopen_s(&f, "Список ноутбуков.bd", "rb");
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

//void outputfile(Notebook *readmas)
//{
//	int i = 1;
//	int t;
//
//	FILE *f;
//
//	fopen_s(&f, "Список ноутбуков.txt", "w");
//
//	fprintf(f, "----------------------------------------------------------------------\n");
//	fprintf(f, "|  №  |       Название      |   CPU   |   RAM   |   HDD   |   цена   |\n");
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
	fprintf(f, "|  №  |       Название      |   CPU   |   RAM   |   HDD   |   цена   |\n");
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