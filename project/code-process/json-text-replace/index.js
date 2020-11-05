let fs = require('fs');
let zhCN = fs.readFileSync('zh-CN.json');
let enUS = fs.readFileSync('en-US.json');
let zhCNData = JSON.parse(zhCN);
let enUSData = JSON.parse(enUS);

// 格式化英文
let mapKeyToEn = new Map();
let mapCnToEn = new Map();
function dfsSetMapKeyToEn(parentKey, object) {
    for(let key in object) {
        let comKey = parentKey+'/'+key;
        if(typeof object[key] === 'object') {
            dfsSetMapKeyToEn(key, object[key]);
        } else if(typeof object[key] === 'string') {
            // 判断 key 包含中文字符
            if(escape(key).indexOf("%u") !=-1) {
                mapCnToEn.set(key, object[key]);
                // console.log(key, '=====', object[key]);
            } else {
                mapKeyToEn.set(comKey, object[key]);
                // console.log(comKey, '=====', object[key]);
            }
        }
    }
}
dfsSetMapKeyToEn('', enUSData);

function dfsTranslateZhCN(parentKey, object) {
    for(let key in object) {
        let comKey = parentKey+'/'+key;
        if(typeof object[key] === 'object') {
            dfsTranslateZhCN(key, object[key]);
        } else if(typeof object[key] === 'string') {
            let comKeyToString = mapKeyToEn.get(comKey);
            if(comKeyToString) {
                object[key] = comKeyToString;
                // console.log(comKey, '=====', object[key]);
            } else {
                let cnToEn = mapCnToEn.get(object[key]);
                if(cnToEn) {
                    // console.log(comKey, '=====', object[key]);
                    object[key] = cnToEn;
                } else {
                    writeRemainderCn += comKey+'\t'+object[key]+'\n';
                    console.log(comKey, '=====', object[key]);
                }
            }
        }
    }
}
let writeRemainderCn = '';
let writeZhCNData = zhCNData;
dfsTranslateZhCN('', writeZhCNData);

fs.writeFileSync('./en-US-new.json', JSON.stringify(writeZhCNData, null, '    '));
fs.writeFileSync('./remainderCn.txt', writeRemainderCn);
