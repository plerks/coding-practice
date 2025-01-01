// https://leetcode.cn/problems/convert-date-to-binary/description/?envType=daily-question&envId=2025-01-01

#include <bits/stdc++.h>

using namespace std;

class Solution3280 {
public:
    string convertDateToBinary(string date) {
        int p1 = date.find("-", 0);
        int p2 = date.find("-", p1 + 1);
        string y = date.substr(0, p1);
        string m = date.substr(p1 + 1, p2 - (p1 +1));
        string d = date.substr(p2 + 1);
        string binary_y = bitset<32>(stoi(y)).to_string();
        string binary_m = bitset<32>(stoi(m)).to_string();
        string binary_d = bitset<32>(stoi(d)).to_string();
        return binary_y.substr(binary_y.find('1')) + "-" + binary_m.substr(binary_m.find('1')) + "-" + binary_d.substr(binary_d.find('1'));
    }
};

int main(int argc, char const *argv[]) {
    Solution3280 solu;
    cout << solu.convertDateToBinary("2080-02-29") << endl;
    return 0;
}
