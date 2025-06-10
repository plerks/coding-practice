/*
url: https://leetcode.cn/problems/kth-missing-positive-number/
标签: 【题单】二分算法
*/

struct Solution1539;

impl Solution1539 {
    // 对于值x，其有个缺失数个数，找最后一个缺失数个数 <= k 的
    pub fn find_kth_positive(arr: Vec<i32>, k: i32) -> i32 {
        let n = arr.len() as i32;

        let check = |x: i32| {
            // 找arr中 <= x 的数的个数
            let cnt = match arr.binary_search(&x) {
                Ok(index) => index,
                Err(index) => index
            };

            // x - cnt 为缺的数的个数，不过x可能本身在arr中，要找最后一个缺失数个数 <= k 的
            // 例如 [2,3,4,7,11], 2 这个用例，x == 6，缺3个数，x == 5，缺2个数，x == 4也缺2个数，所以要找最后一个
            x - cnt as i32 <= k
        };
        
        let mut left = 1;
        let mut right = n + k;
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid) { left = mid + 1; }
            else { right = mid - 1; }
        }

        right
    }
}

fn main() {
    println!("{}", Solution1539::find_kth_positive([2,3,4,7,11].to_vec(), 5));
    println!("{}", Solution1539::find_kth_positive([2,3,4,7,11].to_vec(), 2));
}