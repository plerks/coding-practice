/*
url: https://leetcode.cn/problems/p0NxJO/description/?envType=daily-question&envId=2024-02-06
LeetCode参考: https://leetcode.cn/problems/p0NxJO/solutions/2628589/mo-ta-you-xi-by-leetcode-solution-gkmj/
标签: 贪心, 优先队列
*/

import java.util.PriorityQueue;

public class SolutionLCP30 {
    /* 按原计划遍历，若在nums[i]位置累加后生命值<=0，则应该将所遇到的最小值nums[j]移到后面，这个nums[j]一定为负，
    否则说明[0,i]范围内全>=0，不可能出现累加后生命值<=0。将nums[j]移到后面后，生命值一定恢复为正（因为上一步生命值为正，移除的nums[j]<=nums[i]）。
    最后调整的末尾全为负，累加出最终值即可知道是否有解。
    */
    public int magicTower(int[] nums) {
        int n = nums.length;
        long hp = 1;
        long suffixSum = 0;
        PriorityQueue<Integer> q = new PriorityQueue<>();
        int count = 0;
        for (int i = 0; i < n; i++) {
            q.offer(nums[i]);
            hp += nums[i];
            if (hp <= 0) { // 移动最小值到后面
                int min = q.poll();
                hp -= min;
                suffixSum += min;
                count++;
            }
        }
        return hp + suffixSum > 0 ? count : -1;
    }

    // 实现二，不需要记录suffixSum，只需算一遍nums总和即可知道是否有解
    public int magicTower_implementation2(int[] nums) {
        int n = nums.length;
        long hp = 1;
        for (int i = 0; i < n; i++) {
            hp += nums[i];
        }
        // 把所有负数移动到末尾是最极端的情况，如果nums的和>0，可通过把所有负数移动到末尾过关，否则不行
        if (hp <= 0) return -1;
        hp = 1;
        PriorityQueue<Integer> q = new PriorityQueue<>();
        int count = 0;
        for (int i = 0; i < n; i++) {
            hp += nums[i];
            if (nums[i] <= 0) { // 只有小于0才需要记录，>=0的值越靠前越好，不会挪到后面
                q.offer(nums[i]);
            }
            if (hp <= 0) { // 移动最小值到后面
                hp -= q.poll();
                count++;
            }
        }
        return count;
    }

    public static void main(String[] args) {
        SolutionLCP30 solu = new SolutionLCP30();
        System.out.println(solu.magicTower(new int[]{100,100,100,-250,-60,-140,-50,-50,100,150}));
        System.out.println(solu.magicTower_implementation2(new int[]{100,100,100,-250,-60,-140,-50,-50,100,150}));
    }
}
