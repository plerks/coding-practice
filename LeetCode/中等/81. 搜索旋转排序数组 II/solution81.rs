/*
url: https://leetcode.cn/problems/search-in-rotated-sorted-array-ii/
参考: https://leetcode.cn/problems/search-in-rotated-sorted-array-ii/solutions/705486/gong-shui-san-xie-xiang-jie-wei-he-yuan-xtam4/
相关: LeetCode153. 寻找旋转排序数组中的最小值, LeetCode154. 寻找旋转排序数组中的最小值 II
标签: 【题单】二分算法, [mark], [special]
*/

struct Solution81;

impl Solution81 {
    // 此题前置题目LeetCode154，此题也允许nums元素重复
    // 参考宫水三叶题解，用LeetCode154的代码将最小值的位置直接找出来，然后二分两次
    // 有重复元素时间复杂度是O(n)的
    pub fn search(nums: Vec<i32>, target: i32) -> bool {
        let n = nums.len();
        let mut left = 0;
        let mut right = n as i32 - 1;
        while left < right && nums[right as usize] == nums[0] { right -= 1; } // 剪掉右边相等的值，这样第二段严格低于第一段
        let bound = nums[right as usize];
        let edge = right;
        while left <= right {
            let mid = (left + right) / 2;
            if !(nums[mid as usize] <= bound) { left = mid + 1; }
            else { right = mid - 1; }
        }
        let index = left; // index左右两侧都单增

        // index为最小值所在的位置，两侧都是单增的(虽然不一定严格单增，不过够了)。两次二分
        let ans = Self::binary_search(&nums, target, 0, index - 1);
        if ans < n as i32 && nums[ans as usize] == target { return true; }

        let ans = Self::binary_search(&nums, target, index, edge);
        if ans < n as i32 && nums[ans as usize] == target { return true; }

        false
    }

    // 返回第一个 >= target 的值的位置
    fn binary_search(nums: &Vec<i32>, target: i32, mut left: i32, mut right: i32) -> i32 {
        while left <= right {
            let mid = (left + right) / 2;
            if !(nums[mid as usize] >= target) { left = mid + 1; }
            else { right = mid - 1; }
        }
        left
    }

    // 参考官方题解，不使用LeetCode154找最小值位置，剪掉右边部分后，直接在“两段分别单增，且第二段严格小于第一段的区间”上二分一次，不用两次二分
    // 时间复杂度也是O(n)的
    pub fn search_implementation2(nums: Vec<i32>, target: i32) -> bool {
        let n = nums.len();
        let mut l = 0;
        let mut r = n as i32 - 1;
        while l < r && nums[r as usize] == nums[0] { r -= 1; } // 剪掉右边相等的值，这样第二段严格低于第一段

        // 直接在[0, right]上二分找target，这个区间两段分别单增，且第二段严格小于第一段
        while l <= r {
            let mid = (l + r) / 2;
            if nums[mid as usize] == target { return true; }
            // [l, r]一开始是包含折点的，二分过程中可能变成不包含了，但是能找到单增的部分
            if nums[l as usize] <= nums[mid as usize] { // [l, mid)单增。另一侧的单调性不确定
                if nums[l as usize] <= target && target < nums[mid as usize] { // target在[l, mid)
                    r = mid - 1;
                }
                else {
                    l = mid + 1;
                }
            }
            else { // (mid, r]单增
                if nums[mid as usize] < target && target <= nums[r as usize] { // target在[l, mid)
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }
        }

        false
    }
}

fn main() {
    println!("{}", Solution81::search([2,5,6,0,0,1,2].to_vec(), 0));
    println!("{}", Solution81::search([1,0,1,1,1].to_vec(), 0));
    println!("{}", Solution81::search([2,2,2,3,2,2,2].to_vec(), 3));

    // println!("{}", Solution81::search_implementation2([2,5,6,0,0,1,2].to_vec(), 0));
    // println!("{}", Solution81::search_implementation2([1,0,1,1,1].to_vec(), 0));
    // println!("{}", Solution81::search_implementation2([2,2,2,3,2,2,2].to_vec(), 3));
    println!("{}", Solution81::search_implementation2([5,1,3].to_vec(), 3));
}