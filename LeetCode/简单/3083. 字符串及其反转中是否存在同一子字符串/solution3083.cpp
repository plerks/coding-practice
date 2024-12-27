// https://leetcode.cn/problems/existence-of-a-substring-in-a-string-and-its-reverse/description/?envType=daily-question&envId=2024-12-26
#include <bits/stdc++.h>

using namespace std;

class Solution3083 {
public:
    bool isSubstringPresent(string s) {
        int n = s.size();
        unordered_set<string> set;
        for (int i = 0; i < n - 1; i++) {
            set.insert(s.substr(i, 2));
        }
        reverse(s.begin(), s.end());
        for (int i = 0; i < n - 1; i++) {
            string t = s.substr(i, 2);
            if (set.count(t)) return true;
        }
        return false;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
