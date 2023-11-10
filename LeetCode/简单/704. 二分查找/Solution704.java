/*
url: https://leetcode.cn/problems/binary-search/
相关: 典型问题/有序范围内的二分查找
*/

public class Solution704 {
    public int search(int[] nums, int target) {
        // 不变性: 若target在nums中存在，则要么在mid直接命中，要么被[left, right]包围，若区间大小变为0则说明不存在
        int left = 0, right = nums.length - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            else if (nums[mid] > target) {
                right = mid - 1;
            }
            else left = mid + 1;
        }
        return -1;
    }

    public static void main(String[] args) {
        Solution704 solu = new Solution704();
        System.out.println(solu.search(new int[]{-1,0,3,5,9,12}, 9));
    }
}
