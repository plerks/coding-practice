/*
url: https://leetcode.cn/problems/avoid-flood-in-the-city/?envType=daily-question&envId=2023-10-13
LeetCode参考: https://leetcode.cn/problems/avoid-flood-in-the-city/solutions/2472026/bi-mian-hong-shui-fan-lan-by-leetcode-so-n5c9/
标签: 贪心, TreeSet, 二分搜索
*/

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.TreeSet;

public class Solution1488 {
    // 这个实现超时了
    public int[] avoidFlood_exceed_time_limit(int[] rains) {
        int n = rains.length;
        // 当某天不下雨时，应选择抽干未来最近要下雨的湖
        int[] ans = new int[n];
        HashSet<Integer> set = new HashSet<>(); // 装了水的湖
        for (int i = 0; i < n; i++) {
            if (rains[i] > 0) {
                if (set.contains(rains[i])){
                    return new int[0];
                }
                else {
                    ans[i] = -1;
                    set.add(rains[i]);
                }
            }
            else { // 从有水的湖中选择一个湖抽水
                if (set.isEmpty()) {
                    ans[i] = 1; // 没湖有水，选1号湖空抽
                }
                else {
                    int lake = -1;
                    for (int j = i + 1; j < n; j++) { // 这里耗时太大
                        if (set.contains(rains[j])) {
                            lake = rains[j];
                            break;
                        }
                    }
                    if (lake == -1) { // 有水的湖后面都不会下雨，选1号湖空抽，或者把lake初值直接定义为1
                        ans[i] = 1;
                    }
                    else {
                        ans[i] = lake;
                        set.remove(lake);
                    }
                }
            }
        }
        return ans;
    }

    public int[] avoidFlood(int[] rains) {
        // avoidFlood_exceed_time_limit()在晴天时往后检查已有水的湖在未来谁第一下雨开销太大，要改为在碰到当前湖要下雨时返回去找晴天日期抽它
        HashMap<Integer, Integer> map = new HashMap<>();
        TreeSet<Integer> set = new TreeSet<>(); // 也可以用ArrayList放晴天日期(list会有序)，然后自己写二分搜索找第一个>e的位置
        int[] ans = new int[rains.length];
        for (int i = 0; i < rains.length; i++) {
            if (rains[i] == 0) {
                ans[i] = 1; // 暂时记为抽1号湖的水
                // 记下这天晴天，后续可以用来回顾抽水
                set.add(i);
            }
            else {
                ans[i] = -1;
                if (map.containsKey(rains[i])) { // 这个湖已经有水
                    Integer sunnyDay = set.ceiling(map.get(rains[i])); // 找到这个湖上次下雨后的第一个晴天
                    if (sunnyDay == null) {
                        return new int[0];
                    }
                    else {
                        ans[sunnyDay] = rains[i]; // 这时候才决定之前的晴天抽哪个湖
                        set.remove(sunnyDay);
                    }
                }
                map.put(rains[i], i);
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1488 solu = new Solution1488();
        System.out.println(Arrays.toString(solu.avoidFlood(new int[]{1,2,0,0,2,1})));
    }
}