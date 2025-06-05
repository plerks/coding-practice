/*
url: https://leetcode.cn/problems/find-the-safest-path-in-a-grid/
相关: LeetCode778. 水位上升的泳池中游泳, 典型问题/最短路径问题/vis的修改位置问题
标签: 【题单】二分算法, 多源bfs, 并查集, Dijkstra算法变式
*/

use std::collections::{BinaryHeap, VecDeque};

struct Solution2812;

impl Solution2812 {
    /* 参考灵茶题解，这题和`LeetCode778. 水位上升的泳池中游泳`非常像。
    思路倒是有，二分答案d，把每个点距离最近的1的距离算出来，然后看能否只走>=d的点，实现从(0, 0)走到(n - 1, n - 1)。
    但是算每个点距离最近的1的距离，要从每个1为起点bfs，表格最多n ^ 2个1，总的bfs的开销会是n^2 * n^2，而1 <= grid.length == n <= 400，
    会超时。
    要用“多源bfs”，头一次见这个技巧，每个1都是源头，这样bfs的总开销为O(n^2)
    */
    pub fn maximum_safeness_factor(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len(); // grid为n * n的方阵
        let mut dis = vec![vec![-1; n]; n]; // dis[i][j]表示(i, j)离最近的1的曼哈顿距离
        // 多源bfs
        let mut q = VecDeque::new();
        for i in 0..n {
            for j in 0..n {
                if grid[i][j] == 1 {
                    q.push_back((i, j));
                    dis[i][j] = 0;
                }
            }
        }
        let directions= [(1, 0), (-1, 0), (0, 1), (0, -1)];
        let mut h = 0; // 当前bfs的"层数"
        while !q.is_empty() {
            let size = q.len();
            h += 1;
            for _ in 0..size {
                let node = q.pop_front().unwrap();
                for (dx, dy) in directions {
                    let xx = node.0 as i32 + dx;
                    let yy = node.1 as i32 + dy;
                    if xx >= 0 && xx < n as i32 && yy >= 0 && yy < n as i32 && dis[xx as usize][yy as usize] < 0 { // 用dis[xx][yy] < 0代表vis
                        dis[xx as usize][yy as usize] = h;
                        q.push_back((xx as usize, yy as usize));
                    }
                }
            }
        }

        // 用bfs检查是否能只走距离>=d的路，从(0, 0)走到(n - 1, n - 1)
        let check = |d| {
            let mut q = VecDeque::new();
            let mut vis = vec![vec![false; n]; n];
            let mut res = false;
            if dis[0][0] >= d {
                q.push_back((0, 0));
            }
            vis[0][0] = true; // 也可以这里不写，下面循环里写上 vis[node.0][node.1] = true; 同样能达到标记root已访问的目的，但是最好写在这里。见“典型问题/最短路径问题/vis的修改位置问题”
            while !q.is_empty() {
                // dbg!(q.len());
                let node = q.pop_front().unwrap();
                if node.0 == n - 1 && node.1 == n - 1 {
                    res = true;
                    break;
                }
        
                for (dx, dy) in directions {
                    let xx = node.0 as i32 + dx;
                    let yy = node.1 as i32 + dy;
                    if xx >= 0 && xx < n as i32 && yy >= 0 && yy < n as i32 && !vis[xx as usize][yy as usize] && dis[xx as usize][yy as usize] >= d {
                        q.push_back((xx as usize, yy as usize));
                        vis[xx as usize][yy as usize] = true; // 防止多次入队
                    }
                }
            }
            res
        };
        
        let mut left = 0;
        let mut right = n as i32 - 1; // 从左上走到右下，能达到的最小曼哈顿距离的最大值应该是n - 1，题目保证至少一个1，则放一个1在右上角应该是最大的情况
        while left <= right {
            let mid = (left + right) >> 1;
            if check(mid) { left = mid + 1; }
            else { right = mid - 1; }
        }
        right
    }

    // 以下bfs的写法有误，会导致重复进队，但是这题只需要用bfs判断连通性，且n <= 400，因此也能过。但是这个写法没有价值，只是连通性的判断正确了，但是有无用的重复进队，而且如果要算bfs的距离的话会是错的。
    pub fn maximum_safeness_factor_wrong_but_pass(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len(); // grid为n * n的方阵
        let mut dis = vec![vec![-1; n]; n]; // dis[i][j]表示(i, j)离最近的1的曼哈顿距离
        // 多源bfs
        let mut q = VecDeque::new();
        for i in 0..n {
            for j in 0..n {
                if grid[i][j] == 1 {
                    q.push_back((i, j));
                    dis[i][j] = 0;
                }
            }
        }
        let directions= [(1, 0), (-1, 0), (0, 1), (0, -1)];
        let mut h = 0; // 当前bfs的"层数"
        while !q.is_empty() {
            let size = q.len();
            h += 1;
            for _ in 0..size {
                let node = q.pop_front().unwrap();
                for (dx, dy) in directions {
                    let xx = node.0 as i32 + dx;
                    let yy = node.1 as i32 + dy;
                    if xx >= 0 && xx < n as i32 && yy >= 0 && yy < n as i32 && dis[xx as usize][yy as usize] < 0 { // 用dis[xx][yy] < 0代表vis
                        dis[xx as usize][yy as usize] = h;
                        q.push_back((xx as usize, yy as usize));
                    }
                }
            }
        }

        // 用bfs检查是否能只走距离>=d的路，从(0, 0)走到(n - 1, n - 1)
        let check = |d| {
            let mut q = VecDeque::new();
            let mut vis = vec![vec![false; n]; n];
            let mut res = false;
            if dis[0][0] >= d {
                q.push_back((0, 0));
            }
            while !q.is_empty() {
                let node = q.pop_front().unwrap();
                if node.0 == n - 1 && node.1 == n - 1 {
                    res = true;
                    break;
                }

                if vis[node.0][node.1] { continue; }
                vis[node.0][node.1] = true; // 这两行的bfs写法有误，会导致后面neighbor重复进队，但是这题只需要用bfs判断连通性，且n <= 400，因此也能过

                for (dx, dy) in directions {
                    let xx = node.0 as i32 + dx;
                    let yy = node.1 as i32 + dy;
                    if xx >= 0 && xx < n as i32 && yy >= 0 && yy < n as i32 && !vis[xx as usize][yy as usize] && dis[xx as usize][yy as usize] >= d {
                        q.push_back((xx as usize, yy as usize));
                    }
                }
            }
            res
        };
        
        let mut left = 0;
        let mut right = n as i32 - 1; // 从左上走到右下，能达到的最小曼哈顿距离的最大值应该是n - 1，题目保证至少一个1，则放一个1在右上角应该是最大的情况
        while left <= right {
            let mid = (left + right) >> 1;
            if check(mid) { left = mid + 1; }
            else { right = mid - 1; }
        }
        right
    }

    // 这样的错误bfs写法会直接tle，不一定是死循环，看起来像是时间复杂度直接爆了。待做: 不过不是特别理解爆得这么厉害具体是怎么发生的
    pub fn maximum_safeness_factor_tle(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len(); // grid为n * n的方阵
        let mut dis = vec![vec![-1; n]; n]; // dis[i][j]表示(i, j)离最近的1的曼哈顿距离
        // 多源bfs
        let mut q = VecDeque::new();
        for i in 0..n {
            for j in 0..n {
                if grid[i][j] == 1 {
                    q.push_back((i, j));
                    dis[i][j] = 0;
                }
            }
        }
        let directions= [(1, 0), (-1, 0), (0, 1), (0, -1)];
        let mut h = 0; // 当前bfs的"层数"
        while !q.is_empty() {
            let size = q.len();
            h += 1;
            for _ in 0..size {
                let node = q.pop_front().unwrap();
                for (dx, dy) in directions {
                    let xx = node.0 as i32 + dx;
                    let yy = node.1 as i32 + dy;
                    if xx >= 0 && xx < n as i32 && yy >= 0 && yy < n as i32 && dis[xx as usize][yy as usize] < 0 { // 用dis[xx][yy] < 0代表vis
                        dis[xx as usize][yy as usize] = h;
                        q.push_back((xx as usize, yy as usize));
                    }
                }
            }
        }

        // 用bfs检查是否能只走距离>=d的路，从(0, 0)走到(n - 1, n - 1)
        let check = |d| {
            let mut q = VecDeque::new();
            let mut vis = vec![vec![false; n]; n];
            let mut res = false;
            if dis[0][0] >= d {
                q.push_back((0, 0));
            }
            
            while !q.is_empty() {
                // dbg!(q.len());
                let node = q.pop_front().unwrap();
                if node.0 == n - 1 && node.1 == n - 1 {
                    res = true;
                    break;
                }

                // if vis[node.0][node.1] { continue; } // 相比maximum_safeness_factor_wrong_but_pass()，只是这行注释掉了
                vis[node.0][node.1] = true;
                println!("dequeue: {:?}", node);

                for (dx, dy) in directions {
                    let xx = node.0 as i32 + dx;
                    let yy = node.1 as i32 + dy;
                    if xx >= 0 && xx < n as i32 && yy >= 0 && yy < n as i32 && !vis[xx as usize][yy as usize] && dis[xx as usize][yy as usize] >= d {
                        q.push_back((xx as usize, yy as usize));
                        println!("enqueue: {:?}", (xx, yy));
                    }
                }
            }
            res
        };
        
        let mut left = 0;
        let mut right = n as i32 - 1; // 从左上走到右下，能达到的最小曼哈顿距离的最大值应该是n - 1，题目保证至少一个1，则放一个1在右上角应该是最大的情况
        while left <= right {
            let mid = (left + right) >> 1;
            if check(mid) { left = mid + 1; }
            else { right = mid - 1; }
        }
        right
    }

    /* 参考灵茶题解，不用二分直接做。把各个点的dis分类，然后倒序枚举dis，用并查集进行合并，直到(0, 0)和(n - 1, n - 1)相连，
    这时的dis就是答案
    */
    pub fn maximum_safeness_factor_implementation2(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len(); // grid为n * n的方阵
        let mut dis = vec![vec![-1; n]; n]; // dis[i][j]表示(i, j)离最近的1的曼哈顿距离
        // 多源bfs
        let mut vis = vec![vec![false; n]; n];
        let mut q = VecDeque::new();
        for i in 0..n {
            for j in 0..n {
                if grid[i][j] == 1 {
                    q.push_back((i, j));
                    dis[i][j] = 0;
                    vis[i][j] = true;
                }
            }
        }
        let mut groups = Vec::new(); // 按距离将点分类，(距离, 节点列表)
        
        let directions= [(1, 0), (-1, 0), (0, 1), (0, -1)];

        while !q.is_empty() {
            let size = q.len();
            let mut group = Vec::new();
            for _ in 0..size {
                let node = q.pop_front().unwrap();
                group.push(node);
                for (dx, dy) in directions {
                    let xx = node.0 as i32 + dx;
                    let yy = node.1 as i32 + dy;
                    if xx >= 0 && xx < n as i32 && yy >= 0 && yy < n as i32 && !vis[xx as usize][yy as usize] {
                        q.push_back((xx as usize, yy as usize));
                        vis[xx as usize][yy as usize] = true; // 防止多次入队
                        dis[xx as usize][yy as usize] = (groups.len() + 1) as i32;
                    }
                }
            }
            groups.push(group);
        }
        
        let mut uf = UnionFind::new((n * n) as i32);
        // 倒序枚举距离，把距离小的点合并到周围距离大的点，直到发现 (0, 0) 和 (n - 1, n - 1) 连通
        for ans in (0..groups.len()).rev() {
            for &node in &groups[ans] {
                let (x, y) = node;
                for (dx, dy) in directions {
                    let xx = node.0 as i32 + dx;
                    let yy = node.1 as i32 + dy;
                    if xx >= 0 && xx < n as i32 && yy >= 0 && yy < n as i32 && dis[xx as usize][yy as usize] >= dis[x][y] {
                        uf.unite((x * n + y) as i32, (xx as usize * n + yy as usize) as i32);
                    }
                }
            }
            if uf.is_connected(0, (n * n - 1) as i32) {
                return ans as i32;
            }
        }

        -1
    }

    // 类似`LeetCode778. 水位上升的泳池中游泳`，这题也可以用Dijkstra算法
    // 算出各个点距离最近的1的曼哈顿距离后，要的是到一个点的路径上的距离值都尽量大，路径的开销为路径节点的开销的最小值。让子路径是"距离最近的1"最远的
    pub fn maximum_safeness_factor_implementation3(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len(); // grid为n * n的方阵
        let mut dis = vec![vec![-1; n]; n]; // dis[i][j]表示(i, j)离最近的1的曼哈顿距离
        // 多源bfs
        let mut q = VecDeque::new();
        for i in 0..n {
            for j in 0..n {
                if grid[i][j] == 1 {
                    q.push_back((i, j));
                    dis[i][j] = 0;
                }
            }
        }
        let directions= [(1, 0), (-1, 0), (0, 1), (0, -1)];
        let mut h = 0; // 当前bfs的"层数"
        while !q.is_empty() {
            let size = q.len();
            h += 1;
            for _ in 0..size {
                let node = q.pop_front().unwrap();
                for (dx, dy) in directions {
                    let xx = node.0 as i32 + dx;
                    let yy = node.1 as i32 + dy;
                    if xx >= 0 && xx < n as i32 && yy >= 0 && yy < n as i32 && dis[xx as usize][yy as usize] < 0 { // 用dis[xx][yy] < 0代表vis
                        dis[xx as usize][yy as usize] = h;
                        q.push_back((xx as usize, yy as usize));
                    }
                }
            }
        }

        let mut pq = BinaryHeap::new(); // (距离, 节点)
        let mut vis = vec![false; n * n];
        let mut path_cost = vec![vec![0; n]; n]; // path_cost[i][j]从(0, 0)走到(i, j)，能实现的最大化路径min{dis(node)}
        pq.push((dis[0][0], (0, 0)));
        path_cost[0][0] = dis[0][0];
        let directions= [(1, 0), (-1, 0), (0, 1), (0, -1)];
        while !pq.is_empty() {
            let (d, node) = pq.pop().unwrap();
            let (x, y) = node;
            if vis[node.0 * n + node.1] {
                continue;
            }
            vis[node.0 * n + node.1] = true;
            for (dx, dy) in directions {
                let xx = node.0 as i32 + dx;
                let yy = node.1 as i32 + dy;
                if xx >= 0 && xx < n as i32 && yy >= 0 && yy < n as i32 && std::cmp::min(path_cost[x][y], dis[xx as usize][yy as usize]) > path_cost[xx as usize][yy as usize] {
                    path_cost[xx as usize][yy as usize] = std::cmp::min(path_cost[x][y], dis[xx as usize][yy as usize]);
                    pq.push((path_cost[xx as usize][yy as usize], (xx as usize, yy as usize)));
                }
            }
        }

        path_cost[n - 1][n - 1]
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
    println!("{}", Solution2812::maximum_safeness_factor([[1,0,0],[0,0,0],[0,0,1]].map(|row| row.to_vec()).to_vec()));
    println!("{}", Solution2812::maximum_safeness_factor([[0,0,1],[0,0,0],[0,0,0]].iter().map(|row| row.to_vec()).collect()));
    println!("{}", Solution2812::maximum_safeness_factor([[1]].iter().map(|row| row.to_vec()).collect()));

    let grid = [
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1],
        [1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1],
        [1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0],
    ];
    println!("{}",Solution2812::maximum_safeness_factor(grid.iter().map(|row| row.to_vec()).collect()));

    println!("======");

    // println!("{}",Solution2812::maximum_safeness_factor_tle(grid.iter().map(|row| row.to_vec()).collect()));

    println!("======");

    println!("{}", Solution2812::maximum_safeness_factor_implementation2([[1,0,0],[0,0,0],[0,0,1]].map(|row| row.to_vec()).to_vec()));
    println!("{}", Solution2812::maximum_safeness_factor_implementation2([[0,0,1],[0,0,0],[0,0,0]].iter().map(|row| row.to_vec()).collect()));
    println!("{}", Solution2812::maximum_safeness_factor_implementation2([[1]].iter().map(|row| row.to_vec()).collect()));

    println!("======");

    println!("{}", Solution2812::maximum_safeness_factor_implementation3([[1,0,0],[0,0,0],[0,0,1]].map(|row| row.to_vec()).to_vec()));
    println!("{}", Solution2812::maximum_safeness_factor_implementation3([[0,0,1],[0,0,0],[0,0,0]].iter().map(|row| row.to_vec()).collect()));
    println!("{}", Solution2812::maximum_safeness_factor_implementation3([[1]].iter().map(|row| row.to_vec()).collect()));
}
