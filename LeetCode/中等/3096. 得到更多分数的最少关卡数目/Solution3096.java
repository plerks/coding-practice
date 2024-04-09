// https://leetcode.cn/problems/minimum-levels-to-gain-more-points/description/

public class Solution3096 {
    public int minimumLevels(int[] possible) {
        int sum = 0;
        for (int num : possible) {
            sum += num == 0 ? -1 : 1;
        }
        int pre = 0; // 前面部分的得分
        for (int i = 0; i < possible.length - 1; i++) { // 每个玩家都至少需要完成 1 个关卡，这里循环是possible.length - 1
            pre += possible[i] == 0 ? -1 : 1;
            if (pre > sum - pre) return i + 1;
        }
        return -1;
    }

    public static void main(String[] args) {
        Solution3096 solu = new Solution3096();
        System.out.println(solu.minimumLevels(new int[]{1,1}));
    }
}
