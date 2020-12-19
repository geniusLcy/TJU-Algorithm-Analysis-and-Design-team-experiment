#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

const int maxn = 99;
int w[maxn];   //物品的重量
int v[maxn];   //物品的价值
int s[maxn];   //物品的选择
int n;         //物品的个数
int c;         //背包的容量


int bestv = 0;    //存放最大价值
int bestx[maxn];  //存放最大价值对应的最优解
int total = 1;
//解空间树的结点
struct nodetype
{
    int no;  //结点编号
    int i;   //结点对应的树的层数
    int w;   //当前结点的重量之和
    int v;   //当前结点的价值之和
    int x[maxn];  //当前结点的各个物品的选择结果
    double ub;  //当前结点能够得到的最大的价值
};


//计算某个结点的上界
void bound(nodetype &e)
{
    int i = e.i + 1;
    int sumw = e.w;
    double sumv = e.v;
    while((sumw + w[i] <= c) && i <= n)
    {
        sumw += w[i];
        sumv += v[i];
        i++;
    }
    if(i <= n)
        e.ub = sumv + (c - sumw) * v[i] / w[i];
    else
        e.ub = sumv;
}


//判断解空间树种当前的结点是否比当前的最优解更加优化
void enqueue(nodetype &e, queue<nodetype> &q)
{
    if(e.i == n)
    {
        if(e.v > bestv)
        {
            bestv = e.v;
            for(int j = 1; j <= n; j++)
                bestx[j] = e.x[j];
        }
    }
    else
        q.push(e);
}

//广度优先遍历获得最优解
void BFS()
{
    nodetype e, e1, e2;
    queue<nodetype> q;

    e.i = 0;
    e.w = 0;
    e.v = 0;
    e.no = total++;

    for(int j = 1; j <= n; j++)
    {
        e.x[j] = 0;
    }
    bound(e);
    q.push(e);

    while(!q.empty())
    {
        e = q.front();
        q.pop();
        if(e.w + w[e.i + 1] <= c)
        {
            e1.no = total++;
            e1.i = e.i + 1;
            e1.w = e.w + w[e.i + 1];
            e1.v = e.v + v[e.i + 1];
            for(int j = 1; j <= n; j++)
            {
                e1.x[j] = e.x[j];
            }
            e1.x[e1.i] = 1;
            bound(e1);
            enqueue(e1, q);
        }

        e2.no = total++;
        e2.i = e.i + 1;
        e2.w = e.w;
        e2.v = e.v;
        for(int j = 1; j <= n; j++)
        {
            e2.x[j] = e.x[j];
        }
        e2.x[e2.i] = 0;
        bound(e2);
        if(e2.ub > bestv)
            enqueue(e2, q);
    }
}

int main()
{
    //循环测试8个数据集
    for(int i = 1; i <= 8; i++)
    {
        //获取存放背包的容量、物品的价值、物品的重量、物品的选择结果的数据的文件的文件名
        string data_set_c = "algorithm_exp-main\\data_set\\";
        string data_set_p = "algorithm_exp-main\\data_set\\";
        string data_set_w = "algorithm_exp-main\\data_set\\";
        string data_set_s = "algorithm_exp-main\\data_set\\";
        string num;
        stringstream aa;
        aa << i;
        aa >> num;
        data_set_c = data_set_c + "P0" + num + "\\p0" + num + "_c.txt";
        data_set_p = data_set_p + "P0" + num + "\\p0" + num + "_p.txt";
        data_set_s = data_set_s + "P0" + num + "\\p0" + num + "_s.txt";
        data_set_w = data_set_w + "P0" + num + "\\p0" + num + "_w.txt";

        //从文件中读入背包的容量
        ifstream input;
        input.open(data_set_c.c_str());
        if(input.fail())
            cout << data_set_c << "does not exit" << endl;
        input >> c;
        input.close();

        //从文件中读入各个物品的价值，并计算得到物品的个数
        input.open(data_set_p.c_str());
        if(input.fail())
            cout << data_set_p << "does not exit" << endl;
        int j = 1;
        while(!input.eof())
        {
            input >> v[j];
            if(input.eof()) break;
            j++;
        }
        n = j;
        input.close();

        //从文件中读入各个物品的选择结果
        input.open(data_set_s.c_str());
        if(input.fail())
            cout << data_set_s << "does not exit" << endl;
        j = 1;
        while(!input.eof())
        {
            input >> s[j];
            if(input.eof()) break;
            j++;
        }
        input.close();

        //从文件中读入各个物品的重量
        input.open(data_set_w.c_str());
        if(input.fail())
            cout << data_set_w << "does not exit" << endl;
        j = 1;
        while(!input.eof())
        {
            input >> w[j];
            if(input.eof()) break;
            j++;
        }
        input.close();


        //初始化变量，调用BFS函数用分支限界方法对0/1背包问题进行求值
        memset(bestx, 0, sizeof(bestx));
        bestv = 0;
        BFS();

        //验证算法实现结果的正确性
        int check = 1;
        for(int k = 1; k <= n; k++)
        {
            if(bestx[k] != s[k])
            {
                check = 0;
                break;
            }
        }
        if(check == 1)
            cout << "P0" << num << ": passed!" << endl;
        else
            cout << "P0" << num << ": failed!" << endl;
    }
    return 0;
}
