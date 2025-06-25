#include <bits/stdc++.h>

using namespace std;

/* C++会自动析构成员对象，参考<https://www.cnblogs.com/AntonioSu/p/12269474.html>,
这里当UnionFind的析构函数被调用时，成员对象vector<int> parent和vector<int> size的析构函数也被调用，成员对象内部关联的动态内存也得到释放。
即便手动写一个函数体为空的析构函数，成员对象也会得到析构。也即，成员对象内部是可能关联动态内存的，其内部的动态内存会在调用成员对象的析构函数
时被释放。总之，不用担心成员对象的析构问题，只需考虑自己new出来的东西的delete。 */

class UnionFind {
public:
    /* 不能vector<int> parent(2, 1);，不能在成员变量声明时用构造函数初始化。
    但是见<https://www.zhihu.com/question/371513953/answer/1020815175>,
    <https://stackoverflow.com/questions/13662441/c11-allows-in-class-initialization-of-non-static-and-non-const-members-what-c>
    C++ 11可以直接在声明成员变量的地方初始化(in-class initialization)。对于基本类型直接int cnt = 0即可，对于对象类型不能直接在声明
    的地方调用构造函数，例如不能声明时直接vector<int> v(1, 0)，而是要用initializer_list: vector<int> v = {0}（或者vector<int> v{0}）
    之前`LeetCode1631. 最小体力消耗路径`solution1631.cpp中就写过这样的初始化了，只是当时不知道这是C++ 11的in-class initialization。
    */
    vector<int> parent;
    vector<int> size;

    /* 参考: <https://blog.csdn.net/sinat_20265495/article/details/53642761>
            <https://www.tiger2doudou.com/doku.php/coding:cpp:execution_order_of_the_initilization_list>
            <https://www.cnblogs.com/wangguchangqing/p/6141743.html>
            <https://blog.csdn.net/Hackbuteer1/article/details/6545882>
            <https://blog.csdn.net/weicao1990/article/details/81629955>
    */
    // 成员变量的初始化顺序与初始化列表中列出的变量的顺序无关，它只与成员变量在类中声明的顺序有关。
    /* 初始化列表中，构造函数参数与成员变量重名时的情况，括号外的一定是成员，括号内的可以是构造函数参数，也可以是成员，
       可以用this->明确是哪个，否则重名时优先是构造函数参数。最好是构造函数参数改下名字，比如UnionFind(int _n)，
       避免如果类成员也有n时不清晰。 */
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

    // size[x]，只有x为连通块的根时才有意义，写成return size[find(x)]，以便外部调用时忘了先find()也没事
    // 在unite(x, y)时更新二者的size也不能保证size的每个值都有意义，因为可能：连通块1，2，3，先unite(1, 2)，再unite(1, 3)，
    // 于是size[2]就会不对，所以要先find()
    int getSize(int x) { // 返回x所在集合的大小
        return size[find(x)];
    }
};

int main(int argc, char const *argv[])
{
    UnionFind uf(3);
    uf.unite(0, 1);
    cout << uf.find(1) << endl;
    cout << uf.getSize(uf.find(1)) << endl;
}
