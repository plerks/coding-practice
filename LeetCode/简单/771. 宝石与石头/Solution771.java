// https://leetcode.cn/problems/jewels-and-stones/

import java.util.HashSet;

public class Solution771 {
    public int numJewelsInStones(String jewels, String stones) {
        HashSet<Character> set = new HashSet<>();
        for (int i = 0; i < jewels.length(); i++) {
            set.add(jewels.charAt(i));
        }
        int ans = 0;
        for (int i = 0; i < stones.length(); i++) {
            if (set.contains(stones.charAt(i))) {
                ans++;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution771 solu = new Solution771();
        System.out.println(solu.numJewelsInStones("aA", "aAAbbbb"));
    }
}