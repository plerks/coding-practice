/*
url: https://leetcode.cn/problems/search-a-2d-matrix/
相关: LeetCodeLCR 121. 寻找目标值 - 二维数组
标签: 【题单】二分算法
*/

struct Solution74;

impl Solution74 {
    pub fn search_matrix(matrix: Vec<Vec<i32>>, target: i32) -> bool {
        // 从右上角开始，左小下大
        Self::dfs(&matrix, target, 0, matrix[0].len() as i32 - 1)
    }

    fn dfs(matrix: &Vec<Vec<i32>>, target: i32, i: i32, j: i32) -> bool {
        if i >= matrix.len() as i32 || j < 0 {
            return false;
        }
        if matrix[i as usize][j as usize] == target {
            return true;
        }
        if matrix[i as usize][j as usize] < target {
            return Self::dfs(matrix, target, i + 1, j);
        }
        return Self::dfs(matrix, target, i, j - 1);
    }
}

fn main() {
    println!("{}", Solution74::search_matrix([[1,3,5,7],[10,11,16,20],[23,30,34,60]].map(|row| row.to_vec()).to_vec(), 3));
}