// https://leetcode.cn/problems/rings-and-rods/?envType=daily-question&envId=2023-11-02

public class Solution2103 {
    public int countPoints(String rings) {
        int n = rings.length() / 2;
        // R, G, B分别在stick[i]的0, 1, 2号位置上表示
        int[] rods = new int[10];
        for (int i = 0; i < n; i++) {
            char color = rings.charAt(2 * i);
            int pos = rings.charAt(2 * i + 1) - '0';
            switch (color) {
                case 'R':
                    rods[pos] |= 1;
                    break;
                case 'G':
                    rods[pos] |= 2;
                    break;
                case 'B':
                    rods[pos] |= 4;
                    break;
            }
        }
        int ans = 0;
        for (int val : rods) {
            if (val == 7) {
                ans++;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2103 solu = new Solution2103();
        System.out.println(solu.countPoints("B0B6G0R6R0R6G9"));
    }
}
