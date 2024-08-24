#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    int i, n, x;
    cin >> n >> x;

    int a[n];
    for(i=0;i<n;i++)
        cin >> a[i];

    sort(a, a+n);
    int j=n-1;
    i=0;

    int ans = 0;
    while(i <= j)
    {
        // cout << a[i] << " , " << a[j] << " ; ";
        if(i != j && a[i] + a[j] <= x)
        {
            ans++;
            i++;
            j--;
        }
        else
        {
            ans++;
            j--;
        }
        // cout << i << " , " << j << " : " << ans << "\n";
    }

    cout << ans << "\n";

    return 0;
}