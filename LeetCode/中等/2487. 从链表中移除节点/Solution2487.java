/*
url: https://leetcode.cn/problems/remove-nodes-from-linked-list/?envType=daily-question&envId=2024-01-03
LeetCode参考: https://leetcode.cn/problems/remove-nodes-from-linked-list/solutions/2587737/cong-lian-biao-zhong-yi-chu-jie-dian-by-z53sr/
标签: 单调栈
*/

import java.util.Deque;
import java.util.LinkedList;

public class Solution2487 {
    // 使用单调栈
    public ListNode removeNodes(ListNode head) {
        Deque<ListNode> stack = new LinkedList<>();
        while (head != null) {
            while (!stack.isEmpty() && stack.peek().val < head.val) {
                stack.pop();
            }
            stack.push(head);
            head = head.next;
        }
        ListNode dummyHead = new ListNode(0);
        while (!stack.isEmpty()) {
            ListNode node = stack.pop();
            node.next = dummyHead.next;
            dummyHead.next = node;
        }
        return dummyHead.next;
    }

    // 官方题解的递归做法
    public ListNode removeNodes_recursive(ListNode head) {
        if (head == null) return null;
        head.next = removeNodes_recursive(head.next);
        if (head.next != null && head.next.val > head.val) {
            return head.next;
        }
        return head;
    }

    // 官方题解的解法，其实也是从单调递减上考虑
    public ListNode removeNodes_implementation2(ListNode head) {
        Deque<ListNode> stack = new LinkedList<>();
        ListNode p = head;
        while (p != null) {
            stack.push(p);
            p = p.next;
        }
        p = new ListNode(0); // p充当dummyHead
        while (!stack.isEmpty()) {
            ListNode node = stack.pop();
            if (p.next == null || node.val >= p.next.val) {
                node.next = p.next;
                p.next = node;
            }
        }
        return p.next;
    }

    /* 官方题解的另外一种解法，先反转，然后让链表单调递增，然后再反转回来。
    为什么不能直接摘节点让链表单调递减，即removeNodes_wrong()为什么不行？ 因为原链表中最后一个节点一定会保留，因为其右侧无比自己大的节点，
    所以可以把链表反转过来然后从单增考虑，但是第一个节点不一定还在，removeNodes_wrong()对[5,2,13,3,8]会给出[5,2]的错误结果
    */
    public ListNode removeNodes_implementation3(ListNode head) {
        head = reverse(head);
        ListNode p = head;
        while (p.next != null) {
            if (p.next.val < p.val) {
                p.next = p.next.next;
            }
            else p = p.next;
        }
        return reverse(head); // head是第一个节点，一定不会被摘掉
    }

    private ListNode reverse(ListNode head) {
        ListNode p1 = head;
        ListNode p2 = head.next;
        while (p2 != null) {
            ListNode temp = p2.next;
            p2.next = p1;
            p1 = p2;
            p2 = temp;
        }
        head.next = null;
        return p1;
    }

    public ListNode removeNodes_wrong(ListNode head) {
        ListNode dummyHead = new ListNode(Integer.MAX_VALUE);
        dummyHead.next = head;
        ListNode p = head;
        while (p.next != null) {
            if (p.next.val > p.val) {
                p.next = p.next.next;
            }
            else p = p.next;
        }
        return dummyHead.next;
    }

    public static void main(String[] args) {
        Solution2487 solu = new Solution2487();
        ListNode n1 = new ListNode(5);
        ListNode n2 = new ListNode(2);
        ListNode n3 = new ListNode(13);
        ListNode n4 = new ListNode(3);
        ListNode n5 = new ListNode(8);
        n1.next = n2;
        n2.next = n3;
        n3.next = n4;
        n4.next = n5;
        System.out.println(solu.removeNodes(n1).val);
    }
}
