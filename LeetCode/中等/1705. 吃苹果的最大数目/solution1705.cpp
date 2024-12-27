/*
url: https://leetcode.cn/problems/maximum-number-of-eaten-apples/?envType=daily-question&envId=2024-12-24
参考: https://leetcode.cn/problems/maximum-number-of-eaten-apples/solutions/1172766/chi-ping-guo-de-zui-da-shu-mu-by-leetcod-93ka/
*/
#include <bits/stdc++.h>

using namespace std;

// 在第day天生产了持续rot天的苹果，个数为count
struct apple {
    int day;
    int rot;
    int count;
};

class Solution1705 {
public:
    // 我的解法，通过，112ms。优先吃快要过期的
    int eatenApples(vector<int>& apples, vector<int>& days) {
        int n = apples.size();
        int ans = 0;
        auto comp = [&](apple& x, apple& y) {
            return x.day + x.rot > y.day + y.rot;
        };
        priority_queue<apple, vector<apple>, decltype(comp)> pq(comp);
        int time = 1; // 天数从1开始计数
        while (true) {
            if (time <= n && apples[time - 1] != 0) {
                pq.push({time, days[time - 1], apples[time - 1]});
            }
            // 消费
            while(!pq.empty() && pq.top().day + pq.top().rot <= time) {
                pq.pop();
            }
            if (time > n && pq.empty()) break;
            if (!pq.empty()) {
                ans++;
                apple app = pq.top();
                pq.pop();
                app.count--;
                if (app.count > 0) pq.push(app);
            }
            time++;
        }
        return ans;
    }

    // 官方题解解法，78ms，换一种思路，优先队列存过期时间和苹果数量，没必要记录苹果产生时间
    int eatenApples_implementation2(vector<int>& apples, vector<int>& days) {
        int n = apples.size();
        int ans = 0;
        // [过期时间, 个数]
        auto comp = [&](pair<int, int>& x, pair<int, int>& y) {
            return x.first > y.first;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(comp);
        int time = 1; // 天数从1开始计数
        while (true) {
            if (time <= n && apples[time - 1] != 0) {
                pq.push({time + days[time - 1], apples[time - 1]});
            }
            // 消费
            while(!pq.empty() && pq.top().first <= time) {
                pq.pop();
            }
            if (time > n && pq.empty()) break;
            if (!pq.empty()) {
                ans++;
                auto p = pq.top();
                pq.pop();
                p.second--;
                if (p.second > 0) pq.push(p);
            }
            time++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1705 solu;
    vector<int> apples = {3,0,0,0,0,2};
    vector<int> days = {3,0,0,0,0,2};
    cout << solu.eatenApples(apples, days) << endl;
    cout << solu.eatenApples_implementation2(apples, days) << endl;
    return 0;
}
