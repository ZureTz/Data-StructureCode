#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int M, N, T;
    cin >> M >> N >> T;

    unordered_map<int, int> priority; // 保存每家快递公司的优先级
    unordered_map<int, bool> inPriorityList; // 保存是否在优先清单中

    for (int i = 1; i <= M; i++) {
        priority[i] = 0;
        inPriorityList[i] = false;
    }

    for (int i = 0; i < N; i++) {
        int ts, id;
        cin >> ts >> id;

        // 更新优先级
        priority[id] += 2;

        // 判断是否加入或清除出优先清单
        if (priority[id] > 5) {
            inPriorityList[id] = true;
        } else if (priority[id] <= 3) {
            inPriorityList[id] = false;
        }
    }

    int count = 0;
    for (auto it = inPriorityList.begin(); it != inPriorityList.end(); it++) {
        if (it->second) {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}