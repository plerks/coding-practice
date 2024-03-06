/*
url: https://leetcode.cn/problems/escape-the-spreading-fire/?envType=daily-question&envId=2023-11-09
LeetCode参考: https://leetcode.cn/problems/escape-the-spreading-fire/solutions/1460794/er-fen-bfspythonjavacgo-by-endlesscheng-ypp1/
相关: 典型问题/最短路径问题/最短路径-bfs(针对边权全为1的图), 典型问题/有序范围内的二分查找
标签: 二分查找, bfs
*/

import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;

public class Solution2258 {
    int N = 301; // 题目2 <= m, n <= 300，用进制表示法，用一个整数来表示坐标
    int[][] DIRECTIONS = new int[][]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // 我只想到了用二分去测时间，但是不知道具体该怎么做
    public int maximumMinutes(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int left = 0, right = m * n; // m * n - 1足以让火传遍grid，若m * n - 1都可以逃脱，说明可以无限等待
        // 从左到右，搜索第一个不符合的位置(最小的不符合的位置)
        while (left < right) {
            int mid = (left + right) / 2;
            if (check(grid, mid)) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        // 由于单调性，区间呈现[符合 ... 不符合]的特征。(可能全为符合或不符合)
        /* 循环结束后，按理left应当为[0, m * n]内第一个不符合的位置，但与搜索数组内第一个大于某值的位置不同，第一个不符合的位置在[0, m*n]不一定存在，若存在，left准确
        地汇报了[0, m * n]内第一个不符合的位置，则left-1就是最后一个符合的位置。若第一个不符合的位置不存在，left最终会是m*n，注意这里若left最终为m*n，则left一定不是
        由于是第一个不符合的位置而被汇报出来的，因为根据问题情景若m*n是第一个不符合的位置，那m*n-1才应该是第一个不符合的位置，矛盾。则m*n是符合，说明永远符合。
        因此，由于存在性不满足，循环结束后，left为[0, m * n]内第一个不符合的位置这一性质也不满足。

        一种更好的看法是看left-1，搜索出来的left-1为[0, m * n)内最后一个符合的位置(若无符合的位置则为-1)，则若left - 1为m*n-1，说明m*n-1符合，说明永远符合。这里也
        体现了区间初始取值的重要性，初始的left必须是0，要让left-1能取到-1，初始的right必须>=m*n，因为只要探测到m*n-1符合，则[m*n-1, 正无穷]全部符合。

        更一般的，若初始left==x, right==y，则这个写法最后left-1为[x, y)内最后一个符合的位置(若无符合的位置则left-1为x-1)。
        */
        return left - 1 == m * n - 1 ? 1_000_000_000 : left - 1;
    
        // 这里二分搜索searchLast的闭区间写法:
        /* int left = 0, right = m * n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(grid, mid)) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        // 搜索出的left-1是[0, m*n-1]内最后一个符合的位置(若无符合的位置则left-1为x-1)。
        return left - 1 == m * n - 1? 1_000_000_000 : left - 1; */
    }

    // 检测等待time时间能否逃脱
    public boolean check(int[][] grid, int time) {
        int m = grid.length, n = grid[0].length;
        Deque<Integer> q1 = new LinkedList<>(); // 人的bfs
        Deque<Integer> q2 = new LinkedList<>(); // 火的bfs
        q1.offer(0 * N + 0); // 初始在(0, 0)位置
        boolean[][] onFire = new boolean[m][n]; // 要二分多次，不能直接在grid上修改记录着火点，否则下一次check时grid不是初始的grid
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    onFire[i][j] = true;
                    q2.offer(i * N + j);
                }
            }
        }
        // 等待时间让火扩散
        for (int i = 0; i < time; i++) {
            spreadFire(q2, onFire, grid);
        }
        if (onFire[0][0]) {
            return false; // 起点已经着火
        }
        boolean[][] visited = new boolean[m][n]; // 人能否在着火之前到相应的位置
        visited[0][0] = true;
        while (!q1.isEmpty()) {
            int size = q1.size();
            // 人bfs一层
            for (int i = 0; i < size; i++) {
                int coordinate = q1.poll();
                int x = coordinate / N;
                int y = coordinate % N;
                /* 注意这里是个关键点，对于check(new int[][]{{0,2,0,0,0,0,0},{0,0,0,2,2,1,0},{0,2,0,0,1,2,0},{0,0,2,2,2,0,2},{0,0,0,0,0,0,0}}, 4)，
                等待4分钟后，人第一步从第0行第0列走到第1行第0列，然后火会在人这次移动的同时烧到第1行第0列，若第1行第0列是安全屋则成功逃脱，但是不是，人虽然可以到这里但是不能再走，
                所以这里如果检测到onFire[x][y]，人是不能从这个位置再继续bfs的
                */
                if (onFire[x][y]) {
                    continue;
                }
                for (int[] arr : DIRECTIONS) {
                    int xx = x + arr[0];
                    int yy = y + arr[1];
                    if (xx >= 0 && xx < m && yy >= 0 && yy < n && !visited[xx][yy] && grid[xx][yy] == 0 && !onFire[xx][yy]) {
                        visited[xx][yy] = true;
                        if (xx == m - 1 && yy == n - 1) {
                            return true;
                        }
                        q1.offer(xx * N + yy);
                    }
                }
            }
            spreadFire(q2, onFire, grid);
        }
        return false;
    }

    public void spreadFire(Deque<Integer> q, boolean[][] onFire, int[][] grid) {
        int m = onFire.length, n = onFire[0].length;
        int size = q.size(); // 火扩散一圈
        for (int i = 0; i < size; i++) {
            int coordinate = q.poll();
            int x = coordinate / N;
            int y = coordinate % N;
            for (int[] arr : DIRECTIONS) {
                int xx = x + arr[0];
                int yy = y + arr[1];
                if (xx >= 0 && xx < m && yy >= 0 && yy < n && grid[xx][yy] == 0 && !onFire[xx][yy]) {
                    onFire[xx][yy] = true;
                    q.offer(xx * N + yy);
                }
            }
        }
    }

    public int maximumMinutes_implementation2(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[][] manTime = new int[m][n]; // 用bfs求人到每个点的最短时间
        for (int[] arr : manTime) {
            Arrays.fill(arr, -1); // 用值等于-1表示!visited，这样就不用专门有一个visited矩阵
        }
        manTime[0][0] = 0;
        Deque<Integer> q1 = new LinkedList<>();
        q1.offer(0 * N + 0);
        bfs(manTime, grid, q1);

        int[][] fireTime = new int[m][n]; // 用bfs求火到每个点的最短时间
        /* 若人比火先到某个点，则中途人不会被火烧到，否则火可以从烧到人的位置开始沿着人的路径走，火只会比人先到达那个点，矛盾。
        因此可以尝试让人等d = fireTime[m - 1][n - 1] - manTime[m - 1][n - 1]时间，这样人和火到安全屋的时间相等，但是相等并不一定可行，
        因为可能火与人同步，火烤着人在走。若不可行，则退回到d - 1，人比火先到安全屋，一定可行。
        */
        for (int[] arr : fireTime) {
            Arrays.fill(arr, -1);
        }
        Deque<Integer> q2 = new LinkedList<>();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    fireTime[i][j] = 0;
                    q2.offer(i * N + j);
                }
            }
        }
        bfs(fireTime, grid, q2);

        if (manTime[m - 1][n - 1] == -1) {
            return -1;
        }
        if (fireTime[m - 1][n - 1] == -1) {
            return 1_000_000_000;
        }
        if (manTime[m - 1][n - 1] > fireTime[m - 1][n - 1]) { // 火先到
            return -1;
        }
        int d = fireTime[m - 1][n - 1] - manTime[m - 1][n - 1];
        /* d >= 0，尝试让人等d时间，然后人与火同时到安全屋，这并不一定可行，可能火烤着人在走，需要判断人是否能比火先到[m-2][n-1]或[m-1][n-2]位置，若可以，
        则人可以等d时间前往[m-2][n-1]或[m-1][n-2]位置与火同时到达安全屋
        */
        if (d >= 0) {
            if (manTime[m - 2][n - 1] + d < fireTime[m - 2][n - 1] || manTime[m - 1][n - 2] + d < fireTime[m - 1][n - 2]) {
                return d;
            }
        }
        return d - 1;
    }

    public void bfs(int[][] time, int[][] grid, Deque<Integer> q) {
        int m = grid.length, n = grid[0].length;
        int t = 1;
        while (!q.isEmpty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                int coordinate = q.poll();
                int x = coordinate / N;
                int y = coordinate % N;
                for (int[] arr : DIRECTIONS) {
                    int xx = x + arr[0];
                    int yy = y + arr[1];
                    if (xx >= 0 && xx < m && yy >= 0 && yy < n && grid[xx][yy] == 0 && time[xx][yy] == -1) {
                        time[xx][yy] = t;
                        q.offer(xx * N + yy);
                    }
                }
            }
            t++;
        }
    }

    public static void main(String[] args) {
        Solution2258 solu = new Solution2258();
        System.out.println(solu.maximumMinutes(new int[][]{{0,2,0,0,0,0,0},{0,0,0,2,2,1,0},{0,2,0,0,1,2,0},{0,0,2,2,2,0,2},{0,0,0,0,0,0,0}}));
        // System.out.println(solu.check(new int[][]{{0,2,0,0,0,0,0},{0,0,0,2,2,1,0},{0,2,0,0,1,2,0},{0,0,2,2,2,0,2},{0,0,0,0,0,0,0}}, 4));
        System.out.println(solu.maximumMinutes_implementation2(new int[][]{{0,2,0,0,0,0,0},{0,0,0,2,2,1,0},{0,2,0,0,1,2,0},{0,0,2,2,2,0,2},{0,0,0,0,0,0,0}}));
    }
}
