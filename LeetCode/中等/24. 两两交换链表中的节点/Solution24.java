// https://leetcode.cn/problems/swap-nodes-in-pairs/

public class Solution24 {
    public ListNode swapPairs(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        ListNode left = head;
        ListNode right = head.next;
        ListNode ans = head.next;
        ListNode pBefore = null;
        while (left != null && right != null) {
            if (pBefore != null) {
                pBefore.next = right;
            }
            left.next = right.next;
            right.next = left;
            pBefore = left;
            left = left.next;
            right = left == null ? null : left.next;
        }
        return ans;
    }

    public ListNode swapPairs_implementation2(ListNode head) {
        if(head == null || head.next == null) return head;
        ListNode p = head, ans = head.next;
        ListNode left,right,pBefore = null;
        while(p != null && p.next != null){
            left = p;
            right = p.next;
            left.next = right.next;
            right.next = left;
            if(pBefore != null) pBefore.next = right;
            p = left.next;
            pBefore = left;
        }
        return ans;
    }

    public static void main(String[] args) {
        ListNode n1 = new ListNode(1);
        ListNode n2 = new ListNode(2);
        ListNode n3 = new ListNode(3);
        ListNode n4 = new ListNode(4);
        n1.next = n2;
        n2.next = n3;
        n3.next = n4;
        Solution24 solu = new Solution24();
        solu.swapPairs(n1);
        solu.swapPairs_implementation2(n2);
    }
}

class ListNode {
	int val;
	ListNode next;

	ListNode() {
	}

	ListNode(int val) {
		this.val = val;
	}

	ListNode(int val, ListNode next) {
		this.val = val;
		this.next = next;
	}
}