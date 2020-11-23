/** 腾讯文档面试，2020.11.23 */
/**
 * 1、已知长度的两个单向链表，判断是否相交 （这个没要求写代码）
 * 2、两个升序数组合并，要求合并后依然升序。（下列代码实现，有两种方法）
 */

function sortZain(a, l, r) {
    if (l < r) {
        let i = l;
        const p =  a[r];
        for(let k = l; k < r; k++) {
            if (a[k] < p) {
                [a[k], a[i]] = [a[i], a[k]];
                i++;
            }
        }
        [a[i], a[r]] = [a[r], a[i]];
        sortZain(a, l, i - 1);
        sortZain(a, i + 1, r);
    }
    return a;
}

function arrayZian(x1, x2) {
    let newArray = [...x1, ...x2];
    sortZain(newArray, 0, newArray.length - 1);
    return newArray;
}

function arrayZian1(x1, x2) {
    let newArray = [];
    let k1 = 0;
    let k2 = 0;
    let swap1 = null;
    let swap2 = null;
    if (x1[0] < x2[0]) {
        k1++;
        swap1 = x1[0];
        newArray.push(swap1);
    } else {
        k2++;
        swap2 = x2[0];
        newArray.push(swap2);
    }
    while (k1 < x1.length || k2 < x2.length) {
        if (swap1 !== null) {
            while (k2 < x2.length && x2[k2] < x1[k1]) {
                newArray.push(x2[k2]);
                swap2 = x2[k2];
                k2++;
            }
            if (k1 === x1.length) {
                while (k2 < x2.length) {
                    newArray.push(x2[k2]);
                    k2++;
                }
            }
            swap2 = 'ok';
            swap1 = null;
        } else {
            while (k1 < x1.length && x1[k1] < x2[k2]) {
                newArray.push(x1[k1]);
                swap1 = x1[k1];
                k1++;
            }
            if (k2 === x2.length) {
                while (k1 < x1.length) {
                    newArray.push(x1[k1]);
                    k1++;
                }
            }
            swap1 = 'ok';
            swap2 = null;
        }
    }
    return newArray;
}

const a1 = [0, 2, 5, 8, 10];
const a2 = [1, 7, 9, 75, 99];

// console.log(arrayZian(a1, a2));

const aaaa = arrayZian1(a1, a2);

console.log(aaaa);
