/*
url: https://leetcode.cn/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/description/
LeetCode参考: https://leetcode.cn/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/solutions/150225/mian-shi-ti-33-er-cha-sou-suo-shu-de-hou-xu-bian-6/
其它参考: https://zhuanlan.zhihu.com/p/689913816
相关: LeetCode331. 验证二叉树的前序序列化, LeetCode449. 序列化和反序列化二叉搜索树, LeetCode106. 从中序与后序遍历序列构造二叉树, LeetCode946. 验证栈序列
标签: 后序遍历, 二叉搜索树, 验证栈混洗
*/

import java.util.*;

public class SolutionLCR152 {
    // 容易想到的递归解法，但是这里对postorder数组会反复读
    public boolean verifyTreeOrder(int[] postorder) {
        return verifyBinSearchTree(postorder, 0, postorder.length);
    }

    private boolean verifyBinSearchTree(int[] postorder, int left, int right) { // 检验[left,right)范围内这棵树是否是二叉搜索树
        // postorder中无重复数字，不然如果节点值和根的值相等还得讨论在左子树还是右子树
        int n = right - left; // 节点数
        if (n <= 1) return true;
        int root = postorder[right - 1]; // 根节点值
        int lr = left; // 左子树右端点
        while (lr < right && postorder[lr] < root) {
            lr++;
        }
        // 左子树范围为[left, index)，且现在postorder[index] > root
        int rr = lr; // 右子树右端点
        while (rr < right && postorder[rr] > root) {
            rr++;
        }
        // 现在[index,rr)的值大于root，rr必须是right-1，否则意味着右子树区间右边又开始有小于root的，非二叉搜索树。通过这里能保证root大于左子树小于右子树
        return rr == right - 1 && verifyBinSearchTree(postorder, left, lr) && verifyBinSearchTree(postorder, lr, rr);
    }

    /* 这题有一个想法是类似`LeetCode449. 序列化和反序列化二叉搜索树`，对二叉搜索树，直接对后序遍历排序就可以得到中序遍历，于是
    就可以考虑从中序和后序遍历重建二叉树，即`LeetCode106. 从中序与后序遍历序列构造二叉树`，但是发现对于后序[4,5,6,8,9]，中序
    [4,9,6,5,8]，那里的代码会正常结束，但重建出一棵错误的树，且代码结束时inorderIndex!=0。(注意，不能用inorderIndex是否为0判断重建的树是否正确，
    因为对后序[5,4,3,2,1]，中序[1,2,3,4,5]，会重建出正确的树，且代码结束时inorderIndex!=0）。这样一来，似乎就只能在建树之后再去
    中序和后序遍历一遍确认是否重建出了正确的树，不过可能还有用例会导致while循环里inorderIndex为负，代码不能正常运行的，总之，LeetCode106
    的代码只适用于输入序列保证是树的中序和后序遍历的情况。这题不适合用LeetCode106的代码解。
    */
    public boolean verifyTreeOrder_wrong(int[] postorder) {
        int[] inorder = postorder.clone();
        Arrays.sort(inorder);
        return buildTree(inorder, postorder);
    }

    public boolean buildTree(int[] inorder, int[] postorder) {
	    Deque<TreeNode> stack = new LinkedList<>();
		TreeNode root = new TreeNode(postorder[postorder.length - 1]);
		stack.push(root);
		int inorderIndex = inorder.length - 1;
		TreeNode node = root;
		for (int i = postorder.length - 2; i >= 0; i--) {
			if (node.val != inorder[inorderIndex]) { // 最右侧通路
				node.right = new TreeNode(postorder[i]);
				node = node.right;
				stack.push(node);
			}
			else {
				// 回退到第一个有左子树的节点
				while (!stack.isEmpty() && stack.peek().val == inorder[inorderIndex]) {
					node = stack.pop();
					inorderIndex--;
				}
				node.left = new TreeNode(postorder[i]);
				node = node.left;
				stack.push(node);
			}
		}
		return inorderIndex == 0; // 这里是错的，inorderIndex最终是否为0和重建的树是否正确没有必然关系
	}

    /* 参考题解，这里的过程大概可以这样理解，首先，代码过程和重建树差不多，后序倒过来看是根-右-左，从构建最右侧通路开始看，
    在构建最右侧通路的过程中数值会逐渐增大，root也会更新，而当构建完最右侧通路后，下一个访问的会是某个左子树的根，这时就要知道这棵左子树
    是接在哪里的（也即其root），这时就要发挥单调栈的作用，通过单调栈找到最右侧通路中最后一个大于postorder[i]的节点root（
    再下一个是小于postorder[i]，是更上面的节点），postorder[i]是root的左子树的根，然后就又变成构建最右侧通路的子问题。
    验证是否为二叉搜索树的关键在于验证这个左子树的最右侧通路的值是否都小于其父亲（root），最右侧通路构建的过程保证
    了下一节点是大于上一节点的（否则会触发退栈），一旦触发退栈，这时就会通过`if (postorder[i] > root) return false;`检验
    出左子树的根节点值是否小于root。总结起来，若没触发退栈，则过程在构建最右侧通路，这时会检测右儿子值是否大于root，若触发
    退栈，退栈会找到现在要构建哪个root的左子树，并检验root的值是否大于左子树根节点的值，这样对每个节点，都会确认一遍
    node.left.val < node.val < node.right.val，这样就可以证明是二叉搜索树。
    */
    // 这题如果改成验证二叉搜索树的前序遍历序列，只需对应改成构建最左侧通路即可
    public boolean verifyTreeOrder_implementation2(int[] postorder) {
        Deque<Integer> stack = new LinkedList<>();
        int root = Integer.MAX_VALUE;
        for (int i = postorder.length - 1; i >= 0; i--) {
            if (postorder[i] > root) return false;
            while (!stack.isEmpty() && stack.peek() > postorder[i]) { // 单调递增的栈
                root = stack.pop();
            }
            stack.push(postorder[i]);
        }
        return true;
    }

    // 参考<https://zhuanlan.zhihu.com/p/689913816>，后序遍历序列对应中序遍历序列的栈混洗，由于是二叉搜索树，对postorder排序即可得到中序遍历
    public boolean verifyTreeOrder_implementation3(int[] postorder) {
        int[] inorder = postorder.clone();
        Arrays.sort(inorder);
        Deque<Integer> stack = new LinkedList<>();
        int n = inorder.length;
        for (int i = 0, j = 0; i < n; i++) {
            stack.push(inorder[i]);
            while (!stack.isEmpty() && stack.peek() == postorder[j]) {
                stack.pop();
                j++;
            }
        }
        return stack.isEmpty();
    }

    public static void main(String[] args) {
        SolutionLCR152 solu = new SolutionLCR152();
        System.out.println(solu.verifyTreeOrder(new int[]{4,9,6,5,8}));
        System.out.println(solu.verifyTreeOrder(new int[]{4,6,5,9,8}));
        System.out.println(solu.verifyTreeOrder(new int[]{5,4,3,2,1}));
        System.out.println(solu.verifyTreeOrder_wrong(new int[]{5,4,3,2,1}));
        System.out.println(solu.verifyTreeOrder_implementation2(new int[]{1,3,2,6,5}));
        System.out.println(solu.verifyTreeOrder_implementation2(new int[]{1,2,5,10,6,9,4,3}));
        System.out.println(solu.verifyTreeOrder_implementation3(new int[]{1,2,5,10,6,9,4,3}));
    }
}
