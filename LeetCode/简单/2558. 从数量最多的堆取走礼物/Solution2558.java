// https://leetcode.cn/problems/take-gifts-from-the-richest-pile/?envType=daily-question&envId=2023-10-28

import java.util.PriorityQueue;

public class Solution2558 {
    public long pickGifts(int[] gifts, int k) {
        PriorityQueue<Integer> q = new PriorityQueue<>((x, y) -> y - x);
        long ans = 0;
        for (int val : gifts) {
            q.offer(val);
            ans += val;
        }
        for (int i = 0; i < k; i++) {
            int gift = q.poll();
            ans = ans - (gift - (int)Math.sqrt(gift));
            gift = (int)Math.sqrt(gift);
            q.offer(gift);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2558 solu = new Solution2558();
        System.out.println(solu.pickGifts(new int[]{25,64,9,4,100}, 4));
    }
}
