/*
url: https://leetcode.cn/problems/bitwise-ors-of-subarrays/
标签: 【算法题单】位运算, LogTrick
*/
#include <bits/stdc++.h>

using namespace std;

class Solution898 {
public:
    int subarrayBitwiseORs(vector<int>& arr) {
        unordered_set<int> st;
        for (int i = 0; i < arr.size(); i++) { // 枚举右边界
            st.insert(arr[i]);
            for (int j = i - 1; j >= 0; j--) {
                if ((arr[i] | arr[j]) == arr[j]) break;
                arr[j] |= arr[i];
                st.insert(arr[j]);
            }
        }
        return st.size();
    }
};

int main(int argc, char const *argv[]) {
    Solution898 solu;
    cout << solu.subarrayBitwiseORs(*new vector<int>{1,1,2}) << endl;
    return 0;
}