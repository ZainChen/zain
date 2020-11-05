#include<cstdio>
#include<cstdlib>
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<map>
#include<io.h>
#include<direct.h> //_mkdir函数的头文件
#include<windows.h>
using namespace std;

void getFiles(string path, vector<string>& files);  //获取指定路径下所有文件名和路径(包含子目录下的文件)
bool CreatePath(string strPath);  //创建文件夹(支持含子文件的文件夹)
vector<string> FileReadToString(string fileNamePath);  //从文件读取所有内容存入string串
vector<string> FileReadUTF8ToUnicodeString(string fileNamePath);  //从文件读取UTF8编码文件所有内容存入Unicode编码string串
bool StringWriteToFile(string fileNamePath, string data, string mode);  //将string串写入到指定文件
bool UnicodeToUTF8StringWriteToFile(string fileNamePath, string data, string mode);  //将Unicode编码string串写入到UTF8编码指定文件
bool IsFolder(string strPath);  //判断路径是否是文件夹

long long BinaryToInt(string s);  //二进制字符串转十进制
string IntToString(long long x);  //long long转string(数据不能是012)(数字不能以0开头)
long long StringToInt(string s);  //string转long long(字符为0-9)
string IntToHex(long long x, long long l);  //十进制转长度大于等于l的16进制串(数据不能是012)(大于十进制10的数字不能以0开头)(如果转换后的16进制串大于l,则取实际转换后的长度(如果长度为奇数,自动在高位补一个0),例:cout << IntToHex(64518, 3); //FC06)
long long HexsToInt(string s);  //十六进制字符串转十进制整数
vector<string> SplitStringChar(string str, char ck);  //按指定字符拆分指定string字符串到容器中
string aGetzToBig(string s);  //将字符串中的"a-z"全转换为大写的"A-Z"
long long FindIgnoreBsw(string fData, string sData, long long p);  //从字符串的第p个位置查找子串(忽略字母大小写)
string ReplaceALLHaveRepeat(string s, string olds, string news);  //字符串替换(替换后出现了要替换的字符串继续替换,直到替换找不到为止)
string ReplaceALLNoRepeat(string s, string olds, string news);  //字符串替换(只替换一遍)
int BigIntIsOneNubBig(string a, string b);  //大整数比较大小
string BigIntAdd(string a, string b);  //大整数相加
string BigIntMinus(string a, string b);  //大整数相减(第一个参数减第二个参数)

string GetSystemWindowTime();  //获取系统时间(精确到秒级),需要用到windows.h头文件
void PrintMemory();  //(内存情况比较简单)分别输出可用百分比，可以用物理内存/总物理内存，可用页面文件/总页面文件

CString StringtoCString(string str);  //string转CString
string CStringtoString(CString cs);  //CString转string


wchar_t * UTF8ToUnicode(const char* str);
char * UnicodeToUTF8(const wchar_t *str);
char * UnicodeToANSI(const wchar_t *str);
wchar_t * ANSIToUnicode(const char* str);
string UTF8StringToUnicodeString(string str);
string UnicodeStringToUTF8String(string str);
bool MessageBoxUTF8String(string str);

