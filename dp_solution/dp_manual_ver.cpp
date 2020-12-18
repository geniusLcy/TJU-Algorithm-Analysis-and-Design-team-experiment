#include <iostream>
#include <vector>
using namespace std;

/* 每个线性表的类型都是vector<vector<int>>，其中元组的类型是vector<int> */
vector<vector<vector<int> > > vec;   /* 存储所有线性表的大线性表 */
int n, c, max_value;
int w[10010], v[10010];
int x[10010] = {};

int get_value(int vec_i, int wt){
    int len = vec[vec_i].size();
    for(int i = 0; i < len; i ++)
        if(vec[vec_i][i][0] > wt)
            return vec[vec_i][i - 1][1];
    return vec[vec_i][len - 1][1];
}

void solution(){
    vector<int> first(2);   /* 用于存储每个线性表的第一个元组(0,0) */
    first[0] = first[1] = 0;

    vector<int> temp(2);
    vector<vector<int> > new_line;   /* 空的新线性表 */

    /* 向背包中放入第一个物品，同时构造第一个线性表 */
    vec.push_back(new_line);
    vec[0].push_back(first);
    if(w[n - 1] <= c){
        temp[0] = w[n - 1], temp[1] = v[n - 1];
        vec[0].push_back(temp);
    }

    /* 向背包中放入剩余的n-1个物品 */
    for(int i = n - 2, idx = 1; i >= 0; i --, idx ++){
        vector<vector<int> > Q;   /* 用于存储新线性表中可能添加的新的元组 */

        /* 获取Q */
        int len = vec[idx - 1].size();
        for(int j = 0; j < len; j ++){
            if(vec[idx - 1][j][0] + w[i] <= c){
                temp[0] = vec[idx - 1][j][0] + w[i], temp[1] = vec[idx - 1][j][1] + v[i];
                Q.push_back(temp);
            }
            else break;
        }

        /* 将第i个线性表(vec[i-1])与Q合并，构造第i+1个线性表(vec[i]) */
        vec.push_back(new_line);
        vec[idx].push_back(first);
        int len_Q = Q.size();
        int temp_max_value = 0;
        for(int j = 1, k = 0; j < len || k < len_Q;){
            if(j < len && k < len_Q){
                if(vec[idx - 1][j][0] < Q[k][0]){
                    if(vec[idx - 1][j][1] > temp_max_value){
                        vec[idx].push_back(vec[idx - 1][j]);
                        temp_max_value = vec[idx - 1][j][1];
                    }
                    j ++;
                }
                else if(vec[idx - 1][j][0] == Q[k][0]){
                    if(vec[idx - 1][j][1] < Q[k][1]){
                        vec[idx].push_back(Q[k]);
                        temp_max_value = Q[k][1];
                    }
                    else{
                        vec[idx].push_back(vec[idx - 1][j]);
                        temp_max_value = vec[idx - 1][j][1];
                    }
                    j ++, k ++;
                }
                else{
                    if(Q[k][1] > temp_max_value){
                        vec[idx].push_back(Q[k]);
                        temp_max_value = Q[k][1];
                    }
                    k ++;
                }
            }
            else if(j == len){
                if(Q[k][1] > temp_max_value)
                    vec[idx].push_back(Q[k]);
                k ++;
            }
            else{
                if(vec[idx - 1][j][1] > temp_max_value)
                    vec[idx].push_back(vec[idx - 1][j]);
                j ++;
            }
        }
    }

    /* 获取最大价值 */
    int len_f = vec[n - 1].size();
    max_value = vec[n - 1][len_f - 1][1];

    /* 回溯得到最优解 */
    int c1 = c;
    for(int i = 0; i < n - 1; i ++){
        if(get_value(n - i - 1, c1) == get_value(n - i - 2, c1)) x[i] = 0;
        else{
            x[i] = 1;
            c1 -= w[i];
        }
    }
    x[n - 1] = get_value(0, c1) ? 1 : 0;
}

int main(){
    cout << "Enter n:"; cin >> n;
    cout << "Enter weight:"; for(int i = 0; i < n; i ++) cin >> w[i];
    cout << "Enter value:"; for(int i = 0; i < n; i ++) cin >> v[i];
    cout << "Enter capacity:"; cin >> c;

    solution();

    cout << endl;
    cout << "Max value:" << max_value << endl;
    cout << "An optimal selection:";
    cout << x[0];
    for(int i = 1; i < n; i ++) cout << " " << x[i];
    cout << endl;

    return 0;
}
