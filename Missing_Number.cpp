#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    int n;
    cin >> n;

    ll sum = 0ll;
    int i;
    for(i=0;i<n-1;i++)
    {
        int x;
        cin >> x;
        sum += x;
    }

    cout << ((1ll * n * (n + 1)) / 2 - sum) << "\n";

    return 0;
}