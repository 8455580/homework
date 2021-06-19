#include <stdio.h>
#include <stdlib.h>
#define NUM 20 //最大容量
//顺序查找，输入有序数组a，查找的值value，数组长度n
int SeqSearch(int a[], int value, int n) {
	for (int i = 1; i <= n; i++) {
		//判断a[i]是否与value相等，相等返回下标i
		if (a[i] == value) {
			return i;
		}
	}
	return 0;
}
//二分查找，输入有序数组a，查找的值value，数组长度n
int BinarySearch(int a[], int value, int n)
{
	//每次搜索，分段数组开头下标low，末尾下标high，中间下标mid
	int low, high, mid;
	low = 1;
	high = n;
	while (low <= high)
	{
		mid = (low + high) / 2;
		//判断a[mid]是否与value相等，相等返回下标mid结束算法
		if (a[mid] == value)
			return mid;
		//判断a[mid]是否大于value，是，则更新high
		if (a[mid] > value)
			high = mid - 1;
		//判断a[mid]是否小于value，是，则更新low
		if (a[mid] < value)
			low = mid + 1;
	}
	return 0;
}
/*
输入示例：
	6
输出结果：
	顺序查找：6
	二分查找：6
*/
int main() {
	int num,a[NUM] = {0,1,2,3,4,5,6 };
	int length = 6;
	scanf("%d", &num);
	printf("顺序查找：%d\n",BinarySearch(a, num, length));
	printf("二分查找：%d\n", SeqSearch(a, num, length));
	return 0;
}


