#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 6 10
// 8 15
// 5 12
/*

    we can observe that either
    - finishing time should be less, or
    - deadline should be very high

    on trying example, {7 23}, {9 14}
    we can have 2 orders
    - (23 - 7) + (14 - (7 + 9))
    - (14 - 9) + (23 - (7 + 9))
    in both cases, everything else is same except there is -7 in 1st case and -9 in second case
    it specifies that taking task with less finishing time would always be beneficial
    and deadline order does not matter, even if start time differs
    
*/

int main()
{

    int i, n;
    cin >> n;

    array<int, 2> tasks[n];
    for(i=0;i<n;i++) {
        cin >> tasks[i][0] >> tasks[i][1];
    }

    sort(tasks, tasks+n);
    ll currTime = 0, ans = 0;
    for(i=0;i<n;i++) {
        currTime += tasks[i][0];
        ans += (tasks[i][1] - currTime);
    }

    cout << ans << "\n";
    
    return 0;
}