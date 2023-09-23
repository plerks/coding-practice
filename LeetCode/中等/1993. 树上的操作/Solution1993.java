// https://leetcode.cn/problems/operations-on-tree/?envType=daily-question&envId=2023-09-23

import java.util.ArrayList;
import java.util.List;

public class Solution1993 {
    TreeNode1993[] nodes;

    // 粘贴到LeetCode上要把这个构造函数名改为LockingTree
    public Solution1993(int[] parent) {
        int n = parent.length;
        this.nodes = new TreeNode1993[n];
        for (int i = 0; i < n; i++) {
            nodes[i] = new TreeNode1993(i);
        }
        for (int i = 0; i < n; i++) {
            if (parent[i] != -1) {
                nodes[parent[i]].children.add(nodes[i]);
                nodes[i].parent = nodes[parent[i]];
            }
        }
    }
    
    public boolean lock(int num, int user) {
        if (nodes[num].islocked) return false;
        nodes[num].islocked = true;
        nodes[num].user = user;
        return true;
    }
    
    public boolean unlock(int num, int user) {
        if (nodes[num].islocked && nodes[num].user == user) {
            nodes[num].islocked = false; // 不用更新user
            return true;
        }
        return false;
    }
    
    public boolean upgrade(int num, int user) {
        TreeNode1993 node = nodes[num];
        boolean condition1 = !node.islocked;
        boolean condition2 = false;
        for (TreeNode1993 val : node.children) {
            if (dfsChecklock(val)) {
                condition2 = true;
                break;
            }
        }
        boolean condition3 = true;
        TreeNode1993 parent = node.parent;
        while (parent != null) {
            if (parent.islocked) {
                condition3 = false;
                break;
            }
            parent = parent.parent;
        }
        if (condition1 && condition2 && condition3) {
            node.islocked = true;
            node.user = user;
            for (TreeNode1993 val : node.children) {
                dfsUnlock(val);
            }
            return true;
        }
        return false;
    }

    private boolean dfsChecklock(TreeNode1993 root) {
        if (root.islocked) return true;
        for (TreeNode1993 node : root.children) {
            if (dfsChecklock(node)) {
                return true;
            }
        }
        return false;
    }

    private void dfsUnlock(TreeNode1993 root) {
        if (root == null) return;
        root.islocked = false;
        for (TreeNode1993 node : root.children) {
            dfsUnlock(node);
        }
    }

    public static void main(String[] args) {
        Solution1993 solu = new Solution1993(new int[]{-1, 0, 0, 1, 1, 2, 2});
        System.out.println(solu.lock(2, 2));
        System.out.println(solu.unlock(2, 2));
        System.out.println(solu.unlock(2, 3));
        System.out.println(solu.lock(4, 5));
        System.out.println(solu.upgrade(0, 1));
        System.out.println(solu.lock(0, 1));
    }
}

class TreeNode1993 {
    int val;

    TreeNode1993 parent;

    List<TreeNode1993> children;

    boolean islocked;

    int user;

    TreeNode1993(int val) {
        this.val = val;
        this.parent = null;
        this.children = new ArrayList<>();
        this.islocked = false;
        this.user = -1;
    }
}