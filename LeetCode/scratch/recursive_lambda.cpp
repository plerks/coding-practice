// 相关: LeetCode3149. 找出分数最低的排列

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
    /* 使用C++的lambda实现直接在函数内定义函数的效果，避免平行定义dfs()传参数麻烦(比如dfs要用到外部的一些变量时经常要写一堆传引用的参数)。
    但是lambda里需要递归调用时不能直接这样写:
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

    /* 关于C++ lambda表达式的类型，参考<https://stackoverflow.com/questions/7951377/what-is-the-type-of-lambda-when-deduced-with-auto-in-c11>:
    lambda得到的结果是个函数对象，而其类型，是会新生成个独特的匿名类型(重写了operator())，而如果lambda没有捕获外部变量的话，会处理成函数指针。

    由于lambda表达式的类型是由编译器生成的唯一的匿名类型，所以用auto来接收lambda表达式时，这时的auto不是简单的"右边是什么类型自己就是什么类型"，
    不是那种简单的语法糖。
    */

    dfs(1);

    // 还有个方法是lambda传入自己作为参数，auto& dfs2也可以写万能引用auto&& dfs2
    auto dfs2 = [&](auto& dfs2, int i) { // lambda参数使用了auto，需要C++14及以上
        if (i <= 0) {
            cout << "dfs2" << endl;
            return;
        }
        dfs2(dfs2, i - 1);
    };

    dfs2(dfs2, 1);

    /* 这种写法看起来比较怪，且要多带一个参数。但是这种比用std::function要快，`LeetCode3186. 施咒的最大总伤害`这道题，
    使用std::function会超时，用这种lambda传入自己的技巧就不会，但是不知道为什么使用std::function就会导致超时。
    */

    /* 首先，为什么这样写不能通过编译：
    auto dfs = [&](int i) {
        if (i <= 0) {
            cout << "dfs" << endl;
            return;
        }
        dfs(i - 1);
    };
    右边的lambda表达式会生成一个带operator()的匿名类(这里没捕获变量，所以匿名类没有成员)，然后创建对象：
    class LambdaClass {
        void operator()(int i) {
            if (i <= 0) {
                cout << "dfs" << endl;
                return;
            }
            dfs(i - 1);
        }
    };
    LambdaClass dfs = LambdaClass();
    注意，在生成LambdaClass定义的时候，是没有dfs这个符号的，所以这样写会报错。

    [&](int i) {
        if (i <= 0) {
            cout << "dfs" << endl;
            return;
        }
        dfs(i - 1);
    };
    会直接报错'dfs' was not declared in this scope

    auto dfs = [&](int i) {
        if (i <= 0) {
            cout << "dfs" << endl;
            return;
        }
        dfs(i - 1);
    };
    会报错use of 'dfs' before deduction of 'auto'
    说明等号左边的dfs会先加到符号表里，但是类型是auto还未推导出来，然后处理右边的lambda时，以为lambda里的dfs是想用
    等号左边未明确的dfs，所以这样报错。而 function<void(int)> dfs = [&](int i) { dfs(...); } 时，dfs的类型是明确的，所以没问题。

    auto dfs = [&](int i) {
        if (i <= 0) {
            cout << "dfs" << endl;
            return;
        }
        f(i - 1);
    };
    会报错'f' was not declared in this scope

    所以，lambda里的dfs需要通过参数传进来：auto dfs = [&](auto& dfs, int i) {...}，注意右边的dfs是形参，
    是传进来的，不是直接就是左边的dfs，只是方便起见命名成一样。(理解的话把右边dfs改名为f更好理解)
    
    这样写：
    [&](auto& dfs, int i) {
        if (i <= 0) {
            cout << "dfs" << endl;
            return;
        }
        dfs(dfs, i - 1);
    };
    发现是能通过编译的，但是这时候怎么知道dfs这个变量是什么样的，怎么知道它能用两个参数来调用，为什么能允许通过编译？
    答案是模板！
    
    参考<https://blog.csdn.net/zwvista/article/details/41144649>：
    c++14起，可以在lambda的参数中使用auto，这叫泛型lambda。lambda参数带auto，则operator()会处理为模板函数。
    auto dfs = [&](auto& dfs, int i) {
        if (i <= 0) {
            cout << "dfs" << endl;
            return;
        }
        dfs(dfs, i - 1);
    };
    dfs(dfs, 1);
    相当于
    struct LambdaClass {
        template<typename T>
        void operator()(T& f, int i) const {
            if (i <= 0) {
                cout << "dfs" << endl;
                return;
            }
            f(f, i - 1);
        }
    };
    auto dfs = LambdaClass();
    dfs.operator()(dfs, 1);
    */

    return 0;
}