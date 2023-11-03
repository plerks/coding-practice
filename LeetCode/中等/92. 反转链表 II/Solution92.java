/*
url: https://leetcode.cn/problems/reverse-linked-list-ii/
相关: LeetCode206. 反转链表
标签: 反转链表
*/

public class Solution92 {
    public ListNode reverseBetween(ListNode head, int left, int right) {
        ListNode ll = head, r = head; // 要操作的片段的第一个节点的前一个节点和要操作的片段的最后一个节点
        if (left == 1) {
            ll = null;
        }
        else {
            for (int i = 0; i < left - 2; i++) ll = ll.next;
        }
        for (int i = 0; i < right - 1; i++) r = r.next;
        ListNode l = (ll == null) ? head : ll.next;
        ListNode rr = r.next;
        ListNode node1 = l;
        ListNode node2 = l.next;
        ListNode temp;
        while (node2 != rr) {
            temp = node2.next;
            node2.next = node1;
            node1 = node2;
            node2 = temp;
        }
        if (ll != null) ll.next = r;
        l.next = rr;
        return ll == null ? r : head;
    }

    public static void main(String[] args) {
        Solution92 solu = new Solution92();
        ListNode node1 = new ListNode(5);
        System.out.println(solu.reverseBetween(node1, 1, 1).val);
    }
}
