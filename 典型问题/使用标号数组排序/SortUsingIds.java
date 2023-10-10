import java.util.Arrays;

public class SortUsingIds {
    public static void main(String[] args) {
        int[] studentIds = new int[]{20231010, 20231011, 20231012};
        int[] scores = new int[]{5, 9, 7};
        // 按某一属性排序返回另一属性序列。以上给出每个人的id对应的分数，要返回按分数从大到小排序后的id，直接办法是构造一个对象然后按对象的score属性排序再返回id属性，但可以不用构造对象

        int n = studentIds.length;
        Integer[] ids =  new Integer[n];
        for (int i = 0; i < n; i++) {
            ids[i] = i; // 需要一个标号数组
        }
        // 注意要调用Arrays.sort自定义比较器的方法时不能是int数组，得是对象数组，见/LeetCode/scratch/Arrays.sort()自定义比较器无法排序int[]的问题.java
        Arrays.sort(ids, (x, y) -> {
            return scores[y] - scores[x];
        });
        int[] ans = new int[n];
        for (int i = 0; i < n; i++) {
            ans[i] = studentIds[ids[i]]; // 如果studentIds原本就是0, 1, 2这里只需写ans[i] = ids[i];
        }
        System.out.println(Arrays.toString(ans));
    }
}
