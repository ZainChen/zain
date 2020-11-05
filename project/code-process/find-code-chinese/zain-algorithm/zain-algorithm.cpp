#include"zain-algorithm.h"

// int main(int argc, char* argv[]) {
//     system("CHCP 65001");  //cmd 字符输出改为 utf-8
//     cout << "--------------------\n";

//     cout << zain::IncludeChinese("zain志银") << endl;
//     cout << zain::IncludeChinese("zain") << endl;
//     cout << zain::IncludeChinese("za志银in") << endl;

//     system("pause");
//     return 0;
// }

namespace zain {

/*
获取指定路径下所有文件名和路径(包含子目录下的文件)
头文件:
  #include<io.h>
  #include<vector>
  #include<iostream>
  using namespace std;
参数:
  string path: 指定文件夹路径
  vector<string>& files: 获取到的所有文件名及路径
返回值:
  无
例子:
  vector<string> files;
  getFiles("./data", files);
  for(long long i = 0; i < files.size(); i++) cout << files[i].c_str() << endl;
*/
void getFiles(string path, vector<string>& files) {
	long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			if ((fileinfo.attrib &  _A_SUBDIR)) {
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else {
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

/*
创建文件夹(支持含子文件的文件夹)
头文件:
  #include <direct.h> //_mkdir函数的头文件
  #include <io.h>     //_access函数的头文件
  #include<iostream>
  #include <string>
  using namespace std;
参数:
  string strPath: 待创建的文件名及路径
返回值:
  true: 写入成功
  false: 写入失败
例子:
  vector<string> vecPath;
  vecPath.push_back("C:\\Users\\Administrator\\Desktop\\main\\zain1\\jane1");
  vecPath.push_back("C:\\Users/Administrator\\Desktop\\main/zain2\\jane2\\");
  vecPath.push_back("C:\\Users/Administrator\\Desktop\\main/zain2.1\\jane2/.1");
  vecPath.push_back("./zain3\\jane3");
  vecPath.push_back(".\\zain4/jane4");
  //vecPath.push_back("\\zain5/jane5");  //暂不支持 
  //vecPath.push_back("/zain6\\jane6");  //暂不支持 
  vecPath.push_back("zain7/jane7");
  vecPath.push_back(".zain8/.jane8");
  vecPath.push_back(".zain9/.jane9/");
  vecPath.push_back(".zain10/.jane10\\");
  //vecPath.push_back("../zain8/.jane8");  //暂不支持 
  
  for(int i = 0; i < vecPath.size(); i++) {
    CreatePath(vecPath[i]);
  }
函数说明:
  _access(FilePath, Mode);  //判断文件夹是否存在;FilePath为文件夹路径,Mode为模式(下列四个模式)
  #define R_OK 4 //Test for read permission.
  #define W_OK 2 //Test for write permission.
  #define X_OK 1 //Test for execute permission.
  #define F_OK 0 //Test for existence.
*/
bool CreatePath(string strPath) {
  int iColon = 0, iPos = 0;
  string strPathCreate;
  
  for(int i = 0; i < strPath.size(); i++)
    if(strPath[i] == ':')
      iColon++;
  
  if(iColon > 1) {
    cout << "失败1,文件名为空或包含下列字符:/\\:*?\"<>|\n";
    return false;
  } else if(iColon == 1) {
    iColon = 0;
    int k = 0;
    for(int i = 0; i < strPath.size(); i++) {
      if(strPath[i] == ':') {
        iColon++;
      } else if(strPath[i] == '/' || strPath[i] == '\\') {
        k++;
      }
      strPathCreate += strPath[i];
      iPos++;
      if(iColon == 1 && k == 2)
        break;
    }
    //cout << strPathCreate << endl;
    if(_access(strPathCreate.c_str(), 0) == -1) {
      int iret = _mkdir(strPathCreate.c_str());  //文件名不能包含下列任何字符:/\:*?"<>|
      if(iret == -1) {
        cout << "失败2,文件名为空或包含下列字符:/\\:*?\"<>|\n";
        return false;
      }
    } else {
      //cout << "失败3,文件夹已存在\n";
    }
  }
  
  for(int i = iPos; i < strPath.size(); i++) {
    if(strPath[i] == '/' || strPath[i] == '\\') {
      //cout << strPathCreate << endl;
      if(_access(strPathCreate.c_str(), 0) == -1) {
        int iret = _mkdir(strPathCreate.c_str());  //文件名不能包含下列任何字符:/\:*?"<>|
        if(iret == -1) {
          cout << "失败3,文件名为空或包含下列字符:/\\:*?\"<>|\n";
          return false;
        }
      } else {
        //cout << "失败3,文件夹已存在\n";
      }
    }
    strPathCreate += strPath[i];
  }
  if(strPathCreate != "") {
    //cout << strPathCreate << endl;
    if(_access(strPathCreate.c_str(), 0) == -1) {
      int iret = _mkdir(strPathCreate.c_str());  //文件名不能包含下列任何字符:/\:*?"<>|
      if(iret == -1) {
        cout << "失败4,文件名为空或包含下列字符:/\\:*?\"<>|\n";
        return false;
      }
    } else {
      //cout << "失败3,文件夹已存在\n";
    }
  }
  
  cout << "文件夹创建成功:"+strPath+"\n";
  return true;
}

/*
从文件读取所有内容存入string串
头文件:
  #include<fstream>
  #include<string>
  #include<vector>
  #include<iostream>
  using namespace std;
参数:
  string fileNamePath: 待读取的文件名及路径
返回值:
  储存读取到的所有内容
例子:
  vector<string> str = FileReadToString("./EcuIdS/ysId.txt");
  for(long long i = 0; i < str.size(); i++) cout << str[i] << endl;
*/
vector<string> FileReadToString(string fileNamePath) {
	char iFileNameC[10005];  //打开文件的路径参数需要char型
	vector<string> str;

	if (fileNamePath.size() >= 10000) {
		cout << "string字符串太长,不给予转换为char型:" << fileNamePath << endl;
		return str;
	}

	for (long long i = 0; i < fileNamePath.size(); i++) iFileNameC[i] = fileNamePath[i];
	iFileNameC[fileNamePath.size()] = '\0';

	ifstream ifile;
	ifile.open(iFileNameC, ios::binary);
	if (!ifile) {
		cout << "zain > 找不到文件:" << fileNamePath << "\n";
		return str;
	}
	string data;

	while (getline(ifile, data)) {
		//cout << data << endl;
		str.push_back(data);
	}
	ifile.close();
	return str;
}



/*
将string串写入到指定文件
头文件:
  #include<fstream>
  #include<string>
  #include<iostream>
  using namespace std;
参数:
  string fileNamePath: 待写入的文件名及路径
  string data: 待写入的数据
  string mode: 写入模拟(mode == tail:尾加到源文件;mode == rewrite:重写替换掉源文件所有旧内容)
返回值:
  true: 写入成功
  false: 写入失败
例子:
  无
*/
bool StringWriteToFile(string fileNamePath, string data, string mode) {
	char oFileNameC[10005];  //打开文件的路径参数需要char型
							 //FileNameStringToChar(oFileNameC, fileNamePath);

	if (fileNamePath.size() >= 10000) {
		cout << "string字符串太长,不给予转换为char型:" << fileNamePath << endl;
		return false;
	}

	for (long long i = 0; i < fileNamePath.size(); i++) oFileNameC[i] = fileNamePath[i];
	oFileNameC[fileNamePath.size()] = '\0';

	if (mode == "rewrite") remove(oFileNameC);  //写入前删除该文件(清空文件)
	else if (mode != "tail") {
		cout << "第三个参数错误\n";
		return false;
	}
	ofstream ofile;
	//ofile.open(oFileNameC, ios::app);
	ofile.open(oFileNameC, std::ios::out | std::ios::binary | ios::app);  //已二进制流形式写入文件 
	
	if (!ofile) {  //当文件名不合法时,无法打开或创建文件(文件名不能包含下列字符:\/:*?"<>|)
		cout << "打开或创建文件失败,可能是路径不存在或文件名不合法(文件名不能包含下列字符:\\/:*?\"<>|)\n";
		return false;
	}
	
	ofile << data;
	ofile.close();
	return true;
}

/*
判断路径是否是文件夹
头文件:
  #include<string>
  #include<iostream>
  using namespace std;
参数:
  string strPath: 路径串
返回值:
  true: 是文件夹 
  false: 不是文件夹 
例子:
  无
*/
bool IsFolder(string strPath) {
  int a = 0, b = 0;
  for(int i = strPath.size()-1; i >= 0; i--) {
    if(strPath[i] == '\\' || strPath[i] == '/') {
      a++;
    } else if(strPath[i] == '.') {
      b++;
    }
    if(b == 0 && a > 0)
      return true;
    if(b > 0 && a == 0)
      return false;
  }
  return false;
}

/*
二进制字符串转十进制
头文件:
	#include<iostream>
	using namespace std;
参数:
	string s: 待转化二进制字符串
返回值:
	long long : 转换后的十进制数
例子:
	cout << BinaryToInt("000010101"); //21
*/
long long BinaryToInt(string s) {
	long long sum = 0;
	int k = 0;
	for(int i = s.size()-1; i >= 0; i--) {
		long long q = 1;
		for(int j = 1; j <= k; j++) {
			q *= 2;
		}
		sum += (s[i]-48)*q;
		k++;
	}
	return sum;
}

/*
long long转string(数据不能是012)(数字不能以0开头)
头文件:
#include<string>
#include<iostream>
using namespace std;
参数:
long long x:  待转化的长整形数字
返回值:
x转化为string类型后的字符串
例子:
cout << IntToString(9564) << endl;  //9564
cout << IntToString(00142745) << endl;  //50661  //数字不能以0开头
*/
string IntToString(long long x) {
	if (x == 0) return "0";
	string s = "", s1 = "";
	while (x) {
		s1 += ((x % 10) + '0');
		x /= 10;
	}
	for (long long i = s1.size() - 1; i >= 0; i--) {
		s += s1[i];
	}
	return s;
}

/*
十进制转长度大于等于l的16进制串(数据不能是012)(大于十进制10的数字不能以0开头)(如果转换后的16进制串大于l,则取实际转换后的长度(如果长度为奇数,自动在高位补一个0),例:cout << IntToHex(64518, 3); //FC06)
头文件:
#include<string>
#include<iostream>
using namespace std;
参数:
long long x: 待转换的十进制数
long long l: 转换后的16进制串最小长度(如果转换后的16进制串大于l,则取实际转换后的长度,例:cout << IntToHex(64518, 3); //FC06)
返回值:
转换后的16进制串
例子:
cout << IntToHex(64518, 3); //FC06
*/
string IntToHex(long long x, long long l) {
	string s, a;
	do {
		switch (x % 16) {
		case 10: s += "A"; break;
		case 11: s += "B"; break;
		case 12: s += "C"; break;
		case 13: s += "D"; break;
		case 14: s += "E"; break;
		case 15: s += "F"; break;
		default: s += (char)((x % 16) + '0'); break;
		}
		x /= 16;
	} while (x);
	for (int i = s.size() - 1; i >= 0; i--) a += s[i];

	string ra;
	if (a.size() == 0) cout << "转换错误！！！\n";
	else {
		if (l - a.size() <= 0) {
			if (a.size() % 2) ra += "0";
		}
		else {
			for (int i = 1; i <= l - a.size(); i++) ra += "0";
		}
		ra += a;
	}
	return ra;
}

/*
十六进制字符串转十进制整数
头文件:
#include<string>
#include<iostream>
using namespace std;
参数:
string s: 待转化的十六进制字符串
返回值:
转化后的十进制整数
例子:
cout << HexsToInt("0095");  //输出:149
*/
long long HexsToInt(string s) {
	long long x = 0;
	string s1;
	int k = 0;
	for(long long i = 0; i < s.size(); i++) {
		if(k == 0 && s[i] != '0') {
			s1 += s[i];
			k = 1;
		} else if(k == 1) {
			s1 += s[i];
		}
	}
	if(k == 0) return 0;
	for(long long i = s1.size()-1; i >= 0; i--) {
		long long q = 1;
		for(long long j = 1; j <= s1.size()-1-i; j++)
			q *= 16;
		long long x1 = 0;
		if(s1[i] >= '0' && s1[i] <= '9') x1 = (int)(s1[i]-48);
		else if(s1[i] == 'A' || s1[i] == 'a') x1 = 10;
		else if(s1[i] == 'B' || s1[i] == 'b') x1 = 11;
		else if(s1[i] == 'C' || s1[i] == 'c') x1 = 12;
		else if(s1[i] == 'D' || s1[i] == 'd') x1 = 13;
		else if(s1[i] == 'E' || s1[i] == 'e') x1 = 14;
		else if(s1[i] == 'F' || s1[i] == 'f') x1 = 15;
		x = x+(q*x1);
	}
	return x;
}

/*
string转long long(字符为0-9)
头文件:
#include<string>
#include<iostream>
using namespace std;
参数:
string s:  待转换的字符串
返回值:
s转化为long long类型后的整数
例子:
cout << StringToInt("9564") << endl;  //9564
cout << StringToInt("00142745") << endl;  //142745
*/
long long StringToInt(string s) {
	long long x = 0;
	for (int i = 0; i < s.size(); i++) {
		x = x * 10 + (s[i] - '0');
	}
	return x;
}

//CString StringtoCString(string str) {
//#ifdef _UNICODE
//	//如果是unicode工程
//	USES_CONVERSION; CString s(str.c_str());
//	CString ans(str.c_str());
//	return ans;
//#else
//	//如果是多字节工程
//	//string 转 CString
//	CString ans;
//	ans.Format("%s", str.c_str());
//	return ans;
//#endif // _UNICODE
//}

//string CStringtoString(CString cs) {
//#ifdef _UNICODE
//	//如果是unicode工程
//	USES_CONVERSION;
//	std::string str(W2A(cs));
//	return str;
//#else
//	//如果是多字节工程
//	std::string str(cs.GetBuffer());
//	cs.ReleaseBuffer();
//	return str;
//#endif // _UNICODE
//}

/*
按指定字符拆分指定string字符串到容器中
头文件:
#include<vector>
#include<string>
#include<iostream>
using namespace std;
参数:
string str:  待拆分的字符串
string sk:  用来判断的拆分符
返回值:
拆分后的N个字符串
例子:
vector<string> sn = SplitStringChar("1	*INFINITI EX35 Camp:P8202	J50	2008	NULL	VI_202	2	NULL1	NULL2", '\t');
for(int i = 0; i < sn.size(); i++) cout << sn[i] << endl;
*/
vector<string> SplitStringChar(string str, char ck) {
	vector<string> sr;
	string s;
	long long t = 0;
	for (long long i = 0; i < str.size(); i++) {
		if (str[i] == ck) {
			t++;
			sr.push_back(s);
			s = "";
		}
		else s += str[i];
	}
	if (s != "") sr.push_back(s);
	return sr;
}

/*
将字符串中的"a-z"全转换为大写的"A-Z"
头文件:
#include<string>
#include<iostream>
using namespace std;
参数:
string s:  待转化的字符串
返回值:
s中所有小写字母全转换为大写字母后的字符串
例子:
cout << aGetzToBig("fewa2334ASF");  //输出:FEWA2334ASF
*/
string aGetzToBig(string s) {  //将字符串中的"a-z"全转换为大写的"A-Z"
	string bigStr;
	for (long long i = 0; i < s.size(); i++)
		if (s[i] >= 'a' && s[i] < 'z') bigStr += s[i] - 32;
		else bigStr += s[i];
	return bigStr;
}

/*
从字符串的第p个位置查找子串(忽略字母大小写)
头文件:
#include<string>
#include<iostream>
using namespace std;
参数:
string fData: 待查找的父串
string sData: 用来查找匹配父串的子串
long long p: 查找父串的起始位置(下标)
返回值:
data.npos: 没找到
!= data.npos: 找到后的第一个子串在母串中的位置(下标)
例子:
无
*/
long long FindIgnoreBsw(string fData, string sData, long long p) {
	string f, s;
	//方法:只要将所有串都统一转化为大写或小写即可实现忽略大小写的串查找
	for (long long i = 0; i < fData.size(); i++) {
		if (fData[i] >= 'A' && fData[i] <= 'Z') f += (fData[i] + 32);
		else f += fData[i];
	}
	for (long long i = 0; i < sData.size(); i++) {
		if (sData[i] >= 'A' && sData[i] <= 'Z') s += (sData[i] + 32);
		else s += sData[i];
	}
	//cout << f << "<---->" << s << endl;
	return f.find(s, p);
}

/*
字符串替换(替换后出现了要替换的字符串继续替换,直到替换找不到为止)
头文件:
#include<string>
#include<iostream>
using namespace std;
参数:
string s: 要处理的字符串
string olds: 将要被替换的内容
string news: 替换后的内容
返回值:
s替换处理完成的后的字符串
例子:
cout << ReplaceALLHaveRepeat("12212", "12", "21") << endl;  //22211
*/
string ReplaceALLHaveRepeat(string s, string olds, string news) {
	while(true) {
		long long p = s.find(olds);
		if(p != s.npos) s.replace(p, olds.size(), news);
		else break;
	}
	return s;
}

/*
字符串替换(只替换一遍)
头文件:
    #include<string>
    #include<iostream>
    using namespace std;
参数:
    string s: 要处理的字符串
    string olds: 将要被替换的内容
    string news: 替换后的内容
返回值:
    s替换处理完成的后的字符串
例子:
    cout << ReplaceALLNoRepeat("12212", "12", "21") << endl;  //21221
*/
string ReplaceALLNoRepeat(string s, string olds, string news) {
  for(long long p = 0; p < s.size(); p += news.size()) {
    p = s.find(olds, p);
    if(p != s.npos) s.replace(p, olds.size(), news);
    else break;
  }
  return s;
}

/**
 * 判断字符串中是否存在中文
 * 头文件:
 *     #include<string>
 *     #include<iostream>
 *     using namespace std;
 * 参数:
 *     string s: 要判断的字符串
 * 返回值:
 *     true|false: 存在中文|不存在中文
 */
bool IncludeChinese(string s) {
    // 方法1: ascll 码判断是否是全角字符
    // for(int i = 0; i < s.size(); i++) {
    //     if(!(s[i] >= 0 && s[i] <= 127)) {
    //         return true;
    //     }
    // }
    // return false;

    // 方法2: 位运算
    for(int i = 0; i < s.size() - 1; i++) {
        if(s[i]&0x80 && s[i+1]&0x80) {
            return true;
        }
    }
    return false;
}

/*
大整数比较大小
头文件:
  #include<string>
  #include<iostream>
  using namespace std;
参数:
  string a: 大整数a(0-9)
  string b: 大整数b(0-9)
返回值:
  int: -1|0|1|2: 参数异常|两个参数相等|第一个参数大|第一个参数小
例子:
  无
*/
int BigIntIsOneNubBig(string a, string b) {
  string x, y;
  int k = 0, la = a.size(), lb = b.size();
  for(int i = 0; i < la; i++)
    if(!(a[i] >= '0' && a[i] <= '9'))
      return -1;
  for(int i = 0; i < lb; i++)
    if(!(b[i] >= '0' && b[i] <= '9'))
      return -1;
  while(a[k] == '0' && k < la) k++;
  for(int i = k; i < la; i++)
    x += a[i];
  k = 0;
  while(b[k] == '0' && k < lb) k++;
  for(int i = k; i < lb; i++)
    y += b[i];
  int lx = x.size(), ly = y.size();
  if(lx > ly)
    return 1;
  else if(lx < ly)
    return 2;
  else {
    for(int i = 0; i < lx; i++) {
      if(x[i] > y[i])
        return 1;
      else if(x[i] < y[i])
        return 2;
    }
    return 0;
  }
}

/*
大整数相加 
头文件:
  #include<string>
  #include<iostream>
  using namespace std;
参数:
  string a: 加数a(0-9)
  string b: 加数b(0-9)
返回值:
  string: 大整数相加结果 
例子:
  无
*/
string BigIntAdd(string a, string b) {
  string sum, s, t;
  int len = 0, l1 = a.size(), l2 = b.size(), k = 0, p = 0;
  if(l1 >= l2) {
    for(int i = 0; i < l1-l2; i++)
      t += "0";
    b = t+b;
    len = l1;
  } else if(l1 < l2) {
    for(int i = 0; i < l2-l1; i++)
      t += "0";
    a = t+a;
    len = l2;
  }
  for(int i = len-1; i >= 0; i--) {
    p = (a[i]-'0')+(b[i]-'0')+k;
    k = p/10;
    s += p%10+'0';
  }
  if(k > 0)
    s += k+'0';
  for(int i = s.size()-1; i >= 0; i--)
    sum += s[i];
  return sum;
}

/*
大整数相减(第一个参数减第二个参数)(待开发...)
头文件:
  #include<string>
  #include<iostream>
  using namespace std;
参数:
  string a: 被减数a(0-9)
  string b: 减数b(0-9)
返回值:
  string: 大整数相加结果
例子:
  无
  5420
  0384
*/
string BigIntMinus(string a, string b) {
  string ret;
  int p = BigIntIsOneNubBig(a, b);
  if(p == 0) {
    ret = "0";
  } else if(p == 1) {

  } else if(p == 2) {
    ret += "-";

  }
  

  
  //ret = a+b;

  return ret; 
} 


/**
 * 整形数组快速排序
 * 头文件:
 * #include<string>
 * #include<iostream>
 * using namespace std;
 * 参数:
 * int a[]: 带排序的数组
 * int l: 左区间
 * int r: 右区间
 * 返回值: 空
 * 例子:
 * int a[] = { 2, 1, 4, 5, 3, 8, 7, 9, 0, 6 };
 * zain::quickSortInt(a, 0, sizeof(a)/sizeof(a[0])-1);
 * for (int i = 0; i < 10; i++) {
 *   cout << a[i] << " ";
 * }
 */
void quickSortInt(int* arr, int low, int high) {
    if(low >= high) return;
    int i = low+1, j = high, k = arr[low], temp;
    while(i < j) {
        while(i < j && arr[j] > k) j--;
        while(i < j && arr[i] < k) i++;
        if(i == j) break;
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    if(arr[low] > arr[j]) {
        temp = arr[low];
        arr[low] = arr[j];
        arr[j] = temp;
    }
    quickSortInt(arr, low, i-1);
    quickSortInt(arr, i+1, high);
}

/*
获取系统时间(精确到秒级),需要用到windows.h头文件
头文件:
  #include<cstdio>
  #include<Windows.h>
参数:
  无
返回值:
  string: 当前系统时间(精确到秒级)
例子:
  无
*/
string GetSystemWindowTime() {
	string strTime;
	//int y, m, d, H, M, S, MS, dw;
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	//y = sys.wYear;
	//m = sys.wMonth;
	//d = sys.wDay;
	//H = sys.wHour;
	//M = sys.wMinute;
	//S = sys.wSecond;
	//MS = sys.wMilliseconds;
	//dw = sys.wDayOfWeek;
	char buffer[500];
	sprintf(buffer, "%4d/%02d/%02d %02d:%02d:%02d.%03d 星期%1d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, sys.wDayOfWeek);
	//sprintf_s(buffer, "[Zain %4d/%02d/%02d-%02d:%02d:%02d.%03d]: ", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
	strTime = buffer;
	return strTime;
}


/*
(内存情况比较简单)分别输出可用百分比，可以用物理内存/总物理内存，可用页面文件/总页面文件
头文件:
  #include<cstdio>
  #include<Windows.h>
参数:
  无
返回值:
  无
例子:
  无
*/
void PrintMemory() {
  while(1) {
    MEMORYSTATUSEX mstx;
  	mstx.dwLength = sizeof (mstx);
  	GlobalMemoryStatusEx( &mstx );
  	int iMemeryUsePercentage = mstx.dwMemoryLoad;
  	int iTotalPhysMB = mstx.ullTotalPhys/1024/1024;
  	int iAvailPhysMB = mstx.ullAvailPhys/1024/1024;
  	int iTotalPageFileMB = mstx.ullTotalPageFile/1024/1024;
  	int iAvailPageFileMB = mstx.ullAvailPageFile/1024/1024;
  	char LogBuff[128];
  	memset( LogBuff , 0 , 128 );
  	sprintf( LogBuff , "MemAvailPct=%d%% Phys=%d/%d PageFile=%d/%d" , 100 - iMemeryUsePercentage , iAvailPhysMB , iTotalPhysMB , iAvailPageFileMB , iTotalPageFileMB );
  	//sprintf_s( LogBuff , "MemAvailPct=%d%% Phys=%d/%d PageFile=%d/%d" , 100 - iMemeryUsePercentage , iAvailPhysMB , iTotalPhysMB , iAvailPageFileMB , iTotalPageFileMB );  //MFC使用这条 
    //printf("%s\n",LogBuff);
    printf("%s\r", LogBuff);
    Sleep(100);
  }
}

}