#include <iostream>
#include <queue>
using namespace std;

const int maxn = 99;
int w[maxn];   //物品的重量
int v[maxn];   //物品的价值
int n;         //物品的个数
int c;         //背包的容量


int bestv = 0;   //存放最大价值
int bestx[maxn];  //存放最大价值对应的最优解
int total = 1;
//解空间树的结点
struct nodetype
{
    int no;     //结点编号
    int i;      //结点对应的树的层数
    int w;      //当前结点的重量之和
    int v;      //当前结点的价值之和
    int x[maxn];    //当前结点的各个物品的选择结果
    double ub;      //当前结点的能够得到的最大的价值
};

void input()
{
    cout << "The number of object: " << endl;
    cin >> n;
    cout << "The weight of each object: " << endl;
    for(int i = 1; i <= n; i++)
        cin >> w[i];
    cout  << "The value of each object: " << endl;
    for(int i = 1; i <= n; i++)
        cin >> v[i];
    cout << "The capacity of the backpack: " << endl;
    cin >> c;
}

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

void output()
{
    cout << "The biggest value is: " << bestv << endl;
    cout << "The optimal solution is: ";
    cout << "(";
    for(int j = 1; j < n; j++)
        cout << bestx[j] << ", ";
    cout << bestx[n] << ")" << endl;
}

int main()
{
    input();
    BFS();
    output();
    return 0;
}
