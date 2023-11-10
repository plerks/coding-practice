/*
url: https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/
相关: 典型问题/有序范围内的二分查找
*/

import java.util.Arrays;

public class Solution34 {
	
	public static void main(String[] args) {
		Solution34 solu = new Solution34();
		System.out.println(Arrays.toString(solu.searchRange(new int[] {5,7,7,8,8,10},8)));
        System.out.println(Arrays.toString(solu.searchRange_implementation2(new int[] {5,7,7,8,8,10},8)));
        System.out.println(solu.searchLast_LeftClosedRightOpenInterval(new int[]{5,7,7,7,8,8,10}, 8));
        System.out.println(solu.searchLast_ClosedInterval(new int[]{5,7,7,7,8,8,10}, 8));
	}
	
	public int[] searchRange(int[] nums, int target) {
        int leftIndex = searchFirstLargerOrEqual(nums,target);
        System.out.println(leftIndex);
        int rightIndex = searchFirstLarger(nums,target)-1;
        System.out.println(rightIndex);
        if(leftIndex>=nums.length || nums[leftIndex]!=target) return new int[] {-1,-1}; //数组中不存在target
        return new int[]{leftIndex,rightIndex};
    }
	//搜索第一个小于target的位置
    /* private int searchFirstSmaller(int[] nums,int target){
        int left = 0,right = nums.length-1,mid = 0;
        while(left < right){
            mid = left+(right-left)/2+1; //+1防止死循环，否者前后的区间可能不变
            if(nums[mid] < target){
                left = mid+1;
            }
            else{
                right = mid-1;
            }
        }
        return mid;
    } */
    //搜索第一个大于等于target的位置
    private int searchFirstLargerOrEqual(int[] nums,int target){
        int left = 0,right = nums.length-1,res = nums.length;
        while(left <= right){
            int mid = left+(right-left)/2;
            if(nums[mid] >= target){
                right = mid-1;
                res = mid;
            }
            else{
                left = mid+1;
            }
        }
        return res;
    }

    //搜索第一个大于target的位置
    private int searchFirstLarger(int[] nums,int target){
        int left = 0,right = nums.length-1,res = nums.length;
        while(left <= right){
            int mid = left+(right-left)/2;
            if(nums[mid] > target){
                right = mid-1;
                res = mid;
            }
            else{
                left = mid+1;
            }
        }
        return res;
    }

    public int[] searchRange_implementation2(int[] nums, int target) {
        if (nums.length == 0) return new int[]{-1, -1};
        return new int[]{searchFirst(nums, target), searchLast(nums, target)};
    }

    private int searchFirst(int[] nums,int target) {
        int left = 0, right = nums.length - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] > target) {
                right = mid - 1; // 若存在，第一个出现位置在[left, mid - 1]内
            }
            else if (nums[mid] == target) {
                right = mid;
            }
            else {
                left = mid + 1; // 若存在，第一个出现位置在[mid + 1, right]内
            }
        }
        // 循环结束时left == right
        return nums[left] == target ? left : -1;
        // 注意，left < right时，有left <= mid < right，这里区间大小一定能单调减，不会死循环

        // 另外一种套路写法
        // searchFirstEqual()转化为searchFirstLargerOrEqual()再转化成searchLastSmaller() + 1
        /* int left = 0, right = nums.length;
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        // left - 1最终范围为[-1, nums.length)，则left是[0, nums.length + 1)
        return left < nums.length && nums[left] == target ? left : -1; */
    }

    private int searchLast(int[] nums,int target) {
        // 这里不能像searchFirst()那样写，因为当nums[mid] == target时，会转入[mid, right]，可能死循环，因此转换思路求第一个大于target的位置
        int x = searchFirstLarger_implementation2(nums, target);
        return (x - 1 >= 0 && nums[x - 1] == target) ? x - 1 : - 1;

        // searchLast还有一种写法，多用一个变量ans暂存可能的结果，让区间大小单调递减，以避免死循环，不过这样要写成while (left <= right)，因为在left==right时也要判断是否要更新ans
        /* int left = 0, right = nums.length - 1;
        int ans = 0;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] == target) {
                ans = mid;
                left = mid + 1;
            }
            else if (nums[mid] > target) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return nums[ans] == target ? ans : -1; */
    }

    private int searchFirstLarger_implementation2(int[] nums,int target){
        int left = 0, right = nums.length;
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] > target) {
                right = mid; // 说明在[left, mid]
            }
            else {
                left = mid + 1; // 说明在[mid + 1, right]
            }
        }
        return left;
        // 同样，left < right时，有left <= mid < right，这里区间大小一定能单调减，不会死循环
    }

    private int searchLast_LeftClosedRightOpenInterval(int[] nums,int target) {
        // 左闭右开区间写法，先考虑搜索[0, nums.length)中<=target的最后位置，没有则为-1，check()逻辑相当于nums[mid] <= target。
        int left = 0, right = nums.length;
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] <= target) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        // 搜索出的<=target的最后位置为left - 1，这题要求==target的最后位置，不能直接返回left - 1
        return (left - 1 >= 0 && nums[left - 1] == target) ? left - 1 : -1;
    }

    private int searchLast_ClosedInterval(int[] nums,int target) {
        // 闭区间写法，先考虑搜索[0, nums.length]中<=target的最后位置，没有则为-1，check()逻辑相当于nums[mid] <= target。
        int left = 0, right = nums.length - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] <= target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        // 搜索出的<=target的最后位置为left - 1，这题要求==target的最后位置，不能直接返回left - 1
        return (left - 1 >= 0 && nums[left - 1] == target) ? left - 1 : -1;
    }
}
