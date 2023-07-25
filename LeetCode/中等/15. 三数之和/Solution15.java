// https://leetcode.cn/problems/3sum/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution15 {
	
	public static void main(String[] args) {
		Solution15 solu = new Solution15();
		//System.out.println(solu.maxAreaOfIsland(new int[][] {{1,0,0,0,0}, {1,1,0,0,1}, {1,0,1,1,0}, {1,1,0,0,1}, {0,0,0,0,0}}));
		System.out.println(solu.threeSum(new int[] {-1,0,1,2,-1,-4})); 
	}
	
	public List<List<Integer>> threeSum(int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> res = new ArrayList<List<Integer>>();
        //前后两次的nums[first]不能相等，否则可能有重复解
        for(int first = 0; first < nums.length;first++){
            if(first>0 && nums[first] == nums[first-1]) continue;
            int second = first + 1;
            int third = nums.length-1;
            while(second<third){
            	//前后两次的nums[second]不能相等，否则可能有重复解
            	if(second>first+1 && nums[second]==nums[second-1]){
                    second++;
                    continue;
                } 
                if(nums[first]+nums[second]+nums[third]==0){
                    ArrayList<Integer> list = new ArrayList<>();
                    list.add(nums[first]);
                    list.add(nums[second]);
                    list.add(nums[third]);
                    res.add(list);
                    second++;
                }
                else if(nums[first]+nums[second]+nums[third]<0){
                    second++;
                }
                else third--;
            }
        }
        return res;
    }
}
    
