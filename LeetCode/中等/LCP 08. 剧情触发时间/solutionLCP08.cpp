/*
url: https://leetcode.cn/problems/ju-qing-hong-fa-shi-jian/
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class SolutionLCP08 {
public:
    vector<int> getTriggerTime(vector<vector<int>>& increase, vector<vector<int>>& requirements) {
        // 3种属性都是单调增加的，所以只需要搜索出三个index取最大值即可
        vector<vector<int>> attr;
        attr.push_back({0, 0, 0}); // 第0天
        int C, R, H;
        C = R = H = 0;
        for (int i = 0;i < increase.size(); i++) {
            C += increase[i][0];
            R += increase[i][1];
            H += increase[i][2];
            attr.push_back({C, R, H});
        }
        vector<int> ans;
        for (auto vec : requirements) {
            int p = vec[0], q = vec[1], r = vec[2];
            // 第一个>=
            int index1 = lower_bound(attr.begin(), attr.end(), p, [&](auto &v, int x) {
                return v[0] < x;
            }) - attr.begin();
            int index2 = lower_bound(attr.begin(), attr.end(), q, [&](auto &v, int x) {
                return v[1] < x;
            }) - attr.begin();
            int index3 = lower_bound(attr.begin(), attr.end(), r, [&](auto &v, int x) {
                return v[2] < x;
            }) - attr.begin();
            int res = max({index1, index2, index3});
            if (res == attr.size()) ans.push_back(-1);
            else ans.push_back(res);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    SolutionLCP08 solu;
    auto a = solu.getTriggerTime(*new vector<vector<int>>{{2,8,4},{2,5,0},{10,9,8}}, *new vector<vector<int>>{{2,11,3},{15,10,7},{9,17,12},{8,1,14}});
    return 0;
}