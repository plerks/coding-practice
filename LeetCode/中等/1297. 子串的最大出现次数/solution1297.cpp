/*
url: https://leetcode.cn/problems/maximum-number-of-occurrences-of-a-substring/description/
标签: 【题单】滑动窗口与双指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1297 {
public:
    /* 枚举所有子串，需要O(n^2)时间，知道每个子串是否满足条件又需要O(n)，总共O(n^3)，但这其中有大量无效/重复运算。
    若[left, right]已经出现不同字母个数过多，则[left, right + 1]一定也是非法的；又例如，探明[left, right]的成分之后，
    如果不加改变，检查[left, right + 1]又需要完整读一遍。
    因此需要滑窗。此题滑窗过程在于，对于想要找合法区间[left, right]，站定一端后，单调滑动另外一端，在过程中每次只需O(1)时间
    即可检查区间性质。然后开启对下一个一端位置的检查。
    */
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        int n = s.size();
        unordered_map<string, int> legal; // [合法的字符串, 出现次数]
        int left = 0;
        int right = 0;
        unordered_map<char, int> count;
        int ans = 0;
        // 对于区间[left, right]，考虑right固定好为 0, 1, 2 ... n - 1 后，所有合法的left
        while (right < n) {
            count[s[right]]++;

            while (right - left + 1 >= minSize && right - left + 1 <= maxSize) {
                if (count.size() <= maxLetters) {
                    string sub = s.substr(left, right - left + 1);
                    legal[sub]++;
                    ans = max(ans, legal[sub]);
                }
                count[s[left]]--;
                if (count[s[left]] == 0) count.erase(s[left]);
                left++; // 有minSize限制，left不会加到比right大
            }
            right++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1297 solu;
    cout << solu.maxFreq("aababcaab", 2, 3, 4) << endl;
    cout << solu.maxFreq("abcde", 2, 3, 3) << endl;
    return 0;
}
