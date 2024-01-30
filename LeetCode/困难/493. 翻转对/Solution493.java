/*
url: https://leetcode.cn/problems/reverse-pairs/description/
LeetCode参考: https://leetcode.cn/problems/reverse-pairs/solutions/501005/fan-zhuan-dui-by-leetcode-solution/
相关: LeetCodeLCR 170. 交易逆序对的总数
标签: 类逆序对数, 归并排序, 双指针, 树状数组
*/

public class Solution493 {
    // merge()中求重要翻转对数量的方式性能很差，虽然没超时
    /* int ans;
    int[] temp;
    
    public int reversePairs(int[] nums) {
        if (nums.length == 0) return 0;
        this.ans = 0;
        this.temp = new int[nums.length / 2]; // 用作merge的数组
        mergeSort(nums, 0, nums.length);
        return ans;
    }

    private void mergeSort(int[] nums, int left, int right) {
        if (right - left == 1) return;
        int mid = (left + right) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid, right);
        merge(nums, left, mid, right);
    }

    private void merge(int[] nums, int left, int mid, int right) {
        for (int i = left; i < mid; i++) {
            temp[i - left] = nums[i];
        }
        int p1 = 0, p2 = mid, p = left;
        // (mid - left)为前半段长度
        while (p1 < (mid - left) && p2 < right) {
            if (temp[p1] <= nums[p2]) {
                // temp[p1] <= nums[p2]，但是有可能temp[p1] > 2 * nums[p2]，例如-5,-5
                int k = p2;
                while (k < right && temp[p1] > 2 * (long)nums[k]) k++;
                ans += k - p2;
                nums[p++] = temp[p1++];
            }
            else {
                int k = p1;
                while (k < (mid - left) && temp[k] <= 2 * (long)nums[p2]) k++;
                ans += (mid - left) - k;
                nums[p++] = nums[p2++];
            }
        }
        while (p1 < (mid - left)) {
            nums[p++] = temp[p1++];
        }
    } */

    int ans;
    int[] temp;
    
    public int reversePairs(int[] nums) {
        if (nums.length == 0) return 0;
        this.ans = 0;
        this.temp = new int[nums.length / 2]; // 用作merge的数组
        mergeSort(nums, 0, nums.length);
        return ans;
    }

    private void mergeSort(int[] nums, int left, int right) {
        if (right - left == 1) return;
        int mid = (left + right) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid, right);
        merge(nums, left, mid, right);
    }

    private void merge(int[] nums, int left, int mid, int right) {
        // 用双指针来找重要翻转对
        int lo = left, hi = mid; // 现在nums[lo]是最小值，nums[hi]是最小值
        // 对于两段数组，nums[i]和2*nums[j]都是单增的
        while (lo < mid && hi < right) {
            if (nums[lo] > 2 * (long)nums[hi]) {
                ans += mid - lo; // nums[lo, mid)都能与nums[hi]配成重要翻转对
                hi++;
            }
            else {
                lo++;
            }
        }
        for (int i = left; i < mid; i++) {
            temp[i - left] = nums[i];
        }
        int p1 = 0, p2 = mid, p = left;
        // (mid - left)为前半段长度
        while (p1 < (mid - left) && p2 < right) {
            if (temp[p1] <= nums[p2]) {
                nums[p++] = temp[p1++];
            }
            else {
                nums[p++] = nums[p2++];
            }
        }
        while (p1 < (mid - left)) {
            nums[p++] = temp[p1++];
        }
    }

    public static void main(String[] args) {
        Solution493 solu = new Solution493();
        // System.out.println(solu.reversePairs(new int[]{2,4,3,5,1}));
        // System.out.println(solu.reversePairs(new int[]{-5,-5}));
        System.out.println(solu.reversePairs(new int[]{5,4,3,2,1}));
    }
}
