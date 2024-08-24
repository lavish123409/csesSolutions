#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 1 6
// 2 4
// 4 8
// 3 6
// {1 6}, {2 4}, {3 6}, {4 8}
/*

    sort intervals according to start time

    for every interval
    see on left => every interval start before current interval => if we find any interval whose end time > current end time => current interval is contained in some other interval
    see on right => every interval start after current interval => if we find any interval whose end time < current end time => current interval is containing some other interval

    - traverse left to right in sorted array
    - keep maximum ending time till now
    - compare it with current interval

    - traverse right to left in sorted array
    - keep minmum ending time till now
    - compare it with current interval
    

    WA 1
    - it can also happen that start time is same, then there can exist an interval on right of current interval whose start time is same but end time is high (i.e, current interval can be contained in it)

    improvment 1
    - take maximum prefix array
    - do upper bound on interval array
    - if maximum till ub index-1 > current end time -> 1 else 0
    - similar from right side 

    not possible -> too many cases to cover

    solution
    - we can just change the sort operator such that intervals are sorted according to start time but if start time is same, biggest end time should come first, so that it can contain other intervals on right
*/

int main()
{

    int i, n;
    cin >> n;

    // vector<array<int, 3>> a(n);
    array<int, 3> a[n];
    for(i=0;i<n;i++) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;
    }

    // sort(a.begin(), a.end());
    sort(a, a+n, [](array<int,3> a, array<int,3> b) {
        return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
    });

    // for(i=0;i<n;i++) {
    //     cout << "{" << a[i][0] << " , " << a[i][1] << "} - ";
    // }
    // cout << "\n";

    // vector<int> rhtmn(n), lftmx(n);

    // lftmx[0] = a[0][1];
    // for(i=1;i<n;i++) {
    //     lftmx[i] = max(lftmx[i-1], a[i][1]);
    // }

    // rhtmn[n-1] = a[n-1][1];
    // for(i=n-2;i>=0;i--) {
    //     rhtmn[i] = min(rhtmn[i+1], a[i][1]);
    // }

    // for(i=0;i<n;i++) {
    //     cout << lftmx[i] << " ";
    // }
    // cout << "\n";
    
    // for(i=0;i<n;i++) {
    //     cout << rhtmn[i] << " ";
    // }
    // cout << "\n";

    // vector<bool> contains(n), contained(n);

    // // for(i=n-1;i>=0;i--) {
    // for(i=0;i<n;i++) {
    //     // int ubi = upper_bound(a.begin(), a.end(), {a[i][0], 0, -1}) - a.begin();
    //     int ltei = -1;
    //     int l=i, r=n-1;
    //     while(l <= r) {
    //         int m = l+ (r - l) / 2;
    //         if(a[m][0] <= a[i][0]) {
    //             ltei = m;
    //             l = m+1;
    //         }
    //         else {
    //             r = m-1;
    //         }
    //     }

    //     cout << i << " : " << ltei << "\n";

    //     if(a[ltei][0] < a[i][0]) {
    //         contained[a[i][2]] = lftmx[ltei] >= a[i][1];
    //     }
    //     else {
    //         contained[a[i][2]] = lftmx[ltei] > a[i][1];
    //     }
    //     if(ltei < n-1) {
    //         contains[a[i][2]] = rhtmn[ltei+1] <= a[i][1];
    //     }

    // }

    // for(i=0;i<n;i++) {
    //     cout << contains[i] << " ";
    // }
    // cout << "\n";
    
    // for(i=0;i<n;i++) {
    //     cout << contained[i] << " ";
    // }
    // cout << "\n";

    int rhtmn = int(1e9+1);
    // stack<int> st;
    vector<int> ans(n);
    for(i=n-1;i>=0;i--) {
        if(rhtmn <= a[i][1]) {
            // cout << 1 << " ";
            ans[a[i][2]] = 1;
        }
        else {
            // cout << 0 << " ";
            ans[a[i][2]] = 0;
            // st.push(0);
            rhtmn = a[i][1];
        }
    }

    // while(!st.empty()) {
    //     cout << st.top() << " ";
    //     st.pop();
    // }
    for(int it : ans) {
        cout << it << " ";
    }
    cout << "\n";

    // ans.clear();
    ans = vector<int>(n);
    int lftmx = 0;
    for(i=0;i<n;i++) {
        if(lftmx >= a[i][1]) {
            // cout << 1 << " ";
            ans[a[i][2]] = 1;
        }
        else {
            // cout << 0 << " ";
            ans[a[i][2]] = 0;
            lftmx = a[i][1];
        }
    }

    for(int it : ans) {
        cout << it << " ";
    }
    cout << "\n";
    
    return 0;
}