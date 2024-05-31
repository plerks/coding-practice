/*
url: https://leetcode.cn/problems/string-compression-iii/description/
LeetCode参考: https://leetcode.cn/problems/string-compression-iii/solutions/2790666/mo-ni-pythonjavacgo-by-endlesscheng-3hk7/
标签: LeetCode第399场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3163 {
public:
    // 周赛时的写法，能过，不过写法有点繁琐
    string compressedString(string word) {
        string ans;
        int i = 0;
        int n = word.size();
        char ch = 0;
        int count = 0;
        while (i < n) {
            if (ch == 0) {
                ch = word[i];
                count++;
            }
            else if (word[i] != ch) {
                ans.append(to_string(count));
                ans.append(1, ch);
                ch = 0;
                count = 0;
                continue;
            }
            else if (count == 9) {
                ans.append(to_string(count));
                ans.append(1, ch);
                ch = 0;
                count = 0;
                continue;
            }
            else {
                count++;
            }
            i++;
        }
        ans.append(to_string(count));
        ans.append(1, ch);
        return ans;
    }

    // 灵茶山艾府题解写法
    string compressedString_implementation2(string word) {
        string ans;
        int lastIndex = -1; // 上一个边界位置的字符
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            int count = i - lastIndex;
            if (i + 1 == word.size() || word[i + 1] != word[i]) {
                for (int k = 0; k < count / 9; k++) {
                    ans += '9';
                    ans += ch;
                }
                if (count % 9 > 0) {
                    ans += '0' + count % 9;
                    ans += ch;
                }
                lastIndex = i;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
