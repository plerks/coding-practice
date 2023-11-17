/*
url: https://leetcode.cn/problems/maximum-sum-queries/?envType=daily-question&envId=2023-11-17
LeetCode参考: https://leetcode.cn/problems/maximum-sum-queries/solutions/2305395/pai-xu-dan-diao-zhan-shang-er-fen-by-end-of9h/
标签: 双性质单调栈, 二分查找
相关: 典型问题/有序范围内的二分查找
*/

import java.util.*;

public class Solution2736 {
    public int[] maximumSumQueries(int[] nums1, int[] nums2, int[][] queries) {
        int n = nums1.length;
        int[][] pairs = new int[n][2];
        for (int i = 0; i < n; i++) {
            pairs[i][0] = nums1[i];
            pairs[i][1] = nums2[i];
        }
        Arrays.sort(pairs, (x, y) -> y[0] - x[0]);
        Integer[] idx = new Integer[queries.length];
        for (int i = 0; i < idx.length; i++) idx[i] = i;
        Arrays.sort(idx, (x, y) -> queries[y][0] - queries[x][0]);
        List<int[]> st = new ArrayList<>(); // 单调栈，其中存的是{nums2[j], nums1[j] + nums2[j]}
        int j = 0;
        int[] ans = new int[queries.length];
        for (int id : idx) {
            int x = queries[id][0], y = queries[id][1];
            for (; j < n && pairs[j][0] >= x; j++) { // st中的元素都满足nums1[j] >= 当前query的xi
                /* pairs将nums[1]从大到小排，处理queries也将queries的xi从大到小排，这样满足nums1[j] >= xi只需往栈中增加元素。
                对于一个query，将满足的nums1[j]入栈后，自然期望nums2[j]越大越好，若nums2[j]变小或者相等，由于nums1[j]是单减的，既可能nums2[j]满足不了>=yi的需求，
                nums1[j] + nums2[j]也是一定变小的。此外，栈中nums1[j] + nums2[j]更小的也可舍弃，其和更小，由于其nums1[j]更大，则
                nums2[j]一定更小，也一定不会成为候选解；或者说，nums2[j]单增，则栈中若nums1[j] + nums2[j]更小，则其在和更小的情况下
                更难满足nums2[j] >= yi的条件，没有价值，即使满足nums2[j] >= yi，由于和更小也一定不会被选出。
                这样一来，栈中同时满足nums2[j]单增，nums1[j] + nums2[j]单减。则只需找出第一个nums2[j] >= yi的位置，其和就是最大的。
                */
                while (!st.isEmpty() && st.get(st.size() - 1)[1] <= pairs[j][0] + pairs[j][1]) {
                    st.remove(st.size() - 1);
                }
                if (st.isEmpty() || st.get(st.size() - 1)[0] <= pairs[j][1]) {
                    st.add(new int[]{pairs[j][1], pairs[j][0] + pairs[j][1]});
                }
            }
            int pos = binSearch(st, y);
            ans[id] = pos < st.size() ? st.get(pos)[1] : -1;
        }
        return ans;
    }

    // 在[0, st.size() - 1]搜索第一个>=y的位置, 即最后一个<y的位置+1
    private int binSearch(List<int[]> st, int y) {
        int left = 0, right = st.size() - 1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (st.get(mid)[0] < y) {
                left = mid + 1;
            }
            else right = mid - 1;
        }
        return left - 1 + 1; // left-1为最后一个<y的位置范围[-1, st.size() - 1]，返回值范围[0, st.size()]
    }

    public static void main(String[] args) {
        Solution2736 solu = new Solution2736();
        System.out.println(Arrays.toString(solu.maximumSumQueries(new int[]{19,38,66}, new int[]{9,66,60}, new int[][]{{25,17}, {31,72}})));
    }
}
