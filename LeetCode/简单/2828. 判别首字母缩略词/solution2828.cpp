// https://leetcode.cn/problems/check-if-a-string-is-an-acronym-of-words/description/

#include <bits/stdc++.h>

using namespace std;

class Solution2828 {
public:
    bool isAcronym(const vector<string>& words, string s) {
        string acronym;
        for (auto &word : words) {
            acronym.append(1, word[0]); // append(size_type __n, _CharT __c)
            // acronym.append({word[0]}); // append(initializer_list<_CharT> __l)
        }
        return acronym == s;
    }
};

int main(int argc, char const *argv[]) {
    Solution2828 solu;
    // 提供的参数与函数定义的参数类型不同，属于隐式类型转换的一种情形，见<https://learn.microsoft.com/zh-cn/cpp/cpp/user-defined-type-conversions-cpp?view=msvc-170>
    cout << solu.isAcronym({"alice","bob","charlie"}, "abc") << endl;
    return 0;
}