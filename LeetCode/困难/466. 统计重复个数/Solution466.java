/*
url: https://leetcode.cn/problems/count-the-repetitions/description/
LeetCode参考: https://leetcode.cn/problems/count-the-repetitions/solutions/208874/tong-ji-zhong-fu-ge-shu-by-leetcode-solution/
标签: 循环节
*/

import java.util.*;

// 这题非常非常难，感觉和LeetCode2127. 参加会议的最多员工数那道基环内向树是同一档次的。这题我能想到的只有应该是要找s1和s2的特征联系。
public class Solution466 {
    public int getMaxRepetitions(String s1, int n1, String s2, int n2) {
        Map<Integer, int[]> recall = new HashMap<>();
        int s1Count = 0, s2Count = 0, index = 0;
        int[] preLoop = new int[2];
        int[] inLoop = new int[2];
        /* 找循环节，对于一个s1，其能最多匹配到s2中index-1位置的字符，若之前已经出现这种情况，则这之间的s1和s2配对方式就会是循环的。
        只要s2中的字符在s1中都出现，只要n1够大，一定能找到这种匹配，因为一轮s1下来一定会以一个index匹配结束，而index只能取0~s2.length()-1
        的值，只要经过|s2|+1轮s1，由鸽笼原理index一定会重复。

        recall表并未记录在s1中的位置，是否有可能两次index匹配的位置在s1中不一样？也即，通过recall表找到了两次index重复，但是这两次对应在s1中的匹配位置不同？
        否，第一次将一个index加入recall表时，s2[0, index - 1]的字符都在s1中，而s2[index]位置的字符c会在下一个s1中第一个c出现的位置匹配，
        而下一次要将index加入recall表也是这种情况，因此两次在s1中对应的位置一定是相同的。
        */
        while (true) {
            s1Count++;
            // 反复用一轮s1匹配s2
            for (int i = 0; i < s1.length(); i++) {
                if (s1.charAt(i) == s2.charAt(index)) {
                    index++;
                }
                if (index == s2.length()) {
                    s2Count++;
                    index = 0;
                }
            }
            // 找循环节的过程已经把S1遍历完了，无需再关注循环节，此时在s1Count个s1中找到了s2Count个s2
            if (s1Count == n1) {
                return s2Count / n2;
            }
            // 此时用完一轮s1，s2在index位置找到匹配，也可能整个s1都无法与s2中的一个字符匹配上，说明s2的这个字符在s1中没有出现，也就没有循环节。这种情况相当于循环节只消耗s1，不消耗s2。
            if (recall.containsKey(index)) { // 找到循环节
                preLoop[0] = recall.get(index)[0];
                preLoop[1] = recall.get(index)[1];
                inLoop[0] = s1Count - preLoop[0];
                inLoop[1] = s2Count - preLoop[1];
                // 先是preLoop[0]个s1, preLoop[1]个s2启动，然后inLoop[0]个s1，inLoop[1]个s2循环。preLoop[1]<=preLoop[0], inLoop[1]<=inLoop[0]
                break;
            }
            else recall.put(index, new int[]{s1Count, s2Count});
        }

        int totals2InS1Count = preLoop[1] + (n1 - preLoop[0]) / inLoop[0] * inLoop[1];

        int rests1Count = (n1 - preLoop[0]) % inLoop[0];
        // 某尾还剩一些s1, 末尾还能匹配上s2，只是匹配不了一个完整的循环节

        for (int i = 0; i < rests1Count; i++) {
            for (int j = 0; j < s1.length(); j++) {
                if (s1.charAt(j) == s2.charAt(index)) {
                    index++;
                }
                if (index == s2.length()) {
                    totals2InS1Count++;
                    index = 0;
                }
            }
        }
        return totals2InS1Count / n2;
    }

    public static void main(String[] args) {
        Solution466 solu = new Solution466();
        // System.out.println(solu.getMaxRepetitions("acb", 4, "ab", 2));
        // System.out.println(solu.getMaxRepetitions("aaa", 3, "aa", 1));

        /* 对这类s2的字符未在s1中全部出现的情况，一轮s1下来会发现index还是为0，一个s2中的字符都匹配不上，
        相当于循环节只消耗s1，不消耗s2。还有种情况是("abcd", 3, "ay", 2)，一轮下来index为1，但是s2Count为0，也是不消耗s2
        */
        // System.out.println(solu.getMaxRepetitions("abcd", 3, "xy", 2));

        System.out.println(solu.getMaxRepetitions("abaacdbac", 100, "adcbd", 4));
    }
}
