// https://leetcode.cn/problems/merge-k-sorted-lists/

import java.util.PriorityQueue;

public class Solution23 {
    public ListNode mergeKLists(ListNode[] lists) {
        PriorityQueue<ListNode> pq = new PriorityQueue<>((x, y) -> {
            return x.val - y.val;
        });
        ListNode dummy = new ListNode();
        ListNode p = dummy;
        for (ListNode node : lists) {
            if (node != null) {
                pq.offer(node);
            }
        }
        while (!pq.isEmpty()) {
            ListNode node = pq.poll();
            p.next = node;
            p = p.next;
            if (node.next != null) {
                pq.offer(node.next);
            }
        }
        p = dummy.next;
        dummy.next = null;
        return p;
    }

    public static void main(String[] args) {
    }
}