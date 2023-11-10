public class AbstractSearchLast {
    // 有序范围从是到否变化，求最后一个'是'的位置
    
    public int searchLast_LeftClosedRightOpenInterval(int[] nums,int target) {
        // 左闭右开区间写法，搜索[x, y)中最后一个'是'的位置。
        int left = 0, right = nums.length;
        while (left < right) {
            int mid = (left + right) / 2;
            if (check(nums, mid, target)) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        return left - 1;
    }
    
    public int searchLast_ClosedInterval(int[] nums,int target) {
        // 闭区间写法，搜索[x, y]中最后一个'是'的位置。
        int left = 0, right = nums.length - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(nums, mid, target)) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return left - 1;
    }

    public boolean check(int[] nums, int mid, int target) {
        return nums[mid] < target;
    }

    public static void main(String[] args) {
        AbstractSearchLast solu = new AbstractSearchLast();
        System.out.println(solu.searchLast_LeftClosedRightOpenInterval(new int[]{3,5,5,7,8,8,9,15,20}, 9));
        System.out.println(solu.searchLast_ClosedInterval(new int[]{3,5,5,7,8,8,9,15,20}, 9));
    }
}
