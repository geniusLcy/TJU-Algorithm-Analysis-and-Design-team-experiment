#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

/* 每个线性表的类型都是vector<vector<int>>，其中元组的类型是vector<int> */
vector<vector<vector<int> > > vec;   /* 存储所有线性表的大线性表 */
int n, c, max_value;
int w[10010], v[10010];
int x[10010] = {};
int s[10010];   /* 用于检查算法得到的答案是否与数据集所给答案一致 */

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
    memset(x, 0, 10010);
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
    /* 从数据集文件中读取数据 */
    ifstream input;
    // string path1 = "algorithm_exp-main\\data_set";
    string path1 = "..\\data_set";
    string path2;
    string path;
    int idx;
    string data_set_c, data_set_p, data_set_s, data_set_w;

    for(int dsi = 1; dsi <= 8; dsi ++){
        path2 = "\\P0";
        path2 += static_cast<char>(dsi + 48);
        data_set_c = "\\p0"; data_set_c = data_set_c + static_cast<char>(dsi + 48) + "_c.txt";
        data_set_p = "\\p0"; data_set_p = data_set_p + static_cast<char>(dsi + 48) + "_p.txt";
        data_set_s = "\\p0"; data_set_s = data_set_s + static_cast<char>(dsi + 48) + "_s.txt";
        data_set_w = "\\p0"; data_set_w = data_set_w + static_cast<char>(dsi + 48) + "_w.txt";

        char* path_c = new char[100];

        path = path1 + path2 + data_set_w;
        for(idx = 0; idx < path.length(); idx ++) path_c[idx] = path[idx]; path_c[idx] = '\0';
        input.open(path_c);
        int cnt = 0;
        while(!input.eof()) input >> w[cnt ++];
        n = cnt;
        input.close();

        path = path1 + path2 + data_set_p;
        for(idx = 0; idx < path.length(); idx ++) path_c[idx] = path[idx]; path_c[idx] = '\0';
        input.open(path_c);
        cnt = 0;
        while(!input.eof()) input >> v[cnt ++];
        input.close();

        path = path1 + path2 + data_set_c;
        for(idx = 0; idx < path.length(); idx ++) path_c[idx] = path[idx]; path_c[idx] = '\0';
        input.open(path_c);
        input >> c;
        input.close();

        path = path1 + path2 + data_set_s;
        for(idx = 0; idx < path.length(); idx ++) path_c[idx] = path[idx]; path_c[idx] = '\0';
        input.open(path_c);
        cnt = 0;
        while(!input.eof()) input >> s[cnt ++];
        input.close();

        delete path_c;

        /* 每处理一组数据之前清空所有线性表 */
        while(vec.size())
            vec.pop_back();

        solution();

        /* 检查算法所得答案的正确性 */
        bool flag = true;
        for(int i = 0; i < n; i ++)
            if(x[i] != s[i]){
                flag = false;
                break;
            }
        if(dsi > 1) cout << endl;
        cout << "Data set " << dsi << (flag ? " passed!" : " failed!");
        if(!flag){
            cout << "Your optimal selection:";
            cout << x[0]; for(int i = 1; i < n; i ++) cout << " " << x[i]; cout << endl;
            cout << "Correct optimal selection:";
            cout << s[0]; for(int i = 1; i < n; i ++) cout << " " << s[i]; cout << endl;
        }
    }

    return 0;
}
