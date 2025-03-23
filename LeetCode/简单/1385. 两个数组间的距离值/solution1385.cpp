/*
url: https://leetcode.cn/problems/find-the-distance-value-between-two-arrays/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1385 {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int n1 = arr1.size(), n2 = arr2.size();
        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());
        int l = 0, r = 0;
        int ans = 0;
        for (int i = 0; i < n1; i++) {
            int x = arr1[i];
            while (l < n2 && arr2[l] < x - d) l++;
            while (r < n2 && arr2[r] <= x + d) r++;
            // [l, r)距离x的距离<=d
            if (r - l <= 0) ans++;  
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1385 solu;
    cout << solu.findTheDistanceValue(*new vector<int>{4,5,8}, *new vector<int>{10,9,1,8}, 2) << endl;
    return 0;
}