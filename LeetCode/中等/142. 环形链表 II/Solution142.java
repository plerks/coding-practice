// https://leetcode.cn/problems/linked-list-cycle-ii/

import java.util.HashSet;

public class Solution142 {
    public ListNode detectCycle(ListNode head) {
        HashSet<ListNode> set = new HashSet<>();
        ListNode p = head;
        while (p != null) {
            if (set.contains(p)) {
                return p;
            }
            else {
                set.add(p);
                p = p.next;
            }
        }
        return null;
    }

    public static void main(String[] args) {
    }
}