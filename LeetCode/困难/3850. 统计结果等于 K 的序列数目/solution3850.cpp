/*
url: https://leetcode.cn/problems/count-sequences-to-k/
参考: https://leetcode.cn/problems/count-sequences-to-k/solutions/3906202/zhi-yin-zi-fen-jie-ji-yi-hua-sou-suo-pyt-mb7w/
      https://leetcode.cn/problems/count-sequences-to-k/solutions/3906205/mei-ju-dp-by-tsreaper-bhyt/
      https://leetcode.cn/problems/count-sequences-to-k/solutions/3906226/wo-bu-guan-wo-jiu-yao-yong-zu-he-shu-xue-lfy1/
      https://leetcode.cn/problems/count-sequences-to-k/solutions/3906201/zhe-ban-sou-suo-by-mipha-2022-gouk/
      https://oi-wiki.org/search/bidirectional/
标签: LeetCode第490场周赛, Meet in the middle
*/

// 这次周赛三题

#include <bits/stdc++.h>

using namespace std;

class Solution3850 {
public:
    /*
    1 <= nums.length <= 19，1 <= nums[i] <= 6

    周赛时的想法是状压 dp，枚举分子的选择状态 S，然后要在 U \ S 的可选状态下，求出 S / k 的方案数，
    如何表达值 S / k，周赛时想错了，把多个相乘想成了倍数关系（去想了 f[s][i][j] 表示 s 选择下，得到 i 的 j 倍，比如得到 2 的 3 倍的方案），
    但是完全错了，是多个相乘，应该考虑素因子的指数。

    1 <= nums[i] <= 6，因此素因子只会有 2, 3, 5 。对于得到的值只需要用指数记录就行了。n 个数，其中 4 = 2^2 ，其它都是一次方，
    所以涉及到的值的指数不会超过 2n * n * n

    但是以下代码会 tle，(1 << n) * 20 * 20 * 20 太大了
    */
    int countSequences_tle(vector<int>& nums, long long k) {
        int n = nums.size();
        auto check = [&](int x) -> bool { // 是否是 2，3，5 的幂构成的
            int cnt2 = 0, cnt3 = 0, cnt5 = 0;
            while (x % 2 == 0) cnt2++, x /= 2;
            while (x % 3 == 0) cnt3++, x /= 3;
            while (x % 5 == 0) cnt5++, x /= 5;
            return x == 1;
        };
        if (!check(k)) return 0;

        auto resolve = [&](int x) -> tuple<int, int, int> {
            int cnt2 = 0, cnt3 = 0, cnt5 = 0;
            while (x % 2 == 0) cnt2++, x /= 2;
            while (x % 3 == 0) cnt3++, x /= 3;
            while (x % 5 == 0) cnt5++, x /= 5;
            return {cnt2, cnt3, cnt5};
        };
        // nums[i] 都是 [1, 6] ，所以分子分母都是 2, 3, 5 的幂次
        // 枚举分子的选择状态S并计算出质因数分解，然后分母要在 t = ((1 << n) - 1) ^ S 的可选状态下计算得到 k * 分子 的方案数
        // 分母的这个表要 dp 算
        vector<array<array<array<int, 20>, 20>, 40>> f(1 << n);
        // int f[1 << n][20][20][20]; // nums.size() <= 19
        // memset(f, 0, sizeof(f));
        f[0][0][0][0] = 1;
        for (int s = 1; s < (1 << n); s++) {
            for (int i = 0; i < 40; i++) {
                for (int j = 0; j < 20; j++) {
                    for (int k = 0; k < 20; k++) {
                        int p = __builtin_ctz(s);
                        int t = s ^ (1 << p);
                        // 不选 lowbit
                        f[s][i][j][k] += f[t][i][j][k];
                        // 选 lowbit
                        auto [c2, c3, c5] = resolve(nums[p]);
                        if (i - c2 >= 0 && j - c3 >= 0 && k - c5 >= 0) f[s][i][j][k] += f[t][i - c2][j - c3][k - c5];
                    }
                }
            }
        }

        int ans = 0;
        for (int s = 0; s < (1 << n); s++) { // 枚举分子的选择
            int a[3]{};
            for (int i = 0; i < n; i++) {
                if ((s >> i) & 1) {
                    auto [c2, c3, c5] = resolve(nums[i]);
                    a[0] += c2, a[1] += c3, a[2] += c5;
                }
            }
            int t = ((1 << n) - 1) ^ s;
            auto [c2, c3, c5] = resolve(k);
            if (a[0] - c2 >= 0 && a[1] - c3 >= 0 && a[2] - c5 >= 0) ans += f[t][a[0] - c2][a[1] - c3][a[2] - c5];
        }
        return ans;
    }

    /*
    参考灵茶题解，
    回过头来看，如果是暴力的方式，每个 nums[i] 乘 / 除 / 不选，暴力递归会有 3^n 种情况。

    由于 nums[i] 值域很小只有 [1, 6]，所以大量递归实例乘出来的值是重复的，要计算的是 f[i][k中2的幂次][k中3的幂次][k中5的幂次]，
    于是可以用 f[i][c2][c3][c5] 来记忆化搜索，时间复杂度 O(n^4) ，可以过这个题

    有点神奇的技巧，本来是要搜索 3^n 种情况，但是多加几个参数变成 n^4 了，原因应该是，搜索 3^n 时，实际关心了每一步的值，但是实际由于
    质因数只有 2, 3, 5 ，n 也小，所以 2, 3, 5 的指数的范围很小
    */
    int countSequences(vector<int>& nums, long long k) {
        int n = nums.size();
        auto check = [&](long long x) -> bool { // 是否是 2，3，5 的幂构成的
            int cnt2 = 0, cnt3 = 0, cnt5 = 0;
            while (x % 2 == 0) cnt2++, x /= 2;
            while (x % 3 == 0) cnt3++, x /= 3;
            while (x % 5 == 0) cnt5++, x /= 5;
            return x == 1;
        };
        if (!check(k)) return 0;

        auto resolve = [&](long long x) -> tuple<int, int, int> {
            int cnt2 = 0, cnt3 = 0, cnt5 = 0;
            while (x % 2 == 0) cnt2++, x /= 2;
            while (x % 3 == 0) cnt3++, x /= 3;
            while (x % 5 == 0) cnt5++, x /= 5;
            return {cnt2, cnt3, cnt5};
        };

        unordered_map<int, int> memo;

        auto hash = [&](int i, int e2, int e3, int e5) {
            // 拼成一个 int，每块 6 位就够
            return i << 18 | (e2 + 2 * n) << 12 | (e3 + n) << 6 | (e5 + n); // e2 最多 2n 个，nums 全是 4
        };
        auto dfs = [&](auto& dfs, int i, int e2, int e3, int e5) -> int {
            if (i < 0) return e2 == 0 && e3 == 0 && e5 == 0;
            int key = hash(i, e2, e3, e5);
            auto it = memo.find(key);
            if (it != memo.end()) return it->second;
            auto [c2, c3, c5] = resolve(nums[i]);
            int res = 0;
            // 乘 nums[i]
            res += dfs(dfs, i - 1, e2 - c2, e3 - c3, e5 - c5);
            // 不选
            res += dfs(dfs, i - 1, e2, e3, e5);
            // 除 nums[i]
            res += dfs(dfs, i - 1, e2 + c2, e3 + c3, e5 + c5);

            memo[key] = res;
            return res;
        };

        auto [c2, c3, c5] = resolve(k);
        return dfs(dfs, n - 1, c2, c3, c5);
    }

    /*
    暴力 + Meet in the middle 优化的解法，
    暴力搜索的时间复杂度为 O(3^n)，这题 n <= 19，3^19 大约 1e9，用 Meet in the middle，先暴力算左边能出现的分数并记录在 map 中，
    然后暴力算右边能出现的分数 x 并检查左边形成 k / x 的方案数(有点类似LeetCode1. 两数之和) 

    这样花的时间会是 O(2 * 3^{n / 2}) ，能过这题，甚至用时还算短。

    这个方法不怎么优雅，但是当算法时间复杂度是指数级时，能将 O(a^b) 优化到 O(a^{b/2}) ，确实会带来质的提升，所以也写下
    */
    int countSequences_impl2(vector<int>& nums, long long k) {
        int n = nums.size();
        using i128 = __int128_t;
        map<pair<i128, i128>, int> mp;
        i128 ans = 0;

        auto dfs = [&](auto& dfs, vector<int>& arr, int i, i128 a, i128 b, bool is_left) -> void {
            if (i == arr.size()) {
                if (is_left) mp[{a, b}]++;
                else {
                    auto it = mp.find({b, a});
                    if (it != mp.end()) ans += it->second;
                }
                return;
            }
            // 不选 arr[i]
            dfs(dfs, arr, i + 1, a, b, is_left);

            // 乘 arr[i]
            {
                i128 x = arr[i];
                i128 g = __gcd(a * x, b);
                dfs(dfs, arr, i + 1, a * x / g, b / g, is_left);
            }

            // 除 arr[i]
            {
                i128 x = arr[i];
                i128 g = __gcd(a, b * x);
                dfs(dfs, arr, i + 1, a / g, b * x / g, is_left);
            }
        };

        int m = n / 2;
        vector<int> left(nums.begin(), nums.begin() + m);
        vector<int> right(nums.begin() + m, nums.end());
        dfs(dfs, left, 0, 1, 1, true);
        dfs(dfs, right, 0, k, 1, false); // 注意这里分子是 k

        return ans;
    }

    /*
    但是有更优的解法，参考 TsReaper 题解，nums[i] 在 [1, 6]，要得到 k ，要选出合适个数的 2, 3, 5，但是对于 4 和 6，一个会贡献
    2 个 2，一个会贡献 1 个 2，1 个 3。这两在素因数分解中不是基，所以需要枚举选这 2 者的个数(O(n^2))，然后，问题变成剩下的
    2^{e1} * 3^{e2} * 5^{e3}，要怎么选 nums 中剩下的 2, 3, 5 使得得到 e 次？
    由于可以 乘 / 不选 / 除，所以要递推算一下方案数，f(i, j) = f(i - 1, j - 1) + f(i - 1, j + 1) + f(i - 1, j)

    时间复杂度 O(n^2)
    */
    int countSequences_impl3(vector<int>& nums, long long k) {
        int n = nums.size();
        // f[i][j] 表示对于 i 个 2 / 3 / 5，可以 乘 / 不选 / 除 ，凑出 j 次的方案数
        // 指数范围为 [-n, n] ，向右偏移 n 以避免负下标
        vector<vector<int>> f(n + 1, vector<int>(2 * n + 1));
        f[0][0 + n] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = -n; j <= n; j++) {
                // 考虑最后那个 x 乘 / 不选 / 除
                if (j - 1 + n >= 0) f[i][j + n] += f[i - 1][j - 1 + n];
                f[i][j + n] += f[i - 1][j + n];
                if (j + 1 + n < 2 * n + 1) f[i][j + n] += f[i - 1][j + 1 + n];
            }
        }

        // 对 k 进行质因数分解，只考虑 2, 3, 5
        int need[7]{};
        for (int i = 2; i <= 5; i++) while (k % i == 0) need[i]++, k /= i;
        if (k != 1) return 0;

        auto legal = [&](int i) { // 下标是否合法
            return 0 <= i && i < 2 * n + 1;
        };

        // 统计每种数字的出现次数
        int has[7]{};
        for (int x : nums) has[x]++;

        int ans = 0;

        // 枚举 4 和 6 的选择次数
        for (int i = -has[4]; i <= has[4]; i++) {
            for (int j = -has[6]; j <= has[6]; j++) {
                int c2 = 2 * i + j, c3 = j;
                need[2] -= c2; need[3] -= c3;
                // 乘法原理
                long long t = f[has[4]][i + n] * f[has[6]][j + n];
                if (legal(need[2] + n) && legal(need[3] + n) && legal(need[5] + n)) {
                    t *= f[has[2]][need[2] + n] * f[has[3]][need[3] + n] * f[has[5]][need[5] + n];
                    ans += t;
                }
                need[2] += c2; need[3] += c3; // 恢复
            }
        }
        // 对于还有的 1 ，可以 乘 / 不选 / 除
        for (int _ = 0; _ < has[1]; _++) ans *= 3;
        return ans;
    }

    // [TODO] 有个组合数学 + FFT 的解法，时间复杂度 O(nlogn) ，后面看
};

int main(int argc, char const *argv[]) {
    Solution3850 solu;
    cout << solu.countSequences_impl3(*new vector<int>{2, 3, 2}, 6) << endl;
    return 0;
}