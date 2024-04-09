/*
url: https://leetcode.cn/problems/bulb-switcher-ii/description/
LeetCode参考: https://leetcode.cn/problems/bulb-switcher-ii/solutions/1823969/by-yvehung-1-o1dk/
              https://leetcode.cn/problems/bulb-switcher-ii/solutions/1823710/deng-pao-kai-guan-ii-by-leetcode-solutio-he7o/
标签: 数学, 线性代数
*/

import java.util.*;

public class Solution672 {
    /* 我能想到的是，每个开关只有按奇数和偶数次两种效果，只是要求最终灯泡情况数，因此操作顺序无关，
    这可以这样证明: 考虑i位置的灯泡，对操作序列中会影响i位置的操作，无论如果修改操作顺序，灯泡都是按开-关-开变化的，因此操作顺序无关。
    看起来最终结果最多是2^4=16种组合情况，但是2，3开关和1开关有关系，2，3开关都是偶数次的话就和1开关相同，然后还要考虑presses能不能按那么多下。
    */
    
    /* 参考<https://leetcode.cn/problems/bulb-switcher-ii/solutions/1823969/by-yvehung-1-o1dk/>，
    每个开关对应一个向量x1=[1,1,1,...]，x2=[1,0,1,0,...]，x3=[0,1,0,1,...]，x4=[1,0,0,1,...]。
    一个极大无关向量组是{x1,x2,x4}，对开关的操作结果y = a1 * x1 + a2 * x2 + a3 * x3 + a4 * x4，其中ai取0,1。
    y = (a1 + a3) * x1 + (a2 - a3) * x2 + a4 * x4，这里x1和x2的系数虽然取值不止0,1，但对最终灯泡状态的影响来说只需考虑
    奇数次于偶数次，于是仍然只需考虑0,1取值，于是**最多**只有2^3种最终状态。

    上面如果灯泡数量n较小，向量没这么长，极大无关向量组的向量个数没有这么多，当n==1时为1，n==2时为2，n>=3时为3。
    上面只是分析出了上界，但是实际这个问题还要麻烦。

    对秩r，有个r位的二进制数，初始为0，每次反转一位，**恰好**反转k次，能得到几种情况？
    注意，这个问题与原问题**不是**等价的，修改x3，会是个复合操作，相当于反转了两次。
    这里还有个隐藏的点，当把某位变为1后，presses剩余的次数是要恰好按完的，例如，能否保持这个r位的数只有1个1，从而实现这种最终状态？
    若还剩偶数次press，则都选一个向量按，最终状态不变，若剩奇数次press，若剩1次，则不能，若剩大于等于3的奇数次，按一次x3,x1,x2回到
    初始状态，然后问题变为还剩偶数次要按。
    也就是说这题还是没办法一个公式直接算出来，还是要看情况讨论。上面的分析虽然确定了秩确定了种数上界，但是还是得看每种取值情况能否实现，
    只是好在r最多为3，可以直接讨论。
    当n>=3且presses>=3时，由于**恰好要按**presses次的影响，为什么不用讨论presses的奇偶性？
    当n>=3且presses==3时，已经可以把000-111都取到，当presses为奇数时，多按一次x1反一下，也是能都取到。n==2且presses>=2时同理。
    也就是说，当presses已经能把所有情况取满时，presses再变大也是取满，不会变少。
    */
    public int flipLights(int n, int presses) {
        if (presses == 0) return 1;
        if (n == 1) return 2; // 向量组秩为1
        if (n == 2) return presses == 1 ? 3 : 4; // 秩为2
        else return presses == 1 ? 4 : presses == 2 ? 7 : 8; // 秩为3
        // 这里7是当r==3&&presses==2时，若开关1-4有一个按了2次则最终是初始状态，若有两个按了一次则是C(4,2)=6种情况，枚举之后各不相同，对应的y有7种取值
    }

    // 参考官方题解，再结合上面一种解法的基向量思维
    public int flipLights_implementation2(int n, int presses) {
        if (presses == 0) return 1;
        if (n == 1) return 2;
        if (n == 2) return presses == 1 ? 3 : 4;
        // 4个开关，不用考虑顺序，只考虑奇偶，最多1 << 4种情况，用4位来表示，枚举
        Set<Integer> seen = new HashSet<Integer>();
        for (int i = 0; i < 1 << 4; i++) {
            int[] press = new int[4];
            for (int j = 0; j < 4; j++) {
                press[j] = (i >> j) & 1;
            }
            int sum = 0;
            for (int j = 0; j < 4; j++) sum += press[j];
            if (sum % 2 == presses % 2 && sum <= presses) { // 这样的条件才是presses次能按出来的
                // 上一种解法的思路，用基向量下的坐标来唯一表示状态
                int status = 0;
                if (((press[0] + press[2] + 2) % 2) != 0) status |= 1 << 2;
                if (((press[1] - press[2] + 2) % 2) != 0) status |= 1 << 1;
                if ((press[3] % 2) != 0) status |= 1;
                seen.add(status);
            }
        }
        return seen.size();
    }

    public static void main(String[] args) {
        Solution672 solu = new Solution672();
        System.out.println(solu.flipLights(2, 1));
        System.out.println(solu.flipLights_implementation2(2, 1));
        System.out.println(solu.flipLights_implementation2(3, 1));
    }
}
