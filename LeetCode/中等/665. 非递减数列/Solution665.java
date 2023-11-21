// https://leetcode.cn/problems/non-decreasing-array/

public class Solution665 {
    public boolean checkPossibility(int[] nums) {
        /* 若能通过改变一个元素变为单增，则数组表现为两段单增且第二段第一个点<第一段最后一个点，nums[i] < nums[i - 1]
        此时有两种策略，让nums[i - 1]降为nums[i]，判断nums[i - 2]是否<=nums[i]
        让nums[i]升为nums[i - 1]，判断nums[i + 1]是否>=nums[i - 1]
        */
        int exceptionCount = 0, exceptionIndex = -1;
        for (int i = 1; i < nums.length; i++) {
            if (nums[i] < nums[i - 1]) {
                exceptionCount++;
                exceptionIndex = i;
            }
        }
        if (exceptionCount == 0) return true;
        if (exceptionCount == 1) {
            if ((exceptionIndex - 2 < 0 || nums[exceptionIndex - 2] <= nums[exceptionIndex]) || (exceptionIndex + 1 >= nums.length || nums[exceptionIndex + 1] >= nums[exceptionIndex - 1])) {
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        Solution665 solu = new Solution665();
        System.out.println(solu.checkPossibility(new int[]{-1,4,2,3}));
        System.out.println(solu.checkPossibility(new int[]{4,2,3}));
        System.out.println(solu.checkPossibility(new int[]{5,7,1,8}));
    }
}
