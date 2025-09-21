/*
描述: 只使用坏字符(bad charactor)策略的Boyer-Moore算法。假设字符集都在[0, 256)。
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

// 只使用坏字符(bad charactor)策略的Boyer-Moore算法。假设字符集都在[0, 256)
struct BoyerMoore {
    int match(const string& s, const string& p) {
        int n = s.size(), m = p.size();
        vector<int> bc = buildBC(p);
        int i, j; // i 为当前放置的 s 左端，j 为当前放置的 p 右端
        for (i = 0; i + m <= n; i += max(1, j - bc[s[i + j]])) { // 如果 j - bc[s[i + j]] <= 0，移动一步
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
};

int main(int argc, char const *argv[]) {
    BoyerMoore bm;
    println(bm.match("a", "a"));
    println(bm.match("data structures and algorithms", "ta"));
    return 0;
}