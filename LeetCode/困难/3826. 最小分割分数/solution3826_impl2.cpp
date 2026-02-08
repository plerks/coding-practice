/*
url: https://leetcode.cn/problems/minimum-partition-score/
参考: https://www.bilibili.com/video/BV1mA6tBxEVC/
      https://leetcode.cn/problems/minimum-partition-score/solutions/3893573/hua-fen-xing-dp-xie-lu-you-hua-tu-bao-yo-5cb0/
      https://oi-wiki.org/dp/opt/slope/
标签: LeetCode第175场双周赛, 斜率优化, 凸包, 点积
*/

// 这次双周赛三题

#include <bits/stdc++.h>

using namespace std;

struct vec {
    long long x, y;
};

vec sub(vec a, vec b) {
    return {a.x - b.x, a.y - b.y};
}

long long dot(vec a, vec b) {
    return a.x * b.x + a.y * b.y;
}

// 返回平面向量 a, b 叉积后的 z，det 是 determinant 的缩写
// inf = INT64_MAX / 2 会被运算，然后构成到向量里，然后这里 det_z 再相乘会超 long long，得开 int128，
// 不过不用担心 inf 连续乘爆 int128，循环要计算的 f[k][i] 都是有合法方案的，>= inf 的值不会成为那些 f[k][i] 的值，inf 不会连续乘
__int128 det_z(vec a, vec b) {
    return (__int128)a.x * b.y - (__int128)a.y * b.x;
}

class Solution3826 {
public:
    long long minPartitionScore(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> pre(n + 1); // 这题数据范围前缀和不会超long long
        for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + nums[i];
        vector<vector<long long>> f(k + 1, vector<long long>(n + 1, INT64_MAX / 2)); // f[K][j] 表示对 nums[0, j) (从而下标从 1 开始)分 K 段
        f[0][0] = 0;
        // 用够大的数组当deque，内层循环最多加入 n - k + 1 个元素，再加上开头推进去的点，一共 n - k + 2 个
        // 或者说计算 f_{K, i} ，用到的上一行 f_{K - 1, j} ，前面 K - 1 段的末尾从 nums[K - 2] 到 nums[i - 1] ，一共 i - K + 2 个位置，
        // 看循环，i - K 最大为 n - k，也就是说 dq 最多一共 n - k + 2 个元素
        vector<vec> dq(n - k + 2);
        for (int K = 1; K <= k; K++) {
            int head = 0, tail = 0; // [head, tail) 为deque元素范围
            // 对于 f_{K, i}，要把从 nums[K - 2] 到 nums[i - 1] 的部分都加入凸包，也就是以双指针的方式把 j 位置加入凸包
            // 这样写比灵茶题解里 i 增加 1 就拉个新的 j 进来那种一步一步拉的写法，要好理解一点
            int ptr = K - 2 + 1;
            for (int i = K; i <= n - (k - K); i++) { // f[K][i] 要合法，前面要有 K 个元素，后面要有 k - K 个元素，注意这里下标从 1 开始的
                for (; ptr <= i - 1; ptr++) {
                    long long s = pre[ptr];
                    vec t = {s, f[K - 1][ptr] + s * s - s};
                    while (tail - head > 1 && det_z(sub(dq[tail - 1], dq[tail - 2]), sub(t, dq[tail - 1])) <= 0) {
                        tail--;
                    }
                    dq[tail++] = t;
                }
                
                long long s = pre[i];
                vec u = {-2 * s, 1};
                // 丢掉队首f算出来在递减范围的，这些点在后面也不会成为最优
                while (tail - head > 1 && dot(u, dq[head + 1]) < dot(u, dq[head])) {
                    head++;
                }
                // 现在从队首到队尾，点积呈现单增趋势
                f[K][i] = s * s + s + dot(u, dq[head]);
            }
        }
        return f[k][n] / 2;
    }

    // f数组可以原地优化成只用一行，类似LCS问题也可以单行原地算那样，都不用滚动数组，见灵茶题解，不过理解起来很麻烦
};

int main(int argc, char const *argv[]) {
    Solution3826 solu;
    cout << solu.minPartitionScore(*new vector<int>{5,1,2,1}, 2) << endl;
    // cout << solu.minPartitionScore(*new vector<int>{1}, 1) << endl;
    return 0;
}