#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    int i, j, n, m;
    cin >> n;

    int a[n];
    for(i=0;i<n;i++)
        cin >> a[i];

    int l=0, r;
    ll csum = a[0], ans = a[0];
    for(r=1;r<n;r++)
    {
        csum = max(1ll * a[r], a[r] + csum);
        // csum += a[r];
        // while(l < r && csum - a[l] > csum) {
        //     csum -= a[l];
        //     l++;
        // }

        ans = max(ans, csum);
    }

    cout << ans << "\n";
    
    return 0;
}