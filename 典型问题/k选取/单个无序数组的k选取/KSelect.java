/*
描述: 给定数组nums，k选取找出nums的排序数组S中下标为k的元素S[k]
相关: LeetCode215. 数组中的第K个最大元素, 典型问题/求前k大, LeetCode462. 最小操作次数使数组元素相等 II, LeetCodeLCP 24. 数字游戏, LeetCode295. 数据流的中位数
标签: k选取, 快速排序, 堆
*/

public class KSelect {
    /* 使用快速排序中的partition()，<https://leetcode.cn/problems/kth-largest-element-in-an-array/solutions/307351/shu-zu-zhong-de-di-kge-zui-da-yuan-su-by-leetcode-/>中有说明，
    《算法导论》9.2：期望为线性的选择算法有推导，在随机数据的情况下期望时间复杂度为O(n)，这里这样写达不到。
    此外算法导论9.3有描述最坏情况为线性时间的选择算法，《数据结构(C++语言版)》-ISBN9787302330646 12.2.6节也有。 */
    // C++可以直接用 std::nth_element()
    public int kSelect(int[] nums, int k) {
        int lo = 0, hi = nums.length - 1;
        while (lo < hi) {
            int i = lo, j = hi;
            int pivot = nums[lo];
            while (i < j) {
                while (i < j && nums[j] > pivot) j--;
                if (i < j) nums[i++] = nums[j];
                while (i < j && nums[i] < pivot) i++;
                if (i < j) nums[j--] = nums[i];
            }
            nums[i] = pivot;
            if (i == k) return nums[i];
            else if (i > k) hi = i - 1;
            else lo = i + 1;
        }
        return nums[lo];
    }

    // 用堆实现，时间复杂度O(n+klogn)，《数据结构(C++语言版)》-ISBN9787302330646 12.2.4节还有另外两种用堆实现k选取的办法，不过相差不大。
    public int kSelect_implementation2(int[] nums, int k) {
        int heapSize = nums.length;
        buildMinHeap(nums, heapSize); // 小顶堆
        for (int i = 0; i < k; i++) {
            swap(nums, 0, heapSize - 1);
            heapSize--;
            percolateDown(nums, 0, heapSize);
        }
        return nums[0];
    }

    private void buildMinHeap(int[] nums, int heapSize) {
        for (int i = heapSize - 1; i >= 0; i--) {
            percolateDown(nums, i, heapSize);
        }
    }

    private void percolateDown(int[] nums, int i, int heapSize) {
        int j; // i及其儿子中堪为父者
        while (i != (j = properParent(nums, heapSize, i))) {
            swap(nums, i, j);
            i = j; // 继续下滤
        }
    }

    private int properParent(int[] nums, int heapSize, int i) {
        int properParent = i;
        int l = 2 * i + 1, r = l + 1;
        if (l < heapSize && nums[l] < nums[properParent]) {
            properParent = l;
        }
        if (r < heapSize && nums[r] < nums[properParent]) {
            properParent = r;
        }
        return properParent;
    }

    private void swap(int[] nums, int i, int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }

    public static void main(String[] args) {
        KSelect ks = new KSelect();
        System.out.println(ks.kSelect(new int[]{3,2,1,5,6,4}, 2));
        System.out.println(ks.kSelect_implementation2(new int[]{3,2,1,5,6,4}, 2));
    }
}
