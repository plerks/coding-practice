/*
url: https://leetcode.cn/problems/closest-nodes-queries-in-a-binary-search-tree/description/?envType=daily-question&envId=2024-02-24
LeetCode参考: https://leetcode.cn/problems/closest-nodes-queries-in-a-binary-search-tree/solutions/2645284/er-cha-sou-suo-shu-zui-jin-jie-dian-cha-vp6p2/
标签: 二分查找
*/

import java.util.*;

public class Solution2476 {
    // 34 / 35 个通过的测试用例，超时。题目没说给的二叉搜索树是平衡的。
    public List<List<Integer>> closestNodes(TreeNode root, List<Integer> queries) {
        List<List<Integer>> ans = new ArrayList<>();
        for (int x : queries) {
            int a = -1;
            TreeNode node = root;
            while (node != null) {
                if (node.val == x) {
                    a = x;
                    break;
                }
                else if (node.val > x) {
                    node = node.left;
                }
                else {
                    a = node.val;
                    node = node.right;
                }
            }
            int b = -1;
            node = root;
            while (node != null) {
                if (node.val == x) {
                    b = x;
                    break;
                }
                else if (node.val > x) {
                    b = node.val;
                    node = node.left;
                }
                else {
                    node = node.right;
                }
            }
            ans.add(Arrays.asList(a, b));
        }
        return ans;
    }

    // 参考题解，题目没说给的二叉搜索树是平衡的，所以直接在树上搜索时间复杂度不是logn，直接先遍历一遍弄成数组，然后二分查找
    public List<List<Integer>> closestNodes_implementation2(TreeNode root, List<Integer> queries) {
        List<Integer> list = new ArrayList<>();
        inorder(root, list);
        List<List<Integer>> ans = new ArrayList<>();
        for (int x : queries) {
            int a = -1, b = -1;
            int aIndex = searchLastSmallerOrEqual(list, x);
            if (aIndex > -1) {
                a = list.get(aIndex);
                if (list.get(aIndex) == x) {
                    b = a;
                }
                else if (aIndex < list.size() - 1) {
                    b = list.get(aIndex + 1); // 若不能取到等于x，则first >= x的位置为last <= x的位置 + 1
                }
            }
            else { // a == -1
                b = list.get(0);
            }
            ans.add(Arrays.asList(a, b));
        }
        return ans;
    }

    private int searchLastSmallerOrEqual(List<Integer> list, int x) {
        int left = 0, right = list.size() - 1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (list.get(mid) <= x) {
                left = mid + 1;
            }
            else right = mid - 1;
        }
        return left - 1;
    }

    private void inorder(TreeNode root, List<Integer> list) {
        if (root == null) return;
        inorder(root.left, list);
        list.add(root.val);
        inorder(root.right, list);
    }

    public static void main(String[] args) {
        Solution2476 solu = new Solution2476();
        System.out.println(solu.closestNodes(new TreeNode(6, new TreeNode(2), new TreeNode(13)), Arrays.asList(2,5,6)));
        System.out.println(solu.closestNodes_implementation2(new TreeNode(6, new TreeNode(2), new TreeNode(13)), Arrays.asList(2,5,6)));
    }
}
