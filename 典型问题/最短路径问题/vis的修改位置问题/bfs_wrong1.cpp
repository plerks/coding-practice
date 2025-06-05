#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
    int n = 4;
    vector<vector<int>> graph(n);
    graph[0] = {1, 2};
    graph[1] = {0, 2, 3};
    graph[2] = {0, 1};

    queue<int> q;
    vector<int> vis(n, 0);
    vector<int> enqueue_cnt(n, 0); // 入队次数
    vector<int> dis(n, 0);
    q.push(0); // 以0为root
    enqueue_cnt[0] = 1;

    while (!q.empty()) {
        int node = q.front(); q.pop();

        vis[node] = true;

        for (int neighbor : graph[node]) {
            if (!vis[neighbor]) {
                dis[neighbor] = dis[node] + 1;
                q.push(neighbor);
                // vis[neighbor] = true; // 必须写这行
                enqueue_cnt[neighbor]++;
            }
        }
    }

    cout << "enqueue_cnt: ";
    for (int cnt : enqueue_cnt) { // 输出 1 1 2 1，正确输出应为 1 1 1 1
        cout << cnt << " ";
    }
    cout << endl;

    cout << "dis: ";
    for (int d : dis) { // 输出 0 1 2 2，正确输出应为 0 1 1 2
        cout << d << " ";
    }

    return 0;
}