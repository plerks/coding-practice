/*
url: https://leetcode.cn/problems/range-sum-query-mutable/?envType=daily-question&envId=2023-11-13
其它参考: https://oi-wiki.org/ds/fenwick/
LeetCode参考: https://leetcode.cn/problems/range-sum-query-mutable/solutions/1393053/-by-hu-ge-8-t4rn/
              https://leetcode.cn/problems/range-sum-query-mutable/solutions/1389182/qu-yu-he-jian-suo-shu-zu-ke-xiu-gai-by-l-76xj/
              https://leetcode.cn/problems/range-sum-query-mutable/solutions/1394254/by-fenjue-ewfb/
标签: 树状数组, 线段树, 模板, 兼顾求前缀和与更新
*/

// 暴力法update()开销为O(1)，sumRange()为O(right-left)。用前缀和update()开销为O(n-left)(需要更新前缀和)，sumRange()为O(1)。用前缀和不能优化

// 用树状数组实现，这个树状数组的数据结构，代码很简单，但是技巧性很强

public class Solution307 {
    int[] c;
    int[] nums;

    // 粘贴到LeetCode上把这个方法名改为NumArray
    public Solution307(int[] nums) {
        this.nums = nums;
        this.c = new int[nums.length + 1]; // 树状数组下标不能等于0, 否则会进入死循环, 所以树状数组通常使用的下标会执行+1操作
        for (int i = 1; i <= nums.length; i++) {
            c[i] += nums[i - 1];
            if (i + lowBit(i) <= nums.length) c[i + lowBit(i)] += c[i];
        }
    }
    
    public void update(int index, int val) {
        add(index + 1, val - nums[index]);
        nums[index] = val;
    }
    
    public int sumRange(int left, int right) {
        return prefixSum(right + 1) - prefixSum(left);
    }

    private void add(int index, int val) {
        while (index < c.length) {
            c[index] += val;
            index += lowBit(index);
        }
    }

    private int prefixSum(int index) {
        int sum = 0;
        while (index > 0) {
            sum += c[index];
            index -= lowBit(index); // c[x]记录的是nums(x-lowBit(x), x]间的和，即从nums[x]开始往前的lowBit(x)个数的和
        }
        return sum;
    }

    private int lowBit(int x) {
        return x & -x; // 关于x & -x为什么会取出2^k(k为最后一个1的位置)，见我的LeetCode260. 只出现一次的数字 III中的注释
    }

    public static void main(String[] args) {
        Solution307 solu = new Solution307(new int[]{1,3,5});
        System.out.println(solu.sumRange(0, 2));
        solu.update(1, 2);
        System.out.println(solu.sumRange(0, 2));
    }
}
