/*
url: https://leetcode.cn/problems/find-occurrences-of-an-element-in-an-array/description/
标签: LeetCode第131场双周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3159 {
public:
    vector<int> occurrencesOfElement(vector<int>& nums, vector<int>& queries, int x) {
        vector<int> pos;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == x) {
                pos.push_back(i);
            }
        }
        vector<int> ans;
        for (int q : queries) {
            /* 这里有个C++的坑，周赛时这里写了q - 1 > pos.size() - 1，然后会错误，vector.size()返回类型是size_t，
            是unsigned long long，然后例如q为10，vector的size为0，则q - 1 > vector.size() - 1会是false，因为会隐式转为无符号数的比较，
            而vector.size() - 1无符号数溢出了。(补充，有符号数和无符号数的比较，都是用的cmpl指令，比较时不区分类型，比较后的跳转用的指令看类型，例如jg和ja) */
            if (q > pos.size()) ans.push_back(-1);
            else ans.push_back(pos[q - 1]);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
