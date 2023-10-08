

import java.util.ArrayList;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.TreeMap;
import java.util.Map.Entry;

public class commonDataStructure {
    public static void main(String[] args) {
        Deque<String> stack = new LinkedList<>();
        stack.push("a");
        stack.push("b");
        System.out.println("stack.pop(): " + stack.pop());

        Deque<String> queue = new LinkedList<>();
        queue.offer("a");
        queue.offer("b");
        System.out.println("queue.poll(): " + queue.poll());

        List<Integer> list = new ArrayList<>();
        list.add(5);
        list.add(6);
        list.add(3);
        list.add(7);
        list.add(1);
        list.sort((x ,y) -> {
            return x - y;
        });
        System.out.println("list: " + list);

        PriorityQueue<Integer> pq = new PriorityQueue<>((x, y) -> {
            return x - y;
        });
        pq.offer(6);
        pq.offer(3);
        System.out.println("pq.poll(): " + pq.poll());

        HashMap<String, String> map = new HashMap<>();
        map.put("Name1", "1");
        map.put("Name2", "2");
        for (Entry<String, String> e : map.entrySet()) {
            System.out.println(e.getKey() + ": " + e.getValue());
        }

        HashSet<String> set = new HashSet<>();
        set.add("dd");
        System.out.println(set.contains("dd"));

        /* LeetCode2034第一次用到TreeMap，是二叉搜索树的实现，具体底层是红黑树，
        相比HashMap其中的entry有二叉搜索树的序，LeetCode2034用到了firstKey()和lastKey()来获取最大和最小key
        */
        TreeMap<Integer, Integer> treeMap = new TreeMap<>();
        /* TreeMap<Integer, Integer> treeMapConstructWithComparator = new TreeMap<>((x, y) -> {
            return x - y;
        }); */
        treeMap.put(1, 3);
        treeMap.put(7, 3);
        treeMap.put(5, 8);
        System.out.println("treeMap.get(7): " + treeMap.get(7));
        System.out.println("treeMap.firstKey(): " + treeMap.firstKey());
        System.out.println("treeMap.lastKey(): " + treeMap.lastKey());
    }
}
