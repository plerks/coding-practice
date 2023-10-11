import java.util.HashSet;

public class BaseFormToCheckRepeat {
    public static void main(String[] args) {
        BaseFormToCheckRepeat o = new BaseFormToCheckRepeat();
        System.out.println(o.case1());
        System.out.println(o.case2());
    }

    public boolean case1() {
        int x = 5, y = 6;
        int[][] obstacles = new int[][]{{2, 5}, {3, 6}, {5, 6}, {7, 10}, {6, 2}};

        int n = 11; // n要大于坐标可取值的上界
        HashSet<Integer> set = new HashSet<>();
        for (int[] arr : obstacles) {
            set.add(arr[0] * n + arr[1]);
        }
        return set.contains(x * n + y);
    }

    public boolean case2() {
        int x = 5, y = 6;
        int[][] obstacles = new int[][]{{2, -5}, {-3, 6}, {5, 6}, {7, 10}, {-6, -2}};

        int n = 21; // 二维空间的点，n取2M + 1即可
        HashSet<Integer> set = new HashSet<>();
        for (int[] arr : obstacles) {
            set.add(arr[0] * n + arr[1]);
        }
        return set.contains(x * n + y);
    }
}