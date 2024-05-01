// https://leetcode.cn/problems/remove-stones-to-minimize-the-total/description/

#include <bits/stdc++.h>

using namespace std;

class Solution1962 {
public:
    int minStoneSum(const vector<int>& piles, int k) {
        priority_queue<int> q; // C++的priority_queue是大根堆
        int ans = 0;
        for (auto &pile : piles) {
            q.push(pile);
            ans += pile;
        }
        for (int i = 0; i < k; i++) {
            int x = q.top();
            q.pop();
            ans -= x / 2;
            x = x - x / 2;
            q.push(x);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1962 solu;
    cout << solu.minStoneSum({5, 4, 9}, 2) << endl;
    return 0;
}