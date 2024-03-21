/*
url: https://leetcode.cn/problems/frequency-tracker/description/?envType=daily-question&envId=2024-03-21
相关: LeetCode460. LFU 缓存
*/

import java.util.*;

// 这题和`LeetCode460. LFU 缓存`类似，要用两个map，特殊的是要用一个frequencyMap记录每种频率的出现次数
public class Solution2671 {
    Map<Integer, Integer> map1; // 存number, frequency
    Map<Integer, Integer> map2; // 存frequency, count(这个frequency出现几次)

    // 粘贴到LeetCode上把这个方法改名为FrequencyTracker
    public Solution2671() {
        this.map1 = new HashMap<>();
        this.map2 = new HashMap<>();
    }
    
    public void add(int number) {
        int oldFreq = 0;
        if (map1.containsKey(number)) {
            oldFreq = map1.get(number);
        }
        map1.put(number, oldFreq + 1);
        map2.merge(oldFreq, 0, (x, y) -> x - 1);
        map2.merge(oldFreq + 1, 1, (x, y) -> x + 1);
    }
    
    public void deleteOne(int number) {
        if (!map1.containsKey(number)) return;
        int freq = map1.get(number);
        if (freq == 1) {
            map1.remove(number);
        }
        else {
            map1.merge(number, 0, (x, y) -> x - 1);
        }
        map2.merge(freq, 0, (x, y) -> x - 1);
        map2.merge(freq - 1, 0, (x, y) -> x + 1);
    }
    
    public boolean hasFrequency(int frequency) {
        return map2.getOrDefault(frequency, 0) > 0;
    }
    
    public static void main(String[] args) {
        Solution2671 solu = new Solution2671();
        solu.add(3);
        solu.add(1);
        solu.add(3);
        solu.add(1);
        solu.deleteOne(10);
        solu.deleteOne(6);
        solu.add(7);
        solu.deleteOne(10);
        solu.add(1);
        solu.add(2);
        solu.add(3);
        solu.deleteOne(3);
        System.out.println(solu.hasFrequency(2));
    }
}
