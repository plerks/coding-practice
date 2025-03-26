/*
url: https://leetcode.cn/problems/online-election/
相关: LeetCode1146. 快照数组
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class TopVotedCandidate {
public:
    unordered_map<int, vector<int>> mp;

    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        for (int i = 0; i < times.size(); i++) {
            int t = times[i];
            mp[persons[i]].push_back(t);
        }
    }
    
    int q(int t) {
        int ans = 0;
        int mx = 0; // 最大票数
        int lastVoteTime = 0;
        for (auto &[p, vec] : mp) {
            // 搜索最后一个<=t
            int index = upper_bound(vec.begin(), vec.end(), t) - vec.begin() - 1;
            if (index == -1) continue;
            if (index + 1 > mx) {
                ans = p;
                mx = index + 1;
                lastVoteTime = vec[index];
            }
            else if (index + 1 == mx && vec[index] > lastVoteTime) {
                ans = p;
                lastVoteTime = vec[index];
            }
        }
        return ans;
    }
};

/* 官方题解解法，t单调增加，在构造时就预处理每个时间点的胜者，调用q()时直接查询。由于每个人票数单调增加，
只需和当前最大值比较即可知道当前胜者，因为每个票数单调增加，最大值要么是旧最大值，要么就是最新修改的
*/
class TopVotedCandidate_implementation2 {
public:
    vector<int> times;
    vector<int> winners;

    TopVotedCandidate_implementation2(vector<int>& persons, vector<int>& times) {
        this->times = times;
        unordered_map<int, int> cnt;
        int mx = 0;
        int p = 0;
        for (int i = 0; i < times.size(); i++) {
            cnt[persons[i]]++;
            if (cnt[persons[i]] >= mx) { // 这样同票时最近获得投票的就是胜者
                mx = cnt[persons[i]];
                p = persons[i];
            }
            winners.push_back(p);
        }
    }
    
    int q(int t) {
        int index = upper_bound(times.begin(), times.end(), t) - times.begin() - 1;
        return winners[index];
    }
};

int main(int argc, char const *argv[]) {
    TopVotedCandidate tvc(*new vector<int>{0, 1, 1, 0, 0, 1, 0}, *new vector<int>{0, 5, 10, 15, 20, 25, 30});
    cout << tvc.q(3) << endl;
    cout << tvc.q(12) << endl;
    cout << tvc.q(25) << endl;
    cout << tvc.q(15) << endl;
    cout << tvc.q(24) << endl;
    cout << tvc.q(8) << endl;

    TopVotedCandidate_implementation2 tvc2(*new vector<int>{0, 1, 1, 0, 0, 1, 0}, *new vector<int>{0, 5, 10, 15, 20, 25, 30});
    cout << tvc2.q(3) << endl;
    cout << tvc2.q(12) << endl;
    cout << tvc2.q(25) << endl;
    cout << tvc2.q(15) << endl;
    cout << tvc2.q(24) << endl;
    cout << tvc2.q(8) << endl;
    return 0;
}