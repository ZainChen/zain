#include"zain_algorithm.h"

//遵循结构:永远只有叶子节点存放内容

//----------标题属性值----------
typedef struct {
    int iAlign;  //数据显示表对齐方式
    int iWidth;  //属性格宽度
    string strValue;  //属性值
} ZY_DATA_TITLE_VALUE;

//----------数据固定属性值(且列位置固定)----------
typedef struct {
    int iId;  //编号(十进制,可修改,不能重复)(所有库文件节点唯一标识符,在所有库中都不可重复)
    string strName;  //数据库名(值可修改,不能重复)
    string strPath;  //路径(值不可修改,自动修改)
} ZY_DATA_CON_FIX;

//----------数据----------
typedef struct zy_data {
	vector<ZY_DATA_TITLE_VALUE> vecStrTitleData;  //数据属性标题
    
    vector<ZY_DATA_CON_FIX> vecZdcf;  //所有数据固定属性值

    //完整数据值(完整数据值长度:度固定值数量+其他值)
    typedef struct {
        ZY_DATA_CON_FIX zdcf;  //固定属性值
        vector<string> vecStrCon;  //其它值
        vector<zy_data> vecVecStrDT;  //递归调用自身,链接数据表和表内容等(只存一个)
    } ZY_DATA_COM;
    
    map<int, ZY_DATA_COM > mapIdToDB;  //Id(编号)对应完整数据
    map<string, ZY_DATA_COM > mapNameToDB;  //数据名对应完整数据
    map<string, ZY_DATA_COM > mapPathToDB;  //数据路径对应完整数据

} ZY_DATA;
