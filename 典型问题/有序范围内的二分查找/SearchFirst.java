public class SearchFirst {
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
    }

    public static void main(String[] args) {
        SearchFirst solu = new SearchFirst();
        System.out.println(solu.searchFirst(new int[]{5,7,7,8,8,10}, 8));
    }
}
