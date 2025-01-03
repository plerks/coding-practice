/*
url: https://leetcode.cn/problems/maximum-number-of-occurrences-of-a-substring/description/
参考: https://leetcode.cn/problems/maximum-number-of-occurrences-of-a-substring/solutions/101811/zi-chuan-de-zui-da-chu-xian-ci-shu-by-leetcode-sol/
标签: 【题单】滑动窗口与双指针, 定长滑窗的写法技巧, 定长滑动窗口的写法技巧
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1297 {
public:
    /* 枚举所有子串，需要O(n^2)时间，知道每个子串是否满足条件又需要O(n)，总共O(n^3)，但这其中有大量无效/重复运算。
    若[left, right]已经出现不同字母个数过多，则[left, right + 1]一定也是非法的；又例如，探明[left, right]的成分之后，
    如果不加改变，检查[left, right + 1]又需要完整读一遍。
    因此需要滑窗。此题滑窗过程在于，对于想要找合法区间[left, right]，站定一端后(以right为例)，单调滑动另外一端，在过程中每次只需O(1)时间
    即可检查区间性质。然后开启对下一个right位置的检查。
    这题属于同向的滑窗。
    这题在right单增的同时，left也只需考虑单增。left的单调性让时间复杂度可以达到O(n)。
    如果对于某些题目，right单增的同时left不单调(left需要回退)，那么只需对于每个right，让left从right到0进行枚举，也就是说，
    这样动态维护地枚举，至少也是O(n^2)，而非O(n^3)。

    但是，这题left的单调性是有问题的，对于寻找合法的子串来说，当前轮最后检测过成分的区间是[left - 1, x](注意是left - 1，left最后会自增一次)，
    由于成分可以任意少于maxLetters，于是一定是因为区间长度 < minSize才退出的，即[left - 1, x]的长度一定刚好为minSize(要除去最开始启动的时候，最开始更短)。
    当right从x增加到x+1时，left是否需要回退？例如[left - 2, x + 1]是否也是合法的子串？
    如果[left - 1, x]的不同字符个数 > maxLetters，[left - 2, x + 1]自然也是非法的，但若[left - 1, x]的不同字符个数 <= maxLetters，
    [left - 2, x + 1]似乎又有考虑的必要。
    对于寻找所有合法子串，其实是需要的，但是对于得到ans，left回退又是不需要的，滑窗能满足单调性。

    因为:
    参考[官方题解](https://leetcode.cn/problems/maximum-number-of-occurrences-of-a-substring/solutions/101811/zi-chuan-de-zui-da-chu-xian-ci-shu-by-leetcode-sol/)，
    如果[left - 2, x + 1]最终确实是ans，那么[left - 1, x + 1]同样也是合法的，且出现次数比[left - 2, x + 1]只多不少，所以，只是为了求ans，
    让left单增即可。事实上，只需考虑长度为minSize的子串即可，见maxFreq_implementation2()。

    maxFreq()，对于 "aab", 2, 3, 100 这个用例，是没把"aab"这个合法子串找出来的，但是不影响结果的正确性。

    总结一下，有些滑窗问题也表现出单调性
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

    // 只需考虑长度为minSize的子串
    int maxFreq_implementation2(string s, int maxLetters, int minSize, int maxSize) {
        int n = s.size();
        unordered_map<string, int> legal;
        int left = 0;
        int right = 0;
        unordered_map<char, int> count;
        int ans = 0;
        // 定长滑窗的写法技巧，可以把 初始窗口增长到size 和 保持长度为size逐步右移 合并到一个循环里不用分开写
        while (right < n) {
            // 直接把right加进来
            count[s[right]]++;
            if (right - left + 1 < minSize) {
                right++;
                continue;
            }
            else { // 长度等于minSize
                if (count.size() <= maxLetters) {
                    string sub = s.substr(left, right - left + 1);
                    legal[sub]++;
                    ans = max(ans, legal[sub]);
                }
                // 把left挤出去
                count[s[left]]--;
                if (count[s[left]] == 0) count.erase(s[left]);
                left++;
                right++;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1297 solu;
    cout << solu.maxFreq("aababcaab", 2, 3, 4) << endl;
    cout << solu.maxFreq("abcde", 2, 3, 3) << endl;
    cout << solu.maxFreq("aab", 2, 3, 100) << endl;
    cout << solu.maxFreq_implementation2("aababcaab", 2, 3, 4) << endl;
    cout << solu.maxFreq_implementation2("abcde", 2, 3, 3) << endl;
    cout << solu.maxFreq_implementation2("aab", 2, 3, 100) << endl;
    return 0;
}
