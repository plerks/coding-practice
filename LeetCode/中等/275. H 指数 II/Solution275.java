/*
url: https://leetcode.cn/problems/h-index-ii/?envType=daily-question&envId=2023-10-30
相关: LeetCode274. H 指数, LeetCode35. 搜索插入位置
标签: h指数，二分查找
*/

public class Solution275 {
    public int hIndex(int[] citations) {
        // h指数范围为[0, n]
        int left = 0, right = citations.length;
        int ans = 0;
        while (left <= right) { // 与LeetCode35. 搜索插入位置不同，left==right时不知道left次数是否满足，需要进行判断
            int mid = (left + right) / 2;
            if (mid == 0 || citations[citations.length - mid] >= mid) { // 判断mid是否满足
                ans = mid; // 为了每次让区间严格缩小，需要让left = mid + 1，但是left是符合的，所以用了ans存值
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution275 solu = new Solution275();
        System.out.println(solu.hIndex(new int[]{0}));
    }
}
