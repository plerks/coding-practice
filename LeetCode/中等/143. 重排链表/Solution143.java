import java.util.ArrayList;
import java.util.List;

public class Solution143 {
    public void reorderList(ListNode head) {
        List<ListNode> list = new ArrayList<>();
        for (ListNode p = head; p != null;) {
            list.add(p);
            ListNode temp = p.next;
            p.next = null;
            p = temp;
        }
        ListNode p = head;
        for (int i = 0; i < list.size(); i++) {
            int n1 = i;
            int n2 = list.size() - 1 - i;
            if (n2 > n1) {
                list.get(n1).next = list.get(n2);
                if (list.get(n1) != head) {
                    p.next = list.get(n1);
                }
                p = list.get(n2);
            }
            else if (n2 == n1) {
                if (p != head) {
                    p.next = list.get(n1);
                }
            }
            else {
                break;
            }
        }
    }

    public static void main(String[] args) {
        /* ListNode n1 = new ListNode(1);
        ListNode n2 = new ListNode(2);
        ListNode n3 = new ListNode(3);
        ListNode n4 = new ListNode(4);
        n1.next = n2;
        n2.next = n3;
        n3.next = n4; */
        ListNode n1 = new ListNode(1);
        Solution143 solu = new Solution143();
        solu.reorderList(n1);
    }
}

class ListNode {
    int val;
    ListNode next;
    ListNode() {}
    ListNode(int val) { this.val = val; }
    ListNode(int val, ListNode next) { this.val = val; this.next = next; }
}