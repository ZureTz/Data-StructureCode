# 第二次上机实验：与ChatGPT的代码对比分析

## 队列-贪心算法

> ###### 【问题描述】
>
> 食堂有N个同学要买饭，有M个窗口，第i个人打饭所需时间为Ti，请安排一个合理的方案使得所有人的等待时间之和尽量小。  
>
> 提示：
>
> 　　一种最佳买饭方案是，将N个人按照Ti从小到大的顺序依次分配到M个窗口买饭。
>
> 　　例如，Ti从小到大排序为1，2，3，4，5，6，7，将他们依次分配到3个窗口，则去窗口一买饭的为1，4，7；去窗口二买饭的为2,5；去第三个窗口买饭的为3,6。
>
> 　　第一个窗口买饭的人总等待时间 = 0 + 1 + (1 + 4) = 6
>
> 　　第二个窗口买饭的人总等待时间 = 0 + 2 = 2
>
> 　　第三个窗口买饭的人总等待时间 = 0 + 3 = 3
>
> 　　所以总的等待时间 = 6 + 2 + 3 = 11
>
> 【输入形式】
>
> 第一行两个正整数N和M ，接下来一行为N个正整数Ti。N,M<=1000，Ti<=1000
>
> 【输出形式】
>
> 最小的等待时间之和。（不需要输出具体的安排方案）
>
> 【样例输入】
>
> ```bash
> 7 3
> 3 6 1 4 2 5 7
> ```
>
> 【样例输出】
>
> ```bash
> 11
> ```
### 我的代码

```c++
#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <vector>
using std::cin;
using std::cout;
using ll = long long;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  ll n, m;
  cin >> n >> m;

  std::deque<ll> waitTimes;
  for (ll i = 0; i < n; ++i) {
    ll time;
    cin >> time;
    waitTimes.push_back(time);
  }
  std::sort(waitTimes.begin(), waitTimes.end());

  std::vector<ll> sumTime(m);
  ll result = 0;
  ll iter = 0;
  while (!waitTimes.empty()) {
    result += sumTime[iter];
    sumTime[iter] += waitTimes.front();
    waitTimes.pop_front();
    ++iter;
    if (iter == m) {
      iter = 0;
    }
  }
  cout << result;

  return 0;
}
```

### ChatGPT的代码

```c++
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
```

### 结论

在计算打饭时间总和的时候，首先要查看该窗口有没有人，如果没有人结果则+0；如果有人，将结果加上上个人的等待时间；加完后，上个人的等待时间再自增现在这个人的打饭时间，留给下一次使用。

所以这需要一个长度为打饭窗口的数量的数组`sumTime` 来存储之前的人的等待时间，再初始化一个总结果`result`，为`0`。依次与每个窗口的“上个人的等待时间相加，即`result += sumTime[iter]`，然后让`sumTime[iter] += waitTime.front()`，即让上个人的等待时间自增队列最前面那个人的打饭时间，以便下一次使用。

ChatGPT的代码实际上不如我自己写的代码。其实ChatGPT没有理解题意。

- 题目的意思是按照打饭时间从小到大排序，然后把排序后的队列按照从小到大的顺序出队，按照打饭窗口递增的顺序循环放入学生，然后计算打饭的时间总和，这也是我的算法所表达的意思。
- ChatGPT给出的解释如下：

> 这段代码使用贪心算法来解决给定的问题。
>
> 
>
> 首先，程序读取输入的N和M，分别表示有N个同学和M个窗口。
>
> 然后，程序创建一个大小为N的向量T，用来存储每个同学的打饭时间Ti。
>
> 接下来，程序对向量T进行排序，以便按照打饭时间从小到大进行分配。
>
> 
>
> 接下来，程序使用两层循环进行分配和计算等待时间。
>
> 
>
> 外层循环用来遍历窗口，内层循环用来遍历同学。
>
> 内层循环中，每次取出一个同学进行分配，跳过其他同学，直到遍历完所有同学。
>
> 内层循环的步长为窗口数M，目的是每次分配给每个窗口一个同学。
>
> 
>
> 在内层循环中，totalWaitTime变量累加每个窗口中同学的等待时间。
>
> 等待时间的计算使用j / M * T[j]，其中j表示同学的索引。
>
> 分配给第i个窗口的同学索引范围为i，i+M，i+2M，...，N-1。
>
> 
>
> 最后，程序将计算得到的totalWaitTime输出作为最小等待时间之和的结果。

ChatGPT给出的解释中，将同学分配给打饭窗口的过程是没有问题的。问题在于计算打饭时间总和。首先`j / M * T[j]`用来等待时间总和是不正确的，这看起来只能用来计算每个同学的打饭时间，但如果这样想，那么前面的`j / M`的系数是什么意义呢？可能GPT的理解是窗口序号越靠后。所需打饭时间越长，但这题显然不是这个意思。所以用GPT生成的代码是和题意不符合的。



## 栈和队列-优先级队列

> 【问题描述】
>
> ​    中国石油大学（北京）东门外有M家快递公司，编号 1～M。每家快递公司都有一个优先级，初始时 (0 时刻) 优先级都为0。每经过1个时间单位，如果快递公司没有业务，则优先级会减少1，最低减到0; 而如果快递公司有业务，则优先级不减反加，每有一单业务优先级加2。如果某家快递公司某时刻优先级大于5，则会被系统加入优先清单中；如果优先级小于等于3，则会被清除出优先清单。给定 T 时刻以内的N条业务信息，请你计算 T 时刻时有多少快递公司在优先清单中。
>
> 【输入形式】
>
>  第一行包含 3 个整数M、N和 T。以下N行每行包含两个整数 ts 和 id，表示 ts 时刻编号 id 的快递公司收到一个业务。对于 80% 的评测用例，1 ≤ M, N, T ≤ 10000。 对于所有评测用例，1 ≤ M,N,T ≤ 100000，1 ≤ ts ≤ T，1 ≤ id ≤ 。
>
> 【输出形式】
>
>  输出一个整数代表答案。
>
> 【样例输入】
>
>  ```bash
>2 6 6
>  1 1
>5 2
>  3 1
>6 2
>  2 1
>6 2
>  ```
>
>  【样例输出】
>
>  ```bash
>1
> ```

### 我的代码

```c++
#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
using std::cin;
using std::cout;
using ll = long long;

struct Company {
  ll index;
  ll priority;
  Company(ll index = 0ll, ll priority = 0ll)
      : index(index), priority(priority) {}
};

struct Task {
  ll time;
  ll taskIndex;
  Task(ll time = 0, ll index = 0) : time(time), taskIndex(index) {}
  bool operator==(const Task &rhs) const {
    return time == rhs.time && taskIndex == rhs.taskIndex;
  }
};
struct keyHasher {
  std::size_t operator()(const Task &op) const {
    return std::hash<ll>()(op.time) ^ (std::hash<ll>()(op.taskIndex) << 1);
  }
};

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  ll mComps, n, times;
  cin >> mComps >> n >> times;

  std::vector<ll> companys(mComps);
  std::set<ll> companyPriorityList;

  std::unordered_multiset<Task, keyHasher> inputTasks;
  for (int i = 0; i < n; ++i) {
    ll time, index;
    cin >> time >> index;
    inputTasks.insert(Task(time, index));
  }

  for (int i = 1; i <= times; ++i) {
    for (ll j = 0; j < mComps; ++j) {
      const ll count = inputTasks.count(Task(i, j + 1));
      if (count) {
        companys[j] += (2 * count);
        if (companys[j] > 5) {
          companyPriorityList.insert(j);
        }
        continue;
      }
      // else not found.
      companys[j]--;
      if (companys[j] <= 0) {
        companys[j] = 0;
      }
      if (companys[j] <= 3) {
        const auto itFind = companyPriorityList.find(j);
        if (itFind != companyPriorityList.end()) {
          companyPriorityList.erase(itFind);
        }
      }
    }
  }
  cout << companyPriorityList.size();

  return 0;
}
```

### ChatGPT的代码

```c++
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
```

### 结论

我自己的思路是：创建一个数组`companys`来储存每个公司的优先级，`company[i]`代表的就是第`i`个公司的优先级。然后再创建一个 `unordered_multiset inputTasks`来储存操作；然后，从时间点`1`开始，对每个公司进行遍历，在`inputTask`中寻找对应的`{时间点, 事件}`，如果没有找到，优先级降低1，直到0为止；如果找到，则优先级增加2；按照题目的意思，如果优先级大于5，则放入`companyPriorityList`中，如果如果优先级小于5，则从`companyPriorityList`中取出，最后，输出`companyPriorityList`的大小即可。

- ChatGPT的思路也是先储存公司的优先级（但是是用的`unordered_map<int, int> priority`）。

- 与第一题同样的，ChatGPT的代码也有一点小问题。在后面进行操作的时候，没有考虑到时间的先后顺序。由于优先级减小到0之后并不会继续减小，这意味着所有的任务不是线性的，也就是说，顺序不能调换，ChatGPT没能考虑到这一点。其次，ChatGPT没有考虑到，对于所有没有任务的公司，其优先级会-1。所以，优先级只会增加，不会减小，这是与题目的意思不合的。



## 栈和队列-字符序列组合

> 【问题描述】假设有两组字符序列α和β，初始时α和β的序列如下：
>
> ​           α序列：`[K, 8, X, K, A, 3, A, 9, 5, A]`  ；β序列：`[3, 7, K, 5, J, 5, Q, 6, K, 4]`。从 α开始， α、β轮流输出字符。当轮到某一序列输出时，从自己的字符队列的头部输出一个字符，放到一个容器里，并且压在容器里面最上面（如果有的话）。
>
> ​    执行过程如下：
>
> 　　 α输出K，β输出3， α输出8，β输出7， α输出X，此时容器里面的字符序列为：K,3,8,7,X。当轮到β输出时，他的字符K与容器的字符序列中的K相同，则把包括K在内的以及两个K之间的字符都收起来，放入自己字符队列的队尾。注意：为了操作方便，放入字符的顺序是与容器里面的顺序相反的。此时，α、β队列里面的字符为：
>
> 　　α序列：`[K, A, 3, A, 9, 5, A]`；β序列：`[5, J, 5, Q, 6, K, 4, K, X, 7, 8, 3, K]`
>
> ​    收集字符方继续输出字符。亦即，β序列继续输出5，α输出K，β输出J，α输出A，β输出5，又开始收集字符序列5,K,J,A,5。
>
> 　　此时，α、β队列里面的字符为： α序列：`[3, A, 9, 5, A]`；β序列：`[Q, 6, K, 4, K, X, 7, 8, 3, K, 5, A, J, K, 5]`.
>
> ​    注意：更多的时候收集字符方并不能把桌上的牌都赢走，而是拿走相同字符及其中间的部分。但无论如何，都是收集的一方继续输出字符，有的时候刚输出一个字符又收集字符，也是允许的。当某一序列输处全部字符后，但无法从容器里面收集字符时，过程立即结束。对于本例的初始情况下，最后 α序列会输出所有字符，而β序列最后的形式为：`9K2A62KAX58K57KJ5`。
>
> ​    本题的任务就是已知双方字符序列，计算过程结束时，非空序列的字符序列。当过程无法结束时，输出-1。
>
> 【输入形式】
>
>  输入为2行，2个字符串，分别表示 α、β双方初始手里的牌序列。
>
> 【输出形式】
>
>  输出为1行，1个串，表示 α先出牌，最后非空序列的字符序列。

### 我的代码

```c++
#include <cstddef>
#include <deque>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
using std::cin;
using std::cout;

inline size_t hash(const std::string &s1, const std::string &s2) {
  return std::hash<std::string>()(s1) ^ (std::hash<std::string>()(s2) << 1);
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  std::string alpha, beta;
  cin >> alpha >> beta;

  std::string stack;
  bool flag = true;
  std::unordered_set<size_t> duplicateSet;

  while (!alpha.empty() && !beta.empty()) {
    // cout << alpha << ' ' << beta << ' ' << stack << std::endl;
    const size_t hashNum = hash(alpha, beta);
    // cycle detected, means the execution is infinite
    if (duplicateSet.find(hashNum) != duplicateSet.end()) {
      cout << "-1" << std::endl;
      return 0;
    }

    if (flag) {
      char temp = alpha.front();
      alpha.erase(0, 1);

      size_t find = stack.find(std::string(1, temp));
      if (find != std::string::npos) {
        flag = true;
        alpha.push_back(temp);
        alpha.append(stack.begin(), stack.begin() + find + 1);
        stack.erase(stack.begin(), stack.begin() + find + 1);
        continue;
      }

      stack.insert(0, 1, temp);
      flag = !flag;
      continue;
    }

    char temp = beta.front();
    beta.erase(0, 1);

    size_t find = stack.find(std::string(1, temp));
    if (find != std::string::npos) {
      flag = false;
      beta.push_back(temp);
      beta.append(stack.begin(), stack.begin() + find + 1);
      stack.erase(stack.begin(), stack.begin() + find + 1);
      continue;
    }

    stack.insert(0, 1, temp);
    flag = !flag;
    continue;
  }

  // cout<<alpha<<' '<<beta<<std::endl;
  cout << (alpha.empty() ? beta : alpha) << std::endl;
  return 0;
}
```

### ChatGPT的代码

```c++
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
```

### 结论

这题的主要思路是，把`alpha`和`beta`两个字符串想像成一个队列，而把`stack`想像成一个栈，也就是游戏中的桌子；使用`flag`来追踪哪个字符串会给出字符；如果一个`alpha`，`beta`中的任意一个从`stack`中收集了字符，那么下一个给出字符的就是收集字符的那个字符串。最后，如果任意一个字符串为空，则输出另一个字符串。

这题的难点在于，判断是否会无限进行，判断是否无限进行的主要方法是判断是否会产生周期。这里将每个执行步骤的`alpha`和`beta`字符串计算hash值，并存放在`duplicateSet`中，如果在后面运行的过程中发现产生的hash与`duplicateSet`中的相同，则说明产生了周期，这个时候，就要输出`-1`。

- ChatGPT的主要思路就错了。在`playGame()`中，给出代码的意思是当`alpha[i]`与`beta[j]`相同的时候将字符压入`beta`中，跟题目的意思不一样。
- ChatGPT给出的代码，没有判断是否可能会产生的循环，只以`stack`是否为空来判断是否会无限运行下去，这是不正确的。
