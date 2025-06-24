/*
url: https://leetcode.cn/problems/create-maximum-number/
相关: LeetCode1673. 找出最具竞争力的子序列
标签: 【算法题单】单调栈, 字典序
*/
#include <bits/stdc++.h>

using namespace std;

class Solution321 {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size();
        int n = nums2.size();
        // if (m > n) return maxNumber(nums2, nums1, k);

        vector<int> ans;

        // 枚举从 nums1 选 i 个数，从nums2 选 k-i 个数
        for (int i = max(0, k - n); i <= min(k, m); i++) {
            auto v1 = f(nums1, i);
            auto v2 = f(nums2, k - i);
            // 合并出一个字典序最大的
            int p = 0, q = 0;
            vector<int> t;
            while (p < v1.size() || q < v2.size()) {
                if (p < v1.size() && q < v2.size() && v1[p] == v2[q]) {
                    // v1[p]和v2[q]相等，选v1[p..] v2[q..]字典序较大的那个的头
                    // 例如 [0 1 0 3 9] 和 [0 1 0 5 6]，选出来的是 0 1 0 5 6 ...
                    if (!compare(v1, p, v2, q)) t.push_back(v1[p++]); // 这里真就这么每次比较下字典序，官方题解和我写的思路一样
                    else t.push_back(v2[q++]);
                }
                else if (p < v1.size() && (q == v2.size() || v1[p] > v2[q])) {
                    t.push_back(v1[p++]);
                }
                else t.push_back(v2[q++]);
            }
            ans = max(ans, t);
        }
        return ans;
    }

    // 若字典序 nums1 < nums2或者二者相等，返回true
    bool compare(vector<int>& nums1, int p1, vector<int>& nums2, int p2) {
        int m = nums1.size();
        int n = nums2.size();
        while (p1 < m && p2 < n) {
            if (nums1[p1] == nums2[p2]) {
                p1++;
                p2++;
            }
            else if (nums1[p1] < nums2[p2]) return true;
            else return false;
        }
        if (p1 == m) return true;
        return false;
    }

    // LeetCode1673，把字典序最大的k个数找出来
    vector<int> f(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && st.back() < nums[i] && st.size() - 1 + n - i >= k) st.pop_back();
            if (st.size() < k) st.push_back(nums[i]);
        }
        return st;
    }
};

int main(int argc, char const *argv[]) {
    Solution321 solu;
    // auto a = solu.maxNumber(*new vector<int>{3,4,6,5}, *new vector<int>{9,1,2,5,8,3}, 5);

    // auto b = solu.maxNumber(*new vector<int>{6,7}, *new vector<int>{6,0,4}, 5);

    auto c = solu.maxNumber(*new vector<int>{5,0,2,1,0,1,0,3,9,1,2,8,0,9,8,1,4,7,3}, *new vector<int>{7,6,7,1,0,1,0,5,6,0,5,0}, 31);
    return 0;
}