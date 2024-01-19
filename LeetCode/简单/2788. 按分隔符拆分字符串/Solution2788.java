// https://leetcode.cn/problems/split-strings-by-separator/description/?envType=daily-question&envId=2024-01-20

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution2788 {
    public List<String> splitWordsBySeparator(List<String> words, char separator) {
        // 这里separator仅仅是一个字符而非字符串，所以简单
        List<String> ans = new ArrayList<>();
        for (String s : words) {
            int lo = 0;
            for (int i = 0; i < s.length(); i++) {
                if (s.charAt(i) == separator) {
                    if (i - lo > 0) {
                        ans.add(s.substring(lo, i));
                    }
                    lo = i + 1;
                }
            }
            if (s.length() - lo > 0) ans.add(s.substring(lo));
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2788 solu = new Solution2788();
        System.out.println(Arrays.toString(solu.splitWordsBySeparator(Arrays.asList("$easy$","$problem$"), '$').toArray()));
    }
}
