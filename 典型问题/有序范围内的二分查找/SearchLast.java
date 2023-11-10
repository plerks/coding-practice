public class SearchLast {
    private int searchLast(int[] nums,int target) {
        // 这里不能像searchFirst()那样写，因为当nums[mid] == target时，会转入[mid, right]，可能死循环，因此转换思路求第一个大于target的位置
        int x = searchFirstLarger(nums, target);
        return (x - 1 >= 0 && nums[x - 1] == target) ? x - 1 : - 1;
    }

    private int searchFirstLarger(int[] nums,int target){
        int left = 0, right = nums.length; // 注意这里的范围，firstLarger的位置必存在(有nums.length这个位置保底)
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

    // searchLast还有一种写法，多用一个变量ans暂存可能的结果，让区间大小单调递减，以避免死循环，不过这样要写成while (left <= right)，因为在left==right时也要判断是否要更新ans
    private int searchLast_implementation2(int[] nums,int target) {
        int left = 0, right = nums.length - 1;
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
        return nums[ans] == target ? ans : -1;
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

    public static void main(String[] args) {
        SearchLast solu = new SearchLast();
        System.out.println(solu.searchLast(new int[]{5,7,7,7,8,8,10}, 8));
        System.out.println(solu.searchLast_implementation2(new int[]{5,7,7,7,8,8,10}, 8));
        System.out.println(solu.searchLast_LeftClosedRightOpenInterval(new int[]{5,7,7,7,8,8,10}, 8));
        System.out.println(solu.searchLast_ClosedInterval(new int[]{5,7,7,7,8,8,10}, 8));
    }
}
