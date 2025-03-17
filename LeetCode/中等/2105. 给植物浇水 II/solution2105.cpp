/*
url: https://leetcode.cn/problems/watering-plants-ii/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2105 {
public:
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        // max(plants[i]) <= capacityA, capacityB，到了同一株植物时最多只需补水一次
        int n = plants.size();
        int l = 0, r = n - 1;
        int ans = 0;
        int a = capacityA; // 剩余水量
        int b = capacityB;
        while (l < r) {
            ans += plants[l] > a;
            a = plants[l] > a ? capacityA - plants[l] : a - plants[l];
            l++;
            ans += plants[r] > b;
            b = plants[r] > b ? capacityB - plants[r] : b - plants[r];
            r--;
        }
        // l == r时
        if (l == r) {
            if (a >= b) {
                ans += plants[l] > a;
            }
            else ans += plants[l] > b;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2105 solu;
    cout << solu.minimumRefill(*new vector<int>{2,2,3,3}, 5, 5) << endl;
    return 0;
}