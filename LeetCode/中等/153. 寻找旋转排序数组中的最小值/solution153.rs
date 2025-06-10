/*
url: https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/
参考: https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/solutions/1987499/by-endlesscheng-owgd/
相关: LeetCode154. 寻找旋转排序数组中的最小值 II, LeetCode1095. 山脉数组中查找目标值, LeetCode81. 搜索旋转排序数组 II
标签: 【题单】二分算法, [mark], [special]
*/

struct Solution153;

impl Solution153 {
    // 我的解法，找那个独特的下降点位置，闭区间二分的写法，但是需要改闭区间二分的代码，最后代码比较奇怪
    pub fn find_min(nums: Vec<i32>) -> i32 {
        // nums元素各不相同。nums分为两段，且第一段整体都比第二段高。有个独特的“下降点”
        // 这题答案一定存在，最开始，nums[left] > nums[right]，区间中一定有下降点，但是二分之后就不一定了
        // 例如 [4,5,6,7,0,1,2]，第一次二分之后能知道答案在右边，[0,1,2]没有下降点，这时nums[left] < nums[right]，nums[left]就是答案
        let n = nums.len();
        let mut left = 0;
        let mut right = n as i32 - 1;
        while right - left + 1 > 2 { // [left, right]区间长度 <= 2时直接手动判断，否则像[2, 1]或者[1,2]这种，mid算出来和left一样，判断出来的结果不能使用
            // 下降点在当前区间不存在
            if nums[left as usize] < nums[right as usize] { return nums[left as usize]; }

            // 下降点在当前区间存在
            let mid = (left + right) / 2;
            if nums[left as usize] < nums[mid as usize] {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }

        std::cmp::min(nums[left as usize], nums[right as usize])
    }

    /* 参考灵茶题解，与nums[n - 1]比较，最小值是第一个 <= nums[n - 1] 的位置（注意nums[n - 1]也可能是最小值，
       所以要取等号，不然区间可能全是否）。

       也可以与nums[0]比较，最小值是第一个 < nums[0] 的位置，区间从否到是。但是特殊情况是nums[0]就是最小值，此时结果会是错误的n，特判这种情况直接返回nums[0]。
       注意不能考虑成 最小值是第一个 <= nums[0] 的位置，nums[0] <= nums[0] 是个必成立的点，没有单调性。

       求 nums 最大值的情况应该是与上面对称的
    */
    pub fn find_min_implementation2(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        let mut left = 0;
        let mut right = n as i32 - 1; // 这里可以改成 n - 2，第一个 <= nums[n - 1] 的位置，结果范围本该为[0, n]，但是这题一定能搜索到，实际结果范围为[0, n - 1]
        while left <= right {
            let mid = (left + right) / 2;
            if !(nums[mid as usize] <= nums[n - 1]) { left = mid + 1; }
            else { right = mid - 1; }
        }

        nums[left as usize]
    }

    // 与nums[0]比较的写法
    pub fn find_min_implementation3(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        let mut left = 0;
        let mut right = n as i32 - 1;
        while left <= right {
            let mid = (left + right) / 2;
            if !(nums[mid as usize] < nums[0]) { left = mid + 1; }
            else { right = mid - 1; }
        }
        
        // 如果left为n，则返回nums[0]，否则返回nums[left]
        if left == n as i32 { nums[0] } else { nums[left as usize] }
    }
}

fn main() {
    // println!("{}", Solution153::find_min([3,4,5,1,2].to_vec()));
    // println!("{}", Solution153::find_min([4,5,6,7,0,1,2].to_vec()));
    // println!("{}", Solution153::find_min([11,13,15,17].to_vec()));
    // println!("{}", Solution153::find_min([2,1].to_vec()));
    println!("{}", Solution153::find_min([3,1,2].to_vec()));

    println!("{}", Solution153::find_min_implementation2([3,1,2].to_vec()));

    println!("{}", Solution153::find_min_implementation3([3,1,2].to_vec()));
    println!("{}", Solution153::find_min_implementation3([1,2,3].to_vec()));
}