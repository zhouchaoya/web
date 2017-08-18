//#include <stdio.h>
//
//int differ_bit(int a, int b)
//{
//	int num = 0;
//	int count = 0;
//	num = a^b;
//	while(num)
//	{
//		int i = 0;
//		i = num&1;
//		if(i == 1)
//		count++;
//		num = num>>1;
//
//	}
//	return count;
//}
//int main()
//{
//	int m = 0;
//	int n = 0;
//	int ret = 0;
//	printf("输入两个数：");
//	scanf("%d%d", &m, &n);
//	ret = differ_bit(m, n);
//	printf("%d\n", ret);
//	return 0;
//}


#include <stdio.h>

int Add(int x, int y)
{
	x = x+y;
	printf("%d\n", x);
}

int main()
{
	int (*pfun)(int, int) = Add;
	//pfun(1, 2);
	//pfun = Add;
	pfun = Add;
	(*pfun)(1, 2);

	return 0;
}
