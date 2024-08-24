#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    int i, j, n, m;
    cin >> n;

    pair<int,int> a[n];

    for(i=0;i<n;i++)
    {
        int x, y;
        cin >> x >> y;

        a[i] = {x, y};
    }

    sort(a, a+n);

    set<int> ni;
    int ans = 0;
    for(i=0;i<n;i++)
    {
        while(!ni.empty() && *ni.begin() < a[i].first)
            ni.erase(ni.begin());

        ni.insert(a[i].second);
        ans = max(ans, (int)ni.size());
    }

    cout << ans << "\n";
    
    return 0;
}