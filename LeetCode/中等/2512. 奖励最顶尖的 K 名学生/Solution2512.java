/*
url: https://leetcode.cn/problems/reward-top-k-students/?envType=daily-question&envId=2023-10-11
标签: 使用标号数组排序, 多级条件排序
*/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;

public class Solution2512 {
    public List<Integer> topStudents(String[] positive_feedback, String[] negative_feedback, String[] report, int[] student_id, int k) {
        HashSet<String> positiveWords = new HashSet<>();
        HashSet<String> negativeWords = new HashSet<>();
        for (String s : positive_feedback) {
            positiveWords.add(s);
        }
        for (String s : negative_feedback) {
            negativeWords.add(s);
        }
        int n = report.length;
        int[] scores = new int[n];
        for (int i = 0; i < report.length; i++) {
            String[] arr = report[i].split(" ");
            for (int j = 0; j < arr.length; j++) {
                if (positiveWords.contains(arr[j])) {
                    scores[i] += 3;
                }
                if (negativeWords.contains(arr[j])) {
                    scores[i] -= 1;
                }
            }
        }
        Integer[] ids = new Integer[n];
        for (int i = 0; i < n; i++) {
            ids[i] = i;
        }
        Arrays.sort(ids, (x, y) -> {
            if (scores[x] == scores[y]) return student_id[x] - student_id[y]; // 同分数id小的在前
            return scores[y] - scores[x];
        });
        List<Integer> ans = new ArrayList<>(k);
        for (int i = 0; i < k; i++) {
            ans.add(student_id[ids[i]]);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2512 solu = new Solution2512();
        System.out.println(solu.topStudents(new String[]{"smart","brilliant","studious"}, new String[]{"not"}, new String[]{"this student is not studious","the student is smart"}, new int[]{1,2}, 2));
    }
}
