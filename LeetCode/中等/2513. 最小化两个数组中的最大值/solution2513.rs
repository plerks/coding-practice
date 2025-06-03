/*
url: https://leetcode.cn/problems/minimize-the-maximum-of-two-arrays/
参考: https://leetcode.cn/problems/minimize-the-maximum-of-two-arrays/solutions/2031827/er-fen-da-an-by-endlesscheng-y8fp/
标签: 【题单】二分算法, 容斥原理
*/

struct Solution2513;

impl Solution2513 {
    pub fn minimize_set(divisor1: i32, divisor2: i32, unique_cnt1: i32, unique_cnt2: i32) -> i32 {
        let check = |k| {
            let multiple1 = k / divisor1; // divisor1的倍数个数
            let multiple2 = k / divisor2; // divisor2的倍数个数
            let multiple_both = (k as i64 / Self::lcm(divisor1, divisor2)) as i32; // 同时为divisor1和divisor2的倍数的个数
            let multiple_all = multiple1 + multiple2 - multiple_both; // divisor1 或 divisor2的倍数的个数

            let cnt_both = k - multiple_all; // 两个arr都能放
            let cnt1 = k - multiple1 - cnt_both; // 只能放入arr1
            let cnt2 = k - multiple2 - cnt_both; // 只能放入arr2

            // 先放只能放一个盒子的，然后cnt_both填充剩余的
            return std::cmp::max(0, unique_cnt1 - cnt1) + std::cmp::max(0, unique_cnt2 - cnt2) <= cnt_both;
        };

        let mut left = 2;
        let mut right = i32::MAX as i64;
        while left <= right {
            let mid = (left + right) / 2;
            if !check(mid as i32) { left = mid + 1; }
            else { right = mid - 1; }
        }
        left as i32
    }

    fn gcd(mut x: i32, mut y: i32) -> i32 {
        while x % y != 0 {
            let r = x % y;
            x = y;
            y = r;
        }
        y
    }

    fn lcm(x: i32, y: i32) -> i64 {
        x as i64 * y as i64 / Self::gcd(x, y) as i64
    }

    // 参考灵茶题解，优化right的初值取值以及容斥部分的思路
    pub fn minimize_set_implementation2(divisor1: i32, divisor2: i32, unique_cnt1: i32, unique_cnt2: i32) -> i32 {
        let check = |k| {
            let lcm = Self::lcm(divisor1, divisor2);
            let divisor1 = divisor1 as i64;
            let divisor2 = divisor2 as i64;
            let unique_cnt1 = unique_cnt1 as i64;
            let unique_cnt2 = unique_cnt2 as i64;

            let cnt1 = k / divisor2 - k / lcm; // 只能放入arr1：不能被d1整除且能被d2整除
            let cnt2 = k / divisor1 - k / lcm; // 只能放入arr2
            let cnt_both = k - k / divisor1 - k / divisor2 + k / lcm; // 两个arr都能进：不能被d1整除且不能被d2整除 =  k - d1的倍数 - d2的倍数 + 多减的部分

            // 先放只能放一个盒子的，然后cnt_both填充剩余的
            return std::cmp::max(0, unique_cnt1 - cnt1) + std::cmp::max(0, unique_cnt2 - cnt2) <= cnt_both;
        };

        let mut left = 2;
        /* 这个二分的边界，参考灵茶题解，"二分上界可以取 (uniqueCnt1 + uniqueCnt2) * 2 - 1，因为最坏情况下 d1 = d2 = 2，只能取奇数" (2 <= divisor1, divisor2 <= 10^5)，
        所以需要 k 为 (uniqueCnt1 + uniqueCnt2) * 2 − 1。这种情况下，arr1和arr2可用的数最少，且二者不可用的数完全重合，不能错给另一方使用，
        看起来像是最坏情况。但是再从 std::cmp::max(0, unique_cnt1 - cnt1) + std::cmp::max(0, unique_cnt2 - cnt2) <= cnt_both 这个式子来看，
        这种情况左边取最大值，右边 cnt_both = k - ⌊k / d1⌋ - ⌊k / d2⌋ + ⌊k / lcm⌋ = k - ⌊k / 2⌋，但是 - ⌊k / d1⌋ - ⌊k / d2⌋ + ⌊k / lcm⌋
        当d1为2，d2为3时为 - k/2 - k/6 更小，右边没有取到最小值。这样看 d1 = d2 = 2 的情况不一定为上式最容易为false的情况，也就不一定为最坏情况。
        待做: 这里要严谨应该有点麻烦，或许可以做图辅助分析，要找(d1, d2)，使得不等号右边移过来后，左侧式子的值最大，然后要让k的取值范围有机会能使得<=成立。
        不过至少right取(uniqueCnt1 + uniqueCnt2) * 2 − 1运行是通过的。
        */
        let mut right = ((unique_cnt1 + unique_cnt2) * 2 - 1) as i64;
        while left <= right {
            let mid = (left + right) / 2;
            if !check(mid) { left = mid + 1; }
            else { right = mid - 1; }
        }
        left as i32
    }
}

pub fn main() {
    // println!("{}", Solution2513::minimize_set(2, 7, 1, 3));
    // println!("{}", Solution2513::minimize_set(2, 4, 8, 2));
    // println!("{}", Solution2513::minimize_set(6089, 2207, 873525, 545350));
    // println!("{}", Solution2513::minimize_set(2557, 15901, 805236426, 194763574));
    println!("{}", Solution2513::minimize_set(2, 5, 683651932, 161878530));

    // println!("{}", Solution2513::minimize_set_implementation2(2, 5, 683651932, 161878530));
    println!("{}", Solution2513::minimize_set_implementation2(92761, 48337, 208563424, 9115778));
}