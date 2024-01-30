/*
url: https://leetcode.cn/problems/minimum-seconds-to-equalize-a-circular-array/description/?envType=daily-question&envId=2024-01-30
LeetCode参考: https://leetcode.cn/problems/minimum-seconds-to-equalize-a-circular-array/solutions/2614614/shi-xun-huan-shu-zu-suo-you-yuan-su-xian-1bfa/
              https://leetcode.cn/problems/minimum-seconds-to-equalize-a-circular-array/solutions/2374938/ba-wen-ti-kan-cheng-shi-kuo-san-yuan-su-jddr9/
相关: LeetCode849. 到最近的人的最大距离, LeetCode514. 自由之路, 典型问题/到最近的x的最大距离, 典型问题/到最近的x的所有距离
*/

import java.util.*;

public class Solution2808 {
    // 我的做法，570 / 579 个通过的测试用例，超时。思路和LeetCode514. 自由之路中我的做法很像。
    public int minimumSeconds(List<Integer> nums) {
        HashSet<Integer> set = new HashSet<>();
        for (int val : nums) set.add(val);
        int ans = Integer.MAX_VALUE;
        for (int val : set) {
            int[] numArr = new int[nums.size()];
            for (int i = 0; i < nums.size(); i++) {
                numArr[i] = nums.get(i);
            }
            ans = Math.min(ans, calc(numArr, val));
        }
        return ans;
    }

    private int calc(int[] nums, int x) {
        // 让nums中的所有元素都变成x，需要知道每个非x的元素离x的最短距离，从而可以知道x传播到其所需的时间
        int n = nums.length;
        int[] disL = new int[n]; // disL[i]表示i号位置向左走到x的最短距离
        if (nums[0] == x) {
            disL[0] = 0;
        }
        else {
            for (int i = n - 1; i > 0; i--) {
                if (nums[i] == x) {
                    disL[0] = n - 1 - i + 1;
                    break;
                }
            }
        }
        for (int i = 1; i < n; i++) {
            disL[i] = nums[i] == x ? 0 : disL[i - 1] + 1; // 若i位置上已经是x，则距离为0，否则要先走到i - 1位置再走向x
        }
        int[] disR = new int[n];
        if (nums[n - 1] == x) {
            disR[n - 1] = 0;
        }
        else {
            for (int i = 0; i < n - 1; i++) {
                if (nums[i] == x) {
                    disR[n - 1] = i + 1;
                    break;
                }
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            disR[i] = nums[i] == x ? 0 : disR[i + 1] + 1;
        }
        int max = 0;
        for (int i = 0; i < n; i++) {
            max = Math.max(max, Math.min(disL[i], disR[i]));
        }
        return max;
    }

    /* 这里计算距离类似LeetCode849. 到最近的人的最大距离，但是问题是这里数组是环形的。
    但是只需改成记录x出现的位置，然后按顺序枚举相邻的出现位置，然后单独计算一次首尾出现位置的距离即可（或者在出现位置的列表末尾再增加一个n+首次出现index）。
    这题和LeetCode514. 自由之路有点像，我想起来了LeetCode849. 到最近的人的最大距离这道题，也想到可能需要
    换个思路记录x出现的位置，但是没想到怎么处理数组循环的问题。
    */
    public int minimumSeconds_implementation2(List<Integer> nums) {
        HashMap<Integer, List<Integer>> pos = new HashMap<>();
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int num = nums.get(i);
            pos.computeIfAbsent(num, key -> new ArrayList<>()).add(i);
        }
        int ans = Integer.MAX_VALUE;
        for (List<Integer> list : pos.values()) {
            int max = n - (list.get(list.size() - 1) - list.get(0)); // (list.get(list.size() - 1) - list.get(0))是顺着走，两条路互补，总长度为n
            for (int i = 1; i < list.size(); i++) {
                max = Math.max(max, list.get(i) - list.get(i - 1));
            }
            ans = Math.min(ans, max / 2);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2808 solu = new Solution2808();
        System.out.println(solu.minimumSeconds(Arrays.asList(2,1,3,3,2)));
        System.out.println(solu.minimumSeconds_implementation2(Arrays.asList(8,13,3,3)));
    }
}
