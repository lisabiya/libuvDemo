#include <stdio.h>
#include <string.h>

// 函数外定义变量 x 和 y
int x;
int y;
int addtwonum()
{
	// 函数内声明变量 x 和 y 为外部变量
	extern int x;
	extern int y;
	// 给外部变量（全局变量）x 和 y 赋值
	x = 1;
	y = 2;
	return x + y;
}

static int count = 10;
void func1(void)
{
	/* 'thingy' 是 'func1' 的局部变量 - 只初始化一次
 * 每次调用函数 'func1' 'thingy' 值不会被重置。
 */
	static int thingy = 5;

	thingy++;
	printf(" thingy 为 %d ， count 为 %d\n", thingy, count);
}

void func2(void)
{
	/* 'thingy' 是 'func1' 的局部变量 - 只初始化一次
 * 每次调用函数 'func1' 'thingy' 值不会被重置。
 */
	static int thingy = 100;

	thingy++;
	printf(" thingy 为 %d ， count 为 %d\n", thingy, count);
}

void funcEnum()
{
	enum DAY
	{
		MON,
		TUE,
		WED,
		THU = 10,
		FRI,
		SAT,
		SUN
	};

	enum DAY day;
	day = FRI;
	printf("%d\n", day);

	int a = 1;
	enum DAY day2;
	day2 = a;
	day2 = 1;
	printf("day2 =%d ** %d\n", day2, a);
}

void funcPoint()
{
	int var1 = 101;	   /* 实际变量的声明 */
	int *var2 = &var1; /* 实际变量的声明 */

	printf("Address of var1 po: %p\n", &var1);
	printf("Address of var2 variable: %p\n", var2);
	var1 = 201;
	printf("Value  stored in var1 variable: %d\n", var1);
	printf("Value  stored in var2 variable: %d\n", *var2);
}
int max(int x, int y)
{
	return x > y ? x : y;
}

void funcFPoint()
{
	/* p 是函数指针 */
	int (*p)(int, int) = &max; // &可以省略
	int a, b, c, d;

	printf("请输入三个数字:");
	scanf("%d %d %d", &a, &b, &c);

	/* 与直接调用函数等价，d = max(max(a, b), c) */
	d = p(p(a, b), c);
	printf("最大的数字是: %d\n", d);
}

// 回调函数
void populate_array(int *array, size_t arraySize, int (*getNextValue)())
{
	for (size_t i = 0; i < arraySize; i++)
		array[i] = getNextValue();
}

// 获取随机值
int getNextRandomValue(void)
{
	return 2;
}

void funcFPoint1()
{
	int myarray[10];
	populate_array(myarray, 10, getNextRandomValue);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", myarray[i]);
	}
	printf("\n");
}

void funcString()
{
	char greeting[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
	printf("Greeting message: %s\n", greeting);

	char me[] = "nihao";

	printf("Next : %s\n", me);
}

void funcStruct()
{
	struct Books
	{
		char title[50];
		char author[50];
		char subject[100];
		int book_id;
	} book1 = {"C 语言", "RUNOOB", "编程语言", 123456};

	// printf("title : %s\nauthor: %s\nsubject: %s\nbook_id: %d\n", book1.title, book1.author, book1.subject, book1.book_id);

	typedef struct
	{
		char title[50];
		char author[50];
		char subject[100];
		int *book_id;
	} Reader;

	Reader book2 = {"C 语言", "RUNOOB", "编程语言2", (int *)56};
	printf("me: %p", book2.book_id);
	// printf("title : %s\nauthor: %s\nsubject: %s\nbook_id: %d\n", book2.title, book2.author, book2.subject, book2.book_id);

	struct Books book3 = {"go语言", "RUNOOB", "编程语言3", 56123};
	// printf("title : %s\nauthor: %s\nsubject: %s\nbook_id: %d\n", book3.title, book3.author, book3.subject, book3.book_id);
}

void funcString2()
{
	// char word[] = "你好";

	// printf("me: %p \n", &word);
	// printf("me: %d \n", sizeof(word));
	// printf("me: %d \n", strlen(word));
	// printf("me: %s\n", word);

	char str[] = "http://c.biancheng.net";
	char *pstr = str;
	int len = strlen(str), i;
	//使用*(pstr+i)
	for (i = 0; i < len; i++)
	{
		printf("%c", *(pstr + i));
	}
	printf("\n");
	//使用pstr[i]
	for (i = 0; i < len; i++)
	{
		printf("%c", pstr[i]);
	}

	printf("\n");
	//使用*(str+i)
	for (i = 0; i < len; i++)
	{
		printf("%c", *(str + i));
	}
	printf("\n"); //0x100000f3

	printf("******\n"); //0x100000f3
	char *s;
	s = "hello";
	printf("%c\n", *(s + 1));
}

void funcString3()
{
	char *word = "wordpress";
	int length=strlen(word);
	printf("%c\n", *(word + 1));
	printf("%d\n", length);
}
int main()
{
	// func1();
	// func1();
	// func2();
	// func2();
	// funcEnum();
	// funcPoint();
	// funcFPoint();
	// funcFPoint1();
	// funcString();
	// funcStruct();
	// funcString2();
	funcString3();
}
