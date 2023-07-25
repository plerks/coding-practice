// https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/

import java.util.Arrays;

public class Solution34 {
	
	public static void main(String[] args) {
		Solution34 solu = new Solution34();
		System.out.println(Arrays.toString(solu.searchRange(new int[] {2,2},3)));
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
}
