/*
url: https://leetcode.cn/problems/lfu-cache/description/?envType=daily-question&envId=2023-09-25
LeetCode参考: https://leetcode.cn/problems/lfu-cache/solutions/186348/lfuhuan-cun-by-leetcode-solution/
相关: LeetCode2671. 频率跟踪器
标签: 双Map + 双向链表
*/

import java.util.HashMap;

public class Solution460 {
    int capacity;
    HashMap<Integer, Node> keyMap;
    HashMap<Integer, DoubleLinkedList> freqMap;
    int minFreq;

    // 粘贴到LeetCode上需要把这个方法名改为LFUCache
    public Solution460(int capacity) {
        this.capacity = capacity;
        this.keyMap = new HashMap<>();
        this.freqMap = new HashMap<>();
        this.minFreq = 0;
    }
    
    public int get(int key) {
        if (keyMap.containsKey(key)) {
            Node node = keyMap.get(key);
            freqMap.get(node.freq).remove(node);
            if (freqMap.get(node.freq).size() == 0) {
                if (minFreq == node.freq) {
                    minFreq += 1;
                }
                freqMap.remove(node.freq);
            }
            node.freq++;
            if (!freqMap.containsKey(node.freq)) {
                freqMap.put(node.freq, new DoubleLinkedList());
            }
            freqMap.get(node.freq).addAsFirst(node);
            return node.val;
        }
        return -1;
    }
    
    public void put(int key, int value) {
        if (keyMap.containsKey(key)) {
            Node node = keyMap.get(key);
            node.val = value;
            freqMap.get(node.freq).remove(node);
            if (freqMap.get(node.freq).size() == 0) {
                if (minFreq == node.freq) {
                    minFreq += 1;
                }
                freqMap.remove(node.freq);
            }
            node.freq++;
            if (!freqMap.containsKey(node.freq)) {
                freqMap.put(node.freq, new DoubleLinkedList());
            }
            freqMap.get(node.freq).addAsFirst(node);
            return;
        }
        // 不存在key，不需淘汰
        if (keyMap.size() < capacity) {
            Node node = new Node(key, value, 1);
            keyMap.put(key, node);
            if (!freqMap.containsKey(1)) {
                freqMap.put(1, new DoubleLinkedList());
            }
            freqMap.get(1).addAsFirst(node);
            minFreq = 1;
            return;
        }
        // 不存在key，需要淘汰
        else {
            Node node = new Node(key, value, 1);
            keyMap.put(key, node);
            DoubleLinkedList list = freqMap.get(minFreq);
            keyMap.remove(list.removeLast().key); // 同频率，删除最久未使用的
            if (!freqMap.containsKey(1)) {
                freqMap.put(1, new DoubleLinkedList());
            }
            freqMap.get(1).addAsFirst(node);
            minFreq = 1;
        }
    }

    public static void main(String[] args) {
        Solution460 solu = new Solution460(2);
        solu.put(1, 1);
        solu.put(2, 2);
        System.out.println(solu.get(1));
        solu.put(3, 3);
        System.out.println(solu.get(2));
        System.out.println(solu.get(3));
        solu.put(4, 4);
        System.out.println(solu.get(1));
        System.out.println(solu.get(3));
        System.out.println(solu.get(4));
    }
}

class Node {
    Node prev;
    Node next;
    int key, val, freq;

    public Node(int key, int val, int freq) {
        this.key = key;
        this.val = val;
        this.freq = freq;
    }
}

class DoubleLinkedList {
    Node dummyHead, dummyTail;
    private int size;

    public DoubleLinkedList() {
        this.dummyHead = new Node(-1, -1, -1);
        this.dummyTail = new Node(-1, -1, -1);
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