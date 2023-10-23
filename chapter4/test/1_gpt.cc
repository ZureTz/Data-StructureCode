#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> T(N);
    for (int i = 0; i < N; i++) {
        cin >> T[i];
    }

    sort(T.begin(), T.end());

    int totalWaitTime = 0;
    for (int i = 0; i < M; i++) {
        for (int j = i; j < N; j += M) {
            totalWaitTime += j / M * T[j];
        }
    }

    cout << totalWaitTime << endl;

    return 0;
}