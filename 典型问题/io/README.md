自定义的 io 板子和 debug 工具配置。

## io 板子

快读快写、格式化输出等工具函数。

只使用 c 的 stdio (getchar / printf / putchar)，不使用任何 c++ 的 iostream (cin / cout)，因此也不需要 `cin.tie(0)->sync_with_stdio(false);`。

输入函数:

* `rd(T& x)`，T 为整数类型（int / long long）

* `rd(std::string& s)`

* `rdline(std::string& s)`

输出函数:

* `wr(T x)`，T 为 整数 / 浮点 类型

* `wr(char c)`

* `print(T& t) / println(T& t)`，实现了对常见类型的各种 print 函数

* `print(string& fmt, ...) / println(string& fmt, ...)`，类似 c 的 `printf()`，不过占位符用 `{}`

## debug 工具

本地 debug 工具配置，包括 输入重定向 和 debug打印函数。

namespace my::debug 下的函数作用需要在本地自行定义好 **DEBUG 宏**，若无 DEBUG 宏则不会起任何作用。

预期使用方式为: 本地 IDE 定义好 DEBUG 宏，使用 `debug()` 函数打印调试，且提交至 oj 时无需任何代码更改。

通过在本地定义 DEBUG 宏，在本地开启了:

1. 输入重定向

    stdin 自动重定向为了 INPUT_FILE (默认为 "case.txt")

2. debug 宏函数

    * `debug(x)`，用 BrightYellow 颜色打印 debug 变量

    * `debugf(fmt, ...)`，用 BrightYellow 颜色格式化打印

    注意 `debug()` 和 `debugf()` 都会**自动换行**

my::debug 的内容提交至 OJ 时，只要 OJ 没有定义 DEBUG 宏，就会**自动失效**，**无需**特意删除 debug 相关的内容，且在 OJ 上也不会有任何多余行为（例如尝试打开/重定向文件）。