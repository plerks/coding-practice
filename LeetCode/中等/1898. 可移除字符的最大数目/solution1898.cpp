/*
url: https://leetcode.cn/problems/maximum-number-of-removable-characters/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1898 {
public:
    // LeetCode392. 判断子序列
    bool isSubsequence(string s, string t, vector<int> &remove) { // 判断s是否为t的子序列
        int i = 0, j = 0;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j] && !remove[j]) {
                i++; j++;
            }
            else j++;
        }
        return i == s.size();
    }

    int maximumRemovals(string s, string p, vector<int>& removable) {
        int n = s.size();

        auto check = [&](int k) {
            vector<int> remove(n);
            for (int i = 0; i <= k; i++) remove[removable[i]] = true;
            if (isSubsequence(p, s, remove)) return true;
            return false;
        };

        // 二分寻找最后一个是
        int left = 0, right = removable.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return right + 1; // 最多可以移除[0, right]位置的元素，那么移除个数就是right + 1
    }
};

int main(int argc, char const *argv[]) {
    Solution1898 solu;
    cout << solu.maximumRemovals("abcacb", "ab", *new vector<int>{3,1,0}) << endl;
    cout << solu.maximumRemovals("abcab", "abc", *new vector<int>{0,1,2,3,4}) << endl;
    return 0;
}