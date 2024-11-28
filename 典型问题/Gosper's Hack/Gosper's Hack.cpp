/*
描述: Gosper's Hack。当前的数的二进制表示中有k个1，Gosper's Hack能在O(1)时间内直接得到下一个二进制表示中具有k个1的数
相关: LeetCode2397. 被列覆盖的最多行数, LeetCode2859. 计算 K 置位下标对应元素的和
*/

#include <bits/stdc++.h>

using namespace std;

/*
Gosper's Hack原理:
以连续的1为块，可以将一个数的二进制表示分为多个'1'块，当前已知了一个k个二进制1的数，如何得到下一个？
考虑最右边的那个'1'块，例如，当前的数select分割为 xxx... 01111 0...0 (最右'1'块的右边有0或多个'0'，左边一定至少有一个0)
那么，下一个有k个1的数应当将最右'1'块的最左边那个1向左移动一位与0交换(01变成10)，然后，把右边剩下的1全移到末尾。
变成： xxx... 10000 0...111
那么，如何得到这个值？

int lowbit = select & -select;
int x = select + lowbit;
select = ((select ^ x) / lowbit >> 2) | x; // 位运算优先级较低，这里会先/再>>

select为当前选出的符合要求的数(xxx... 01111 0...0)，用select + lowbit得到的x是 xxx... 10000 0...0 (最右'1'块在末尾加上了1)
开头的10我们已经得到形式，
然后，select ^ x会得到 000... 11111 0...0，然后/lowbit相当于右移把末尾的0丢掉，得到 000... 11111，(1已移动到末尾)
再>>2丢掉2个1(移动的位数是2与前面10的长度是2是对应的)，这样我们就得到了末尾 000... 111。
最后再与x或，即可得到 xxx... 10000 0...111

注意以下代码溢出时会有问题，gh.count(INT_MAX, 31)得到的下一个值会是不正确的-1，因为溢出后右移时符号位会补1而非0
*/

class GospersHack {
public:
    // 求[0, N]中二进制表示具有k个1的数的个数
    int count(int N, int k) {
        int select = (1 << k) - 1; // 选出的第一个数，k个1全在末尾，是最小的一个，Gosper's Hack会将符合条件的值顺序求出
        int ans = 0;
        while (select <= N) {
            ans++;
            int lowbit = select & -select;
            int x = select + lowbit;
            select = ((select ^ x) / lowbit >> 2) | x;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    GospersHack gh;
    cout << gh.count(8, 2) << endl;
    return 0;
}
