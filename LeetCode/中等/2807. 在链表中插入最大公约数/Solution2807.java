// https://leetcode.cn/problems/insert-greatest-common-divisors-in-linked-list/description/?envType=daily-question&envId=2024-01-06

public class Solution2807 {
    public ListNode insertGreatestCommonDivisors(ListNode head) {
        ListNode ans = head;
        while (head != null && head.next != null) {
            int gcd = gcd(head.val, head.next.val);
            ListNode temp = head.next;
            ListNode gcdNode = new ListNode(gcd);
            head.next = gcdNode;
            gcdNode.next = temp;
            head = temp;
        }
        return ans;
    }

    private int gcd(int a, int b) {
        if (a < b) {
            int temp = a;
            a = b;
            b = temp;
        }
        while (a % b != 0) {
            int r = a % b;
            a = b;
            b = r;
        }
        return b;
    }

    public static void main(String[] args) {
        ListNode n1 = new ListNode(18);
        ListNode n2 = new ListNode(6);
        ListNode n3 = new ListNode(10);
        ListNode n4 = new ListNode(3);
        n1.next = n2;
        n2.next = n3;
        n3.next = n4;
        Solution2807 solu = new Solution2807();
        solu.insertGreatestCommonDivisors(n1);
    }
}
