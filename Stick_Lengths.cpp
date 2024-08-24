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

    sort(a, a+n);
    ll ans = 0ll;
    for(i=0;i<n;i++)
        ans += abs(a[n/2] - a[i]);

    cout << ans << "\n";
    
    return 0;
}