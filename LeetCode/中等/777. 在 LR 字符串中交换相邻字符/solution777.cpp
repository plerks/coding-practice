/*
url: https://leetcode.cn/problems/swap-adjacent-in-lr-string/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution777 {
public:
    // 初始思路，过不了"LXXLXRLXXL", "XLLXRXLXLX"这个用例，因为result实际不能改
    bool canTransform_wa(string s, string result) {
        // L和R能借助X往左/右，移成最终形态
        moveR(s);
        moveL(s);
        moveR(result);
        moveL(result);
        string s1;
        string s2;
        for (int c : s) if (c != 'X') s1.push_back(c);
        for (int c : result) if (c != 'X') s2.push_back(c);
        return s1 == s2;
    }

    void moveR(string& s) { // 把R尽量往右移动
        int n = s.size();
        int i = n - 1, j = n - 1;
        while (i >= 0) {
            if (s[i] == 'R') {
                swap(s[i], s[j]);
                i--;
                j--;
            }
            else if (s[i] == 'L') {
                j = i - 1;
                i--;
            }
            else i--;
        }
    }

    void moveL(string& s) {
        int n = s.size();
        int i = 0, j = 0;
        while (i < n) {
            if (s[i] == 'L') {
                swap(s[i], s[j]);
                i++;
                j++;
            }
            else if (s[i] == 'R') {
                j = i + 1;
                i++;
            }
            else i++;
        }
    }

    /* 换一个方式思考，s和result，去除X后要相同，也就是LR的相对位置相同，
    且对应的L和R，s的要L靠右，R的要靠左，这样s才能变成result
    */
    bool canTransform(string s, string result) {
        int n = s.size();
        int i = 0, j = 0;
        while (i < n) {
            if (s[i] == 'X') {
                i++;
                continue;
            }
            if (result[j] == 'X') {
                j++;
                continue;
            }
            
            if (s[i] != result[j]) return false;
            if (s[i] == 'L' && i < j) return false;
            if (s[i] == 'R' && i > j) return false;
            i++; j++;
        }
        while (j < n && result[j] == 'X') j++; 
        return j == n; // j能否匹配完
    }

    // 灵茶题解写法，更简洁
    bool canTransform_implementation2(string s, string result) {
        int n = s.size();
        string test1 = s, test2 = result;
        test1.erase(remove(test1.begin(), test1.end(), 'X'), test1.end());
        test2.erase(remove(test2.begin(), test2.end(), 'X'), test2.end());
        if (test1 != test2) return false; // 先判断一下成分是否相同

        int j = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'X') continue;
            while (result[j] == 'X') j++; // 前面判断了成分相同，这里不需要判断j < n
            if (i != j && (s[i] == 'L') != (i > j)) { // 'L'则i > j, 'R'则i < j，(s[i] == 'L') != (i > j)把两个都判断了
                return false;
            }
            j++;
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    Solution777 solu;
    cout << solu.canTransform("RXXLRXRXL", "XRLXXRRLX") << endl;
    // cout << solu.canTransform("LLR", "RRL") << endl;
    // cout << solu.canTransform("XRRXRX", "RXLRRX") << endl;
    // cout << solu.canTransform("LXXLXRLXXL", "XLLXRXLXLX") << endl;
    return 0;
}