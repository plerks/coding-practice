/*
url: https://leetcode.cn/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/description/
参考: https://www.bilibili.com/video/BV1TqxCeZEmb/
      https://leetcode.cn/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/solutions/2934309/liang-ci-hua-chuang-pythonjavacgo-by-end-2lpz/
相关: LeetCode3297. 统计重新排列后包含另一个字符串的子字符串数目 I
标签: LeetCode第417场周赛, 滑动窗口, 滑动窗口例题
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3306 {
public:
    // 周赛时的写法，通过，但是刚好12:00才调出来交上去，周赛刚好结束
    // 思路为：这里先检查能否缩小区间再移动，检查left位置是否满足，如果满足，则left位置左边的元音是可以扩展的，用dp先统计下每个位置左边的元音个数
    long long countOfSubstrings(string word, int k) {
        int n = word.size();
        long long ans = 0;
        int mask = 0;
        mask |= 1 << ('a' - 'a');
        mask |= 1 << ('e' - 'a');
        mask |= 1 << ('i' - 'a');
        mask |= 1 << ('o' - 'a');
        mask |= 1 << ('u' - 'a');
        int i = 0;
        int consonant = 0;
        unordered_map<char, int> map;

        auto isVow = [&](char c) {
            return ((1 << (c - 'a')) & mask) > 0;
        };

        vector<long long> dp(n, 0); // dp[i]表示从i位置往左(不包含i位置)，元音字母的长度
        dp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (isVow(word[i - 1])) {
                dp[i] = dp[i - 1] + 1;
            }
            else dp[i] = 0;
        }

        for (int j = 0; j < n; j++) {
            if (isVow(word[j])) map[word[j]]++;
            else consonant++;
            while (true) {
                if (isVow(word[i])) {
                    map[word[i]]--;
                    if (map[word[i]] == 0) map.erase(word[i]);
                    if (map.size() == 5) {
                        i++;
                    }
                    else {
                        map[word[i]]++;
                        break;
                    }
                }
                if (!isVow(word[i])) {
                    if (consonant > k) {
                        consonant--;
                        i++;
                    }
                    else break;
                }
            }

            if (map.size() == 5 && consonant == k) {
                ans += dp.at(i) + 1;
            }
        }
        return ans;
    }


    long long countOfSubstrings_implementation2(string word, int k) {
        int n = word.size();
        long long ans = 0;
        int mask = 0;
        mask |= 1 << ('a' - 'a');
        mask |= 1 << ('e' - 'a');
        mask |= 1 << ('i' - 'a');
        mask |= 1 << ('o' - 'a');
        mask |= 1 << ('u' - 'a');
        int i = 0;
        int consonant = 0;
        unordered_map<char, int> map;

        auto isVow = [&](char c) {
            return ((1 << (c - 'a')) & mask) > 0;
        };

        vector<long long> dp(n, 0); // dp[i]表示从i位置往左(不包含i位置)，元音字母的长度
        dp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (isVow(word[i - 1])) {
                dp[i] = dp[i - 1] + 1;
            }
            else dp[i] = 0;
        }

        for (int j = 0; j < n; j++) {
            if (isVow(word[j])) map[word[j]]++;
            else consonant++;
            // 周赛时一开始滑窗就是写成这样，然后一直调不对
            while (map.size() == 5 && consonant >= k) {
                if (isVow(word[i])) {
                    map[word[i]]--;
                    if (map[word[i]] == 0) map.erase(word[i]);
                }
                else {
                    consonant--;
                }
                i++;
            }
            /* while结束之后，i位置是不合法的，但是，与`LeetCode3297. 统计重新排列后包含另一个字符串的子字符串数目 I`不同的是，
            i - 1位置也不一定是合法的，例如word = "ieaouqqieaouqq"，k = 1，窗口是ieaouqq时，会移动成eaouqq停下，但是
            ieaouqq也是不合法的！所以，检查一下i - 1位置，如果合法，那么方案数才能加上i - 1左侧的元音字母数。周赛时没有想清楚
            i - 1位置不一定是合法的，一直调不出来。
            */
            if (i - 1 >= 0) {
                if (isVow(word[i - 1])) {
                    map[word[i - 1]]++;
                    if (map.size() == 5 && consonant == k) {
                        ans += dp[i - 1] + 1;
                    }
                    map[word[i - 1]]--;
                    if (map[word[i - 1]] == 0) map.erase(word[i - 1]);
                }
                else {
                    consonant++;
                    if (map.size() == 5 && consonant == k) {
                        ans += dp[i - 1] + 1;
                    }
                    consonant--;
                }
            }
        }
        return ans;
    }

    /* 灵茶山艾府解法，while (map.size() == 5 && consonant >= k)的窗口滑动条件是对的，但是，这个条件
    实际滑的是 含所有元音字母且辅音字母个数>=k 的最小窗口，这个性质对窗口左边界具有单调性(从是到否，可能全否(此时相当于-1位置为'是')，所以着眼于找第一个否)，
    所以可以用滑动窗口。
    我把while (map.size() == 5 && consonant >= k)用成了：找第一个不对的位置，但是这里实际的不对，是元音不够或者辅音不够，并不能知道上一个位置辅音是否刚好k个
    而为了求 含所有元音字母且辅音字母个数==k 的方案数，用含所有元音字母且辅音字母个数>=k - 用含所有元音字母且辅音字母个数>=k + 1
    */
    long long countOfSubstrings_implementation3(string word, int k) {
        return f(word, k) - f(word, k + 1);
    }

    long long f(string &word, int k) {
        const string VOWEL = "aeiou";
        int i = 0;
        int consonant = 0;
        unordered_map<char, int> map;
        int n = word.size();
        long long ans = 0;
        for (int j = 0; j < n; j++) {
            if (VOWEL.find(word[j]) != string::npos) {
                map[word[j]]++;
            }
            else consonant++;
            while (map.size() == 5 && consonant >= k) {
                if (VOWEL.find(word[i]) != string::npos) {
                    map[word[i]]--;
                    if (map[word[i]] == 0) map.erase(word[i]);
                }
                else consonant--;
                i++;
            }
            // i是第一个不满足的位置，i - 1是最后一个满足的位置，[0, i - 1]都满足
            ans += i - 1 + 1;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3306 solu;
    cout << solu.countOfSubstrings("ieaouqqieaouqq", 1) << endl;
    cout << solu.countOfSubstrings_implementation2("ieaouqqieaouqq", 1) << endl;
    cout << solu.countOfSubstrings_implementation3("ieaouqqieaouqq", 1) << endl;
    return 0;
}
