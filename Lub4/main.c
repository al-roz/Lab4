#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX 100

struct entry
{
	int old;
	char* name;
	char* sernam;
	char* grup;
	char telephonNumber[12];
	int	assessments[5];
	int id;
};
typedef struct entry ENTRY;

struct list
{
	ENTRY person;
	struct list* next;
};
typedef struct list LIST;

void add(LIST* head, ENTRY* addValue)
{
	LIST* tmp;
	tmp = (LIST*)malloc(sizeof(LIST));

	tmp->person.name = (unsigned char*)malloc(addValue->name);
	strcpy_s(tmp->person.name, strlen(addValue->name) + 1, addValue->name);

	tmp->person.sernam = (unsigned char*)malloc(addValue->sernam);
	strcpy_s(tmp->person.sernam, strlen(addValue->sernam) + 1, addValue->sernam);

	tmp->person.old = addValue->old;

	tmp->person.grup = (unsigned char*)malloc(addValue->grup);
	strcpy_s(tmp->person.grup, strlen(addValue->grup) + 1, addValue->grup);

	strcpy_s(tmp->person.telephonNumber, 12, addValue->telephonNumber);

	for (int i = 0; i < 5; i++)
	{
		tmp->person.assessments[i] = addValue->assessments[i];
	}

	tmp->next = 0;
	LIST* curr = head;
	while (curr->next != 0)
		curr = curr->next;
	curr->next = tmp;
}

void delete(LIST* head, char* sername)
{
	while (head)
	{
		if (head->next == 0) {
			printf("Такого ученика нет\n");
			return 0;
		}
		if (strcmp(head->next->person.sernam, sername) == 0)
		{
			head->next = head->next->next;
			return 0;
		}
		
		head = head->next;
		
	}
}

void output(LIST* head)
{
	while (head)
	{
		if (head->person.id != 0) {
			printf("%s %s %d %s %s\n", head->person.sernam , head->person.name, head->person.old, head->person.grup, head->person.telephonNumber);
			for (int i = 0; i < 5; i++)
			{
				printf("%d ", head->person.assessments[i]);
			}
			printf("\n");
		}
		head = head->next;
	}
}

void outOtl(LIST* head)
{
	while (head)
	{
		if (head->person.id != 0) {
			int flag = 1;
			for (int i = 0; i < 5; i++)
				if (head->person.assessments[i] < 4) flag = 0;
			if (flag == 1)
			{
				printf("%s %s %d %s %s\n", head->person.sernam, head->person.name, head->person.old, head->person.grup, head->person.telephonNumber);
				for (int i = 0; i < 5; i++)
				{
					printf("%d ", head->person.assessments[i]);
				}
				printf("\n");
			}
			
		}
		head = head->next;
	}
}

void FilePrintList(LIST* head, char* FileName)
{
	FILE* f;
	fopen_s(&f, FileName, "w");
	while (head)
	{
		if (head->person.id != 0) {
			fprintf(f,"%s\n %s\n %d\n %s\n %s\n ", head->person.sernam, head->person.name, head->person.old, head->person.grup, head->person.telephonNumber);
			for (int i = 0; i < 5; i++)
			{
				fprintf(f,"%d ", head->person.assessments[i]);
			}
			fprintf(f,"\n");
		}
		head = head->next;
	}
	fclose(f);

}

void FileInputList(LIST* head, char* FileName)
{
	FILE* f;
	fopen_s(&f, FileName, "r");
	ENTRY addValue;
	int k = 1;
	char s[51];
	while (!feof(f))
	{

		addValue.id = k;
		k++;

		fgets(s, 50, f);
		s[strlen(s)-1] = 0;
		addValue.sernam = (char*)malloc(strlen(s) * sizeof(char));
		strcpy_s(addValue.sernam, strlen(s) + 1, s);

		fgets(s, 50, f);
		s[strlen(s)-1] = 0;
		addValue.name = (char*)malloc(strlen(s) * sizeof(char));
		strcpy_s(addValue.name, strlen(s) + 1, s);

		fscanf_s(f, "%d", &addValue.old);
		fgets(s, 50, f);

		fgets(s, 50, f);
		s[strlen(s)-1] = 0;
		addValue.grup = (char*)malloc(strlen(s) * sizeof(char));
		strcpy_s(addValue.grup, strlen(s) + 1, s);

		fgets(addValue.telephonNumber, 50, f);
		addValue.telephonNumber[strlen(addValue.telephonNumber)-1] = 0;
		
		char re;
		for (int i = 0; i < 5; i++)
		{
			fscanf_s(f, "%d", &addValue.assessments[i]);
			
		}
		fscanf_s(f,"%c", &re);
		
		add(head, &addValue);

	}
}

void FindOnGrop(LIST* head, char* grup)
{
	while (head)
	{
		if (head->person.id != 0) {
			
			if (strcmp(head->person.grup, grup) == 0)
			{
				printf("%s %s %d %s %s\n", head->person.sernam, head->person.name, head->person.old, head->person.grup, head->person.telephonNumber);
				for (int i = 0; i < 5; i++)
				{
					printf("%d ", head->person.assessments[i]);
				}
				printf("\n");
			}
		}
		head = head->next;
	}
}

int main()
{
	setlocale(LC_ALL, "Ru");
	LIST* head = (LIST*)malloc(sizeof(LIST));
	head->next = NULL;
	head->person.id = 0;
	ENTRY addValue;
	int k = 1;
	while (1)
	{
		char key, re;
		printf("Выберите действие:\n");
		printf("1.Добавить ученика в список\n");
		printf("2.Удалить ученика из списка\n");
		printf("3.Вывести учащихся из списка\n");
		printf("4.Вывести успевающих студентов\n");
		printf("5.Вывести учащихся в файл\n");
		printf("6.Считать из файла\n");
		printf("7.Вывести студентов из одной группы\n");

		
		scanf_s("%c", &key);
		scanf_s("%c",&re);

		switch (key)
		{
		case '1' :
			printf("Введите данные для добавления(фамилия, имя, возраст, группа, телефон,(оценки - 5 штук), начиная с новой строки\n");
			char s[256];

			addValue.id = k;
			k++;

			gets(s);
			addValue.sernam = (char*)malloc(strlen(s) * sizeof(char));
			strcpy_s(addValue.sernam, strlen(s) + 1, s);

			gets(s);
			addValue.name = (char*)malloc(strlen(s) * sizeof(char));
			strcpy_s(addValue.name, strlen(s) + 1, s);

			scanf_s("%d", &addValue.old);
			gets(s);

			gets(s);
			addValue.grup = (char*)malloc(strlen(s) * sizeof(char));
			strcpy_s(addValue.grup, strlen(s) + 1, s);

			gets(addValue.telephonNumber);

			for (int i = 0; i < 5; i++)
				scanf_s("%d", &addValue.assessments[i]);
			scanf_s("%c", &re);
			add(head, &addValue);
			system("pause");			
			break;

		case '2' :
			printf("Введите фамилию\n");
			char sername[20];
			gets(sername);
			delete(head, sername);
			break;

		case '3' :
			output(head);
			system("pause");
			break;

		case '4' :
			outOtl(head);
			system("pause");
			break;

		case '5' :
			printf("Введите имя файла\n");			
			char FileName[30];
			gets(FileName);
			FilePrintList(head, FileName);
			break;

		case '6' :
			printf("Введите имя файла\n");
			FileName[30];
			gets(FileName);
			FileInputList(head, FileName);
			break;

		case '7' :
			printf("Введите групу\n");
			gets(s);
			FindOnGrop(head, s);
			system("pause");
			break;

		default:
			exit(1);
		}
		system("cls");
		
		

	}

	
}