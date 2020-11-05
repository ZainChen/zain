#include"./zain-algorithm/zain-algorithm.cpp"

/**
 * 开始查找代码文件中的中文
 */
void startFind();

/**
 * 提示输入或拖入待查找文件夹或文件（路径不能包含中文字符）
 */
string cinFilePath();

/**
 * 提示输入查找后，生成的结果文件储存路径（路径不能包含中文字符）
 */
string coutFilePath();

/**
 * 获取输入文件或文件夹下所有文件路径
 * 参数:
 *     path: 输入的，待查找的文件或文件夹
 * 返回值:
 *     文件或文件夹下所有文件路径
 */
vector<string> getFilePathAll(string path);

/**
 * 过滤掉指定后缀名的文件，不参与查找（忽略后缀名大小写）
 * 参数:
 *     pathAll: 待过滤的所有文件路径（包含文件名）
 *     suffixes: 所有指定需要过滤的后缀
 * 返回值:
 *     过滤后的所有文件路径
 */
vector<string> filterFileSuffixes(vector<string> pathAll, vector<string> suffixes);

/**
 * 判断路径是否等于指定后缀
 * 参数:
 *     path: 待判断的路径
 *     suffixes: 待判断的后缀
 * 返回值:
 *     true|false: 路径的后缀名等于指定后缀|路径的后缀名不等于指定后缀
 */
bool equalSuffixes(string path, string suffixes);

/**
 * 查找所有指定文件中的所有中文字符
 * 参数:
 *     filePaths: 所有文件路径
 * 返回值:
 *     找到的所有中文数据（chineseDataAll: 所有中文数据, chineseAnnotateAll: 所有中文注释, chineseNotAnnotateAll: 所有非注释中文）
 */
map<string, string> findFilesChineseData(vector<string> filePaths);

/**
 * 判断字符串数据，中文是否全在注释中
 * 参数:
 *     data: 带判断的字符串数据
 * 返回值:
 *     true|false: 中文都在注释中|有中文在非注释中
 */
bool confirmChineseAnnotate(string data);

/**
 * 查找字符串中的所有中文字符串（查找规则，下列符号中的都是中文字符串：'', "", ``, ><, <>）
 * 参数:
 *     data: 待查找的数据
 * 返回值:
 *     找到的所有中文字符串
 */
vector<string> findChineseString(string data);
