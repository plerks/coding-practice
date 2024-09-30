// https://leetcode.cn/problems/seat-reservation-manager/?envType=daily-question&envId=2024-09-30

#include <bits/stdc++.h>

using namespace std;

class SeatManager {
public:
    priority_queue<int, vector<int>, greater<int>> q;

    SeatManager(int n) {
        for (int i = 1; i <= n; i++) q.push(i);
    }
    
    // 占据
    int reserve() {
        int number = q.top();
        q.pop();
        return number;
    }
    
    // 解放
    void unreserve(int seatNumber) {
        q.push(seatNumber);
    }
};

int main(int argc, char const *argv[]) {
    SeatManager s(5);
    cout << s.reserve() << endl;
    cout << s.reserve() << endl;
    s.unreserve(2);
    cout << s.reserve() << endl;
    cout << s.reserve() << endl;
    cout << s.reserve() << endl;
    cout << s.reserve() << endl;
    s.unreserve(5);
    return 0;
}
