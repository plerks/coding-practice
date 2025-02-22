/*
描述: 使用kmp，找出s中所有的p出现位置并返回。
参考: https://leetcode.cn/problems/shortest-matching-substring/solutions/3076453/xian-xing-zuo-fa-kmpmei-ju-zhong-jian-sa-5qow/
      https://oi-wiki.org/string/kmp/
相关: LeetCode3455. 最短匹配子字符串
时间复杂度: O(n)
*/
#include <bits/stdc++.h>

using namespace std;

// 用《数据结构(C++语言版)》-ISBN9787302330646 中的kmp讲法来写
struct KmpAllMatches1 {
    vector<int> buildOptimizedNext(string& p) {
        int n = p.size();
        vector<int> next(n + 1);
        next[0] = -1;
        int j = 0, t = -1;
        while (j < n) { // 要寻找所有匹配位置，这里j范围要大1，把next[n]也算出来
            // 现在t为非改进next[j]，目标：求出非改进next[j + 1]，再求出改进next[j + 1]
            while (t != -1 && p[j] != p[t]) t = next[t];
            next[j + 1] = (p[j + 1] != p[t + 1]) ? t + 1 : next[t + 1];
            j++;
            t++;
        }
        return next;
    }

    // 在s中找出p的所有出现位置
    vector<int> kmp_all_matches(string& s, string& p) {
        if (p.size() == 0) {
            vector<int> matches(s.size() + 1);
            iota(matches.begin(), matches.end(), 0);
            return matches;
        }
        vector<int> next = buildOptimizedNext(p);
        vector<int> matches;
        int i = 0, j = 0;
        int m = s.size();
        int n = p.size();
        while (i < m) {
            while (j != -1 && s[i] != p[j]) j = next[j];
            i++;
            j++;
            if (j == n) {
                matches.push_back(i - j);
                j = next[j]; // p[n]没有字符，相当于在n处失配，j变为next[n]
            }
        }
        return matches;
    }
};

// 灵茶山艾府`LeetCode3455. 最短匹配子字符串`题解中的写法，和oi wiki的风格类似
struct KmpAllMatches2 {
    // 计算p的pi数组，pi[i]的定义为p[0, i]的最长真前后缀匹配长度
    /* 时间复杂度为什么是线性的？
       内层的while循环虽然循环多次，但是match减小受match > 0限制，而每次match增加只会+1，而match最多增加n-1次，所以while的总开销不过O(n)
    */
    vector<int> calcPi(string& p) {
        vector<int> pi(p.size());
        int match = 0; // 匹配长度
        // 这个写法没有next[0] = -1的定义，直接从pi[0] = 0开始
        for (int i = 1; i < p.size(); i++) {
            char c = p[i];
            while (match > 0 && p[match] != c) {
                match = pi[match - 1];
            }
            if (p[match] == c) match++;
            pi[i] = match;
        }
        return pi;
    }

    // 在s中找出p的所有出现位置
    // 两层循环的时间复杂度是线性的，分析类似calcPi()，match最多增大n次，所以while执行也最多n次
    // 这个写法没用改进next表的策略(不把失配的相同字符移过来比对)，不过不影响时间复杂度
    vector<int> kmp_all_matches(string& s, string& p) {
        if (p.size() == 0) {
            vector<int> matches(s.size() + 1);
            iota(matches.begin(), matches.end(), 0);
            return matches;
        }
        vector<int> pi = calcPi(p);
        vector<int> matches;
        int match = 0; // 匹配长度
        // 这里的写法是顺序枚举s[i]，求i作为右端点的最长匹配长度
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            while (match > 0 && p[match] != c) {
                match = pi[match - 1];
            }
            if (p[match] == c) match++;
            if (match == p.size()) {
                matches.push_back(i - p.size() + 1);
                match = pi[match - 1]; // s[i-p.size()+1, i]完全匹配p，则i+1位置第一步能知道的最长真前后缀匹配长度就为pi[p.size()-1]
            }
        }
        return matches;
    }
};

int main(int argc, char const *argv[]) {
    KmpAllMatches1 kam1;
    auto a1 = kam1.kmp_all_matches(*new string("abaacbaecebba"), *new string("ba"));
    auto a2 = kam1.kmp_all_matches(*new string("aaaaaa"), *new string("aa"));
    auto a3 = kam1.kmp_all_matches(*new string("aaaaaa"), *new string(""));

    KmpAllMatches2 kam2;
    auto b1 = kam2.kmp_all_matches(*new string("abaacbaecebba"), *new string("ba"));
    auto b2 = kam2.kmp_all_matches(*new string("aaaaaa"), *new string("aa"));
    auto b3 = kam2.kmp_all_matches(*new string("aaaaaa"), *new string(""));
    return 0;
}