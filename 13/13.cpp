#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define min(x,y) ((x) > (y)?(y):(x))
int edit(char S[2000],char T[2000])
{
    int sLen = strlen(S);
    int tLen = strlen(T);
    int dp[sLen+1][tLen+1];
    int i = 0;
    int j = 0;
    dp[0][0] = 0;
    
	//��ʼ��dp 
    for ( i = 1;i <= sLen;i++)
        dp[i][0] = i;
    for ( j = 1;j <= tLen;j++)
        dp[0][j] = j;
        
     //�������ֲ�ͬ��ϵ����Сֵ   
    for ( i = 1;i <= sLen;i++)
    {
        for (j = 1;j <= tLen;j++)
        {
            if (S[i-1] == T[j-1])
            {
                dp[i][j] = dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = 1 + min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1]);
            }
        }
    }
    return dp[sLen][tLen];
}
int main()
{
    char S[2000];
    scanf("������Դ��%s",S);
    char T[2000];
    scanf("������Ŀ�괮%s",T);
    printf("%d\n",edit(S,T));
    return 0;
}

