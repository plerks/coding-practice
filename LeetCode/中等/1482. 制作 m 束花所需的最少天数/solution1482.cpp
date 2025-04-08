/*
url: https://leetcode.cn/problems/minimum-number-of-days-to-make-m-bouquets/
标签: 【题单】二分算法, 分组循环
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1482 {
public:
    // 我的解法，check时直接模拟并用上了分组循环，比较麻烦，用时187ms
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int x, int y) {
            return bloomDay[x] < bloomDay[y];
        });

        auto check = [&](int d) {
            vector<bool> bloom(n);
            // 最后一个<=d
            int index = lower_bound(idx.begin(), idx.end(), d, [&](int id, int d) {
                return bloomDay[id] <= d;
            }) - idx.begin() - 1;
            // idx[0, index]开花
            for (int i = 0; i <= index; i++) bloom[idx[i]] = true;
            int cnt = 0;
            for (int i = 0; i < n;) {
                if (bloom[i] == false) {
                    i++;
                    continue;
                }
                int start = i;
                for (i++; i < n && bloom[i] == true; i++);
                cnt += (i - start) / k;
            }
            return cnt >= m;
        };

        int mx = *max_element(bloomDay.begin(), bloomDay.end());
        int left = 0, right = mx;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left == mx + 1 ? -1 : left;
    }

    /* 官方题解解法，只需遍历bloomDay比较日期，即可知道这朵花是否开花，然后这个遍历顺序是从花的左到右做的，
    记已经积累的开花数，即可达到分组循环的效果。用时47ms
    */
    int minDays_implementation2(vector<int>& bloomDay, int m, int k) {
        auto check = [&](int d) {
            int cnt = 0;
            int len = 0;
            for (int i = 0; i < bloomDay.size(); i++) {
                if (bloomDay[i] <= d) len++;
                else len = 0;
                if (len == k) { // 当即判断
                    cnt++;
                    len = 0;
                    continue;
                }
            }
            return cnt >= m;
        };

        int mx = *max_element(bloomDay.begin(), bloomDay.end());
        int left = 0, right = mx;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (!check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return left == mx + 1 ? -1 : left;
    }
};

int main(int argc, char const *argv[]) {
    Solution1482 solu;
    cout << solu.minDays(*new vector<int>{1,10,3,10,2}, 3, 1) << endl;
    cout << solu.minDays_implementation2(*new vector<int>{1,10,3,10,2}, 3, 1) << endl;
    return 0;
}