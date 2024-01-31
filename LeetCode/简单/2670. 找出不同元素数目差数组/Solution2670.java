import java.util.Arrays;

public class Solution2670 {
    public int[] distinctDifferenceArray(int[] nums) {
        boolean[] mapL = new boolean[51]; // 1 <= nums[i] <= 50，mapL[i]表示i是否出现
        boolean[] mapR = new boolean[51];
        int n = nums.length;
        int[] countL = new int[n]; // countL[i]表示[0,i]的不同元素数量
        countL[0] = 1;
        mapL[nums[0]] = true;
        for (int i = 1; i < n; i++) {
            if (mapL[nums[i]] == true) {
                countL[i] = countL[i - 1];
            }
            else {
                countL[i] = countL[i - 1] + 1;
                mapL[nums[i]] = true;
            }
        }
        int[] countR = new int[n]; // countR[i]表示[i, n-1]的不同元素数量
        countR[n - 1] = 1;
        mapR[nums[n - 1]] = true;
        for (int i = n - 2; i >= 0; i--) {
            if (mapR[nums[i]] == true) {
                countR[i] = countR[i + 1];
            }
            else {
                countR[i] = countR[i + 1] + 1;
                mapR[nums[i]] = true;
            }
        }
        int[] ans = new int[n];
        for (int i = 0; i < n; i++) {
            ans[i] = countL[i] - (i + 1 == n ? 0 : countR[i + 1]);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2670 solu = new Solution2670();
        System.out.println(Arrays.toString(solu.distinctDifferenceArray(new int[]{3,2,3,4,2})));
    }
}
