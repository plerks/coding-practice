/*
url: https://leetcode.cn/problems/handling-sum-queries-after-update/
LeetCode参考: https://leetcode.cn/problems/handling-sum-queries-after-update/solutions/2359836/jing-ran-guo-liao-ha-ha-by-chi-xue-piuf/
*/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution2569 {
    public long[] handleQuery(int[] nums1, int[] nums2, int[][] queries) {
        long numOfOneInNum1 = 0;
        for (int i = 0; i < nums1.length; i++) {
            if (nums1[i] == 1) {
                numOfOneInNum1++;
            }
        }
        long sum = 0;
        for (int i = 0; i < nums2.length; i++) {
            sum += nums2[i];
        }
        List<Long> list = new ArrayList<>();
        for (int i = 0; i < queries.length; i++) {
            if (queries[i][0] == 1) {
                for (int j = queries[i][1]; j <= queries[i][2]; j++) {
                    nums1[j] ^= 1;
                    numOfOneInNum1 += nums1[j] == 1 ? 1 : -1;
                }
            }
            else if (queries[i][0] == 2) {
                sum += queries[i][1] * numOfOneInNum1;
            }
            else {
                list.add(sum);
            }
        }
        long[] ans = new long[list.size()];
        for (int i = 0; i < list.size(); i++) {
            ans[i] = list.get(i);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2569 solu = new Solution2569();
        System.out.println(Arrays.toString(solu.handleQuery(new int[]{1,0,1}, new int[]{0,0,0}, new int[][]{{1,1,1},{2,1,0},{3,0,0}})));
    }
}