#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define NUM 20 //最大容量
struct point {
	double x; 
	double y;
};
double distance(point z1, point z2) {
	double t;
	t = (z1.x - z2.x)*(z1.x - z2.x) + (z1.y - z2.y)*(z1.y - z2.y);
	return sqrt(t);
};
double min(double p1, double p2) {
	return p1 < p2 ? p1 : p2;
}
double EfficientClosestPair(point p[], point q[], int n) {
	int i, k, num=0, index;
	double d1, dt, d, m,dminsq;
	point p1[NUM], q1[NUM], pt[NUM], qt[NUM], s[NUM];
	//当n<=3时,直接求最小距离 
	if (n == 2) {
		return distance(p[0], p[1]);
	}
	else if(n==3) {
		return min(distance(p[0], p[1]), distance(p[1], p[2]));
	}
	else {
		//将p的前[n/2]个点复制到p1 
		for (i = 0; i < n / 2; i++) {
			p1[i]= p[i];
		}
		//将q的前[n/2]个点复制到q1 
		for (i = 0; i < n / 2; i++) {
			q1[i]= q[i];
		}
		//将p剩余的[n/2]个点复制到pt 
		for (i = n/2; i < n; i++) {
			pt[i-n/2] = p[i]; 
		}
		//将q剩余的[n/2]个点复制到qt 
		for (i = n/2; i < n; i++) {
			qt[i - n / 2] = q[i];
		}
		//将p1,q1中的最小距离赋值给d1 
		d1 = EfficientClosestPair(p1, q1, n / 2);
		//将pt,qt中的最小距离赋值给dt 
		dt = EfficientClosestPair(pt, qt, n - n / 2);
		//将二者最小的距离赋值给d 
		d = min(d1, dt);
		//m=p数组中间值的x
		index = int(ceil(n / 2.0) - 1);
		m = p[index].x;
		//将q中所有|x-m|<d的点复制到数组s[0..num-1] 
		for (i = 0; i < n; i++) {
			if (fabs(q[i].x - m) < d) {
				s[num++] = q[i];
			}
		}
		//设最小距离dminsq为d*d 
		dminsq = d * d;
		//对数组s中的每两个点的值进行判断，如果小于dminsq，则将这两个点的长度赋值给dminsq
		for (i = 0; i < num - 2; i++) {
			k = i + 1;
			while (k <= num - 1 && (s[k].y - s[i].y)*(s[k].y - s[i].y) < dminsq) {
				dminsq = min((s[k].x - s[i].x)*(s[k].x - s[i].x) + (s[k].y - s[i].y)*(s[k].y - s[i].y), dminsq);
				k++;
			}
		}
	}
	//返回最小距离 
	return sqrt(dminsq);
}

int main() {
	point p[NUM] = { {1.0,0},{1.0,2.0},{2.0,1.0},{2.5,1.0},{4.0,0},{4.0,1.0},{6.0,0},{6.0,1.0},{6.0,2.0} };
	point q[NUM]= { {1.0,0},{4.0,0},{6.0,0},{2.0,1},{2.5,1.0},{4.0,1.0},{6.0,1.0},{1.0,2.0},{6.0,2.0} };
	printf("最小距离为：%f\n",EfficientClosestPair(p, q, 9));
	return 0;
}
