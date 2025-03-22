/*
url: https://leetcode.cn/problems/recover-the-original-array/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2122 {
public:
    vector<int> recoverArray(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        unordered_map<int, int> pos;
        vector<int> ans;
        for (int i = 1; i < n; i++) {
            int k = (nums[i] - nums[0]) / 2; // 枚举k
            if (k == 0) continue; // 题目要求k是正整数
            vector<int> tag(n); // 0表示是low的，1表示是high的
            /* 然后如何区分low和high，low和high可能错着，
            现在没被访问的第一个一定是low的，然后通过这个low能标记一个high。
            继续这样做，如果标记不上对应的high则非法。
            */
            int l = 0, r = 0;
            bool legal = true;
            for (int j = 0; j < n; j++) {
                if (tag[l] == 0) {
                    while (r < n && nums[r] < nums[l] + 2 * k) r++;
                    if (r == n || nums[r] != nums[l] + 2 * k) {
                        legal = false;
                        break;
                    }
                    tag[r] = 1;
                    l++;
                    r++;
                }
                else l++;
            }
            if (legal) {
                for (int j = 0; j < n; j++) {
                    if (tag[j] == 0) ans.push_back(nums[j] + k);
                }
                return ans;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2122 solu;
    // auto a = solu.recoverArray(*new vector<int>{2,10,6,4,8,12});
    auto b = solu.recoverArray(*new vector<int>{1,1,3,3});
    return 0;
}