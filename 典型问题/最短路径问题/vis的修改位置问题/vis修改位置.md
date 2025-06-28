bfs，dfs，优先队列Dijkstra算法中都会用到vis数组，这里捋一下vis的修改应该写在哪里

# dfs的vis修改位置
刚进入`dfs(x)`，立刻修改`vis[x] = true;`。

注意不能在遍历neighbor完成后再修改`vis[x]`为true，这会导致`dfs(neighbor)`时重新产生`dfs(x)`，会死循环。

## dfs节省vis数组
如果图是一棵树，可以通过在dfs()参数里记录fa，既避免了重复访问节点，又省下了vis数组的空间。

---

# bfs的vis修改位置

bfs关键要保证**每个节点只入队一次**。

所以，neighbor入队前检查，未被访问过才入队，入队后直接标记为visited，这会漏掉标记root节点为已访问，所以进循环前单独做一下：`vis[root] = true;`。

## 写法1
```cpp
q.push(root)
vis[root] = true;

while (!q.empty()) {
    int node = q.front(); q.pop();

    for (int neighbor : graph[node]) {
        if (!vis[neighbor]) { // 别忘了这个判断
            q.push(neighbor);
            vis[neighbor] = true;
        }
    }
}
```

也可以不单独`vis[root] = true;`，在循环里得到 node 和 neighbor 时都进行标记，这会重复标记一个vis已经为true的节点为true，但是不影响时间复杂度。

## 写法2
```cpp
q.push(root)

while (!q.empty()) {
    int node = q.front(); q.pop();

    vis[node] = true; // 这行只会对标记root发挥实际作用，其它都是重复置为true

    for (int neighbor : graph[node]) {
        if (!vis[neighbor]) { // 别忘了这个判断
            q.push(neighbor);
            vis[neighbor] = true;
        }
    }
}
```

## 错误写法1
不能只写`vis[node] = true`而漏掉必须的`vis[neighbor] = true;`，这会导致一个节点可能重复入队。例如节点0拉进1，2，然后1，2错误地没被标记为visited，然后节点1时通过了`if (!vis[neighbor])`的检查又把2拉进队了，错误示范见 ./bfs_wrong1.cpp。

## 错误写法2
不要像优先队列Dijkstra一样在`vis[node] = true`前面写上`if (vis[node]) { continue; }`，这样是错的，会导致一个节点出队后没拉进自己未被访问的邻居，错误示范见 ./bfs_wrong2.cpp。

## bfs总结

**入队时**标记为visited，**`vis[neighbor] = true;`必须有**。标记root节点，可以while循环之前写`vis[root] = true;`，也可以while循环里面`vis[node] = true;`，时间复杂度一样，最好前一种，因为bfs是在**入队时**标记已访问，但是后一种写法看起来像是出队时标记，只是刚好作用是对的。

bfs的vis是表示某个节点**是否已经入队过**。

## bfs节省vis数组
初始时把dis数组初始化为-1，可以用`dis[x] > 0`来代替vis数组判断节点是否已被访问(是否已经入队过)。

---

# 优先队列Dijkstra算法的vis修改位置
优先队列Dijkstra是**出队时**将**出队的**`node`标记为visited，边权都非负的情况下，对同一个node，**第一次出队时对邻居的松弛操作就是最优松弛结果**，所以node出队时直接将node标记为visited，后续通过`if (vis[node]) { continue; }`的判断，避免多次无意义地去遍历松弛同一个node的neighbor（毕竟只有第一次是有用的）。

优先队列Dijkstra的vis是表示某个节点**是否已经出队过**。与bfs不同，优先队列Dijkstra中，一个节点可能多次入队，于是也可能多次出队，对同一个node，只有第一次出队需要去松弛邻居，后续的出队都该直接continue。

```cpp
pq.push({root, 0});

while (!pq.empty()) {
    auto [node, distance] = pq.top(); pq.pop();

    if (vis[node]) { continue; } // 可以用`if (distance > dis[node]) { continue; }`代替这两行。用vis判断，还是要有个dis数组记录最小距离。
    vis[node] = true;

    for (neighbor) {
        if (distance + w < dis[neighbor]) { // 注意这里是计算与更新距离，和bfs不一样
            // 注意这里面不同于bfs，不要去标记neighbor为visited，neighbor出队时才标记
            dis[neighbor] = distance + w;
            pq.push({neighbor, distance});
        }
    }
}
```

## 优先队列Dijkstra算法节省vis数组
可以用`if (distance > dis[node]) { continue; }`来代替vis数组判断节点是否已被访问(是否已经出队过)，如果`distance > dis[node]`，说明优先队列里这个node曾有更小的距离，其一定已经出队了(因为已经轮到了现在距离更大的出队)。

---

# 相关
LeetCode2812. 找出最安全路径、./最短路径-Dijkstra-使用优先队列