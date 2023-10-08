/*
url: https://leetcode.cn/problems/stock-price-fluctuation/?envType=daily-question&envId=2023-10-08
LeetCode参考: https://leetcode.cn/problems/stock-price-fluctuation/solutions/1225718/gu-piao-jie-ge-bo-dong-by-leetcode-solut-rwrb/
标签: HashMap, TreeMap, 二叉搜索树, 红黑树
*/

import java.util.HashMap;
import java.util.TreeMap;

public class Solution2034 {
    // 获取最大最小值要用TreeMap(底层是红黑树)来获取，由于输入的记录可能有错，不是用min, max两个变量就能求最大最小，得完全记录
    int currentTime;
    HashMap<Integer, Integer> map1 = new HashMap<>(); // 记录key时间的价格value
    TreeMap<Integer, Integer> map2 = new TreeMap<>(); // 记录每个价格的出现，由于可能后续会发生修正，需要记录价格出现次数

    // 粘贴到LeetCode上要把这个方法名改成StockPrice
    public Solution2034() {
        map1 = new HashMap<>();
        map2 = new TreeMap<>();
        currentTime = -1;
    }
    
    public void update(int timestamp, int price) {
        if (!map1.containsKey(timestamp)) { // 非修正记录
            map1.put(timestamp, price);
            map2.put(price, map2.getOrDefault(price, 0) + 1);
            currentTime = Math.max(currentTime, timestamp);
        }
        else { // 是修正记录
            int oldPrice = map1.get(timestamp);
            map2.put(oldPrice, map2.get(oldPrice) - 1);
            if (map2.get(oldPrice) == 0) {
                map2.remove(oldPrice);
            }
            map1.put(timestamp, price);
            map2.put(price, map2.getOrDefault(price, 0) + 1);
        }
    }
    
    public int current() {
        return map1.get(currentTime);
    }
    
    public int maximum() {
        return map2.lastKey();
    }
    
    public int minimum() {
        return map2.firstKey();
    }

    public static void main(String[] args) {
    }
}