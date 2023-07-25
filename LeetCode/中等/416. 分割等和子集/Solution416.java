// https://leetcode.cn/problems/partition-equal-subset-sum/

class Solution416 {
	
	public static void main(String[] args) {
		Solution416 solu = new Solution416();
		System.out.println(solu.canPartition(new int[] {1,5,11,5}));
	}
	/*递归版解法1
	public boolean canPartition(int[] nums) {
		int sum = 0;
		for(int i=0;i<nums.length;i++) sum += nums[i];
		if(sum%2==1) return false;
		//不选nums[0],则要尝试用[1,nums.length)的数字构造出sum/2，选则要尝试构造出sum/2-nums[0]
		List<Integer> list1 = new ArrayList<>();
		List<Integer> list2 = new ArrayList<>();
		list2.add(nums[0]);
		return canGetSum(1,sum/2,nums,list1) || canGetSum(1,sum/2-nums[0],nums,list2); 
	}
	
	private boolean canGetSum(int index, int target, int[] nums,List<Integer> list) {
		if(index==nums.length-1) {
			if(nums[index]==target) {
				list.add(nums[index]);
				for(int i = 0;i<list.size();i++) System.out.print(list.get(i)+" ");
				return true;
			}
			else return false;
		}
		else {
			List<Integer> list1 = new ArrayList<>(list);
			List<Integer> list2 = new ArrayList<>(list);
			list2.add(nums[index]);
			return canGetSum(index+1,target,nums,list1) || canGetSum(index+1,target-nums[index],nums,list2);
		}
	}*/
	
	/*递归版解法2
	public boolean canPartition(int[] nums) {
		int sum = 0;
		for(int i=0;i<nums.length;i++) sum += nums[i];
		if(sum%2==1) return false;
		//不选nums[0],则要尝试用[1,nums.length)的数字构造出sum/2，选则要尝试构造出sum/2-nums[0]
		List<Integer> list = new ArrayList<>();
		if(canGetSum(1,sum/2,nums,list)) {
			return true;
		}
		list.add(nums[0]);
		if(canGetSum(1,sum/2-nums[0],nums,list)) {
			list.remove(list.size()-1);
			return true;
		}
		return false;
	}
	
	private boolean canGetSum(int index, int target, int[] nums,List<Integer> list) {
		if(index==nums.length-1) {
			if(nums[index]==target) {
				list.add(nums[index]);
				for(int i = 0;i<list.size();i++) {
					System.out.print(list.get(i)+" ");
					if(i==list.size()-1) System.out.println();
				}
				list.remove(list.size()-1);
				return true;
			}
			else return false;
		}
		else {
			if(canGetSum(index+1,target,nums,list)) {
				return true;
			}
			else {
				list.add(nums[index]);
				if(canGetSum(index+1,target-nums[index],nums,list)){
					list.remove(list.size()-1);
					return true;
				}
				else {
					list.remove(list.size()-1);
				}
			}
		}
		return false;
	}*/
	public boolean canPartition(int[] nums) {
		int sum = 0;
		for(int i=0;i<nums.length;i++) sum += nums[i];
		if(sum%2==1) return false;
		return solve(nums,sum/2);
	}
	private boolean solve(int[] nums, int target) {
		boolean[][] dp = new boolean[nums.length][target+1];
		for(int j=0;j<dp[0].length;j++) {
			dp[0][j] = nums[0]==j;
		}
		for(int i=1;i<dp.length;i++)
			for(int j=0;j<dp[0].length;j++) {
				if(j<nums[i]) {
					dp[i][j] = dp[i-1][j];
				}
				else dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i]];
			}
		return dp[nums.length-1][target];
	}
}