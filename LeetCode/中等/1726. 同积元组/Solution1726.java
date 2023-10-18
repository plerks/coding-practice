// https://leetcode.cn/problems/tuple-with-same-product/submissions/?envType=daily-question&envId=2023-10-19

import java.util.HashMap;
import java.util.Map;

public class Solution1726 {
    public int tupleSameProduct(int[] nums) {
        HashMap<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) { // 这里j > i，但是元组nums[i], nums[j]可互换，因此最后要多乘2
                map.put(nums[i] * nums[j], map.getOrDefault(nums[i] * nums[j], 0) + 1);
            }
        }
        int ans = 0;
        for (Map.Entry<Integer, Integer> entry : map.entrySet()) {
            int n = entry.getValue();
            ans += n * (n - 1) * 2 * 2; // A(n, 2) * 2 * 2
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1726 solu = new Solution1726();
        System.out.println(solu.tupleSameProduct(new int[]{2, 3, 4, 6}));
    }
}
