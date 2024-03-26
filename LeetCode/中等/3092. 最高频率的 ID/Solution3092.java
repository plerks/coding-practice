/*
url: https://leetcode.cn/problems/most-frequent-ids/description/
LeetCode参考: https://leetcode.cn/problems/most-frequent-ids/solutions/2704858/ha-xi-biao-you-xu-ji-he-pythonjavacgo-by-7brw/
标签: LeetCode第390场周赛, 双Map, 懒惰删除的优先队列, 懒惰删除
*/

import java.util.*;

// 此题属于我参加的LeetCode第390场周赛
public class Solution3092 {
    /* 周赛时写的暴力解法，562 / 622 个通过的测试用例，超时。
    当时的想法是，需要用一个map来存id是清晰的，然后关键是要快速求最大值，这符合优先队列的特征，但是优先队列又只能动头，
    不好更新元素出现频率，就放弃了这个思路。然后想着把map的value组织成TreeMap，类似LeetCode2671. 频率跟踪器和LeetCode460. LFU 缓存
    的做法，用第二个map查frequency，但是当时想错了，想成TreeMap的[K,V]是[frequency,id]了，然后这样id的频率变化时
    要去修改frequency就要顺序查找TreeMap去找value为id的节点，优化不了时间复杂度，frequency也有值重复的问题。这题不该没做出来，
    LeetCode2671是前几天的每日一题。
    */
    public long[] mostFrequentIDs_exceed_time_limit(int[] nums, int[] freq) {
        int n = nums.length;
        Map<Integer, Long> map = new HashMap<>();
        for (int num : nums) {
            map.put(num, 0L);
        }
        long[] ans = new long[n];
        for (int i = 0; i < n; i++) {
            int f = freq[i];
            map.put(nums[i], map.getOrDefault(nums[i], 0L) + f);
            long max = 0;
            for (long value : map.values()) {
                max = Math.max(max, value);
            }
            ans[i] = max;
        }
        return ans;
    }

    // 灵茶山艾府题解解法一，HashMap + TreeMap
    public long[] mostFrequentIDs(int[] nums, int[] freq) {
        int n = nums.length;
        Map<Integer, Long> map1 = new HashMap<>();
        for (int num : nums) {
            map1.put(num, 0L);
        }
        TreeMap<Long, Integer> map2 = new TreeMap<>();
        long[] ans = new long[n];
        for (int i = 0; i < n; i++) {
            int f = freq[i]; // freq[i] != 0
            int id = nums[i];
            long oldFreq = map1.get(id);
            long newFreq = oldFreq + f;
            if (map2.merge(oldFreq, -1, Integer::sum) == 0) {
                map2.remove(oldFreq);
            }
            map1.put(id, newFreq);
            map2.merge(newFreq, 1, Integer::sum);
            ans[i] = map2.lastKey();
        }
        return ans;
    }

    // 灵茶山艾府题解解法二，懒惰删除的优先队列
    public long[] mostFrequentIDs_implementation2(int[] nums, int[] freq) {
        int n = nums.length;
        Map<Integer, Long> map = new HashMap<>();
        PriorityQueue<long[]> q = new PriorityQueue<>((x, y) -> (x[1] > y[1]) ? -1 : 1);
        long[] ans = new long[n];
        for (int i = 0; i < n; i++) {
            int f = freq[i];
            int id = nums[i];
            long newFreq = map.merge(id, (long)f, Long::sum); // 更新频率
            q.offer(new long[]{id, newFreq});
            // 优先队列里存了[id,freq]，freq可能是过期的，而map是准确的，若堆顶的freq不匹配，一定是旧的直接删，若匹配，一定是合法且最大的
            while (!q.isEmpty() && q.peek()[1] != map.get((int)q.peek()[0])) { // 这里可以不用判断!q.isEmpty()
                q.poll();
            }
            ans[i] = q.peek()[1];
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution3092 solu = new Solution3092();
        System.out.println(Arrays.toString(solu.mostFrequentIDs(new int[]{2,3,2,1}, new int[]{3,2,-3,1})));
        System.out.println(Arrays.toString(solu.mostFrequentIDs_implementation2(new int[]{2,3,2,1}, new int[]{3,2,-3,1})));
    }
}
