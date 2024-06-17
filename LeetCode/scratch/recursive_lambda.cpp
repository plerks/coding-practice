// 相关: LeetCode3149. 找出分数最低的排列

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
    /* 使用C++的lambda实现直接在函数内定义函数的效果，避免平行定义dfs()传参数麻烦(比如dfs要用到外部的一些变量时经常要写一堆传引用的参数)。
    但是lambda不支持递归调用，所以写成以下这样是过不了编译的:
    */
    /* auto dfs_wrong = [&](int i) {
        if (i <= 0) {
            cout << "dfs" << endl;
            return;
        }
        dfs_wrong(i - 1);
    }; */

    // 解决办法是用std::function包装一下
    function<void(int)> dfs = [&](int i) {
        if (i <= 0) {
            cout << "dfs" << endl;
            return;
        }
        dfs(i - 1);
    };

    /* 参考<https://stackoverflow.com/questions/7861506/recursive-call-in-lambda-c11>，原理应该是这样:
    auto dfs = [&](int i)的写法，lambda里面包含dfs这个名字，所以为了推导lambda表达式的类型需要知道dfs这个名字的类型，
    而dfs这个名字是auto类型的，推导它的类型又需要知道右边的类型，也就是说使用auto接收lambda表达式，而lambda表达式里面又递归的话，
    会出现循环推导类型，所以不能编译。

    而function<void(int)> dfs = [&](int i)不一样，dfs这个名字一开始就直接知道类型，虽然写在左边，
    但是推导右边的lambda表达式的类型时，dfs这个名字是可见且明确类型的，所以lambda表达式的类型也就是清楚的，类型推导不会遇到困难。

    此外，关于C++ lambda表达式的类型，参考<https://stackoverflow.com/questions/7951377/what-is-the-type-of-lambda-when-deduced-with-auto-in-c11>:
    lambda得到的结果是个函数对象，而其类型，是会新生成个独特的匿名类型(重写了operator())，而如果lambda没有捕获外部变量的话，会处理成函数指针。

    由于lambda表达式的类型是由编译器生成的唯一的匿名类型，所以用auto来接收lambda表达式时，这时的auto不是简单的"右边是什么类型自己就是什么类型"，
    不是那种简单的语法糖。
    */

    dfs(1);

    // 还有个方法是lambda传入自己作为参数
    auto dfs2 = [&](auto dfs2, int i) { // lambda参数使用了auto，需要C++14及以上
        if (i <= 0) {
            cout << "dfs2" << endl;
            return;
        }
        dfs2(dfs2, i - 1);
    };

    dfs2(dfs2, 1);

    /* 这种写法看起来比较怪，且要多带一个参数。但是这种比用std::function要快，`LeetCode3186. 施咒的最大总伤害`这道题，
    使用std::function会超时，用这种lambda传入自己的技巧就不会。
    */

    return 0;
}