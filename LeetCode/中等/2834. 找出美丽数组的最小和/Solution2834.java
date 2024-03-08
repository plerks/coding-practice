// https://leetcode.cn/problems/find-the-minimum-possible-sum-of-a-beautiful-array/description/?envType=daily-question&envId=2024-03-08

public class Solution2834 {
    public int minimumPossibleSum(int n, int target) {
        /* 从小的开始选，若选择了x，则target-x不能出现，应当选x和target-x中的较小者出现。
        x==target-x的位置在x=target/2处，这个数可以选。然后从target-1右边开始选
        */
        final int MOD = (int)1e9 + 7;
        int x = 1;
        long ans = 0;
        while (x <= n && target - x >= x) {
            ans += x;
            x++;
        }
        int count = x - 1; // count为已选出的数个数
        x = target;
        while (count < n) {
            ans += x;
            count++;
            x++;
        }
        return (int)(ans % MOD);
    }

    // 根据上面的分析，可以直接套公式算
    public int minimumPossibleSum_implementation2(int n, int target) {
        final int MOD = (int)1e9 + 7;
        long ans = 0;
        long bound = target / 2;
        if (bound >= n) { // [1, target / 2]的数够用，选[1, n]
            return (int)((1 + (long)n) * n / 2 % MOD);
        }
        else { // [1, target / 2] + [target, target + n - bound)
            // 这里注意(long)target + target + n得把target转成long，否则对1000000000, 1000000000这个用例target + target + n会溢出
            ans = ((1 + bound) * bound / 2 + ((long)target + target + n - bound - 1) * (n - bound) / 2) % MOD;
            return (int)ans;
        }
    }

    public static void main(String[] args) {
        Solution2834 solu = new Solution2834();
        System.out.println(solu.minimumPossibleSum(2, 3));
        System.out.println(solu.minimumPossibleSum_implementation2(2, 3));
        System.out.println(solu.minimumPossibleSum_implementation2(13, 50));
        System.out.println(solu.minimumPossibleSum_implementation2(1000000000, 1000000000));
    }
}
