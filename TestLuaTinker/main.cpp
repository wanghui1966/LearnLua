#include <iostream>
using namespace std;

#include "ClassExample.h"
#include "LuaTinkerEngine.h"

int main()
{
    sClassExample.NewInstance();

    sLuaTinkerEngine.NewInstance();

    sLuaTinkerEngine.Init();

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
            sLuaTinkerEngine.ReloadLua();
            cout << "reload lua file ok" << endl;
            break;
        case 2:
            sLuaTinkerEngine.TestFun();
            sLuaTinkerEngine.TestChannelCenter();
            cout << "code call example" << endl;
            break;
        default:
            cout << "error order" << endl;
            break;
        }
        cout << "...end..." << endl;
        cin >> order;
    }

    sLuaTinkerEngine.DeleteInstance();
    sClassExample.DeleteInstance();

    return 0;
}