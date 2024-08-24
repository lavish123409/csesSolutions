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

    sort(a, a+n, [](pair<int,int>& a, pair<int,int>& b) {
        return a.second < b.second || (a.second == b.second && a.first < b.first);
    });

    int ciet=0, ans = 0;
    for(i=0;i<n;i++)
    {
        if(a[i].first < ciet)
            continue;

        ans++;
        ciet = a[i].second;
    }

    cout << ans << "\n";
    
    return 0;
}