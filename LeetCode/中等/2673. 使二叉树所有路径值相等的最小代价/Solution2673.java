/*
url: https://leetcode.cn/problems/make-costs-of-paths-equal-in-a-binary-tree/description/?envType=daily-question&envId=2024-02-28
LeetCode参考: https://leetcode.cn/problems/make-costs-of-paths-equal-in-a-binary-tree/solutions/2656293/shi-er-cha-shu-suo-you-lu-jing-zhi-xiang-65hk/
相关: LeetCode2846. 边权重均等查询
*/

public class Solution2673 {
    /* 我能分析出的是最后一层的兄弟节点必须调成相等，但是关键是可以
      1      2
     / \    / \
    2   2  1   1
    然后就不知道怎么处理了。这里关键要把值累加上去
    */
    public int minIncrements(int n, int[] cost) {
        int ans = 0;
        /* 兄弟节点的值必须调成相等，因为其往上的路径是相同的。
        当这一层的节点调好之后，相当于多棵子树的路径值调成相等，但是不同子树的和值不相等。
        因此将值加到根节点中，通过调整根的值把不同的和调成相等(若调叶子则兄弟节点都要改，不如调根)，直到所有子树都有同一个根时则所有路径的和相等
        */
        for (int i = n - 2; i > 0; i -= 2) { // i遍历所有左孩子
            ans += Math.abs(cost[i] - cost[i + 1]); // 把左右孩子变相等，变为的值可以选[left.val, right.val]中的任一值，开销都是相等的
            // 这里是max是因为题目只允许增加值，不允许减少，不然到底变为[left.val, right.val]中的哪一值，对上层会有区别
            cost[i / 2] += Math.max(cost[i], cost[i + 1]); // x=2i+1的父节点i可以通过x/2获得
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2673 solu = new Solution2673();
        System.out.println(solu.minIncrements(7, new int[]{1,5,2,2,3,3,1}));
    }
}
