/*
url: https://leetcode.cn/problems/find-a-peak-element-ii/description/
LeetCode参考: https://leetcode.cn/problems/find-a-peak-element-ii/solutions/2571587/tu-jie-li-yong-xing-zui-da-zhi-pan-duan-r4e0n/
相关: LeetCode162. 寻找峰值, 典型问题/有序范围内的二分查找
标签: 二分查找
*/

#include <bits/stdc++.h>

using namespace std;

// 题目要求O(mlogn)或O(nlogm)的复杂度，m，n为矩阵行列数，矩阵元素各不相同
class Solution1901 {
public:
    /* 相比LeetCode162. 寻找峰值，输入改为二维之后，每个行的峰值都需要检查列的方向才能知道是否
    是二维情况下的峰值，这样就需要试每行的所有峰值，这样的思路就达不到时间复杂度要求。

    参考灵茶山艾府题解，考虑某一行的最大值mat[i][j]。
    1. 若mat[i+1][j] > mat[i][j]，则i+1行到第m-1行的最大值一定是峰值(若这个最大值不在第i+1行，显然，
    若在第i+1行，其一定大于左右下的值，由于其 >= mat[i+1][j] > mat[i][j] >= mat[i][0...n-1]，则其也一定是峰值)。
    由于下半部分存在峰值，只需在下半部分找峰值即可。
    2. 若mat[i+1][j] < mat[i][j]，若mat[i-1][j] < mat[i][j]，则mat[i][j]为峰值，若mat[i-1][j] > mat[i][j]，这与上
    一种情况相同，因此上方一定有个峰值。
    这样决定往上还是往下的过程是个二分矩阵的过程，这里二分是在一个方向上二分，不是行列方向都在二分。
    */
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        // 这题用闭区间二分自然一点，这里练习用开区间二分写
        int m = mat.size(), n = mat[0].size();
        int left = -1, right = m; // 最开始在(-1, m)行号的范围里找
        while (left + 1 < right) { // 区间不为空
            int i = (left + right) >> 1;
            int j = maxIndexJ(mat, i);
            // mat[i][j]为中间行的最大元素
            if (i + 1 < m && mat[i + 1][j] > mat[i][j]) {
                left = i;
            }
            else if (i - 1 >= 0 && mat[i - 1][j] > mat[i][j]) {
                right = i;
            }
            else return {i, j};
        }
        // 循环结束时left + 1 == right
        /* 最后一次进循环时left == right - 2，峰值一定存在，因为矩阵中的最大值一定是个峰值，因此
        当left == right - 2时，峰值一定存在在mid行，此时一定会走else return {i, j}的分支，所以
        一定不会执行下面的return。
        */
        return {-1, -1};
    }
    
    // 返回第i行最大值所在的列
    int maxIndexJ(vector<vector<int>>& mat, int i) {
        int max = INT_MIN;
        int j = 0;
        for (int k = 0; k < mat[0].size(); k++) {
            if (max < mat[i][k]) {
                max = mat[i][k];
                j = k;
            }
        }
        return j;
    }

    // 不在循环里写return，用searchFirst和searchLast的代码
    vector<int> findPeakGrid_implementation2(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        int left = -1, right = m; // 最开始在(-1, m)行号的范围里找
        while (left + 1 < right) { // 区间不为空
            int i = (left + right) >> 1;
            int j = maxIndexJ(mat, i);
            // mat[i][j]为中间行的最大元素
            if (i + 1 < m && mat[i + 1][j] > mat[i][j]) {
                left = i;
            }
            else {
                right = i;
            }
        }
        // 循环结束时left + 1 == right
        /* 这里最后应该是left还是left + 1好像必须要举例去看，本来开区间写法searchLast最后是return left，相应的first是left + 1，
        当一开始有0,1,2三行且峰值在第2行时，结束时left为1，right为2，所以是left + 1。这里不好区分是searchLast还是searchFirst问题。 */
        return {left + 1, maxIndexJ(mat, left + 1)}; // C++函数返回对象时会调用拷贝构造函数/移动构造函数，所以这里initializer_list会自动转成vector<int>
    }
};

int main(int argc, char const *argv[]) {
    Solution1901 solu;
    vector<vector<int>> nums = {{1,4},{3,2}};
    vector<int> ans = solu.findPeakGrid(nums);
    cout << '[' << ans[0] << ", " << ans[1] << ']' << endl;
    ans = solu.findPeakGrid_implementation2(nums);
    cout << '[' << ans[0] << ", " << ans[1] << ']' << endl;
    return 0;
}