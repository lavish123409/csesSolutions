#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 7
/*

    take a queue

    takeIt = 0

    for element in queue:
        if takeIt:
            cout << queue.front()
            queue.pop()
        else:
            q.push(q.front())
            q.pop()
        takeIt = (takeIt + 1) % 2
    
*/

int main()
{

    int i, n;
    cin >> n;

    queue<int> nums;

    for(i=1;i<=n;i++) {
        nums.push(i);
    }

    int takeIt = 0;
    while(!nums.empty()) {
        if(takeIt) {
            cout << nums.front() << " ";
            nums.pop();
        }
        else {
            nums.push(nums.front());
            nums.pop();
        }

        takeIt = (takeIt + 1) % 2;
    }
    cout << "\n";

    return 0;
}