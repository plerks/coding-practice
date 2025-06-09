/*
url: https://leetcode.cn/problems/find-k-th-smallest-pair-distance/
相关: LeetCode373. 查找和最小的 K 对数字
标签: 【题单】二分算法
*/

struct Solution719;

impl Solution719 {
    pub fn smallest_distance_pair(mut nums: Vec<i32>, k: i32) -> i32 {
        let n = nums.len();
        nums.sort();

        // 距离<=x的数对的个数是否 < k，返回第一个使回答为是的x。（第一个左侧有k个数对的x）
        let check = |x| {
            let mut j = 0;
            let mut cnt = 0;
            // 双指针
            for i in 0..n {
                while j < n && nums[j] - nums[i] <= x {
                    j += 1;
                }
                // [i + 1, j)
                cnt += j - i - 1;
            }
            cnt < k as usize
        };
        
        let mut left = 0;
        let mut right = nums.last().unwrap() - nums.first().unwrap();
        while left <= right {
            let mid = (left + right) / 2;
            if check(mid) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        left
    }
}

pub fn main() {
    println!("{}", Solution719::smallest_distance_pair([1,6,1].to_vec(), 3));
}