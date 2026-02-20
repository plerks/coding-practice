/*
url: https://leetcode.cn/problems/weighted-word-mapping/
标签: LeetCode第176场双周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3838 {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        vector<int> weight;
        for (string& word : words) {
            int w = 0;
            for (char ch : word) {
                w += weights[ch - 'a'];
                w %= 26;
            }
            weight.push_back(w);
        }
        string ans;
        for (int w : weight) {
            ans.push_back('a' + 25 - w);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}