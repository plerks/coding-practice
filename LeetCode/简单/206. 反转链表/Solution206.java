/*
url: https://leetcode.cn/problems/reverse-linked-list
相关: LeetCode92. 反转链表 II
标签: 反转链表
*/

public class Solution206 {
    public ListNode reverseList(ListNode head) {
        if (head == null) return null;
        ListNode left, right, temp;
        left = head;
        right = head.next;
        head.next = null;
        // 反转left和right之间的边方向
        while (right != null) {
            temp = right.next;
            right.next = left;
            left = right;
            right = temp;
        }
        return left;
    }

    public static void main(String[] args) {
        Solution206 solu = new Solution206();
        ListNode node1 = new ListNode(1);
        ListNode node2 = new ListNode(2);
        node1.next = node2;
        System.out.println(solu.reverseList(node1).val);
    }
}
