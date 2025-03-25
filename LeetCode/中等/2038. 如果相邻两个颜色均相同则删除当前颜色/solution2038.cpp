/*
url: https://leetcode.cn/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2038 {
public:
    bool winnerOfGame(string colors) {
        int n = colors.size();
        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < n;) {
            int start = i;
            for (; i + 1 < n && colors[i + 1] == colors[i]; i++);
            // [start, i]
            if (colors[start] == 'A' && i - start + 1 >= 3) cnt1 += i - start + 1 - 2;
            else if (i - start + 1 >= 3) cnt2 += i - start + 1 - 2;
            i++;
        }
        return cnt1 > cnt2;
    }
};

int main(int argc, char const *argv[]) {
    Solution2038 solu;
    // cout << solu.winnerOfGame("AAABABB") << endl;
    cout << solu.winnerOfGame("AAAAABBB") << endl;
    return 0;
}