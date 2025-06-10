/*
url: https://leetcode.cn/problems/find-in-mountain-array/
相关: LeetCode852. 山脉数组的峰顶索引, LeetCode153. 寻找旋转排序数组中的最小值
标签: 【题单】二分算法
*/

struct Solution1095;

struct MountainArray {
    nums: Vec<i32>
}

impl MountainArray {
    fn get(&self, index:i32)->i32 {
        self.nums[index as usize]
    }

    fn length(&self)->i32 {
        self.nums.len() as i32
    }
}

impl Solution1095 {
    pub fn find_in_mountain_array(target: i32, mountain_arr: &MountainArray) -> i32 {
        let n = mountain_arr.length();

        let index = Self::peak_index_in_mountain_array(mountain_arr);

        let ans = Self::bin_search1(mountain_arr, target, 0, index);
        if ans != -1 { return ans; }

        let ans = Self::bin_search2(mountain_arr, target, index + 1, n - 1);
        if ans != -1 { return ans; }

        -1
    }

    // LeetCode852. 山脉数组的峰顶索引，找到山峰位置然后分左右二分两次
    fn peak_index_in_mountain_array(mountain_arr: &MountainArray) -> i32 {
        let n = mountain_arr.length() as i32;
        let mut left = 1;
        let mut right = n;
        while left <= right {
            let mid = (left + right) / 2;
            if mountain_arr.get(mid - 1) < mountain_arr.get(mid) { left = mid + 1; }
            else { right = mid - 1; }
        }
        right
    }

    // 二分查找第一个 >= target 的位置，区间从否到是
    fn bin_search1(mountain_arr: &MountainArray, target: i32, mut left: i32, mut right: i32) -> i32 {
        while left <= right {
            let mid = (left + right) / 2;
            if mountain_arr.get(mid) < target { left = mid + 1; }
            else { right = mid - 1; }
        }
        if left < mountain_arr.length() as i32 && mountain_arr.get(left) == target { left } else { -1 }
    }

    // 二分查找第一个 <= target 的位置，区间从否到是
    fn bin_search2(mountain_arr: &MountainArray, target: i32, mut left: i32, mut right: i32) -> i32 {
        while left <= right {
            let mid = (left + right) / 2;
            if !(mountain_arr.get(mid) <= target) { left = mid + 1; }
            else { right = mid - 1; }
        }
        if left < mountain_arr.length() as i32 && mountain_arr.get(left) == target { left } else { -1 }
    }
}

fn main() {
    let mountain_arr = MountainArray { nums: vec![1,2,3,4,5,3,1] };
    println!("{}", Solution1095::find_in_mountain_array(3, &mountain_arr));

    let mountain_arr = MountainArray { nums: vec![0,1,2,4,2,1] };
    println!("{}", Solution1095::find_in_mountain_array(3, &mountain_arr));

    let mountain_arr = MountainArray { nums: vec![1, 5, 2] };
    println!("{}", Solution1095::find_in_mountain_array(2, &mountain_arr))
}