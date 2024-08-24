#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    int i, j, n, m;
    cin >> n >> m;

    map<int,int> h;
    int t[m];

    for(i=0;i<n;i++)
    {
        int x;
        cin >> x;

        h[x]++;
    }

    for(i=0;i<m;i++)
    {
        int x;
        cin >> x;

        // auto bpt = upper_bound(h.begin(), h.end(), {x, -1});
        auto bpt = h.upper_bound(x);
        if(bpt == h.begin())
        {
            cout << "-1\n";
            continue;
        }
        
        bpt--;
        int ans = (*bpt).first;
        cout << ans << "\n";

        int frq = (*bpt).second;
        if(frq == 1)
            h.erase(ans);
        else
            h[ans] = frq-1;

    }

    
    return 0;
}