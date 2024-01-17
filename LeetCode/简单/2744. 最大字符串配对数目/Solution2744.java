// https://leetcode.cn/problems/find-maximum-number-of-string-pairs/description/?envType=daily-question&envId=2024-01-17

import java.util.HashSet;

public class Solution2744 {
    public int maximumNumberOfStringPairs(String[] words) {
        HashSet<String> set = new HashSet<>();
        int ans = 0;
        for (String s : words) {
            if (set.contains(new StringBuilder(s).reverse().toString())) {
                ans++;
            }
            set.add(s);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2744 solu = new Solution2744();
        System.out.println(solu.maximumNumberOfStringPairs(new String[]{"cd","ac","dc","ca","zz"}));
    }
}
