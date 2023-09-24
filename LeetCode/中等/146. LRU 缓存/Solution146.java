/*
url: https://leetcode.cn/problems/lru-cache/?envType=daily-question&envId=2023-09-24
LeetCode参考: https://leetcode.cn/problems/lru-cache/solutions/259678/lruhuan-cun-ji-zhi-by-leetcode-solution/
标签: map + 双向链表, LinkedHashMap
*/

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

// 实现方式达不到题目要求的get和put都是O(1)，得自己控制双向链表才能达到O(1)，不过能过LeetCode
public class Solution146 {
    List<int[]> buffer; // 数组0为key, 1为value
    int capacity;
    Map<Integer, int[]> map;

    // 粘贴到LeetCode上需将这个方法名改为LRUCache
    public Solution146(int capacity) {
        this.capacity = capacity;
        buffer = new LinkedList<>();
        this.map = new HashMap<>();
    }

    public int get(int key) {
        if (map.containsKey(key)) {
            int[] temp = map.get(key);
            buffer.remove(temp); // 这里没法O(1)，得自己控制双向链表才能达到O(1)
            buffer.add(temp); // 最近用过，将其移到最后
            map.put(temp[0], temp);
            return temp[1];
        }
        else {
            return -1;
        }
    }

    public void put(int key, int value) {
        if (map.containsKey(key)) {
            int[] temp = map.get(key);
            buffer.remove(temp);
            temp[1] = value;
            buffer.add(temp);
            return;
        }
        // 不存在key, 不需淘汰
        if (buffer.size() < capacity) {
            int[] newCache = new int[]{key, value};
            buffer.add(newCache);
            map.put(key, newCache);
            return;
        }
        // 不存在key, 需要淘汰
        int[] removed = buffer.remove(0);
        map.remove(removed[0]);
        int[] newCache = new int[]{key, value};
        buffer.add(newCache);
        map.put(key, newCache);
    }

    public static void main(String[] args) {
    }
}