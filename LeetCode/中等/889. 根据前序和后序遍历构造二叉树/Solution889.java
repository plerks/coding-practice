/*
url: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-postorder-traversal/description/?envType=daily-question&envId=2024-02-22
LeetCode参考: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-postorder-traversal/solutions/3550/gen-ju-qian-xu-he-hou-xu-bian-li-gou-zao-er-cha-sh/
              https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-postorder-traversal/solutions/2649218/tu-jie-cong-on2-dao-onpythonjavacgojsrus-h0o5/
相关: LeetCode105. 从前序与中序遍历序列构造二叉树, LeetCode106. 从中序与后序遍历序列构造二叉树
标签: 前序遍历, 先序遍历, 后序遍历
*/

public class Solution889 {
    public TreeNode constructFromPrePost(int[] preorder, int[] postorder) {
        TreeNode root = myConstructFromPrePost(preorder, postorder, 0, 0, preorder.length);
        return root;
    }

    /* preorder的第一个和postorder的最后一个一定相等，都是根，然后要区分左右子树的范围，也可以通过首尾相等的特点区分
    */
    private TreeNode myConstructFromPrePost(int[] preorder, int[] postorder, int p1, int p2, int length) {
        // p1，p2为树范围在preorder和postorder数组中的起点
        if (length == 0) return null;
        TreeNode root = new TreeNode(preorder[p1]);
        if (length == 1) return root;
        int leftRoot = preorder[p1 + 1];
        int leftLength = 1; // 左子树节点数
        while (postorder[p2 + leftLength - 1] != leftRoot) {
            leftLength++;
        }
        /* 这里默认preorder[p1 + 1]为左子树的根，从而可以通过在postorder中找preorder[p1 + 1]出现的位置知道左子树的size。
        当找出来leftLength < length时，说明root左右子树都有，此时preorder和postorder数组在左右子树对应范围内的元素集合一定是相同的，
        否则说明输入序列不合法。
        那么，既然两段对应的集合相同，是否一定能成功构造出子树？
        是，这可以递归证明，root的左右子树能否成功构造取决于使用新的preorder和postorder元素能否构造出一棵树，从而递归，最终递归基一定是
        能构造出树的。
        只知道先序和后序遍历重建树不唯一性体现在哪里？
        当找出来leftLength == length时，此时说明root只有一棵子树，可以选择为左或右子树，这种选择在递归构建树时可能多次发生，
        从而树可能有多种情况，这里的代码直接会为左子树。

        此外，灵茶山艾府的题解中有提到结论：如果二叉树的每个非叶节点都有两个儿子，知道前序和后序就能唯一确定这棵二叉树。
        */
        root.left = myConstructFromPrePost(preorder, postorder, p1 + 1, p2, leftLength);
        root.right = myConstructFromPrePost(preorder, postorder, p1 + 1 + leftLength, p2 + leftLength, length - 1 - leftLength);
        return root;
    }

    public static void main(String[] args) {
        Solution889 solu = new Solution889();
        System.out.println(solu.constructFromPrePost(new int[]{1,2,4,5,3,6,7}, new int[]{4,5,2,6,7,3,1}).val);
    }
}
