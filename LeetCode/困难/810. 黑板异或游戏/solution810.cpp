/*
url: https://leetcode.cn/problems/chalkboard-xor-game/
参考: https://leetcode.cn/problems/chalkboard-xor-game/solutions/789745/gong-shui-san-xie-noxiang-xin-ke-xue-xi-ges7k/
标签: 【算法题单】位运算, 博弈论
*/
#include <bits/stdc++.h>

using namespace std;

class Solution810 {
public:
    /* 参考宫水三叶题解。这题宫水三叶题解的分析很精彩，评论区提到了“ICG博弈”这一概念。
    考虑Alice要怎样才能赢，若一开始所有元素的异或s为0，则Alice直接赢，否则(s!=0)，
    若元素个数为偶数，Alice一定能在下一回合开始时不让Bob赢，这是因为：
        若此时Alice无论怎么选都会让Bob在下一回合开始时赢，则 s^nums[0]=0，s^nums[1]=0，... 
        于是 (s^...^s) ^ s = 0，一共奇数个s，得出s=0，矛盾。
    Bob一定无法在下回合赢，于是回到Alice后，要么现在的s=0，Alice直接赢，要么由于s!=0且元素个数为偶数，Alice暂时赢不了，但是一定有办法继续让Bob赢不了

    也就是说，Alice可能一时赢不了，但是Bob一定一直赢不了。直到最后元素选完或者中途碰上s=0，Alice就赢了。
    */
    bool xorGame(vector<int>& nums) {
        int s = 0;
        for (int x : nums) s ^= x;
        return s == 0 || nums.size() % 2 == 0;
    }
};

int main(int argc, char const *argv[]) {
    Solution810 solu;
    cout << solu.xorGame(*new vector<int>{1,1,2}) << endl;
    cout << solu.xorGame(*new vector<int>{0,1}) << endl;
    cout << solu.xorGame(*new vector<int>{1,2,3}) << endl;
    return 0;
}