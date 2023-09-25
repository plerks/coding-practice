/*
url: https://leetcode.cn/problems/lru-cache/?envType=daily-question&envId=2023-09-24
LeetCode参考: https://leetcode.cn/problems/lru-cache/solutions/259678/lruhuan-cun-ji-zhi-by-leetcode-solution/
标签: map + 双向链表, LinkedHashMap
*/

import java.util.HashMap;
import java.util.Map;

// 实现方式达不到题目要求的get和put都是O(1)，得自己控制双向链表才能达到O(1)，不过能过LeetCode
public class Solution146 {
    int capacity;
    Map<Integer, Node> map;
    DoubleLinkedList list;

    // 粘贴到LeetCode上需将这个方法名改为LRUCache
    public Solution146(int capacity) {
        this.capacity = capacity;
        this.map = new HashMap<>();
        this.list = new DoubleLinkedList();
    }

    public int get(int key) {
        if (map.containsKey(key)) {
            Node node = map.get(key);
            list.remove(node);
            list.addAsFirst(node); // 最近用过，将其移到最前
            return node.val;
        }
        else {
            return -1;
        }
    }

    public void put(int key, int value) {
        if (map.containsKey(key)) {
            Node node = map.get(key);
            list.remove(node);
            list.addAsFirst(node);
            node.val = value;
            return;
        }
        // 不存在key, 不需淘汰
        if (list.size() < capacity) {
            Node node = new Node(key, value);
            list.addAsFirst(node);
            map.put(key, node);
            return;
        }
        // 不存在key, 需要淘汰
        Node removed = list.removeLast();
        map.remove(removed.key);
        Node node = new Node(key, value);
        list.addAsFirst(node);
        map.put(key, node);
    }

    public static void main(String[] args) {
    }
}

class Node {
    Node prev;
    Node next;
    int key, val;

    public Node(int key, int val) {
        this.key = key;
        this.val = val;
    }
}

class DoubleLinkedList {
    Node dummyHead, dummyTail;
    private int size;

    public DoubleLinkedList() {
        this.dummyHead = new Node(-1, -1);
        this.dummyTail = new Node(-1, -1);
        dummyHead.next = dummyTail;
        dummyTail.prev = dummyHead;
        size = 0;
    }

    public void remove(Node node) {
        node.prev.next = node.next;
        node.next.prev = node.prev;
        size--;
    }

    public Node removeLast() {
        Node node = dummyTail.prev;
        this.remove(node);
        return node;
    }

    public void addAsFirst(Node node) { // 加到头部
        Node temp = dummyHead.next;
        dummyHead.next = node;
        node.prev = dummyHead;
        temp.prev = node;
        node.next = temp;
        size++;
    }

    public int size() {
        return this.size;
    }

}