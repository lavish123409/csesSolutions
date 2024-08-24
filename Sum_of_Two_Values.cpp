#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    int i, j, n, m;
    cin >> n >> m;

    pair<int,int> a[n];

    for(i=0;i<n;i++)
    {
        int x, y;
        cin >> x;

        a[i] = {x, i};
    }

    sort(a, a+n);

    int l=0, r=n-1;
    while(l < r)
    {
        int sum = a[l].first + a[r].first;
        if(sum == m)
        {
            cout << (a[l].second + 1) << " " << (a[r].second + 1) << "\n";
            return 0;
        }
        else if(sum < m)
            l++;
        else
            r--;
    }

    cout << "IMPOSSIBLE\n";
    
    return 0;
}