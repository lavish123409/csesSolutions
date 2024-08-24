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
    ll sum = a[0];

    if(sum > 1) {
        cout << "1\n";
        return 0;
    }

    for(i=1;i<=n;i++) {
        if(i == n || a[i] > sum+1) {
            cout << sum+1 << "\n";
            return 0;
        }
        sum += a[i];
    }

    // cout << sum+1 << "\n";
    
    return 0;
}