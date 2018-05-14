#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define NUM 100

typedef struct {
	char ISBN[10];			//书号 
	char book[30];			//书名 
	char author[20];			//作者
	int  edition;			//版本号
	char press[50];			//出版社名
	int year;				//出版年
}Bookinfo;

int Input(Bookinfo dictList[], int n); 							//数据输入 
void Display(Bookinfo dictList[], int n);						//输出数据 
int Delete(Bookinfo dictList[], int n, char *book);				//删除书名为book的第一条记录 
int Delete_a_record(Bookinfo dictList[], int n); 				//输入待删除的书名，调用Delete 
void Sort_by_Name(Bookinfo dictList[], int n); 					//按书名升序排列
int Insert(Bookinfo dictList[], int n, Bookinfo *s);
int Insert_a_record(Bookinfo dictList[], int n); 				//输入信息，调用Insert有序插入
int Query(Bookinfo dictList[], int n, char * book);				//查找并显示书名为book的所有记录 
void Query_a_record(Bookinfo dictList[], int n);				//输入待查找的姓名，调用Query查找 
int AddfromText(Bookinfo dictList[], int n, char *filename);	//从文件中添加一批记录，调用Insert插入，返回新的记录数 
void WritetoText(Bookinfo dictList[], int n, char *filename);	//将数组记录写入文件
void Display_main_menu();										//显示主菜单


/*主程序*/
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
			printf("输入文件名:");
			scanf("%s", filename);
			n = AddfromText(books, n, filename);
			system("pause");
			printf("\n");
			break;
		case '8':
			printf("输入文件名:");
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
	printf("请依次输入书号、书名、作者、版本号、出版社名、出版年（以空格隔开，回车结束输入）：\n");
	scanf("%s %s %s %d %s %d",dictList[n].ISBN, dictList[n].book, dictList[n].author, 
		&dictList[n].edition, dictList[n].press, &dictList[n].year);
	n++;
	printf("输入成功！\n");
	return n;
}

void Display(Bookinfo dictList[], int n)
{
	int i;
	if (n == 0)
	{
		printf("不存在图书信息！\n");
		return;
	}
	//system("cls");
	printf("书号      书名            作者        版本       出版社              出版年\n");
	for (i = 0; i < n; i++)
	{
		if (i != 0 && i % 10 == 0)
		{
			printf("请输入回车键显示下一屏");
			system("pause");
			//system("cls");
			printf("ISBN      book            author    edition   press               year\n");
		}
		printf("%-10s%-16s%-12s第%d版%20s%10d\n",dictList[i].ISBN, dictList[i].book, 
			dictList[i].author, dictList[i].edition, dictList[i].press, dictList[i].year);
	}
	printf("显示结束！\n");
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
		printf("删除失败，不存在该图书记录！\n");
	else
	{
		for (; i < n - 1; i++)
			dictList[i] = dictList[i + 1];
		n--;
		//printf("删除图书信息成功！\n");
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
		printf("删除失败！不存在图书信息！\n");
		return 0;
	}

	printf("请输入要删除的书名：");
	scanf("%s",bookname);

		for (i = 0, j = 0; i < n; i++)		//查找同名图书信息
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
			printf("删除失败！不存在该图书！\n");
			return n;
		}

		else	
		{
			printf("书名为%s的图书信息如下：\n", bookname);		//输出所有该书名的图书
			printf("书号      书名            作者        版本       出版社              出版年\n");
			for (i = 0; i < j; i++)
			{
				printf("%-10s%-16s%-12s第%d版%20s%10d\n",dictList[record[i]].ISBN, dictList[record[i]].book, 
					dictList[record[i]].author, dictList[record[i]].edition, dictList[record[i]].press, dictList[record[i]].year);
			}

			char ISBN[10];
			printf("请输入要删除的书目书号：");//输入待删除书目的书号
			scanf("%s", ISBN);

			printf("请输入y（yes）确认删除：");//确认是否删除
			while (getchar() != '\n');//消除回车影响

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
				int m = j + 1;//j表示下标，作为参数传给Delete函数时表示个数，需要+1
				Delete(dictList, m, dictList[j].book);
				for (; j < n - 1; j++)
					dictList[j] = dictList[j + 1];
				n--;
				printf("删除图书信息成功！\n");
				return n;
			}
			else
			{
				printf("删除取消！\n");
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
		printf("排序失败！不存在图书信息！\n");
		return;
	}
	else
	{
		//冒泡排序
		for (i = 0; i < n - 1; i++)
			for (j = i + 1; j<n; j++)
				if (strcmp(dictList[i].book, dictList[j].book) >0)
				{
					bookinfo = dictList[i];
					dictList[i] = dictList[j];
					dictList[j] = bookinfo;
				}
		printf("排序成功！\n");
	}
}

int Insert(Bookinfo dictList[], int n, Bookinfo *s)
{
	int i,j;
	
	for (i = 0; i < n; i++)
		if (strcmp(dictList[i].book, (*s).book)>0)//找到该记录应该处于的位置(i前面一个)
			break;

	for (j = n - 1; j >= i; --j)		//将后面的记录后移一位
		dictList[j + 1] = dictList[j];

	dictList[i] = *s;				//插入该记录

	//printf("插入信息成功！\n");
	n++;

	return n;
}

int Insert_a_record(Bookinfo dictList[], int n)	
{
	int i = 0;
	Bookinfo bookinfo;

	printf("请输入要插入图书的书号、书名、作者、版本号、出版社名、出版年（以空格隔开，回车结束输入）：\n");
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
		printf("查找失败！不存在该书名的图书！\n");
		return -1;
	}

	else
	{
		printf("查找成功！书名为%s的图书信息如下：\n", book);
		printf("书号      书名            作者        版本       出版社              出版年\n");
		for (i = 0; i < j; i++)
		{
			printf("%-10s%-16s%-12s第%d版%20s%10d\n",dictList[record[i]].ISBN, dictList[record[i]].book, 
				dictList[record[i]].author, dictList[record[i]].edition, dictList[record[i]].press, dictList[record[i]].year);
		}

		return j;
	}
}

void Query_a_record(Bookinfo dictList[], int n)
{
	if (n == 0)
	{
		printf("查找失败！不存在图书信息！\n");
		return;
	}

	char bookname[30];
	printf("请输入要查找的书名：");
	scanf("%s", bookname);

	Query(dictList, n, bookname);
}

int AddfromText(Bookinfo dictList[], int n, char *filename)
{
	FILE *fp;
	int k, i;
	Bookinfo bookinfo;

	if ((fp = fopen(filename, "r")) == NULL) {
		printf("打开文件失败！\n");
		return n;
	}

	fscanf(fp, "%d", &k);	//读出文件记录数
	for (i = 0; i < k; i++)
	{
		fscanf(fp, "%s %s %s %d %s %d", bookinfo.ISBN, bookinfo.book, bookinfo.author, 
			&bookinfo.edition, bookinfo.press, &bookinfo.year);
		n = Insert(dictList, n, &bookinfo);
	}

	fclose(fp);
	printf("成功从文件输入数据！\n");
	return n;
}

void WritetoText(Bookinfo dictList[], int n, char *filename)
{
	FILE *fp;
	int i;

	if ((fp = fopen(filename, "w")) == NULL) {
		printf("打开文件失败!\n");
		return;
	}
	fprintf(fp, "%d\n", n);

	for (i = 0; i < n; i++)
		fprintf(fp, "%-10s%-16s%-12s%d%20s%10d\n", dictList[i].ISBN, dictList[i].book, dictList[i].author,
			dictList[i].edition, dictList[i].press, dictList[i].year);
	
	fclose(fp);
	printf("成功将记录写到文件！\n");
}

void Display_main_menu()
{
	printf(
		"************************************\n"
		"*	   图书管理系统            *\n"
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