/*
url: https://leetcode.cn/problems/swim-in-rising-water/
参考: https://leetcode.cn/problems/swim-in-rising-water/solutions/582250/shui-wei-shang-sheng-de-yong-chi-zhong-y-862o/
标签: 【题单】二分算法, 并查集, Dijkstra算法变式, [mark], [special]
*/

use std::{cmp::Reverse, collections::BinaryHeap};

struct Solution778;

impl Solution778 {
    pub fn swim_in_water(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len();

        let check = |t| {
            let mut vis = vec![vec![false; n]; n];
            return Self::dfs(0, 0, t, &mut vis, &grid);
        };

        let mut left = 0;
        let mut right = *grid
            .iter()
            .filter_map(|row| row.iter().max())
            .max()
            .unwrap();
        while left <= right {
            let mid = (left + right) / 2;
            if !check(mid) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        left
    }

    // 从(i, j)能否走到(m - 1, n - 1)
    // rust实现lambda的递归有点麻烦，直接写成函数
    fn dfs(i: i32, j: i32, t: i32, vis: &mut Vec<Vec<bool>>, grid: &Vec<Vec<i32>>) -> bool {
        let n = grid.len();
        if !(i >= 0 && i < n as i32 && j >= 0 && j < n as i32) {
            return false;
        }
        
        if t < grid[i as usize][j as usize] {
            return false;
        }

        if i == n as i32 - 1 && j == n as i32 - 1 {
            return true;
        }

        if vis[i as usize][j as usize] {
            return false;
        }
        vis[i as usize][j as usize] = true;

        return Self::dfs(i - 1, j, t, vis, grid) || Self::dfs(i + 1, j, t, vis, grid) || Self::dfs(i, j - 1, t, vis, grid) || Self::dfs(i, j + 1, t, vis, grid);
    }

    /* 参考官方题解，更直接的解法，用并查集。
    题目满足：
    n == grid.length
    n == grid[i].length
    1 <= n <= 50
    0 <= grid[i][j] < n^2
    grid[i][j] 中每个值均无重复

    所以，grid中的值从 0 到 n^2 - 1，那么，模拟时间t的增加，把grid中所有<=t的点都连上，检查(0, 0)和(n - 1, n - 1)是否相连了。
    把grid中所有<=t的点都连上的做法是：找到高度为t的点的位置(预处理)，然后将自己连到已被水覆盖的区域。
    这样就相当于：在任意t时刻，得到了现在的水坑情况。
    */
    pub fn swim_in_water_implementation2(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len();
        let total = n * n;
        let mut pos = vec![(0, 0); total]; // pos[i]表示值i在grid中的位置
        for i in 0..n {
            for j in 0..n {
                pos[grid[i][j] as usize] = (i as i32, j as i32);
            }
        }

        let directions: [[i32; 2]; 4] = [[0, 1], [0, -1], [1, 0], [-1, 0]];

        let legal = |x, y| {
            return x >= 0 && x < n as i32 && y >= 0 && y < n as i32;
        };

        // 把(x, y)标号为 x * n + y
        let mut uf = UnionFind::new(total as i32);
        
        for t in 0..total {
            // 找到t高度的点，合并入水坑
            let (x, y) = pos[t];
            for direction in directions {
                let xx = x + direction[0];
                let yy = y + direction[1];
                if legal(xx, yy) && grid[xx as usize][yy as usize] < t as i32 {
                    uf.unite(x * n as i32 + y, xx * n as i32 + yy);
                }
            }
            if uf.is_connected(0, n as i32 * n as i32 - 1) { return t as i32; }
        }

        -1
    }

    /* 参考官方题解，用Dijkstra算法，这里是特殊的Dijkstra算法，计算源点到一个点的距离时，既不是路径上边权的sum，也不是路径上边权的max，
        而是 max(dis, grid[u][v])，也即是路径上节点值的最大值。
    */
    pub fn swim_in_water_implementation3(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len();
        let mut pq = BinaryHeap::new();
        pq.push(Reverse((grid[0][0], (0i32, 0i32)))); // (距离, node)，初始时刻先要等grid[0][0]时间，把(0, 0)淹没
        let mut distance = vec![i32::MAX; n * n as usize];
        distance[0] = grid[0][0];

        let directions: [[i32; 2]; 4] = [[0, 1], [0, -1], [1, 0], [-1, 0]];

        let legal = |x: i32, y: i32| {
            return x >= 0 && x < n as i32 && y >= 0 && y < n as i32;
        };

        while !pq.is_empty() {
            let (dis, node) = pq.pop().unwrap().0;
            if dis > distance[(node.0 * n as i32 + node.1) as usize] {
                continue;
            }
            for direction in directions {
                let neighbor = (node.0 + direction[0], node.1 + direction[1]);
                if legal(neighbor.0 as i32, neighbor.1 as i32) {
                    let (i, j) = node;
                    let (u, v) = neighbor;
                    // 由node去松弛其周围的节点
                    if std::cmp::max(dis, grid[u as usize][v as usize]) < distance[(neighbor.0 * n as i32 + neighbor.1) as usize] {
                        distance[(neighbor.0 * n as i32 + neighbor.1) as usize] = std::cmp::max(dis, grid[u as usize][v as usize]);
                        pq.push(Reverse((distance[(neighbor.0 * n as i32 + neighbor.1) as usize], (u, v))));
                    }
                }
            }
        }

        return distance[n * n - 1];
    }
}

struct UnionFind {
    parent: Vec<i32>
}

impl UnionFind {
    pub fn new(n: i32) -> Self {
        let mut uf = Self {
            parent: vec![0; n as usize]
        };
        for (i, x) in uf.parent.iter_mut().enumerate() {
            *x = i as i32;
        }
        uf
    }

    fn find(&mut self, i: i32) -> i32 {
        if self.parent[i as usize] != i {
            self.parent[i as usize] = self.find(self.parent[i as usize]);
        }
        self.parent[i as usize]
    }

    pub fn unite(&mut self, i: i32, j: i32) {
        if self.find(i) == self.find(j) {
            return;
        }
        let ri = self.find(i);
        let rj = self.find(j);
        self.parent[ri as usize] = rj;
    }

    pub fn is_connected(&mut self, i: i32, j: i32) -> bool {
        self.find(i) == self.find(j)
    }
}

pub fn main() {
    println!("{}",Solution778::swim_in_water(vec![vec![0, 2], vec![1, 3]]));
    println!("{}",Solution778::swim_in_water(
        vec![
            vec![0, 1, 2, 3, 4],
            vec![24, 23, 22, 21, 5],
            vec![12, 13, 14, 15, 16],
            vec![11, 17, 18, 19, 20],
            vec![10, 9, 8, 7, 6]
        ])
    );

    println!("{}",Solution778::swim_in_water_implementation2(vec![vec![0, 2], vec![1, 3]]));
    println!("{}",Solution778::swim_in_water_implementation2(
        vec![
            vec![0, 1, 2, 3, 4],
            vec![24, 23, 22, 21, 5],
            vec![12, 13, 14, 15, 16],
            vec![11, 17, 18, 19, 20],
            vec![10, 9, 8, 7, 6]
        ])
    );

    println!("{}",Solution778::swim_in_water_implementation3(vec![vec![0, 2], vec![1, 3]]));
    println!("{}",Solution778::swim_in_water_implementation3(
        vec![
            vec![0, 1, 2, 3, 4],
            vec![24, 23, 22, 21, 5],
            vec![12, 13, 14, 15, 16],
            vec![11, 17, 18, 19, 20],
            vec![10, 9, 8, 7, 6]
        ])
    );
    println!("{}",Solution778::swim_in_water_implementation3([[3, 2], [0, 1]].map(|row| row.to_vec()).to_vec()));
    println!("{}",Solution778::swim_in_water_implementation3([[10,12,4,6].to_vec(),[9,11,3,5].to_vec(),[1,7,13,8].to_vec(),[2,0,15,14].to_vec()].to_vec()));
}
