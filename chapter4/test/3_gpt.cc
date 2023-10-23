#include <iostream>
#include <string>
#include <stack>
using namespace std;

string playGame(string alpha, string beta) {
    stack<char> container; // 容器

    int i = 0, j = 0; // 两个序列的索引
    int alphaLen = alpha.length();
    int betaLen = beta.length();

    while (i < alphaLen && j < betaLen) {
        char a = alpha[i];
        char b = beta[j];
        
        if (a == b) { // 当前字符相同
            // 将容器中的字符压入对方的序列中
            while (!container.empty()) {
                beta += container.top();
                container.pop();
            }

            // 将当前字符及其之间的字符从序列中移除
            alpha.erase(0, i + 1);
            beta.erase(0, j + 1);

            i = 0; // 从头开始继续比较
            j = 0;
        } else {
            // 将字符添加到容器中
            container.push(a);

            // 切换到下一个字符
            if (i + 1 < alphaLen) i++;
            if (j + 1 < betaLen) j++;
        }
    }

    // 将容器中的字符加入到非空序列中
    string result;
    while (!container.empty()) {
        result += container.top();
        container.pop();
    }

    // 如果alpha序列不为空，则将剩余字符加入到结果中
    if (i < alphaLen) {
        result += alpha.substr(i);
    }

    return result;
}

int main() {
    string alpha, beta;
    cin >> alpha >> beta;

    string result = playGame(alpha, beta);
    if (result.empty()) {
        cout << -1 << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}