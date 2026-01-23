/*
url: https://leetcode.cn/problems/race-car/
参考: https://leetcode.cn/problems/race-car/solutions/38854/sai-che-by-leetcode/
      https://leetcode.com/problems/race-car/solutions/124326/summary-of-the-bfs-and-dp-solutions-with-frqz/
      https://leetcode.cn/problems/race-car/solutions/2016059/yue-guo-zhong-dian-yi-ding-li-ke-hui-tou-a22h/
标签: 【题单】图论算法, [mark]
*/
#include <bits/stdc++.h>

using namespace std;

class Solution818 {
public:
    // 暴力bfs搜索，但是speed很快会超int，但是题解里有分析，最优路径可以调整成"向右，向左"一轮之后整体往右走了，
    // 速度超过 2 * target 后，上一轮的向右最后一步走了 target 距离，位置一定 >= target，越过了 target 之后一定调头，
    // 这个 > 2 * target 的速度一定不会再用来走。所以把 > 2 * target 的速度全丢掉就能过了。
    // 时间复杂度 O(taget * log(target)) ，每个状态可以加速 log(target) 次
    // 运行用时 753ms，比用Dijkstra的慢很多，可能是因为vis这个set比dis这个数组慢很多
    int racecar(int target) {
        queue<pair<int, int>> q; // (pos, speed)
        unordered_set<long long> vis;
        auto hash = [&](int pos, int speed) -> long long {
            return ((long long)pos << 32) | (unsigned)speed;
        };
        q.push({0, 1});
        vis.insert(0);
        int level = 0;
        while (!q.empty()) {
            int sz = q.size();
            for (int _ = 0; _ < sz; _++) {
                auto [pos, speed] = q.front(); q.pop();
                if (pos == target) return level;
                int pos1, pos2;
                int speed1, speed2;
                pos1 = pos2 = pos;
                speed1 = speed2 = speed;
                // A
                pos1 += speed1;
                speed1 <<= 1;
                if (!vis.count(hash(pos1, speed1)) && abs(speed1) <= 2 * target) {
                    q.push({pos1, speed1});
                    vis.insert(hash(pos1, speed1));
                }
                // R
                speed2 = speed > 0 ? -1 : 1;
                if (!vis.count(hash(pos2, speed2))) {
                    q.push({pos2, speed2});
                    vis.insert(hash(pos2, speed2));
                }
            }
            level++;
        }
        return -1;
    }

    /* 官方题解解法一，假设最优路径是 A..ARA...A... 的形式，将连续的 A 合并写成，A^{k1} R A^{k2} R A^{k3}... 的形式，
    每次 R 之后速度大小变为1 ，A^{k} 的位移为 +/- (2^k - 1) ，因此路径可以写成多个 A^{k}R 的形式，但是最优路径末尾一定没有 R，
    开头也可以调整成不以 R 开头。例如 RARAARA 可以调整成 AARARRA 。
    此外，可以调整奇偶子列内部的顺序，使得最开始向右走的过程中，每经过两段后的当前位置单增。
    当正的部分第一次 >= target 后，一定不会再继续前进，而是开始后退，因为如果再前进一段，只会徒增一段后退的
    来抵消。

    于是可以算 2^k - 1 >= target 的最小 K，最多走到 2^K - 1 的位置，每段的步数也不会超过 K。相当于每个点有 K 个邻居，用
    Dijkstra算最短路。
    相当于把搜索下一步是 A 还是 R 变成了搜索下一段有几个 A ，且 A 的个数一定不会太大，以上都是为了得到这个最关键的结论：
        车的活动范围不会太大，这样暴力搜索就有个上界了。

    在 Dijkstra 搜索过程中，不记录当前位置，而是记录与 target - 当前位置 这个位移 displacement ，> 0 表示在 target 左边，< 0 表示在 target 右边。
    下一段一定是对着 target 方向走的，所以，假设走的距离是 walk，当前位移为 d，则当前位置为 target - d，不妨想成当前位置在 target 左边，
    则新位置为 walk + target - d，新位移为 target - (walk + target - d) = d - walk。

    由于行动是 向右段 向左段 ... 这样交替的，所以我们还需要记录速度方向，但是官方题解这里用了个技巧去省略了记录速度方向（但是题解居然没解释这一点）。

    每走一段，我们把位移翻转，这样就可以一直认为在往右走。假设 target = 2，最开始在 0 位置，位移为 +2， 枚举向右走的步数，
    假设向右A的步数是 0 ，则这时候会从 0 开始往左走，也就是开始远离 target 。这时候是应该记录速度方向的，但是可以不这么做，
    把当前位置翻转一下，认为当前在 +4 位置，位移为 -2，然后仍然认为现在是向右走的，这样接下来也是远离target。
    这样不翻转速度而是翻转位移，对于"到达target的行动"是同样的效果。

    这样记录下，dis[i]（i 为位移）的含义是:
        若 i > 0，表示与 target 的距离是 |i|，且当前前进方向为远离 target 方向，
        若 i < 0，表示与 target 的距离是 |i|，且当前前进方向为靠近 target 方向。
    */
    // 运行用时 35ms，时间复杂度应该是 O(target * log^2{target})，相当于 target 个节点，每个点 log{target} 条边，总边数 e = tlogt，时间复杂度 eloge = tlog^2{t}
    int racecar_implementation2(int target) {
        // 找 2^K >= target + 1 的第一个 K，即 2^K > target 的第一个 K
        // 找 >= x 的2的次幂不能用 __lg，因为最高的2的幂不一定 >=，但是找 > x 就行了，一定是 __lg(x) + 1
        int K = __lg(target) + 1;
        int barrier = 1 << K;
        vector<int> dis(2 * barrier + 1, INT_MAX); // 位移的范围为 [-barrier, barrier]，向右偏移把下标范围变成 [0, 2 * barrier]，但是题解用的是取模的方式，也可以
        const int MOD = 2 * barrier + 1;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // (步数，target 到 cur_pos 的位移，以-x方向为正方向)
        pq.push({0, target});
        dis[target] = 0;
        while (!pq.empty()) {
            auto [step, d] = pq.top(); pq.pop();
            if (step > dis[(d + MOD) % MOD]) continue;
            for (int k = 0; k <= K; k++) { // 枚举下一段连续走的步数
                int walk = (1 << k) - 1; // 认为速度一直向右
                int new_d = -(d - walk); // 翻转位移
                int new_step = step + k + (new_d != 0); // 如果新位置不在target位置，则末尾还要有个R，否则不用R了。
                if (-barrier <= new_d && new_d <= barrier && new_step < dis[(new_d + MOD) % MOD]) {
                    dis[(new_d + MOD) % MOD] = new_step;
                    pq.push({new_step, new_d});
                }
            }
        }
        return dis[0];
    }

    // dp的解法，看英文区的那篇题解，把思路解释得很清楚，官方题解说得很不清楚
    /* 设 f[i] 为从位置 0 走到 i，初速度为 1，且指向 i 方向的最小步数，如何找递归关系？
    第一段一定朝着 i 走，考虑枚举第一段最后走到的位置 j:

    1. 若 j < i，则说明第一段还没走到 i 就反向了，但是我们不知道反向走了多少步，但是由官方题解中的分析，反向走不会走到 <= 0 的位置，
    于是我们可以枚举这个步数。然后走完这个反向段，再 R 一次之后，问题变成从 x 走到 i，且初速度为 1，从 x 指向 i，变成子问题 T(i - x)

    2. j == i，也就是说 i 是 2^k - 1 的形式，直接就能走到 i

    3. j > i，走过 i 了，然后再经过一次 R 之后，问题变成 T(j - i)
        j 不会无限大，只需考虑第一次 j 越过 i，然后一定会开始往回走。
        j - i 也一定比 i 小，能变成子问题。设 2^{k} - 1 < i < 2^{k + 1} - 1，
        j 对应的步数为 p，则 j = 2^p - 1，j > i => p 为 k + 1，则 j = 2^{k + 1} - 1，则 2 * i >= 2^{k + 1}，于是 j - i < i
    */
    // 这个 dp 的解法很有意思，虽然会走到 i 右边的位置，但是不会变成父问题，仍然是子问题
    // 时间复杂度应该是 O(target * log^2{target})
    int racecar_implementation3(int target) {
        vector<int> f(target + 1, INT_MAX);
        f[0] = 0;
        for (int i = 1; i <= target; i++) {
            int p;
            for (p = 1; (1 << p) - 1 < i; p++) { // 枚举第一段的步数，A^{p}，p 从 1 开始，因为一开始一定朝着 i 走至少一步
                int j = (1 << p) - 1; // 现在所在的位置
                for (int q = 0; (1 << q) - 1 < j; q++) { // 现在R，并枚举回退的步数A^{q}
                    int x = j - ((1 << q) - 1);
                    f[i] = min(f[i], p + 1 + q + 1 + f[i - x]);
                }
            }
            int j = (1 << p) - 1; // 现在 j 是第一个 >= i 的 2^k - 1 形式的位置，判断是 j = i 还是 j > i
            f[i] = min(f[i], (j == i) ? p : (p + 1 + f[j - i]));
        }
        return f[target];
    }

    // 关于越过终点一定回头的严格证明，见<https://leetcode.cn/problems/race-car/solutions/2016059/yue-guo-zhong-dian-yi-ding-li-ke-hui-tou-a22h/>
};

int main(int argc, char const *argv[]) {
    Solution818 solu;
    // cout << solu.racecar(5617) << endl;
    cout << solu.racecar_implementation2(2) << endl;
    cout << solu.racecar_implementation3(3) << endl;
    return 0;
}