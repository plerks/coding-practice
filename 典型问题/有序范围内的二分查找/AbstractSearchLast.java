public class AbstractSearchLast {
    // 有序范围从是到否变化，求最后一个'是'的位置
    
    public int searchLast_ClosedInterval(int[] nums,int target) {
        // 闭区间写法，搜索[x, y]中最后一个'是'的位置。
        int left = 0, right = nums.length - 1;
        while (left <= right) { // 区间不为空
            int mid = (left + right) / 2;
            if (check(nums, mid, target)) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        // 循环结束时left - 1 == right
        return left - 1;
    }

    public int searchLast_LeftClosedRightOpenInterval(int[] nums,int target) {
        // 左闭右开区间写法，搜索[x, y)中最后一个'是'的位置。
        int left = 0, right = nums.length;
        while (left < right) { // 区间不为空
            int mid = (left + right) / 2;
            if (check(nums, mid, target)) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        // 循环结束时left == right
        return left - 1;
    }

    public int searchLast_LeftOpenRightClosedInterval(int[] nums,int target) {
        int left = -1, right = nums.length - 1;
        while (left < right) { // 区间不为空
            int mid = (left + right) / 2;
            if (check(nums, mid, target)) {
                left = mid;
            }
            else {
                right = mid - 1;
            }
        }
        // 循环结束时left == right
        return left;
    }

    public int searchLast_OpenInterval(int[] nums,int target) {
        int left = -1, right = nums.length;
        while (left + 1 < right) { // 区间不为空
            int mid = (left + right) / 2;
            if (check(nums, mid, target)) {
                left = mid;
            }
            else {
                right = mid;
            }
        }
        // 循环结束时left + 1 == right
        return left;
    }

    public boolean check(int[] nums, int mid, int target) {
        return nums[mid] < target;
    }

    public static void main(String[] args) {
        AbstractSearchLast solu = new AbstractSearchLast();
        System.out.println(solu.searchLast_ClosedInterval(new int[]{3,5,5,7,8,8,9,15,20}, 9));
        System.out.println(solu.searchLast_LeftClosedRightOpenInterval(new int[]{3,5,5,7,8,8,9,15,20}, 9));
        System.out.println(solu.searchLast_LeftOpenRightClosedInterval(new int[]{3,5,5,7,8,8,9,15,20}, 9));
        System.out.println(solu.searchLast_OpenInterval(new int[]{3,5,5,7,8,8,9,15,20}, 9));
    }
}
