/*
url: https://leetcode.cn/problems/peak-index-in-a-mountain-array/
相关: LeetCode1095. 山脉数组中查找目标值
标签: 【题单】二分算法
*/

struct Solution852;

impl Solution852 {
    pub fn peak_index_in_mountain_array(arr: Vec<i32>) -> i32 {
        let n = arr.len() as i32;
        // 搜索最后一个 arr[i - 1] < arr[i] 的位置i，区间从是到否
        let mut left = 0;
        let mut right = n;
        while left <= right {
            let mid = (left + right) / 2;
            if mid - 1 < 0 || arr[mid as usize - 1] < arr[mid as usize] { left = mid + 1; }
            else { right = mid - 1; }
        }
        right
    }

    pub fn peak_index_in_mountain_array_implementation2(arr: Vec<i32>) -> i32 {
        let n = arr.len() as i32;
        // 搜索最后一个 arr[i - 1] < arr[i] 的位置i，区间从是到否
        let mut left = 1; // 初始left取1，若山峰果真在arr[0]，最后right会为0
        let mut right = n;
        while left <= right {
            let mid = (left + right) / 2;
            if arr[mid as usize - 1] < arr[mid as usize] { left = mid + 1; }
            else { right = mid - 1; }
        }
        right
    }
}

fn main() {
    println!("{}", Solution852::peak_index_in_mountain_array([0,10,5,2].to_vec()));
    println!("{}", Solution852::peak_index_in_mountain_array_implementation2([0,10,5,2].to_vec()));
}