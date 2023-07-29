// https://leetcode.cn/problems/linked-list-cycle/

import java.util.HashSet;

public class Solution141 {
    public boolean hasCycle(ListNode head) {
        // DFS
        if (head == null) {
            return false;
        }
        HashSet<ListNode> set = new HashSet<>();
        ListNode p = head;
        while (p.next != null) {
            if (set.contains(p.next)) {
                return true;
            }
            set.add(p.next);
            p = p.next;
        }
        return false;
    }

    public static void main(String[] args) {
        
    }
}

// 这题儿子最多只有一个，输入是单纯的链表
class ListNode {
    int val;
    ListNode next;
    ListNode(int x) {
        val = x;
        next = null;
    }
}