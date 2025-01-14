/*
url: https://leetcode.cn/problems/permutation-in-string/description/
相关: LeetCode3298. 统计重新排列后包含另一个字符串的子字符串数目 II
标签: 【题单】滑动窗口与双指针, 右端点字母更新左指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution567 {
public:
    /* 我的做法，窗口除了成分要够，还不能有多余的，也就是说，窗口必须==，>=还不行，
    以下这样写可以保证滑窗内左端点字母数量 <= s1的此字母，不会有多余，但是s1其它字母不知道是 > = <，
    比如 s1 = "ab"，窗口 = "abb" "abc" "ac"
    */
    bool checkInclusion(string s1, string s2) {
        int n = s2.size();
        int map1[26]{};
        for (char c : s1) map1[c - 'a']++;
        int map2[26]{};
        // 窗口不仅要包含s1的所有成分，还不能有多余的字符
        int l = 0;
        for (int r = 0; r < n; r++) {
            map2[s2[r] - 'a']++;
            // l可能等于 r + 1 ，于是l可能等于n，产生下标越界，需要判断 l <= r
            while (l <= r && map2[s2[l] - 'a'] > map1[s2[l] - 'a']) {
                map2[s2[l] - 'a']--;
                l++;
            }
            // 把左边多余字母都剔掉，这时候必须完全相等
            bool equal = true;
            for (int i = 0; i < 26; i++) {
                if (map1[i] != map2[i]) {
                    equal = false;
                    break;
                }
            }
            if (equal) return true;
        }
        return false;
    }

    /* 参考官方题解，成分判等时更简单，不需要每个字母都判断一遍，关键是要用窗口的右端点字母来移动左指针
    */
    bool checkInclusion_implementation2(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        int diff[26]{};
        for (char c : s1) diff[c - 'a']--;
        int l = 0;
        for (int r = 0; r < n; r++) {
            diff[s2[r] - 'a']++;
            /* 注意，这里写成while (l <= r && diff[s2[l] - 'a'] > 0)是不能用长度来判等的，例如[s1="ab", s2="bo"]
            错误写法：
            while (l <= r && diff[s2[l] - 'a'] > 0) {
                diff[s2[l] - 'a']--;
                l++;
            }
            if (r - l + 1 == m) return true; */


            /* 字母都是由r引入的，用右端点的字母来移动左指针，保证了窗口内每种字母要么不够，要么相等，绝不会有多余，
            这样用长度就能判断是否相等。注意这样写看似会发生 s1 = "ab" 窗口 = "cb" ，然后认为长度相等的情况，
            实际上不会，多余字母c在之前就会被丢出去窗口。
            */
            while (diff[s2[r] - 'a'] > 0) {
                diff[s2[l] - 'a']--;
                l++;
            }
            if (r - l + 1 == m) return true;
        }
        return false;
    }

    // 官方题解的另一种解法，记录s1和窗口中个数不等的字母的数量，也能快速判等
    bool checkInclusion_implementation3(string s1, string s2) {
        int n = s2.size();
        int diff[26]{};
        for (char c : s1) diff[c - 'a']--;
        int l = 0;
        int count = 0; // 个数不等的字母的数量
        for (int d : diff) count += d != 0;
        for (int r = 0; r < n; r++) {
            if (diff[s2[r] - 'a'] == 0) count++;
            diff[s2[r] - 'a']++;
            if (diff[s2[r] - 'a'] == 0) count--;
            // 用右端点字母移动左指针
            while (diff[s2[r] - 'a'] > 0) {
                if (diff[s2[l] - 'a'] == 0) count++;
                diff[s2[l] - 'a']--;
                if (diff[s2[l] - 'a'] == 0) count--;
                l++;
            }
            if (count == 0) return true;
        }
        return false;
    }

    /* 用这种记录个数不等的字母的数量的方式，用左端点字母移动左指针的写法也能避免判断每个字母，也即，checkInclusion()可以写成以下这样。
    
    不过，还是用右端点字母更新左指针的策略更优秀，也就是说checkInclusion_implementation2和checkInclusion_implementation3的解法更好。
    */
    bool checkInclusion_implementation4(string s1, string s2) {
        int n = s2.size();
        int diff[26]{};
        for (char c : s1) diff[c - 'a']--;
        int l = 0;
        int count = 0; // 个数不等的字母的数量
        for (int d : diff) count += d != 0;
        for (int r = 0; r < n; r++) {
            if (diff[s2[r] - 'a'] == 0) count++;
            diff[s2[r] - 'a']++;
            if (diff[s2[r] - 'a'] == 0) count--;
            // 用左端点字母移动左指针，不如使用右端点字母的写法
            while (l <= r && diff[s2[l] - 'a'] > 0) {
                if (diff[s2[l] - 'a'] == 0) count++;
                diff[s2[l] - 'a']--;
                if (diff[s2[l] - 'a'] == 0) count--;
                l++;
            }
            if (count == 0) return true;
        }
        return false;
    }
};

int main(int argc, char const *argv[]) {
    Solution567 solu;
    // cout << solu.checkInclusion("ab", "eidbaooo") << endl;

    cout << solu.checkInclusion_implementation2("ab", "bo") << endl;
    // cout << solu.checkInclusion_implementation2("a", "b") << endl;

    cout << solu.checkInclusion_implementation3("ab", "bo") << endl;
    return 0;
}