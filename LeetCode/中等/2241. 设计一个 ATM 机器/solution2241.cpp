// https://leetcode.cn/problems/design-an-atm-machine/description/?envType=daily-question&envId=2025-01-05

#include <bits/stdc++.h>

using namespace std;

class ATM {
public:
    vector<int> cnt;
    vector<int> val;

    ATM() : cnt(5), val({20, 50, 100, 200, 500}) {
        
    }
    
    void deposit(vector<int> banknotesCount) {
        for (int i = 0; i < banknotesCount.size(); i++) {
            cnt[i] += banknotesCount[i];
        }
    }
    
    vector<int> withdraw(int amount) {
        vector<int> ans(5);
        for (int i = 4; i >= 0; i--) {
            int c = min(cnt[i], amount / val[i]);
            amount -= c * val[i];
            ans[i] = c;
        }
        if (amount == 0) {
            for (int i = 0; i <= 4; i++) cnt[i] -= ans[i];
            return ans;
        }
        return {-1};
    }
};

int main(int argc, char const *argv[]) {
    ATM atm;
    atm.deposit({0,0,1,2,1});
    auto x = atm.withdraw(600);
    atm.deposit({0,1,0,1,1});
    atm.withdraw(600);
    atm.withdraw(500);
    return 0;
}