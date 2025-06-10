/*
url: https://leetcode.cn/problems/single-element-in-a-sorted-array/
标签: 【题单】二分算法, [special]
*/

struct Solution540;

impl Solution540 {
    /* 可以把所有num全异或一遍得到只出现一次的那个数，但是这题nums有序，能O(log n)
    找第一个相邻不相等的值x，ans出现之前，nums[偶] == nums[奇]，出现之后，nums[偶] != nums[奇]，
    ans本身出现在偶数下标位置。
    于是，找第一个 nums[i] != nums[i + 1]的偶数下标
    */
    pub fn single_non_duplicate(nums: Vec<i32>) -> i32 {
        let n = nums.len() as i32;
        let mut left: i32 = 0;
        let mut right: i32 = n / 2 - 1;
        while left <= right {
            let mid = (left + right) / 2;
            if 2 * mid + 1 < n && nums[2 * mid as usize] == nums[2 * mid as usize + 1] { left = mid + 1; }
            else { right = mid - 1; }
        }
        
        nums[left as usize * 2]
    }
}

fn main() {
    println!("{}", Solution540::single_non_duplicate([1,1,2,3,3,4,4,8,8].to_vec()));
    println!("{}", Solution540::single_non_duplicate([3,3,7,7,10,11,11].to_vec()));
    println!("{}", Solution540::single_non_duplicate([1].to_vec()));
    println!("{}", Solution540::single_non_duplicate([1,1,2].to_vec()));
    println!("{}", Solution540::single_non_duplicate([1,2,2,3,3].to_vec()));
}