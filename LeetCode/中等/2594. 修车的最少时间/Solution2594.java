/*
url: https://leetcode.cn/problems/minimum-time-to-repair-cars/?envType=daily-question&envId=2023-09-07
LeetCode参考: https://leetcode.cn/problems/minimum-time-to-repair-cars/solutions/2177199/er-fen-da-an-pythonjavacgo-by-endlessche-keqf/
其它参考: https://en.cppreference.com/w/cpp/numeric/math/sqrt
相关: https://leetcode.cn/problems/search-insert-position/
标签: 二分查找
*/

public class Solution2594 {
    public long repairCars(int[] ranks, int cars) {
        int minR = Integer.MAX_VALUE;
        for (int r : ranks) minR = Math.min(minR, r);
        long upperBound = (long)minR * cars * cars;
        long left = 0, right = upperBound;
        while (left < right) {
            long mid = (left + right) / 2;
            if (getMaxRepair(ranks, mid) >= cars) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        return left;
    }

    private long getMaxRepair(int[] ranks, long time) {
        long sum = 0;
        for (int r : ranks) {
            // time时间能修的车辆数为根号下t/r
            /* 关于这里开方会不会因为精度问题导致错误，参考
            [相关讨论]<https://leetcode.cn/problems/minimum-time-to-repair-cars/solutions/2177199/er-fen-da-an-pythonjavacgo-by-endlessche-keqf/comments/1961767/>:
            
            <https://en.cppreference.com/w/cpp/numeric/math/sqrt>

            std::sqrt is required by the IEEE standard to be correctly rounded from the infinitely precise result.
            In particular, the exact result is produced if it can be represented in the floating-point type.
            
            文档的意思应该是指，在二进制以及浮点数位数有限的情况下，开根号虽然可能像根号2或者0.1一样，浮点数无法精确表示，但是每个二进制位
            是准确的，这里要的只是整数部分，因此取出来的整数部分一定是对的。
            */
            sum += Math.sqrt(time / r);
        }
        return sum;
    }

    public static void main(String[] args) {
        Solution2594 solu = new Solution2594();
        System.out.println(solu.repairCars(new int[]{4,2,3,1}, 10));
    }
}