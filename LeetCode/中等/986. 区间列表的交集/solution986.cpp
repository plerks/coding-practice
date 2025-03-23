/*
url: https://leetcode.cn/problems/interval-list-intersections/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution986 {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        int n1 = firstList.size(), n2 = secondList.size();
        int i = 0, j = 0;
        vector<vector<int>> ans;
        while (i < n1 && j < n2) {
            int l = max(firstList[i][0], secondList[j][0]);
            int r = min(firstList[i][1], secondList[j][1]);
            if (r - l + 1 > 0) ans.push_back({l, r});
            if (firstList[i][1] >= secondList[j][1]) j++;
            else i++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution986 solu;
    auto a = solu.intervalIntersection(*new vector<vector<int>>{{0,2},{5,10},{13,23},{24,25}}, *new vector<vector<int>>{{1,5},{8,12},{15,24},{25,26}});
    return 0;
}