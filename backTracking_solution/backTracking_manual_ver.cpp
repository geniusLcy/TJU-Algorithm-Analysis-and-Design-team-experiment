#include <stdio.h>
#include <conio.h>
#include<stdlib.h>
#include <algorithm>
#include <iostream>
#include<string.h>
#include <sstream>
#include <fstream>
using namespace std;

int n;//物品数量
double c;//背包容量
double v[100];//各个物品的价值
double w[100];//各个物品的重量
double cw = 0.0;//当前背包重量
double cp = 0.0;//当前背包中物品价值
double bestp = 0.0;//当前最优价值
double perp[100];//单位物品价值排序后
int order[100];//物品编号
int put[100];//设置是否装入
int res[100];//保存答案
int ans[100];//保存标准答案
int all=0;


//按单位价值排序
void mysort()
{
    int i,j;
    int temporder = 0;
    double temp = 0.0;

    for(i=1;i<=n;i++)
        perp[i]=v[i]/w[i];

    for(i=1;i<=n-1;i++)
    {
        for(j=i+1;j<=n;j++)
            if(perp[i]<perp[j])//冒泡排序perp[],order[],sortv[],sortw[]
            {
                temp = perp[i];
                perp[i]=perp[j];
                perp[j]=temp;

                temporder=order[i];
                order[i]=order[j];
                order[j]=temporder;

                temp = v[i];
                v[i]=v[j];
                v[j]=temp;

                temp=w[i];
                w[i]=w[j];
                w[j]=temp;
            }
    }
}


//计算上界函数
double bound(int i)
{
    double leftw= c-cw;
    double b = cp;
    while(i<=n && w[i]<=leftw)
    {
        leftw-=w[i];
        b+=v[i];
        i++;
    }
    if(i<=n)
        b+=v[i]/w[i]*leftw;
    return b;

}

//回溯函数
void backtrack(int i)
{
    if(i>n)
    {
        if(cp>bestp)
        {
            for(int i=1;i<=n;++i)
                res[i]=put[i];
            bestp=cp;
        }
        return;
    }
    if(cw+w[i]<=c)
    {
        cw+=w[i];
        cp+=v[i];
        put[order[i]]=1;
        backtrack(i+1);
        cw-=w[i];
        cp-=v[i];
        put[order[i]]=0;
    }
    if(bound(i+1) > bestp)
        backtrack(i+1);
}

void input()
{
    printf("Enter nums: ");
    scanf("%d", &n);
    printf("Enter weight of each object:\n");
    for(int i = 1; i <= n; i++)
        scanf("%lf", &w[i]);
    printf("Enter value of each object:\n");
    for(int i = 1; i <= n; i++)
        scanf("%lf", &v[i]);
    printf("Enter capacity: ");
    scanf("%lf", &c);
}

void output()
{
    printf("the most price:%lf\n",bestp);
    printf("the answer:\n");
    for(int i=1;i<=n;i++){ printf("%d ",res[i]); }
    printf("\n");
}

int main()
{
    input();


    //初始化
    cw = 0.0;
    cp = 0.0;
    bestp = 0.0;
    memset(put,0,sizeof(put));
    for(int i=1;i<=n;++i)
        order[i]=i;

    
    mysort();
    backtrack(1);

    output();
    return 0;
}