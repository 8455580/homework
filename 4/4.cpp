#include <stdio.h>
#include <stdlib.h>
#define NUM 20 //最大容量
int a[NUM]= { 0,11,3,22,4 }, b[NUM];
void merge(int start, int end, int mid) {
	int i = start, j = mid + 1,k=start;//例如i=1,j=2,mid=1
	while (i <= mid && j <= end)//i<=mid,j<=end
		//对2个序列中小的数放入另外一个数组中,例如2个长度为1的序列11和3
		if (a[i] <= a[j])
			b[k++] = a[i++];//把3放入数组b中
		else
			b[k++] = a[j++];
	//当退出循环可能左边剩余，也可能右边剩余，因为可能某个序列中的值比另一个序列中的所有值都大
	//左边剩余
	while (i<=mid){
		b[k++] = a[i++];
	}
	//右边剩余，例子中11剩余，把11放入数组b中
	while (j <= end) {
		b[k++] = a[j++];
	}
	//将排好序的数组重新赋值给a
	for (i = start; i <= end; i++) {
		a[i] = b[i];
	}
}
void mergeSort(int start, int end) {
	if (start < end) {
		//mid=数组中间的值的下标(start + end) / 2
		int mid = (start + end) / 2;
		//按照mid分割数组为（start，mid）和（mid+1，end），递归分割直到子序列的长度为1
		mergeSort(start, mid);
		mergeSort(mid + 1, end);
		//递归调用merge函数进行归并排序
		merge(start, end, mid);
	}
}
int main() {
	mergeSort(1, 4);
	//输出排序后的数组a
	for (int i = 1; i < 5; i++) {
		printf("%d ", a[i]);
	}
	return 0;
}

