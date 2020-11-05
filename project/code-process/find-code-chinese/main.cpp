#include"./find-code-chinese.cpp"

int main(int argc, char* argv[]) {
    // cmd 字符输出改为 utf-8
    system("CHCP 65001");
    cout << "--------------------\n";
    
    startFind();

    system("pause");
    return 0;
}
