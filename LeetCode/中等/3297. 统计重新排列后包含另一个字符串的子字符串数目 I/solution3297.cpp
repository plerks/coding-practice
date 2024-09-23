/*
url: https://leetcode.cn/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-i/description/
参考: https://www.bilibili.com/video/BV1WRtDejEjD/
相关: LeetCode3298. 统计重新排列后包含另一个字符串的子字符串数目 II, LeetCode76. 最小覆盖子串
标签: LeetCode第416场周赛, 滑动窗口, 滑动窗口例题, 二分
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3297 {
public:
    /* 周赛时的解法，O(nlogn)复杂度，比不上滑动窗口O(n)但是能过。对每个左端点在i位置，用前缀出现次数二分搜索右端点最小需要到达的位置j，
    然后[i, j]右边还有n - 1 - j个字符，共n - j种情况。周赛时候没调出来，因为最后写成了ans += (i + 1) * (long long)(n - mx)，
    这样写是[i, j]左右都能扩展，这样就重复算了，[i, j]和[i + 1, j]可能扩展出同一串，要固定左边界看才是不重不漏的。
    */
    long long validSubstringCount(string word1, string word2) {
        int n = word1.size();
        vector<vector<int>> pre(26, vector<int>(n)); // pre[c][j]表示i字母在word1[0 ... j]的出现次数

        for (int i = 0; i < 26; i++) {
            pre[i][0] = (word1[0] - 'a') == i ? 1 : 0;
            for (int j = 1; j < n; j++) {
                if (word1[j] - 'a' == i) {
                    pre[i][j] = pre[i][j - 1] + 1;
                }
                else pre[i][j] = pre[i][j - 1];
            }
        }

        vector<int> fre(26);
        for (char c : word2) {
            fre[c - 'a']++;
        }

        long long ans = 0;

        for (int i = 0; i < n; i++) {
            // 对每个字母，搜索第一个右侧位置，使得pre[c][j] - pre[c][i] + (1 : 0) >= fre[c]，取最大
            int mx = 0;
            for (int c = 0; c < 26; c++) {
                int left = i;
                int right = n - 1;
                while (left <= right) {
                    int j = (left + right) / 2;
                    int d = (word1[i] - 'a') == c ? 1 : 0;
                    if (pre[c][j] - pre[c][i] + d < fre[c]) {
                        left = j + 1;
                    }
                    else right = j - 1;
                }
                mx = max(mx, left);
            }
            ans += (long long)(n - mx);
        }

        return ans;
    }

    // 参考灵茶山艾府题解，双指针都是从左往右，先枚举左端点
    long long validSubstringCount_implementation2(string word1, string word2) {
        /* 考虑左端点固定在i位置，右端点最小要在j位置，当外层循环的i右移到达i + 1后，
        j不变或者往右，具有单调性，于是j设为全局的变量，从而滑动窗口把O(n^2)变成了O(n)
        */
        // 也可以外层循环从左到右枚举右边界，然后左边界也是从左往右，这里窗口有最小要求，所以两个指针是同向的
        int n = word1.size();
        vector<int> map1(26);
        vector<int> map2(26);
        for (char c : word2) {
            map2[c - 'a']++;
        }

        function<bool()> less = [&]() {
            for (int i = 0; i < 26; i++) {
                if (map1[i] < map2[i]) return true;
            }
            return false;
        };

        long long ans = 0;

        int right = 0;
        // 最开始是[0, 0)
        for (int left = 0; left < n; left++) {
            // 减去被移出的上一个位置
            if (left - 1 >= 0) {
                map1[word1[left - 1] - 'a']--;
            }
            while (right <= n - 1 && less()) {
                map1[word1[right] - 'a']++;
                right++;
            }
            // 右边可选的部分是[right, n - 1]，长度为n - right, 有n - right + 1种情况
            /* right移到了n位置，有两种情况，[left, right)是满足要求的，ans可以加上n - right + 1。
            还有一种情况是right移到了n位置都不够涵盖word2的成分，所以这里要判断一下才能加
            */
            if (!less()) ans += n - right + 1;
        }
        return ans;
    }

    // 优化validSubstringCount_implementation2()
    long long validSubstringCount_implementation3(string word1, string word2) {
        int n = word1.size();
        vector<int> map1(26);
        vector<int> map2(26);
        for (char c : word2) {
            map2[c - 'a']++;
        }

        function<bool()> less = [&]() {
            for (int i = 0; i < 26; i++) {
                if (map1[i] < map2[i]) return true;
            }
            return false;
        };

        long long ans = 0;

        int right = 0;
        for (int left = 0; left < n; left++) {
            if (left - 1 >= 0) {
                map1[word1[left - 1] - 'a']--;
            }
            // 在word1[n]位置假想有个无穷字符，这样right = n代表够，right = n + 1代表不够，可以避免ans加之前再用less()判断
            while (right <= n && less()) {
                if (right == n) {
                    right++;
                    break;
                }
                map1[word1[right] - 'a']++;
                right++;
            }
            if (right != n + 1) ans += n - right + 1;
        }
        return ans;
    }

    // 灵茶山艾府题解写法
    /* 这样考虑这个问题，这里双指针是同向的，以都是从左到右为例(这个问题双指针都从左到右和都从右到左是等价的)，那么外层循环枚举左指针还是右指针好呢？
       应该是外层枚举右指针好一些，外层枚举右，由于左指针不会超过右指针，所以左指针也不会有越界的问题。
       反之则不然，外层枚举左，则右指针可能因为不够word2成分一直往右从而越界。
    */
    long long validSubstringCount_implementation4(string word1, string word2) {
        int n = word1.size();
        vector<int> map1(26);
        vector<int> map2(26);
        for (char c : word2) {
            map2[c - 'a']++;
        }

        function<bool()> less = [&]() {
            for (int i = 0; i < 26; i++) {
                if (map1[i] < map2[i]) return true;
            }
            return false;
        };

        long long ans = 0;

        int left = 0;

        for (int right = 0; right < n; right++) {
            // 加上当前位置的字符
            map1[word1[right] - 'a']++;
            while (!less()) {
                map1[word1[left] - 'a']--;
                left++;
            }
            // left - 1才是最后一个使得成分包含word2的左端点
            // 这里本来还要判断下[left - 1, right]够不够，若够，则加left，若不够，则加0，但关键是若不够left一定会是0，刚好统一为加left
            // 还有一种写法是先将right移到第一次够的位置，这样后面区间始终是够的，见validSubstringCount_implementation5()
            ans += left;
        }
        return ans;
    }

    // 修改validSubstringCount_implementation4()，先将right移到够的位置
    long long validSubstringCount_implementation5(string word1, string word2) {
        int n = word1.size();
        vector<int> map1(26);
        vector<int> map2(26);
        for (char c : word2) {
            map2[c - 'a']++;
        }

        function<bool()> less = [&]() {
            for (int i = 0; i < 26; i++) {
                if (map1[i] < map2[i]) return true;
            }
            return false;
        };

        long long ans = 0;

        int left = 0;
        int right = 0;
        while (right <= n - 1 && less()) {
            map1[word1[right] - 'a']++;
            right++;
        }
        if (less()) return 0; // 字符用完都不够
        // right - 1是第一次够的位置，但是例如["aaab","ab"]这个用例，第一次够也有多个子串满足，下面的循环从right - 1开始尝试
        map1[word1[right - 1] - 'a']--;

        // right是下一个要尝试的位置
        for (int j = right - 1; j < n; j++) {
            // 加上当前位置的字符
            map1[word1[j] - 'a']++;
            while (!less()) {
                map1[word1[left] - 'a']--;
                left++;
            }
            // 首先将right移到了第一次够的位置，这样后面区间始终是够的，算种数就行
            ans += left;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3297 solu;
    cout << solu.validSubstringCount("bcabca", "abc") << endl;
    cout << solu.validSubstringCount_implementation2("bcabca", "abc") << endl;
    cout << solu.validSubstringCount_implementation3("bcabca", "abc") << endl;
    cout << solu.validSubstringCount_implementation4("bcabca", "abc") << endl;
    cout << solu.validSubstringCount_implementation5("bcabca", "abc") << endl;
    return 0;
}
