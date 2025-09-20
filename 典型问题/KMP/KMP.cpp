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

    template <typename T>
    void print(const std::vector<T>& vec, const std::string& separator = ", ") {
        std::cout << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            print(vec[i]);
            if (i + 1 != vec.size()) std::cout << separator;
        }
        std::cout << "]";
    }

    template <typename T>
    void println(const std::vector<T>& vec, const std::string& separator = ", ") {
        print(vec, separator);
        std::cout << '\n';
    }
}
using namespace io;

struct KMP {
    vector<int> build_next(string p) {
        int m = p.size();
        vector<int> next(m, 0);
        next[0] = -1;
        int t = -1; // t 为 非改进next[j - 1]
        for (int i = 1; i < m; i++) {
            while (t != -1 && p[t] != p[i - 1]) t = next[t];
            ++t;
            next[i] = t;
        }
        return next;
    }

    vector<int> build_optimized_next(string p) {
        int m = p.size();
        vector<int> next(m, 0);
        next[0] = -1;
        int t = -1; // t 为 非改进next[j - 1]
        for (int i = 1; i < m; i++) {
            while (t != -1 && p[t] != p[i - 1]) t = next[t];
            ++t;
            next[i] = (p[t] != p[i]) ? t : next[t];
        }
        return next;
    }

    int match(string s, string p) {
        int n = s.size(), m = p.size();
        vector<int> next = build_next(p);
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (j == -1 || s[i] == p[j]) {
                i++;
                j++;
            }
            else j = next[j];
        }
        return (j == m) ? i - j : -1;
    }

    int optimized_match(string s, string p) {
        int n = s.size(), m = p.size();
        vector<int> next = build_optimized_next(p);
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (j == -1 || s[i] == p[j]) {
                i++;
                j++;
            }
            else j = next[j];
        }
        return (j == m) ? i - j : -1;
    }
};

int main(int argc, char const *argv[]) {
    KMP kmp;
    println(kmp.build_next("CINCINNATI"));
    println(kmp.match("data structures and algorithms", "ta"));
    println(kmp.build_optimized_next("CINCINNATI"));
    println(kmp.optimized_match("data structures and algorithms", "ta"));
    return 0;
}