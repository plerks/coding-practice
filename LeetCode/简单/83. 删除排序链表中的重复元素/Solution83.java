/*
url: https://leetcode.cn/problems/remove-duplicates-from-sorted-list/description/?envType=daily-question&envId=2024-01-14
相关: LeetCode26. 删除有序数组中的重复项, LeetCode82. 删除排序链表中的重复元素 II
标签: 双指针
*/

public class Solution83 {
    public ListNode deleteDuplicates(ListNode head) {
        if (head == null) return null;
        ListNode p1 = head;
        ListNode p2 = head.next;
        while (p2 != null) {
            if (p1.val != p2.val) {
                p1 = p1.next;
                p2 = p2.next;
            }
            else {
                p1.next = p2.next;
                p2 = p1.next;
            }
        }
        return head;
    }

    public static void main(String[] args) {
    }
}
