/*
url: https://leetcode.cn/problems/couples-holding-hands/?envType=daily-question&envId=2023-11-11
LeetCode参考: https://leetcode.cn/problems/couples-holding-hands/solutions/602783/qing-lu-qian-shou-by-leetcode-solution-bvzr/
              https://leetcode.cn/problems/couples-holding-hands/solutions/599958/qing-lu-qian-shou-by-leetcode-gl1c/
              https://leetcode.cn/problems/couples-holding-hands/solutions/603505/liang-chong-100-de-jie-fa-bing-cha-ji-ta-26a6/
              https://leetcode.cn/problems/couples-holding-hands/solutions/1863771/-by-coco-e1-0spa/
标签: 并查集, 贪心, 座位问题
*/

public class Solution765 {
    /* 按照参考题解中的分析，需要调整的次数为所有连通分量的大小-1之和，假设有n个连通分量，大小分别为a1,a2,...an。开始的总节点数为N，则
    N = a1 + a2 + ... + an，ans = (a1-1) + (a2-1) + ... + (an-1)，则有ans = N - n
    */
    public int minSwapsCouples(int[] row) {
        int N = row.length / 2;
        int count = N; // 并查集中连通分量个数
        int[] p = new int[N];
        for (int i = 0; i < N; i++) {
            p[i] = i;
        }
        // 一对情侣的编号/2相同，用这个作为组号，进行union
        for (int i = 0; i < row.length; i += 2) {
            // 也可以不维护这个count，最后遍历一遍N，看是否p[i]=i来查连通分量个数
            count = union(p, row[i] / 2, row[i + 1] / 2, count);
        }
        return N - count;
    }

    // 参考<https://leetcode.cn/problems/couples-holding-hands/solutions/603505/liang-chong-100-de-jie-fa-bing-cha-ji-ta-26a6/>写的最简易并查集，不考虑子树大小关系进行合并
    public int union(int[] p, int i, int j, int count) {
        int r1 = find(p, i);
        int r2 = find(p, j);
        if (r1 == r2) return count;
        p[r1] = p[r2];
        return count - 1;
    }

    public int find(int[] p, int x) {
        if (p[x] != x) {
            p[x] = find(p, p[x]);
        }
        return p[x];
    }

    /* 参考<https://leetcode.cn/problems/couples-holding-hands/solutions/603505/liang-chong-100-de-jie-fa-bing-cha-ji-ta-26a6/>的题解，
    使用贪心的办法，从左向右遍历每两个座位，若不成对，则势必要进行最少一次交换将mate换过来，事实上也只需要一次即可。然后后续已匹配好的座位是不需要再
    动的。当把mate换过来后，wrong换过去可能能直接让wrong配对，问题规模缩减为n-2，也可能不能让wrong配对，问题规模缩减为n-1。这两种情况对应上一种解法
    中的环大小的概念，若2队刚好坐错位置，则只需把mate交换过来，wrong自然配好，环大小为2；若环更大则换mate之后不能让wrong配对，问题规模只能缩减为n-1。
    */
    public int minSwapsCouples_implementation2(int[] row) {
        int[] position = new int[row.length]; // 记录每个编号的人坐在哪里
        for (int i = 0; i < row.length; i++) {
            position[row[i]] = i;
        }
        int ans = 0;
        for (int i = 0; i < row.length; i += 2) {
            if (row[i] / 2 != row[i + 1] / 2) { // 不配对，把和row[i]一对的换过来(把和row[i + 1]一对的换过来一样)
                int mate = row[i] ^ 1; // 一对情侣的编号直接只有最后一位相反
                int wrong = row[i + 1];
                row[i + 1] = mate; // 这行可以不做，不需要实际地把mate移动过来
                row[position[mate]] = wrong;
                position[wrong] = position[mate];
                ans++;
                // position[mate]不用更新，后续不会再用到
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution765 solu = new Solution765();
        System.out.println(solu.minSwapsCouples(new int[]{0,2,1,3}));
        System.out.println(solu.minSwapsCouples_implementation2(new int[]{0,2,1,3}));
    }
}
