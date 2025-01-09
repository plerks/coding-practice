/*
url: https://leetcode.cn/problems/design-task-manager/description/
参考: https://leetcode.cn/problems/design-task-manager/solutions/3039132/lan-shan-chu-dui-pythonjavacgo-by-endles-q5vb/
标签: LeetCode第147场双周赛, 堆 + 懒惰删除
*/

#include <bits/stdc++.h>

using namespace std;

struct Task {
    int userId;
    int taskId;
    int priority;

    bool operator==(const Task& o) const {
        return this->userId == o.userId && this->taskId == o.taskId && this->priority == o.priority;
    }
};

struct Comp {
    bool operator()(const Task& x, const Task& y) const {
        if (x.priority != y.priority) return x.priority > y.priority;
        return x.taskId > y.taskId;
    }
};

// 周赛时的写法，通过
class TaskManager {
public:
    set<Task, Comp> set;
    unordered_map<int, Task> map;

    TaskManager(vector<vector<int>>& tasks) {
        for (auto &task : tasks) {
            add(task[0], task[1], task[2]);
        }
    }
    
    void add(int userId, int taskId, int priority) {
        set.insert({userId, taskId, priority});
        map[taskId] = {userId, taskId, priority};
    }
    
    void edit(int taskId, int newPriority) {
        int userId = map[taskId].userId;
        int oldPriority = map[taskId].priority;
        Task oldTask = {userId, taskId, oldPriority};
        Task newTask = {userId, taskId, newPriority};
        map[taskId].priority = newPriority;
        set.erase(oldTask);
        set.insert(newTask);
    }
    
    void rmv(int taskId) {
        Task task = map[taskId];
        map.erase(taskId);
        set.erase(task);
    }
    
    int execTop() {
        if (set.empty()) return -1;
        int ans = (*set.begin()).userId;
        set.erase(set.begin());
        return ans;
    }
};

struct Comp2 {
    bool operator()(const Task& x, const Task& y) const {
        if (x.priority != y.priority) return x.priority < y.priority;
        return x.taskId < y.taskId;
    }
};

// 灵茶山艾府解法，用 heap + 懒惰删除 的组合，处理堆不能修改内部元素的问题，也可以直接用std::map
class TaskManager2 {
public:
    priority_queue<Task, vector<Task>, Comp2> pq;
    unordered_map<int, Task> mp;

    TaskManager2(vector<vector<int>>& tasks) {
        vector<Task> ta;
        for (auto& v : tasks) {
            ta.push_back({v[0], v[1], v[2]});
            mp.insert({v[1], {v[0], v[1], v[2]}});
        }
        // 这里用堆化的方式初始化pq
        // priority_queue<int> pq(data.begin(), data.end());会自动调用 std::make_heap
        // 效果等同于 make_heap(tasks.begin(), tasks.end()); priority_queue<int> pq(data.begin(), data.end());
        priority_queue<Task, vector<Task>, Comp2> other(ta.begin(), ta.end());
        this->pq = std::move(other);
    }
    
    void add(int userId, int taskId, int priority) {
        pq.push({userId, taskId, priority});
        mp[taskId] = {userId, taskId, priority};
    }
    
    void edit(int taskId, int newPriority) {
        add(mp[taskId].userId, taskId, newPriority);
    }
    
    void rmv(int taskId) {
        // 懒惰删除
        mp[taskId].userId = -1;
    }
    
    int execTop() {
        while(!pq.empty()) {
            Task t = pq.top();
            pq.pop();
            if (t == mp[t.taskId]) {
                mp[t.taskId].userId = -1; // 懒惰删除
                return t.userId;
            }
            // 如果货不对板，说明堆中数据是过时数据，直接丢弃开始下一轮循环
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    TaskManager tm(*new vector<vector<int>>{{1, 101, 10}, {2, 102, 20}, {3, 103, 15}});
    tm.add(4, 104, 5);
    tm.edit(102, 8);
    cout << tm.execTop() << endl;
    tm.rmv(101);
    tm.add(5, 105, 15);
    cout << tm.execTop() << endl;

    TaskManager2 tm2(*new vector<vector<int>>{{1, 101, 10}, {2, 102, 20}, {3, 103, 15}});
    tm2.add(4, 104, 5);
    tm2.edit(102, 8);
    cout << tm2.execTop() << endl;
    tm2.rmv(101);
    tm2.add(5, 105, 15);
    cout << tm2.execTop() << endl;

    return 0;
}
