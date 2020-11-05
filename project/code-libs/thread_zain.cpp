//多线程编程-Zain
#include<cstdlib>
#include<string>
#include<iostream>
#include<thread>
#include<windows.h>
using namespace std;



int main_MkdirFile(string s1) {
  
  string s = "mkdir "+s1;
  system(s.c_str());
  cout << "已创建文件夹" << s1 << endl;
  
  return 0;
}

int main(int n, char *c[])  {
  
  // string s[2];
  // for(int i = 0; i < n; i++) {
  //   for(int j = 0; j < strlen(c[i]); j++) {
  //     s[i] += c[i][j];
  //   }
  // }
  
  thread t(main_MkdirFile, "zain");
  t.detach();
  
  Sleep(1000);
  //system("pause");
  
  return 0;
}

