/*
url: https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/description/?envType=daily-question&envId=2024-01-15
标签: 双指针
相关: LeetCode26. 删除有序数组中的重复项, LeetCode83. 删除排序链表中的重复元素
*/

public class Solution82 {
    public ListNode deleteDuplicates(ListNode head) {
        if (head == null) return null;
        ListNode dummmyHead = new ListNode(-1);
        dummmyHead.next = head;
        ListNode p1 = head, p2 = head.next;
        ListNode p = dummmyHead; // p为上一个有效的节点
        while (p2 != null) {
            if (p1.val == p2.val) {
                while (p2 != null && p1.val == p2.val) {
                    p2 = p2.next;
                }
                p.next = p2; // 暂时让p.next = p2，但是p2能否被选出还不确定
                p1 = p2;
                p2 = (p1 == null) ? null : p1.next;
            }
            else {
                p.next = p1;
                p = p.next;
                p1 = p2;
                p2 = (p1 == null) ? null : p1.next;
            }
        }
        return dummmyHead.next;
    }

    public static void main(String[] args) {
    }
}
