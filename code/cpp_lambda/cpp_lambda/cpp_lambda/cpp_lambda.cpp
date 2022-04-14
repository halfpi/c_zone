// cpp_lambda.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 如何在 C++11 中使用 Lambda 表达式
// https://www.oracle.com/cn/servers/technologies/howto-use-lambda-exp-cpp11.html

#include <iostream>
#include <algorithm>

int main()
{
    int a[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    std::sort(a, &a[10], [](int x, int y) {return x < y; });
    // 注意是a[10], Sorts the elements in the range [first, last)
    for (int i = 0; i < 10; i++)
    {
        printf("%i ", a[i]);
    }
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
