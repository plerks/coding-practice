/*
描述: 字符串哈希的模板，来自[TsReaper的题解](https://leetcode.cn/problems/find-the-occurrence-of-first-almost-equal-substring/solutions/2933927/er-fen-ha-xi-by-tsreaper-5ox7/)
*/

// 可用作提交测试的题目: LeetCode28. 找出字符串中第一个匹配项的下标

#include <bits/stdc++.h>

using namespace std;

// ---------- 字符串哈希模板 - BEGIN ----------

// 全局变量rng，一个random number generator，用当前时间初始化随机数种子，每次调用都会变
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// 辅助函数，用来返回 [x, y] 内的随机整数
int rnd(int x, int y) {
    return uniform_int_distribution<int>(x, y)(rng); // 先生成了个uniform_int_distribution对象，然后调用operator()(Generator& g)
}

// MOD 为模数，BASE 为进制
long long MOD = 1e18 + rnd(0, 1e9), BASE = 233 + rnd(0, 1e3);

// 如果 s 中会出现'\0'，需要改成 BASE + 1 进制，让每位的值在 [1, BASE] 而非 [0, BASE - 1]，
// 否则若仍然采用后者，会无法分辨前导零，会认为 "0ABC" == "ABC"，
// 这里假设 s 中不会出现 '\0'
struct HashString {
    vector<__int128> P, H; // P[i]存储BASE^i % MOD，H[i]存储前缀哈希hash(s[0,i))

    HashString(const string& s) {
        int n = s.size();
        P.resize(n + 1);
        P[0] = 1;
        for (int i = 1; i <= n; i++) P[i] = P[i - 1] * BASE % MOD;
        H.resize(n + 1); // H 向右偏移了一位，hash(s[0]) 在 H[1]
        H[0] = 0;
        for (int i = 1; i <= n; i++) H[i] = (H[i - 1] * BASE + s[i - 1]) % MOD;
    }

    // 查询s[l, r]的指纹
    long long query(int l, int r) {
        if (l > r) return 0;
        // hash(s[l, r]) = (hash(s[0, r]) - hash(s[0, l - 1]) * BASE^{r - l + 1}) % MOD
        // 注意 H 向右偏移了一位，所以 H 使用下标要 +1
        return (H[r + 1] - H[l - 1 + 1] * P[r - l + 1] % MOD + MOD) % MOD;
    }
};

// ---------- 字符串哈希模板 - END ----------


int match(const string& s, const string& p) {
    HashString hs(s);
    HashString hp(p);
    int n = s.size(), m = p.size();
    for (int i = 0; i + m <= n; i++) {
        if (hs.query(i, i + m - 1) == hp.query(0, m - 1)) return i;
    }
    return -1;
}

int main(int argc, char const *argv[]) {
    string s = "data structures and algorithms";
    string p = "ta";
    cout << match(s, p) << endl;
    return 0;
}