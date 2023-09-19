// https://leetcode.cn/problems/na-ying-bi/?envType=daily-question&envId=2023-09-20

public class SolutionLCP6 {
    public int minCount(int[] coins) {
        int ans = 0;
        for (int val : coins) {
            ans += (val + 1) / 2;
        }
        return ans;
    }

    public static void main(String[] args) {
        SolutionLCP6 solu = new SolutionLCP6();
        System.out.println(solu.minCount(new int[]{4,2,1}));
    }
}
