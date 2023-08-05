/*
url: https://leetcode.cn/problems/merge-two-sorted-lists/
LeetCode参考: https://leetcode.cn/problems/merge-two-sorted-lists/solutions/2373870/die-dai-by-csjerry-2uj5/
*/
public class Solution21 {
    public ListNode mergeTwoLists(ListNode list1, ListNode list2) {
        if (list1 == null) return list2;
        if (list2 == null) return list1;
        ListNode p1 = list1;
        ListNode p2 = list2;
        ListNode head, p;
        if (p1.val < p2.val) {
            head = p1;
            p = head;
            p1 = p1.next;
        }
        else {
            head = p2;
            p = head;
            p2 = p2.next;
        }
        while (p1 != null && p2 != null) {
            if (p1.val < p2.val) {
                p.next = p1;
                p = p.next;
                p1 = p1.next;
            }
            else {
                p.next = p2;
                p = p.next;
                p2= p2.next;
            }
        }
        if (p1 != null) p.next = p1;
        if (p2 != null) p.next = p2;
        return head;
    }

    public ListNode mergeTwoLists_implementation2(ListNode list1, ListNode list2) {
        // 参考<https://leetcode.cn/problems/merge-two-sorted-lists/solutions/2373870/die-dai-by-csjerry-2uj5/>，用dummy node，代码看起来整齐点
        if (list1 == null) return list2;
        if (list2 == null) return list1;
        ListNode dummy = new ListNode();
        ListNode p = dummy;
        while (list1 != null && list2 != null) {
            if (list1.val < list2.val) {
                p.next = list1;
                p = p.next;
                list1 = list1.next;
            }
            else {
                p.next = list2;
                p = p.next;
                list2 = list2.next;
            }
        }
        if (list1 != null) p.next = list1;
        if (list2 != null) p.next = list2;
        ListNode temp = dummy.next;
        dummy.next = null;
        return temp;
    }

    public static void main(String[] args) {
    }
}

class ListNode {
    int val;
    ListNode next;
    ListNode() {}
    ListNode(int val) { this.val = val; }
    ListNode(int val, ListNode next) { this.val = val; this.next = next; }
}