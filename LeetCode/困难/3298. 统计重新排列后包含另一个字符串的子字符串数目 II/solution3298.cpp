/*
url: https://leetcode.cn/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/description/
参考: https://www.bilibili.com/video/BV1WRtDejEjD/
相关: LeetCode3297. 统计重新排列后包含另一个字符串的子字符串数目 I, LeetCode76. 最小覆盖子串, LeetCode2516. 每种字符至少取 K 个
标签: LeetCode第416场周赛, 滑动窗口, 滑动窗口例题
*/

// 这次周赛2题，第三题虽然枚举左端点 + 二分的思路不是最佳，但是能过，不过周赛时没调出来

#include <bits/stdc++.h>

using namespace std;

class Solution3298 {
public:
    /* 参考灵茶山艾府题解，
    相比LeetCode3297，主要优化less的比较，less每次都比较26次，多余了，在字母变更时只看变更的字母够不够，即可知道目前不够的字母是否大于0，
    不过试了下不优化1237ms也能过，优化之后205ms。
    */
    long long validSubstringCount(string word1, string word2) {
        int n = word1.size();
        vector<int> diff(26); // 统计字母频率之差
        for (char c : word2) {
            diff[c - 'a']--;
        }

        int count = 0; // word1不够频率的字母个数
        for (int d : diff) {
            count += (d < 0);
        }

        long long ans = 0;

        int left = 0;

        for (int right = 0; right < n; right++) {
            diff[word1[right] - 'a']++;
            if (diff[word1[right] - 'a'] == 0) {
                count--;
            }
            while (count == 0) {
                diff[word1[left] - 'a']--;
                if (diff[word1[left] - 'a'] == -1) {
                    count++;
                }
                left++;
            }
            ans += left;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3298 solu;
    cout << solu.validSubstringCount("bcca", "abc") << endl;
    return 0;
}
