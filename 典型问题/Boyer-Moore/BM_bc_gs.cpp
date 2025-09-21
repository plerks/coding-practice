/*
描述: 使用坏字符(bad charactor)策略 + 好后缀(good suffix)策略的Boyer-Moore算法。假设字符集都在[0, 256)。
*/

// 可用作提交测试的题目: LeetCode28. 找出字符串中第一个匹配项的下标

#include <bits/stdc++.h>

using namespace std;

// io tool
namespace io {
    template <typename T>
    void print(const T& value) {
        std::cout << value;
    }

    template <typename T>
    void println(const T& value) {
        std::cout << value;
        std::cout << '\n';
    }

    template <template <typename> typename T, typename K>
    void print(const T<K>& container, const std::string& separator = ", ") {
        std::cout << "[";
        for (size_t i = 0; i < container.size(); ++i) {
            print(container[i]);
            if (i + 1 != container.size()) std::cout << separator;
        }
        print(']');
    }

    template <template <typename> typename T, typename K>
    void println(const T<K>& container, const std::string& separator = ", ") {
        print(container, separator);
        print('\n');
    }
}
using namespace io;

// 使用坏字符(bad charactor)策略 + 好后缀(good suffix)策略的Boyer-Moore算法。假设字符集都在[0, 256)
struct BoyerMoore {
    int match(const string& s, const string& p) {
        int n = s.size(), m = p.size();
        vector<int> bc = buildBC(p);
        vector<int> gs = buildGS(p);
        int i, j; // i 为当前放置的 s 左端，j 为当前放置的 p 右端
        for (i = 0; i + m <= n; i += max(j - bc[s[i + j]], gs[j])) {
            for (j = m - 1; j >= 0 && s[i + j] == p[j]; j--); // 一轮从 j = m - 1 开始，从右往左的比对
            if (j < 0) break;
        }
        return j < 0 ? i : -1;
    }

    // 使用一维的 bc 表即可
    vector<int> buildBC(const string& p) {
        vector<int> bc(256, -1); // 字符集范围
        int m = p.size();
        for (int i = 0; i < m; i++) {
            bc[p[i]] = i;
        }
        return bc;
    }

    // 反了个方向，从右往左的Z函数
    vector<int> buildSS(const string& p) {
        int m = p.size();
        vector<int> ss(m);
        ss[m - 1] = m;
        for (int i = m - 2, l = m - 1, r = m - 1; i >= 0; i--) {
            if (i >= l) {
                ss[i] = min(ss[m - 1 - r + i], i - l + 1);
            }
            while (i - ss[i] >= 0 && p[i - ss[i]] == p[m - 1 - ss[i]]) ss[i]++;
            if (i - ss[i] + 1 < l) {
                l = i - ss[i] + 1;
                r = i;
            }
        }
        return ss;
    }

    // gs 表
    vector<int> buildGS(const string& p) {
        vector<int> ss = buildSS(p);
        int m = p.size();
        vector<int> gs(m, m);
        for (int i = 0, j = m - 1; j >= 0; j--) {
            if (ss[j] == j + 1) { // 情况(a)
                while (i < m - j - 1) {
                    gs[i++] = m - j - 1;
                }
            }
        }

        // 虽然 ss[m - 1] 一定不会产生更新，但是要将其排除，不然会出现-1下标
        for (int j = 0; j < m - 1; j++) { // 情况(b)
            gs[m - ss[j] - 1] = m - j - 1;
        }
        return gs;
    }
};

int main(int argc, char const *argv[]) {
    BoyerMoore bm;
    println(bm.match("a", "a"));
    println(bm.match("data structures and algorithms", "ta"));
    println(bm.match("aabaaabaaac", "aabaaac"));

    println(bm.buildGS("AABCDADCAABCAA"));
    return 0;
}