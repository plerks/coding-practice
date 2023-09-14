// https://leetcode.cn/problems/WHnhjV/?envType=daily-question&envId=2023-09-15

public class SolutionLCP50 {
    public int giveGem(int[] gem, int[][] operations) {
        for (int[] operation : operations) {
            int num = gem[operation[0]] / 2;
            gem[operation[0]] -= num;
            gem[operation[1]] += num;
        }
        int max = Integer.MIN_VALUE, min = Integer.MAX_VALUE;
        for (int val : gem) {
            max = Math.max(max, val);
            min = Math.min(min, val);
        }
        return max - min;
    }

    public static void main(String[] args) {
        SolutionLCP50 solu = new SolutionLCP50();
        System.out.println(solu.giveGem(new int[]{3,1,2}, new int[][]{{0,2},{2,1},{2,0}}));
    }
}