#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 1 2 1 3 2 7 4 2
/*

    _ y _ x _ _ _ x y

    ans = 0
    li = {e1 -> i1, e2 -> i2}
    lgi = -1

    for ind, el in arr:
        if li[el] > lgi:
            lgi = li[el]
        
        ans = max(ans, ind - lgi)
        li[el] = ind

    return ans

*/

int main()
{
    int i, n;
    cin >> n;

    int a[n];
    map<int,int> li;
    for(i=0;i<n;i++) {
        cin >> a[i];
    }

    int ans = 0, lgi = -1;
    for(i=0;i<n;i++) { //  1 : [1 1 1 1 1 1]
        if(li.count(a[i]) && li[a[i]] > lgi) { // {1 -> 0}
            lgi = li[a[i]]; // lgi = 0
        }

        ans = max(ans, i - lgi); // ans = max(1, 1 - (0)) = 1
        li[a[i]] = i; // {1 -> 1}
    }

    cout << ans << "\n";
    return 0;
}