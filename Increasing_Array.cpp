#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    int n, i;
    cin >> n;

    int mx=0;
    ll ans=0;

    for(i=0;i<n;i++)
    {
        int x;
        cin >> x;

        if(x >= mx)
            mx = x;
        else
        {
            ans += (mx - x);
        }
    }

    cout << ans << "\n";

    return 0;
}