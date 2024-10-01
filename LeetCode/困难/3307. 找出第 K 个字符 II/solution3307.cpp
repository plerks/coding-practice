/*
url: https://leetcode.cn/problems/find-the-k-th-character-in-string-game-ii/
参考: https://www.bilibili.com/video/BV1TqxCeZEmb/
      https://leetcode.cn/problems/find-the-k-th-character-in-string-game-ii/solutions/2934284/liang-chong-zuo-fa-di-gui-die-dai-python-5f6z/
相关: LeetCode3304. 找出第 K 个字符 I, LeetCode779. 第K个语法符号, LeetCode1545. 找出第 N 个二进制字符串中的第 K 位
标签: LeetCode第417场周赛
*/

// 这次周赛2题，第三题就差一点点时间就能交上去

#include <bits/stdc++.h>

using namespace std;

class Solution3307 {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        if (operations.empty()) return 'a';
        int n = operations.size();
        int op = operations.back();
        operations.pop_back();
        /* 本来是1 << (n - 1)判断k在左半边还是右半边，但是这题1 <= k <= 10^14，1 <= operations.length <= 100，
        移位会溢出。不过k肯定到不了1 << 63，所以63以上可以直接判定大于k而不移位 */
        if (n >= 63 || k <= (1LL << (n - 1))) { // k在左半边，注意k是从1开始编号的
            return kthCharacter(k, operations);
        }
        else { // k在右半边，求左半边那个字符再+1
            return (kthCharacter(k - (1LL << (n - 1)), operations) - 'a' + op) % 26 + 'a';
        }
    }

    // 改成迭代，这里改成迭代的思路不是递归的逆过程，很特殊
    char kthCharacter_implementation2(long long k, vector<int>& operations) {
        /* 递归最后会变成'a'，我们需要记录中途+1了多少次。
        从k所在的位置开始，如果k在右边则加op，否则直接看左半边
        */
        int inc = 0;
        /* for (int i = n; i >= 0; i--) { // operation[i]时s的长度为2^i
            int op = operations[i];
            int m = 1LL << (n - 1);
            if (k > m) {
                inc += op;
                k -= m;
            }
        } */

        /* 本来是像上面那样写，但是1LL << (n - 1)有溢出的问题，但是，若 k > m，则有 k > 2^i，
        即i < logk（logk为整数时<logk，非整时<⌈logk⌉或写成<=⌊logk⌋），或者把k > 2^i处理为k - 1 >= 2^i，
        即i <= ⌊log(k - 1)⌋（用减1的方式把 < 变成 <=，能得到一个统一的用下界表示的形式）

        这样一来，i只需从__lg(k - 1)（或者二进制长度-1）开始枚举
        */
        for (int i = 64 - (k - 1 == 0 ? 64 : __builtin_clzll(k - 1)) - 1; i >= 0; i--) { // operation[i]操作前s的长度为2^i，如果k超过了，则需要考虑operation[i]
            int op = operations[i];
            long long m = 1LL << i;
            if (k > m) {
                inc += op;
                k -= m;
            }
        }
        return 'a' + inc % 26;
    }

    // kthCharacter_implementation2()中的k > m等价于k - 1 >= m，后面k又减去了m，相当于遍历了k - 1的二进制1的位置
    char kthCharacter_implementation3(long long k, vector<int>& operations) {
        k--;
        int inc = 0;
        for (int i = 64 - (k == 0 ? 64 : __builtin_clzll(k)) - 1; i >= 0; i--) { // operation[i]操作前s的长度为2^i，如果k超过了，则需要考虑operation[i]
            if (k >> i & 1) inc += operations[i];
        }
        return 'a' + inc % 26;
    }
};

int main(int argc, char const *argv[]) {
    Solution3307 solu;
    vector<int> operations1 = {0, 1, 0, 1};
    cout << solu.kthCharacter(10, operations1) << endl;

    vector<int> operations2 = {0, 1, 0, 1};
    cout << solu.kthCharacter_implementation2(10, operations2) << endl;

    vector<int> operations3 = {0, 1, 0, 1};
    cout << solu.kthCharacter_implementation2(10, operations3) << endl;
    return 0;
}
