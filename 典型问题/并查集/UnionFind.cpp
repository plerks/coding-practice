#include <bits/stdc++.h>

using namespace std;

class UnionFind {
public:
    vector<int> parent; // 不能vector<int> parent(2, 1);，不能在类声明中直接初始化
    vector<int> size;

    /* 参考: <https://blog.csdn.net/sinat_20265495/article/details/53642761>
            <https://www.tiger2doudou.com/doku.php/coding:cpp:execution_order_of_the_initilization_list>
            <https://www.cnblogs.com/wangguchangqing/p/6141743.html>
            <https://blog.csdn.net/Hackbuteer1/article/details/6545882>
            <https://blog.csdn.net/weicao1990/article/details/81629955>
    */
    // 成员变量的初始化顺序与初始化列表中列出的变量的顺序无关，它只与成员变量在类中声明的顺序有关。
    /* 初始化列表中，构造函数参数与成员变量重名时的情况，括号外的一定是成员，可以用this->明确是哪个，否则重名时优先是构造函数参数。
       最好是构造函数参数改下名字，比如UnionFind(int _n)，避免如果类成员也有n时不清晰。 */
    /* 这里n只有到了构造函数才知道，因此需要使用初始化列表，若不在初始化列表里构造，到了构造函数内部再初始化，这时已经用默认构造函数构造了，
    例如这时再this->parent = vector<int>(n)，是先创建一个匿名对象然后调用赋值运算符，对对象类型，性能影响大。 */
    UnionFind(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // C++ union是关键字！这里不能像Java里直接叫union()，改叫unite()
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return; // x, y已经相连，不要做下面的操作
        if (size[rx] < size[ry]) {
            parent[rx] = ry;
            size[ry] += size[rx];
        }
        else {
            parent[ry] = rx;
            size[rx] += size[ry];
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int getSize(int x) {
        return size[x];
    }
};

int main(int argc, char const *argv[])
{
    UnionFind uf(3);
    uf.unite(0, 1);
    cout << uf.find(1) << endl;
    cout << uf.getSize(uf.find(1)) << endl;
}
