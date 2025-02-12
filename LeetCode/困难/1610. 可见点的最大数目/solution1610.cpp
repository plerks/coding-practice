/*
url: https://leetcode.cn/problems/maximum-number-of-visible-points/
参考: https://leetcode.cn/problems/maximum-number-of-visible-points/solutions/1159054/you-xiao-ke-jian-dian-de-zui-da-shu-mu-b-r1qz/
标签: 【题单】滑动窗口与双指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1610 {
public:
    // 我的解法，通过
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        // 把location转换到原点
        for (auto &point : points) {
            point[0] -= location[0];
            point[1] -= location[1];
        }
        int n = points.size();
        vector<double> f;
        int origin = 0;
        for (int i = 0; i < n; i++) {
            double y = points[i][1];
            double x = points[i][0];
            if (x > 0) f.push_back(atan(y / x));
            else if (x == 0) {
                if (y == 0) origin++; // 就在原点的点的数量，相当于极角任意，不放入f，最后加上去
                else if (y > 0) f.push_back(M_PI / 2);
                else f.push_back(-M_PI / 2);
            }
            else if (y <= 0) f.push_back(atan(y / x) - M_PI);
            else f.push_back(atan(y / x) + M_PI);
        }
        n = f.size(); // 各个点的极角，范围为[-π, π]，去除了已经在原点的点
        sort(f.begin(), f.end());
        int ans = 0;
        int r = 1;

        // 判断f[r]是否在[f[l], f[l]+θ]内
        auto check = [&](int l, int r) {
            if (l < r) return f[r] <= f[l] + angle * M_PI / 180.0;
            else return f[r] + 2 * M_PI <= f[l] + angle * M_PI / 180.0; // 如果f[r]越过了f末尾，弧度要加上2π去和f[l]+θ比
        };

        for (int l = 0; l < n; l++) {
            if (r == l) r = (r + 1) % n;
            while (l != r && check(l, r)) {
                r = (r + 1) % n;
            }
            if (r <= l) ans = max(ans, n + r - l); // 如果r比l小说明转了一圈
            else ans = max(ans, r - l);
        }
        return ans + origin;
    }

    /* 官方题解做法，用atan2这个函数，避免写一堆判断，atan2直接得出范围为[-π, π]的角的弧度，只有两个参数都为0需要特判一下防止ub。
    此外，角到π的位置突变的问题，官方题解的做法是把弧度加上2π加到末尾，0<=angle<360，所以不会有重复计数的问题。
    */
    int visiblePoints_implementation2(vector<vector<int>>& points, int angle, vector<int>& location) {
        for (auto &point : points) {
            point[0] -= location[0];
            point[1] -= location[1];
        }
        int n = points.size();
        vector<double> f;
        int origin = 0;
        for (int i = 0; i < n; i++) {
            int x = points[i][0];
            int y = points[i][1];
            if (x == 0 && y == 0) {
                origin++;
                continue;
            }
            f.push_back(atan2(y, x));
        }
        int m = f.size();
        sort(f.begin(), f.end());
        for (int i = 0; i < m; i++) {
            f.push_back(f[i] + 2 * M_PI);
        }
        // 滑窗
        // 可以r先动，拖着l动；也可以l先动，推着r动
        int l = 0;
        int ans = 0;
        for (int r = 0; r < 2 * m; r++) {
            while (f[l] < f[r] - angle * M_PI / 180.0) {
                l++;
            }
            ans = max(ans, r - l + 1);
        }
        return ans + origin;
    }
};

int main(int argc, char const *argv[]) {
    Solution1610 solu;
    cout << solu.visiblePoints(*new vector<vector<int>>{{2,1},{2,2},{3,3}}, 90, *new vector<int>{1,1}) << endl;
    cout << solu.visiblePoints(*new vector<vector<int>>{{2,1},{2,2},{3,4},{1,1}}, 90, *new vector<int>{1,1}) << endl;
    cout << solu.visiblePoints(*new vector<vector<int>>{{1,0},{2,1}}, 13, *new vector<int>{1,1}) << endl;
    cout << solu.visiblePoints(*new vector<vector<int>>{{1,1},{2,2},{3,3},{4,4},{1,2},{2,1}}, 0, *new vector<int>{1,1}) << endl;
    
    cout << solu.visiblePoints_implementation2(*new vector<vector<int>>{{2,1},{2,2},{3,3}}, 90, *new vector<int>{1,1}) << endl;
    cout << solu.visiblePoints_implementation2(*new vector<vector<int>>{{2,1},{2,2},{3,4},{1,1}}, 90, *new vector<int>{1,1}) << endl;
    cout << solu.visiblePoints_implementation2(*new vector<vector<int>>{{1,0},{2,1}}, 13, *new vector<int>{1,1}) << endl;
    cout << solu.visiblePoints_implementation2(*new vector<vector<int>>{{1,1},{2,2},{3,3},{4,4},{1,2},{2,1}}, 0, *new vector<int>{1,1}) << endl;
    return 0;
}