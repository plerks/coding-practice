/*
url: https://leetcode.cn/problems/nth-magical-number/
标签: 【题单】二分算法, 容斥原理
*/

struct Solution878;

impl Solution878 {
    pub fn nth_magical_number(n: i32, a: i32, b: i32) -> i32 {
        let lcm = Self::lcm(a, b);

        // [1, k]是否有n个神奇数
        let check = |k| {
            let cnt = k / a as i64 + k / b as i64 - k / lcm;
            cnt < n as i64
        };

        let mut left = 1i64;
        let mut right = lcm * n as i64;
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid) { left = mid + 1; }
            else { right = mid - 1; }
        }
        const MOD: i64 = 1e9 as i64 + 7;
        (left % MOD) as i32
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
}

pub fn main() {
    println!("{}", Solution878::nth_magical_number(1, 2, 3));
    println!("{}", Solution878::nth_magical_number(1000000000, 39999, 40000));
}