/*
url: https://leetcode.cn/problems/minimum-number-of-operations-to-make-word-k-periodic/description/
标签: LeetCode第396场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3137 {
public:
    int minimumOperationsToMakeKPeriodic(string word, int k) {
        map<string, int> myMap;
        int n = word.size();
        for (int i = 0; i < n / k; i++) {
            string sub = word.substr(i * k, k);
            myMap[sub]++;
        }
        int maxFreq = 0;
        for (auto &p : myMap) {
            maxFreq = max(maxFreq, p.second);
        }
        return n / k - maxFreq;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
