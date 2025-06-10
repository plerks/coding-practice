/*
url: https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/
相关: LeetCode153. 寻找旋转排序数组中的最小值, LeetCode81. 搜索旋转排序数组 II
标签: 【题单】二分算法
*/

struct Solution154;

impl Solution154 {
    /* 此题题面与LeetCode153相同，但是此题nums变成有重复元素了。
    如果还是像LeetCode153一样，找 <= nums[n - 1] 的第一个元素，此时是没有单调性的，
    [10,1,10,10,10] 这个用例就能看出来，区间回答全为是，找不到1的位置。

    改成找 < nums[0] 的第一个元素又如何？
    还是 [10,1,10,10,10] 这个用例，对于 < nums[0]，区间不是单调的，也不行

    改成找 < nums[n - 1]的第一个元素又如何？
    还是不行，还是不单调

    所以，只能改成把两头的相同元素除掉，让二分区间的左端点严格大于右端点才行。
    然后找 <= nums[right] 的第一个元素

    这题时间复杂度是O(n)了
    */
    pub fn find_min(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        let mut left: i32 = 0;
        let mut right: i32 = n as i32 - 1;
        let mut ans = i32::MAX;
        while left < right && nums[left as usize] == nums[right as usize] {
            ans = std::cmp::min(ans, nums[left as usize]);
            left += 1;
            right -= 1;
        }
        if left > right { return ans; }

        let bound = nums[right as usize];
        while left <= right {
            let mid = (left + right) / 2;
            if !(nums[mid as usize] <= bound) { left = mid + 1; }
            else { right = mid - 1; }
        }

        std::cmp::min(ans, nums[left as usize])
    }

    // 优化find_min()写法，把右侧的剪掉就行了
    pub fn find_min_implementation2(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        let mut left = 0;
        let mut right = n as i32 - 1;
        while left < right && nums[right as usize] == nums[0] { right -= 1; }
        let bound = nums[right as usize];
        while left <= right {
            let mid = (left + right) / 2;
            if !(nums[mid as usize] <= bound) { left = mid + 1; }
            else { right = mid - 1; }
        }

        nums[left as usize]
    }
}

fn main() {
    // println!("{}", Solution154::find_min([1,3,5].to_vec()));
    // println!("{}", Solution154::find_min([2,2,2,0,1].to_vec()));
    // println!("{}", Solution154::find_min([3,1,3].to_vec()));
    // println!("{}", Solution154::find_min([10,1,10,10,10].to_vec()));
    // println!("{}", Solution154::find_min([1,2,1].to_vec()));
    println!("{}", Solution154::find_min([2,0,0,2].to_vec()));

    // println!("{}", Solution154::find_min_implementation2([10,1,10,10,10].to_vec()));
    // println!("{}", Solution154::find_min_implementation2([1,2,1].to_vec()));
    // println!("{}", Solution154::find_min_implementation2([1,3,5].to_vec()));
    // println!("{}", Solution154::find_min_implementation2([3,1,3].to_vec()));
    println!("{}", Solution154::find_min_implementation2([2,0,0,2].to_vec()));
}