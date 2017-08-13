#include <iostream>
using namespace std;

#include "ToluaEngine.h"

int main()
{
    sToluaEngine.NewInstance();

    sToluaEngine.Init();
    
    // 代码调用示例
    cout << "输入0表示结束循环，输入1表示重新加载lua文件，输入2表示运行测试." << endl;
    int order = 0;
    cin >> order;
    while (order)
    {
        cout << "...start..." << endl;
        switch (order)
        {
        case 0:
            break;
        case 1:
            sToluaEngine.ReloadLua();
            cout << "reload lua file ok" << endl;
            break;
        case 2:
            sToluaEngine.TestFun();
            cout << "code call example" << endl;
            break;
        default:
            cout << "error order" << endl;
            break;
        }
        cout << "...end..." << endl;
        cin >> order;
    }

    sToluaEngine.DeleteInstance();

    return 0;
}
