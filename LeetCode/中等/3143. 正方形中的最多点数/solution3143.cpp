/*
url: https://leetcode.cn/problems/maximum-points-inside-the-square/description/
LeetCode参考: https://leetcode.cn/problems/maximum-points-inside-the-square/solutions/2775310/er-fen-bian-chang-tong-shi-ji-lu-da-an-z-92w5/
标签: LeetCode第130场双周赛, 二分查找, 最小次小
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3143 {
public:
    // 我的解法，二分，通过
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        // 正方形边长过大之后将不合法，二分查找最后一个合法正方形的规模
        int maxN = 0;
        for (auto &point : points) {
            maxN = max(maxN, max(abs(point[0]), abs(point[1])));
        }
        int left = 0, right = maxN;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (check(points, s, mid)) {
                left = mid + 1;
            }
            else right = mid - 1;
        }
        int ans = 0;
        for (int i = 0; i < points.size(); i++) {
            auto &point = points[i];
            if (max(abs(point[0]), abs(point[1])) <= (left - 1)) {
                ans++;
            }
        }
        return ans;
    }

    bool check(vector<vector<int>>& points, string s, int maxN) {
        set<char> mySet;
        for (int i = 0; i < points.size(); i++) {
            auto &point = points[i];
            if (max(abs(point[0]), abs(point[1])) <= maxN) {
                char tag = s[i];
                if (mySet.find(tag) != mySet.end()) return false;
                mySet.insert(tag);
            }
        }
        return true;
    }

    /* 灵茶山艾府题解解法，正方形右上角为(n, n)，若正方形包含某个点(x, y)，则要满足(x, y)的切比雪夫距离max(|x|, |y|) <= n。
    将点按标签分组，正方形合法，则n < 所有标签的点的次小切比雪夫距离的最小值。也就是说正方形最多扩展到次小值里最小那个 - 1。*/
    int maxPointsInsideSquare_implementation2(vector<vector<int>>& points, string s) {
        int n = points.size();
        /* 静态数组初始化，如果只提供了一个值，那么这个值将赋给数组的第一个元素，剩下的元素将初始化为零。
        int min[26] = {0}可以得到全0，int min[26] = {INT_MAX}只有第一个元素为INT_MAX，其它为0。
        写int min[26] = {INT_MAX}不行
        */
        int min[26];
        for (int i = 0; i < 26; i++) min[i] = INT_MAX;
        int minOfSubMin = INT_MAX; // 按标签分组的次小切比雪夫距离中的最小值
        for (int i = 0; i < n; i++) {
            auto &point = points[i];
            int x = point[0], y = point[1], tag = s[i] - 'a';
            int d = max(abs(x), abs(y));
            if (d < min[tag]) {
                minOfSubMin = std::min(minOfSubMin, min[tag]);
                min[tag] = d;
            }
            else {
                minOfSubMin = std::min(minOfSubMin, d);
            }
        }
        int ans = 0;
        // 无需遍历所有点，最多26个
        for (int d : min) {
            if (d < minOfSubMin) ans++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3143 solu;
    vector<vector<int>> points = {{2,2},{-1,-2},{-4,4},{-3,1},{3,-3}};
    cout << solu.maxPointsInsideSquare(points, "abdca") << endl;
    cout << solu.maxPointsInsideSquare_implementation2(points, "abdca") << endl;
    return 0;
}
