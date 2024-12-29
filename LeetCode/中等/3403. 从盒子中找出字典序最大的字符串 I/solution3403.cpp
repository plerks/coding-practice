/*
url: https://leetcode.cn/problems/find-the-lexicographically-largest-string-from-the-box-i/
参考: https://www.bilibili.com/video/BV13f68YjE7o/
标签: LeetCode第430场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3403 {
public:
    // 周赛时的写法，通过，但是写复杂了
    string answerString(string word, int numFriends) {
        if (numFriends == 1) return word;
        int n = word.size();
        vector<string> candidate;
        char mxchar = 'a';
        for (int i = 0; i < n; i++) {
            mxchar = std::max(mxchar, word[i]);
        }
        for (int i = 0; i < n; i++) {
            if (word[i] == mxchar) {
                string temp;
                int j = i;
                while (j < n && n - (j - i + 1) >= numFriends - 1) {
                    temp += word[j];
                    j++;
                }
                candidate.push_back(temp);
            }
        }
        return *max_element(candidate.begin(), candidate.end());
    }

    string answerString_implementation2(string word, int numFriends) {
        if (numFriends == 1) return word;
        int n = word.size();
        vector<string> candidate;
        char mxchar = *max_element(word.begin(), word.end());
        string s;
        for (int i = 0; i < n; i++) {
            if (word[i] == mxchar) {
                string temp = word.substr(i, n - (numFriends - 1));
                if (temp > s) s = temp;
            }
        }
        return s;
    }
};

/* 灵茶山艾府视频讲解里还提到了如何把这题从 n ^ 2 优化到 nlogn
1. 枚举所有长为 n - (numFriends - 1) 的子串，有 n 个，然后用字符串哈希，二分造成字符串哈希不相等的位置，需要O(log(n - numFriends))时间，
找到第一个不相等的位置后，就可以通过与当前的s比较知道谁大，总时间复杂度 O(nlog(n - numFriends))

2. 后缀数组 O(1) 比较任意两个子串的大小，但是有一个 O(nlogn) 的 ST 表的预处理 (待做: 这两个技巧没看过)
*/

int main(int argc, char const *argv[]) {
    return 0;
}
