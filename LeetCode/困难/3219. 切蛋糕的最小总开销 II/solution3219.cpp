/*
url: https://leetcode.cn/problems/minimum-cost-for-cutting-cake-ii/description/
参考: https://leetcode.cn/problems/minimum-cost-for-cutting-cake-ii/solutions/3024578/qie-dan-gao-de-zui-xiao-zong-kai-xiao-ii-oisi/
      https://leetcode.cn/problems/minimum-cost-for-cutting-cake-ii/solutions/2843063/tan-xin-ji-qi-zheng-ming-jiao-huan-lun-z-ivtn/
相关: LeetCode3218. 切蛋糕的最小总开销 I
标签: 贪心
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3219 {
public:
    /* 参考官方题解，
    算法: 将horizontalCut和verticalCut从大到小排序，每次选大的刀来切，
    这样导出的切割方式，不会有调整得到更优的余地:
    如果相邻两刀都是水平或竖直，交换没有影响，无需考虑
    若相邻两刀为一刀水平，一刀竖直，假设已经横切了p刀，竖向切了q刀，
    则先水平后竖直的开销为 (q + 1) * horizontalCut[i] + (p + 2) * verticalCut[j]
    先竖直后水平的开销为 (p + 1) * verticalCut[j] + (q + 2) * horizontalCut[i]
    二者之差为 verticalCut[j] - horizontalCut[i]，于是当 horizontalCut[i] > verticalCut[j]时先水平切，即
    谁大谁先。
    交换任意两刀可由交换相邻刀实现，上面已经证明了这种策略下交换相邻刀不会造成更优，于是交换任意两刀也不会产生更优，算法得到的是最优解。

    我倒是想到了可能有个贪心策略选择切割方式的问题，但是不知道怎么考虑目前已经得到的块数。
    */
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        sort(horizontalCut.begin(), horizontalCut.end());
        sort(verticalCut.begin(), verticalCut.end());
        int p = 0, q = 0;
        long long ans = 0;
        while (!horizontalCut.empty() || !verticalCut.empty()) {
            if (!horizontalCut.empty() && (verticalCut.empty() || horizontalCut.back() >= verticalCut.back())) {
                ans += horizontalCut.back() * (q + 1);
                horizontalCut.pop_back();
                p++;
            }
            else {
                ans += verticalCut.back() * (p + 1);
                verticalCut.pop_back();
                q++;
            }
        }
        return ans;
    }

    /* 灵茶山艾府题解解法，
    逆向来看，相当于求这个图的最小生成树，用类似Kruskal算法的过程。选最小的边，相当于把块粘起来。
    */
    long long minimumCost_implementation2(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        sort(horizontalCut.begin(), horizontalCut.end());
        sort(verticalCut.begin(), verticalCut.end());
        int i = 0, j = 0; // i, j表示横纵向的粘连次数，例如横向粘连一次，则横向的行数从 m 变到 m - 1
        long long ans = 0;
        while (i < m - 1 || j < n - 1) {
            if (j == n - 1 || i < m - 1 && horizontalCut[i] <= verticalCut[j]) {
                ans += horizontalCut[i] * (n - j);
                i++;
            }
            else {
                ans += verticalCut[j] * (m - i);
                j++;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3219 solu;
    vector<int> horizontalCut = {1, 3};
    vector<int> verticalCut = {5};
    cout << solu.minimumCost(3, 2, horizontalCut, verticalCut) << endl;

    vector<int> horizontalCut2 = {1, 3};
    vector<int> verticalCut2 = {5};
    cout << solu.minimumCost(3, 2, horizontalCut2, verticalCut2) << endl;
    return 0;
}
