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


int main()
{
    for(int j=1;j<=8;++j)
    {
        printf("\nP0%d\n",j);
        string data_set_c = "..\\data_set\\";
        string data_set_p = "..\\data_set\\";
        string data_set_w = "..\\data_set\\";
        string data_set_s = "..\\data_set\\";
        string num;
        stringstream ss;
        ss << j;
        ss >> num;
        data_set_c = data_set_c + "P0" + num + "\\p0" + num + "_c.txt";
        data_set_p = data_set_p + "P0" + num + "\\p0" + num + "_p.txt";
        data_set_s = data_set_s + "P0" + num + "\\p0" + num + "_s.txt";
        data_set_w = data_set_w + "P0" + num + "\\p0" + num + "_w.txt";
        

        //从文件中读入背包的容量
        ifstream input;

        input.open(data_set_c.c_str());
        if(input.fail())
            cout << data_set_c << " does not exit" << endl;
        input >> c;
        input.close();

        //从文件中读入各个物品的价值，并计算得到物品的个数
        input.open(data_set_p.c_str());
        if(input.fail())
            cout << data_set_p << " does not exit" << endl;
        int k = 1;
        while(!input.eof())
        {
            input >> v[k];
            if(input.eof()) break;
            k++;
        }
        n = k;
        input.close();

        //从文件中读入各个物品的选择结果
        input.open(data_set_s.c_str());
        if(input.fail())
            cout << data_set_s << " does not exit" << endl;
        k = 1;
        while(!input.eof())
        {
            input >> ans[k];
            if(input.eof()) break;
            k++;
        }
        input.close();

        //从文件中读入各个物品的重量
        input.open(data_set_w.c_str());
        if(input.fail())
            cout << data_set_w << " does not exit" << endl;
        k = 1;
        while(!input.eof())
        {
            input >> w[k];
            if(input.eof()) break;
            k++;
        }
        input.close();

        //初始化
        cw = 0.0;
        cp = 0.0;
        bestp = 0.0;
        memset(put,0,sizeof(put));
        for(int i=1;i<=n;++i)
            order[i]=i;

        
        mysort();
        backtrack(1);
        printf("the most price:%lf\n",bestp);
        printf("the result:\n");
        int check=1;
        for(int i=1;i<=n;i++)
        {
            printf("%d ",res[i]);
            if(res[i]!=ans[i])
                check=0;
        }
        cout<<endl;
        printf("the answer:\n");
        for(int i=1;i<=n;i++)
        {
            printf("%d ",ans[i]);
        }
        cout<<endl;
        if(check == 1)
        {
            printf("P0%d: passed!\n",j);
            all++;
        }
        else
            printf("P0%d: failed!\n",j);
        
        if(j==8)
        {
            if(all==8)
                cout<<"\nyou have passed all points!\n"<<endl;
            else 
                printf("you only passed %d points!\n",all);
        }
    }
    return 0;
}