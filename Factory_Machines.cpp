#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 3 2 5
/*

    limit after which we can make target or more than target products

    I approach (cheated from william lin)
    - binary search the answer, from 0 to max in array * target
    - take mid value of time and traverse through the array
    - find out how many total products can be made
    - check if total products made is greater than or equal to the target
        - if it is, current time value can be a potential answer and we can find better answer on left side (less time)
        - otherwise, it is not our answer and we can search answer on right side (more time)

    l=0
    r = max(numOfSec)
    ans = r
    while l <= r:
        m = l + r / 2
        totalProducts = 0
        for time in numOfSec:
            totalProducts += (m / time)

        if totalProducts >= target:
            ans = m
            r = m-1
        else:
            l = m+1

    print ans
*/

int main()
{

    int i, n, target;
    cin >> n >> target;

    int a[n];
    ll l=0, r=INT_MAX;
    for(i=0;i<n;i++) {
        cin >> a[i];
        r = min(r, 1ll * a[i]);
    }
    r *= target;
    ll ans=0;

    while(l <= r) {
        ll m = l + (r - l) / 2;
        ll totalProducts = 0;
        for(i=0;i<n;i++) {
            totalProducts += (m / a[i]);
        }
        // cout << "m: " << m << " - ";
        // cout << "tp: " << totalProducts << "\n";

        if(totalProducts >= target) {
            ans = m;
            r = m-1;
        }
        else {
            l = m+1;
        }
    }

    // ll x=0;
    // for(i=0;i<n;i++) {
    //     x += (41666667 / a[i]);
    //     cout << x << " ";
    // }
    // cout << "\n";
    // cout << x << " : " << (x >= target) << "\n";
    // cout << (41666667 * 25) << "\n";
    // cout << (1ll * 41666670 * 25) << "\n";

    // cout << "------------------------------------------------------\n";
    // x=0;
    // for(i=0;i<n;i++) {
    //     x += (41666667 / a[i]);
    //     cout << x << " ";
    // }
    // cout << "\n";
    // cout << x << " : " << (x >= target) << "\n";
    // cout << (41666667 * 25) << "\n";
    // cout << (1ll * 41666667 * 25) << "\n";

    cout << ans << "\n";

    return 0;
}