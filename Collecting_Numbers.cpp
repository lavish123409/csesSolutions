#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 4 2 1 5 3
/*

    1st -> 4 5
    2nd -> 2 3
    3rd -> 1

    [4 5]
    [2 3]
    [1]

    cmir = [
        5
        3
        1
    ] <- sorted

    for n in arr:
        if there exist max number in cmir < n:
            cmir[round] = n
        else
            cmir.push(n)

    there exist max number in cmir {
        ptr = upper bound(cmir, n)
        ptr--
        if ptr exist => there exist max number in cmir < n
    }

*/

int main()
{
    int i, j, n, m;
    cin >> n;

    pair<int,int> a[n];
    for(i=0;i<n;i++) {
        int x;
        cin >> x;

        a[i] = {x, i};
    }

    sort(a, a+n);
    int ans = 1;
    for(i=1;i<n;i++) {
        ans += (a[i].second < a[i-1].second);
    }

    cout << ans << "\n";

    // set<int> cn;
    // int nnf = 1, ans = 0;
    // for(i=n-1;i>=0;i--) {
    //     cn.insert(a[i]);
    //     if(a[i] == nnf) {
    //         ans++;
    //         while(cn.count(nnf)) nnf++;
    //     }
    // }

    // cout << ans << "\n";

    // vector<int> ans;
    // for(i=0;i<n;i++) {
    //     // int gni = upper_bound(ans.rbegin(), ans.rend(), a[i]) - ans.rbegin();
    //     // gni--;
    //     // gni = n - 1 - gni;
    //     int as = ans.size();
    //     int gni = upper_bound(ans.rbegin(), ans.rend(), a[i]) - ans.rbegin();
    //     gni--;
    //     // for(int it : ans) {
    //     //     cout << it << " ";
    //     // }
    //     // cout << "\n";
    //     // // gni = int(as) - 1 - gni;
    //     // cout << "gni : " << gni << "\n";
    //     if(gni < 0)
    //         ans.push_back(a[i]);
    //     else
    //         ans[as - 1 - gni] = a[i];
    // }

    // // vector<int> ans = {5, 4, 3, 2, 1};
    // // cout << upper_bound(ans.rbegin(), ans.rend(), 5) - ans.rbegin()<< "\n";

    // cout << ans.size() << "\n";
    
    return 0;
}