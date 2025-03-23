/*
url: https://leetcode.cn/problems/long-pressed-name/
相关: LeetCode809. 情感丰富的文字
标签: 【题单】滑动窗口与双指针, 分组循环
*/
#include <bits/stdc++.h>

using namespace std;

class Solution925 {
public:
    // 我的解法，用分组循环。可以把两个分组循环写在一起，这样就不用存切割结果了，见LeetCode809. 情感丰富的文字
    bool isLongPressedName(string name, string typed) {
        int n = name.size(), m = typed.size();
        vector<string> v1;
        vector<string> v2;
        for (int i = 0; i < n;) {
            int start = i;
            for (i++; i < n && name[i] == name[i - 1]; i++);
            v1.push_back(name.substr(start, i - start));
        }
        for (int i = 0; i < m;) {
            int start = i;
            for (i++; i < m && typed[i] == typed[i - 1]; i++);
            v2.push_back(typed.substr(start, i - start));
        }
        if (v1.size() != v2.size()) return false;
        for (int i = 0; i < v1.size(); i++) {
            if (!(v1[i].size() <= v2[i].size() && v1[i][0] == v2[i][0])) return false;
        }
        return true;
    }

    // 官方题解解法，双指针，当a 和 aa匹配，name的a结束后，j++去消耗掉多余的a。但是，要确保j是匹配成功剩余的a(j > 0)
    bool isLongPressedName_implementation2(string name, string typed) {
        int n = name.size(), m = typed.size();
        int i = 0, j = 0;
        while (j < m) { // 把j用完
            if (i < n && name[i] == typed[j]) {
                i++;
                j++;
            }
            else if (j > 0 && typed[j] == typed[j - 1]) { // j > 0说明是在匹配成功的状态
                j++;
            }
            else return false;
        }
        return i == n;
    }
};

int main(int argc, char const *argv[]) {
    Solution925 solu;
    cout << solu.isLongPressedName("alex", "aaleex") << endl;
    cout << solu.isLongPressedName("saeed", "ssaaedd") << endl;
    return 0;
}