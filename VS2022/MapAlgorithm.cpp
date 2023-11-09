#include<vector>
#include<queue>
using namespace std;

//题目一：单源最短路径————迪杰斯特拉算法
int networkDelayTime(vector<vector<int>>& times, int n, int k)
{
    //先建图
    vector<vector<pair<int, int>>> m(n + 1, vector<pair<int, int>>());

    for (int i = 0; i < times.size(); i++)
    {
        m[times[i][0]].push_back({ times[i][1],times[i][2] });
    }

    //实现迪杰斯特拉
    //从k结点出发
    int ans = 0;
    vector<bool> close(n + 1, false);
    vector<int> cost(n + 1, INT_MAX); cost[k] = 0;
    auto cmp = [&](const int a, const int b) {return cost[a] > cost[b]; };
    priority_queue<int, vector<int>, decltype(cmp)> q(cmp);
    q.push(k);
    while (!q.empty())
    {
        int t = q.top(); q.pop();
        if (close[t] == true) continue;
        close[t] = true;
        int cur = cost[t];
        ans = cur;
        for (int i = 0; i < m[t].size(); i++)
        {
            if (!close[m[t][i].first])
            {
                cost[m[t][i].first] = min(cost[m[t][i].first], cur + m[t][i].second);
                ans = max(ans, cur + m[t][i].second);
                q.push(m[t][i].first);
            }
        }
    }
    for (int i = 1; i <= n; i++) if (close[i] == false) return -1;
    return ans;

}