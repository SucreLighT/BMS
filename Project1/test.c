#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define NUM 100

typedef struct {
	char ISBN[10];			//��� 
	char book[30];			//���� 
	char author[20];			//����
	int  edition;			//�汾��
	char press[50];			//��������
	int year;				//������
}Bookinfo;

int Input(Bookinfo dictList[], int n); 							//�������� 
void Display(Bookinfo dictList[], int n);						//������� 
int Delete(Bookinfo dictList[], int n, char *book);				//ɾ������Ϊbook�ĵ�һ����¼ 
int Delete_a_record(Bookinfo dictList[], int n); 				//�����ɾ��������������Delete 
void Sort_by_Name(Bookinfo dictList[], int n); 					//��������������
int Insert(Bookinfo dictList[], int n, Bookinfo *s);
int Insert_a_record(Bookinfo dictList[], int n); 				//������Ϣ������Insert�������
int Query(Bookinfo dictList[], int n, char * book);				//���Ҳ���ʾ����Ϊbook�����м�¼ 
void Query_a_record(Bookinfo dictList[], int n);				//��������ҵ�����������Query���� 
int AddfromText(Bookinfo dictList[], int n, char *filename);	//���ļ������һ����¼������Insert���룬�����µļ�¼�� 
void WritetoText(Bookinfo dictList[], int n, char *filename);	//�������¼д���ļ�
void Display_main_menu();										//��ʾ���˵�


/*������*/
int main()
{
	Bookinfo books[NUM];
	int n = 0;
	char choice;
	char filename[16];

	//Display_main_menu();

	while (1)
	{
		while (getchar() != '\n');

		Display_main_menu();
		printf("Give your choice:");

		choice = getchar();
		switch (choice)
		{
		case '1':
			n = Input(books, n);
			system("pause");
			printf("\n");
			break;
		case '2':
			Display(books, n);
			system("pause");
			printf("\n");
			break;
		case '3':
			n = Delete_a_record(books, n);
			system("pause");
			printf("\n");
			break;
		case '4':
			Sort_by_Name(books, n);
			system("pause");
			printf("\n");
			break;
		case '5':
			n = Insert_a_record(books, n);
			system("pause");
			printf("\n");
			break;
		case '6':
			Query_a_record(books, n);
			system("pause");
			printf("\n");
			break;
		case '7':
			printf("�����ļ���:");
			scanf("%s", filename);
			n = AddfromText(books, n, filename);
			system("pause");
			printf("\n");
			break;
		case '8':
			printf("�����ļ���:");
			scanf("%s", filename);
			WritetoText(books, n, filename);
			system("pause");
			printf("\n");
			break;
		case '0':
			printf("Goodbye!\n");
			system("pause");
			printf("\n");
			return;
		}
	}
	return 0;
}

int Input(Bookinfo dictList[], int n)
{
	printf("������������š����������ߡ��汾�š����������������꣨�Կո�������س��������룩��\n");
	scanf("%s %s %s %d %s %d",dictList[n].ISBN, dictList[n].book, dictList[n].author, 
		&dictList[n].edition, dictList[n].press, &dictList[n].year);
	n++;
	printf("����ɹ���\n");
	return n;
}

void Display(Bookinfo dictList[], int n)
{
	int i;
	if (n == 0)
	{
		printf("������ͼ����Ϣ��\n");
		return;
	}
	//system("cls");
	printf("���      ����            ����        �汾       ������              ������\n");
	for (i = 0; i < n; i++)
	{
		if (i != 0 && i % 10 == 0)
		{
			printf("������س�����ʾ��һ��");
			system("pause");
			//system("cls");
			printf("ISBN      book            author    edition   press               year\n");
		}
		printf("%-10s%-16s%-12s��%d��%20s%10d\n",dictList[i].ISBN, dictList[i].book, 
			dictList[i].author, dictList[i].edition, dictList[i].press, dictList[i].year);
	}
	printf("��ʾ������\n");
}

int Delete(Bookinfo dictList[], int n, char *book)
{
	int i = 0;
	int flag = 0;

	for (; i < n; i++)
	{
		if (!strcmp(dictList[i].book, book))
		{
			flag = 1;
			break;
		}
			
	}

	if (flag == 0)
		printf("ɾ��ʧ�ܣ������ڸ�ͼ���¼��\n");
	else
	{
		for (; i < n - 1; i++)
			dictList[i] = dictList[i + 1];
		n--;
		//printf("ɾ��ͼ����Ϣ�ɹ���\n");
	}

	return n;
}

int Delete_a_record(Bookinfo dictList[], int n)
{
	char bookname[30];
	int i,j, record[10];
	int flag = 0;

	if (n == 0)
	{
		printf("ɾ��ʧ�ܣ�������ͼ����Ϣ��\n");
		return 0;
	}

	printf("������Ҫɾ����������");
	scanf("%s",bookname);

		for (i = 0, j = 0; i < n; i++)		//����ͬ��ͼ����Ϣ
		{
			if (!strcmp(dictList[i].book, bookname))
			{
				record[j] = i;
				j++;
				flag = 1;
			}
		}

		if(flag == 0)
		{
			printf("ɾ��ʧ�ܣ������ڸ�ͼ�飡\n");
			return n;
		}

		else	
		{
			printf("����Ϊ%s��ͼ����Ϣ���£�\n", bookname);		//������и�������ͼ��
			printf("���      ����            ����        �汾       ������              ������\n");
			for (i = 0; i < j; i++)
			{
				printf("%-10s%-16s%-12s��%d��%20s%10d\n",dictList[record[i]].ISBN, dictList[record[i]].book, 
					dictList[record[i]].author, dictList[record[i]].edition, dictList[record[i]].press, dictList[record[i]].year);
			}

			char ISBN[10];
			printf("������Ҫɾ������Ŀ��ţ�");//�����ɾ����Ŀ�����
			scanf("%s", ISBN);

			printf("������y��yes��ȷ��ɾ����");//ȷ���Ƿ�ɾ��
			while (getchar() != '\n');//�����س�Ӱ��

			if (getchar() == 'y')
			{
				for (i = 0; i < j; i++)
				{
					if (!strcmp(dictList[record[i]].ISBN, ISBN))
					{
						j = record[i];
						break;
					}
				}
				int m = j + 1;//j��ʾ�±꣬��Ϊ��������Delete����ʱ��ʾ��������Ҫ+1
				Delete(dictList, m, dictList[j].book);
				for (; j < n - 1; j++)
					dictList[j] = dictList[j + 1];
				n--;
				printf("ɾ��ͼ����Ϣ�ɹ���\n");
				return n;
			}
			else
			{
				printf("ɾ��ȡ����\n");
				return n;
			}
		}
}

void Sort_by_Name(Bookinfo dictList[], int n)
{
	int i, j;
	Bookinfo bookinfo;

	if (n == 0)
	{
		printf("����ʧ�ܣ�������ͼ����Ϣ��\n");
		return;
	}
	else
	{
		//ð������
		for (i = 0; i < n - 1; i++)
			for (j = i + 1; j<n; j++)
				if (strcmp(dictList[i].book, dictList[j].book) >0)
				{
					bookinfo = dictList[i];
					dictList[i] = dictList[j];
					dictList[j] = bookinfo;
				}
		printf("����ɹ���\n");
	}
}

int Insert(Bookinfo dictList[], int n, Bookinfo *s)
{
	int i,j;
	
	for (i = 0; i < n; i++)
		if (strcmp(dictList[i].book, (*s).book)>0)//�ҵ��ü�¼Ӧ�ô��ڵ�λ��(iǰ��һ��)
			break;

	for (j = n - 1; j >= i; --j)		//������ļ�¼����һλ
		dictList[j + 1] = dictList[j];

	dictList[i] = *s;				//����ü�¼

	//printf("������Ϣ�ɹ���\n");
	n++;

	return n;
}

int Insert_a_record(Bookinfo dictList[], int n)	
{
	int i = 0;
	Bookinfo bookinfo;

	printf("������Ҫ����ͼ�����š����������ߡ��汾�š����������������꣨�Կո�������س��������룩��\n");
	scanf("%s %s %s %d %s %d", bookinfo.ISBN, bookinfo.book, bookinfo.author, 
		&bookinfo.edition, bookinfo.press, &bookinfo.year);

	n = Insert(dictList, n, &bookinfo);

	return n;
}

int Query(Bookinfo dictList[], int n, char * book)
{
	int i, j, record[10];

	for (i = 0, j = 0; i < n; i++)
	{
		if (!strcmp(dictList[i].book, book))
		{
			record[j] = i;
			j++;
		}
	}

	if (j == 0)
	{
		printf("����ʧ�ܣ������ڸ�������ͼ�飡\n");
		return -1;
	}

	else
	{
		printf("���ҳɹ�������Ϊ%s��ͼ����Ϣ���£�\n", book);
		printf("���      ����            ����        �汾       ������              ������\n");
		for (i = 0; i < j; i++)
		{
			printf("%-10s%-16s%-12s��%d��%20s%10d\n",dictList[record[i]].ISBN, dictList[record[i]].book, 
				dictList[record[i]].author, dictList[record[i]].edition, dictList[record[i]].press, dictList[record[i]].year);
		}

		return j;
	}
}

void Query_a_record(Bookinfo dictList[], int n)
{
	if (n == 0)
	{
		printf("����ʧ�ܣ�������ͼ����Ϣ��\n");
		return;
	}

	char bookname[30];
	printf("������Ҫ���ҵ�������");
	scanf("%s", bookname);

	Query(dictList, n, bookname);
}

int AddfromText(Bookinfo dictList[], int n, char *filename)
{
	FILE *fp;
	int k, i;
	Bookinfo bookinfo;

	if ((fp = fopen(filename, "r")) == NULL) {
		printf("���ļ�ʧ�ܣ�\n");
		return n;
	}

	fscanf(fp, "%d", &k);	//�����ļ���¼��
	for (i = 0; i < k; i++)
	{
		fscanf(fp, "%s %s %s %d %s %d", bookinfo.ISBN, bookinfo.book, bookinfo.author, 
			&bookinfo.edition, bookinfo.press, &bookinfo.year);
		n = Insert(dictList, n, &bookinfo);
	}

	fclose(fp);
	printf("�ɹ����ļ��������ݣ�\n");
	return n;
}

void WritetoText(Bookinfo dictList[], int n, char *filename)
{
	FILE *fp;
	int i;

	if ((fp = fopen(filename, "w")) == NULL) {
		printf("���ļ�ʧ��!\n");
		return;
	}
	fprintf(fp, "%d\n", n);

	for (i = 0; i < n; i++)
		fprintf(fp, "%-10s%-16s%-12s%d%20s%10d\n", dictList[i].ISBN, dictList[i].book, dictList[i].author,
			dictList[i].edition, dictList[i].press, dictList[i].year);
	
	fclose(fp);
	printf("�ɹ�����¼д���ļ���\n");
}

void Display_main_menu()
{
	printf(
		"************************************\n"
		"*	   ͼ�����ϵͳ            *\n"
		"*  1.Input records                 *\n"
		"*  2.Display all records           *\n"
		"*  3.Delete a record               *\n"
		"*  4.Sort                          *\n"
		"*  5.Insert a record               *\n"
		"*  6.Query                         *\n"
		"*  7.Add records from a Text File  *\n"
		"*  8.Write to a Text File          *\n"
		"*  0.Quit                          *\n"
		"************************************\n");
}