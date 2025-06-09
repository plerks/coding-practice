/*
url: https://leetcode.cn/problems/ugly-number-iii/
标签: 【题单】二分算法, 容斥原理
*/

struct Solution1201;

impl Solution1201 {
    pub fn nth_ugly_number(n: i32, a: i32, b: i32, c: i32) -> i32 {
        let n = n as i64;
        let a = a as i64;
        let b = b as i64;
        let c = c as i64;

        let ab = Self::lcm(a, b);
        let ac = Self::lcm(a, c);
        let bc = Self::lcm(b, c);
        let abc = Self::lcm(a, Self::lcm(b, c));

        let check = |x: i64| {
            let mut cnt = 0;
            cnt += x / a + x / b + x / c - x / ab - x / bc - x / ac + x / abc;
            cnt < n as i64
        };

        let mut left = 1;
        let mut right = 2 * 1e9 as i64; // 本题结果在 [1, 2 * 10^9] 的范围内，不这样这里写abc * n会爆i64
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        left as i32
    }

    fn gcd(mut x: i64, mut y: i64) -> i64 {
        while x % y != 0 {
            let r = x % y;
            x = y;
            y = r;
        }
        y
    }

    fn lcm(x: i64, y: i64) -> i64 {
        x as i64 * y as i64 / Self::gcd(x, y) as i64
    }
}

pub fn main() {
    println!("{}", Solution1201::nth_ugly_number(3, 2, 3, 5));
    println!("{}", Solution1201::nth_ugly_number(1000000000, 2, 740091218, 473796308));
}