/*
url: https://leetcode.cn/problems/preimage-size-of-factorial-zeroes-function/
标签: 【题单】二分算法, 勒让德定理
*/

struct Solution793;

impl Solution793 {
    /* 勒让德定理，在n!的质因数分解中，质数p的幂次是 ⌊n/p⌋ + ⌊n/p^2⌋ + ⌊n/p^3⌋ + ⌊n/p^4⌋ + ⌊n/p^5⌋ + ...
    n!的末尾0的数量取决于因子10的数量，而10的数量取决于2和5的数量，所以用勒让德定理。
    由勒让德定理，2的因子数量一定 >= 5的数量，所以只考虑5的数量即可知道10的数量。
    要找x1和x2，使得 x1 为第一个因子数量 >= k，x2 为最后一个因子数量 <= k，再转化一下，
    第一个因子数量 >= k 用 最后一个 < k + 1 来求，再转化成 最后一个 <= k - 1，这样就只需要写一个check
    */
    pub fn preimage_size_fzf(k: i32) -> i32 {
        let k = k as i64;

        let check = |x, kk| {
            let mut p = 5;
            let mut cnt = 0; // x!中5的幂次的数量
            while x >= p {
                cnt += x / p;
                p *= 5;
            }
            cnt <= kk
        };

        let mut left = 0;
        let mut right = 5 * (k + 1);
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid, k - 1) { left = mid + 1; }
            else { right = mid - 1; }
        }
        let x1 = left;

        let mut left = 0;
        let mut right = 5 * (k + 1);
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid, k) { left = mid + 1; }
            else { right = mid - 1; }
        }
        let x2 = right;

        (x2 - x1 + 1) as i32
    }
}

pub fn main() {
    println!("{}", Solution793::preimage_size_fzf(0));
    println!("{}", Solution793::preimage_size_fzf(5));
    println!("{}", Solution793::preimage_size_fzf(3));
    println!("{}", Solution793::preimage_size_fzf(79));
}