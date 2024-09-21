// https://leetcode.cn/problems/node-with-highest-edge-score/description/?envType=daily-question&envId=2024-09-21

#include <bits/stdc++.h>

using namespace std;

class Solution2374 {
public:
    int edgeScore(vector<int>& edges) {
        int n = edges.size();
        vector<long long> score(n, 0);
        for (int i = 0; i < edges.size(); i++) {
            score[edges[i]] += i;
        }
        int ans = 0;
        long long mx = score[0];
        for (int i = 1; i < score.size(); i++) {
            if (score[i] > mx) {
                ans = i;
                mx = score[i];
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
