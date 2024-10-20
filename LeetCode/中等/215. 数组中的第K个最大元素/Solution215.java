/*
url: https://leetcode.cn/problems/kth-largest-element-in-an-array/description/
LeetCode参考: https://leetcode.cn/problems/kth-largest-element-in-an-array/solutions/307351/shu-zu-zhong-de-di-kge-zui-da-yuan-su-by-leetcode-/
相关: 典型问题/k选取, LeetCode462. 最小操作次数使数组元素相等 II, LeetCode295. 数据流的中位数, LeetCodeLCP 24. 数字游戏
标签: k选取, 快速排序, 堆
*/

// 这题的k和典型问题/k选取中的k有些不同，这里的k取1表示求nums最大的元素，那里k取1表示求nums排好序后的数组S的S[1]
// `LeetCode462. 最小操作次数使数组元素相等 II`使用到此题
public class Solution215 {
    /* 使用快速排序中的partition()，参考题解有说明，《算法导论》9.2：期望为线性的选择算法有推导，在随机数据的情况下期望时间复杂度为O(n)，
    这里这样写达不到。此外算法导论9.3有描述最坏情况为线性时间的选择算法，《数据结构(C++语言版)》-ISBN9787302330646 12.2.6节也有。 */
    public int findKthLargest(int[] nums, int k) {
        // 这题k取1，意思是第1个最大的元素，即为nums最大的元素。这里转换一下k，变为求排好序的nums中下标为k的元素。
        k = nums.length - k;
        int lo = 0, hi = nums.length - 1;
        while (lo < hi) {
            int i = lo, j = hi;
            int pivot = nums[lo];
            while (i < j) {
                /* 这里写成while (i < j && nums[j] >= pivot) j--; nums[i] = nums[j];
                while (i < j && nums[i] <= pivot) i++; nums[j] = nums[i];会超时，有个用例几乎
                全是1，会导致partition后轴点偏左或偏右，而不是偏向于二分，因此要采用如下写法。
                */
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
    public int findKthLargest_implementation2(int[] nums, int k) {
        int heapSize = nums.length;
        buildMaxHeap(nums, heapSize); // 大顶堆
        for (int i = 1; i < k; i++) {
            swap(nums, 0, heapSize - 1);
            heapSize--;
            percolateDown(nums, 0, heapSize);
        }
        return nums[0];
    }

    private void buildMaxHeap(int[] nums, int heapSize) {
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
        if (l < heapSize && nums[l] > nums[properParent]) {
            properParent = l;
        }
        if (r < heapSize && nums[r] > nums[properParent]) {
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
        Solution215 solu = new Solution215();
        System.out.println(solu.findKthLargest(new int[]{3,2,1,5,6,4}, 2));
        System.out.println(solu.findKthLargest_implementation2(new int[]{3,2,1,5,6,4}, 2));
    }
}
