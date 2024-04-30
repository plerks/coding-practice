

import java.util.ArrayList;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.TreeMap;
import java.util.TreeSet;
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
        map.merge("Name1", "3", (x, y) -> x + y);
        System.out.println("map.get(\"Name1\"): " + map.get("Name1"));

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

        // LeetCode1488. 避免洪水泛滥第一次用到TreeSet，底层使用了TreeMap
        TreeSet<Integer> treeSet = new TreeSet<>();
        // TreeSet<Integer> treeSetConstructWithComparator = new TreeSet<>((x, y) -> x - y);
        treeSet.add(1);
        treeSet.add(5);
        treeSet.add(7);
        System.out.println("treeSet.first(): " + treeSet.first());
        System.out.println("treeSet.last(): " + treeSet.last());
        // first >=。"Returns the least element in this set greater than or equal to the given element, or null if there is no such element."
        System.out.println("treeSet.ceiling(0): " + treeSet.ceiling(0));
        // last <=。"Returns the greatest element in this set less than or equal to the given element, or null if there is no such element."
        System.out.println("treeSet.floor(5): " + treeSet.floor(5));
        /* 元素从小到大排，position(first >= x) == position(last <= x)或者position(first >= x) == position(last <= x) + 1，
        符合ceil在floor之上的关系。TreeMap对应的方法是ceilingEntry()和floorEntry()。 */
    }
}
