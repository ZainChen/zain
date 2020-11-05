#include"./find-code-chinese.h"

/**
 * 开始查找代码文件中的中文
 */
void startFind() {
    string strCinFilePath = cinFilePath();
    string strCoutFilePath = coutFilePath();
    vector<string> vecStrFilePathAll = getFilePathAll(strCinFilePath);
    string strSuffixes[7] = {".png", ".docx", ".ico", ".gif", ".json", ".test.ts", ".test.tsx"};
    vector<string> suffixes(strSuffixes, strSuffixes+7);
    vector<string> vecStrfilterFilePathAll = filterFileSuffixes(vecStrFilePathAll, suffixes);
    cout << "正在查找指定目录下所有文件内容...\n";
    map<string, string> mapFindData = findFilesChineseData(vecStrfilterFilePathAll);
    cout << "指定目录下所有文件内容查找完成.\n";
    cout << "正在写入所有中文数据...\n";
    zain::StringWriteToFile(strCoutFilePath+"/chineseDataAll.txt", mapFindData["chineseDataAll"], "rewrite");
    cout << "所有中文数据写入完成.\n";
    cout << "正在写入所有中文注释数据...\n";
    zain::StringWriteToFile(strCoutFilePath+"/chineseAnnotateAll.txt", mapFindData["chineseAnnotateAll"], "rewrite");
    cout << "所有中文注释数据写入完成.\n";
    cout << "正在写入所有非注释中文数据...\n";
    zain::StringWriteToFile(strCoutFilePath+"/chineseNotAnnotateAll.txt", mapFindData["chineseNotAnnotateAll"], "rewrite");
    cout << "所有非注释中文数据写入完成.\n";
    cout << "正在写入指定 json 数据...\n";
    zain::StringWriteToFile(strCoutFilePath+"/chineseJson.json", mapFindData["chineseJson"], "rewrite");
    cout << "指定 json 数据写入完成.\n";

}

/**
 * 提示输入或拖入待查找文件夹或文件（路径不能包含中文字符）
 */
string cinFilePath() {
    string strCinPath;
    cout << "---查找出所有指定文件中的中文、中文注释、中文非注释----\n";
    cout << "输入或拖入待查找文件夹或文件（路径不能包含中文字符）：";
    cin >> strCinPath;
    return strCinPath;
}

/**
 * 提示输入查找后，生成的结果文件储存路径（路径不能包含中文字符）
 */
string coutFilePath() {
    string strCoutPath;
    cout << "输入查找后，生成的结果文件储存路径（路径不能包含中文字符）：";
    cin >> strCoutPath;
    return strCoutPath;
}

/**
 * 获取输入文件或文件夹下所有文件路径
 * 参数:
 *     path: 输入的，待查找的文件或文件夹
 * 返回值:
 *     文件或文件夹下所有文件路径
 */
vector<string> getFilePathAll(string path) {
    vector<string> vecStrPathAll;
    if(zain::IsFolder(path)) {
        zain::getFiles(path, vecStrPathAll);
    } else {
        vecStrPathAll.push_back(path);
    }
    return vecStrPathAll;
}

/**
 * 过滤掉指定后缀名的文件，不参与查找（忽略后缀名大小写）
 * 参数:
 *     pathAll: 待过滤的所有文件路径（包含文件名）
 *     suffixes: 所有指定需要过滤的后缀
 * 返回值:
 *     过滤后的所有文件路径
 */
vector<string> filterFileSuffixes(vector<string> pathAll, vector<string> suffixes) {
    vector<string> filterFilePathAll;
    for(int i = 0; i < pathAll.size(); i++) {
        bool containSuffixes = false;
        for(int j = 0; j < suffixes.size(); j++) {
            if(equalSuffixes(pathAll[i], suffixes[j])) {
                containSuffixes = true;
                break;
            }
        }
        if(!containSuffixes) {
            filterFilePathAll.push_back(pathAll[i]);
        }
    }
    return filterFilePathAll;
}

/**
 * 判断路径是否等于指定后缀
 * 参数:
 *     path: 待判断的路径
 *     suffixes: 待判断的后缀
 * 返回值:
 *     true|false: 路径的后缀名等于指定后缀|路径的后缀名不等于指定后缀
 */
bool equalSuffixes(string path, string suffixes) {
    long long pathSize = path.size();
    long long suffixesSize = suffixes.size();
    if(pathSize <= 0 || suffixesSize <= 0) {
        return false;
    }
    if(pathSize < suffixesSize) {
        return false;
    }
    string bigPath = zain::aGetzToBig(path);
    string bigSuffixes = zain::aGetzToBig(suffixes);
    do {
        pathSize--;
        suffixesSize--;
        if(bigPath[pathSize] != bigSuffixes[suffixesSize]) {
            return false;
        }
    } while(suffixesSize > 0);
    return true;
}

/**
 * 查找所有指定文件中的所有中文字符
 * 参数:
 *     filePaths: 所有文件路径
 * 返回值:
 *     找到的所有中文数据（chineseDataAll: 所有中文数据, chineseAnnotateAll: 所有中文注释, chineseNotAnnotateAll: 所有非注释中文）
 */
map<string, string> findFilesChineseData(vector<string> filePaths) {
    map<string, string> mapData;
    mapData["chineseDataAll"] = "文件路径\t行号\t内容\n";
    mapData["chineseAnnotateAll"] = "文件路径\t行号\t内容\n";
    mapData["chineseNotAnnotateAll"] = "文件路径\t行号\t内容\n";
    mapData["chineseJson"] = "{\n    \"OtherAll\": {\n";
    for(long long i = 0; i < filePaths.size(); i++) {
        vector<string> vecStrData = zain::FileReadToString(filePaths[i]);
        for(long long j = 0; j < vecStrData.size(); j++) {
            if(zain::IncludeChinese(vecStrData[j])) {
                mapData["chineseDataAll"] += filePaths[i]+"\t"+zain::IntToString(j+1)+"\t"+vecStrData[j]+"\n";
                if(confirmChineseAnnotate(vecStrData[j])) {
                    mapData["chineseAnnotateAll"] += filePaths[i]+"\t"+zain::IntToString(j+1)+"\t"+vecStrData[j]+"\n";
                } else {
                    mapData["chineseNotAnnotateAll"] += filePaths[i]+"\t"+zain::IntToString(j+1)+"\t"+vecStrData[j]+"\n";
                    vector<string> vecStrChinese = findChineseString(vecStrData[j]);
                    for(long long k = 0; k < vecStrChinese.size(); k++) {
                        mapData["chineseJson"] += "        \""+vecStrChinese[k]+"\": \""+vecStrChinese[k]+"\",\n";
                    }
                }
            }
        }
    }
    mapData["chineseJson"] += "    }\n}\n";
    return mapData;
}

/**
 * 判断字符串数据，中文是否全在注释中
 * 参数:
 *     data: 带判断的字符串数据
 * 返回值:
 *     true|false: 中文都在注释中|有中文在非注释中
 */
bool confirmChineseAnnotate(string data) {
    int dataSize = data.size();
    // 遇到第一个 '*' 后，如果之前的字符都是 '空格' 或 '\t'，则判定为所有字符都在注释中
    string dataAsterisk = "";
    bool haveAsterisk = false;
    for(int i = 0; i < dataSize; i++) {
        if(data[i] == '*' || data[i] == '/') {
            haveAsterisk = true;
            break;
        } else {
            dataAsterisk += data[i];
        }
    }
    if(haveAsterisk) {
        bool allAnnotate = true;
        for(int i = 0; i < dataAsterisk.size(); i++) {
            if(!(dataAsterisk[i] == ' ' || dataAsterisk[i] == '\t')) {
                allAnnotate = false;
                break;
            }
        }
        if(allAnnotate) {
            return true;
        }
    }
    // 遇到第一个 '//' 后，如果之前的字符中含有中文，则判定有中文在非注释中
    bool haveDoubleSlash = false;
    string dataDoubleSlash = "";
    for(int i = 0; i < dataSize-1; i++) {
        if(data[i] == '/' && data[i+1] == '/') {
            haveDoubleSlash = true;
            break;
        } else {
            dataDoubleSlash += data[i];
        }
    }
    if(haveDoubleSlash) {
        if(zain::IncludeChinese(dataDoubleSlash)) {
            return false;
        } else {
            return true;
        }
    } else {
        // 如果没有 '*' 和 '//' 则判断字符串数据是否含有中文，有中文，则判定有中文在非注释中
        if(zain::IncludeChinese(data)) {
            return false;
        } else {
            return true;
        }
    }
}

// 标记重复中文串，用来去重
map<string, bool> mapMarkFindChineseString;
/**
 * 查找字符串中的所有中文字符串（查找规则，下列符号中的都是中文字符串：'', "", ``, ><, <>）
 * 参数:
 *     data: 待查找的数据
 * 返回值:
 *     找到的所有中文字符串
 */
vector<string> findChineseString(string data) {
    vector<string> vecStr;
    // 储存找到的中文字符串片段
    string strFind = "";
    // 标记开始记录的字符
    char startRecord = ' ';
    for(long long i = 0; i < data.size(); i++) {
        if(startRecord == ' ' && (data[i] == '\'' || data[i] == '\"' || data[i] == '`' || data[i] == '>')) {
            startRecord = data[i];
            continue;
        }
        if(startRecord != ' ') {
            if( startRecord == '\'' && data[i] == '\'' ||
                startRecord == '\"' && data[i] == '\"' ||
                startRecord == '`' && data[i] == '`' ||
                startRecord == '>' && data[i] == '<'
             ) {
                startRecord == ' ';
                if(strFind != "" && !mapMarkFindChineseString[strFind] && zain::IncludeChinese(strFind)) {
                    mapMarkFindChineseString[strFind] = true;
                    vecStr.push_back(strFind);
                }
                strFind = "";
                continue;
            }
            strFind += data[i];
        }
    }
    return vecStr;
}