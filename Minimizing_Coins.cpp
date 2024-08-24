#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    int i, j, n, x;
    cin >> n >> x;

    int c[n], dp[x+1];
    for(i=0;i<n;i++)
        cin >> c[i];

    // sort(c, c+n);

    // memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for(i=1;i<=x;i++)
    {
        dp[i] = INT_MAX;
        for(j=0;j<n;j++)
        {
            // if(c[j] > i)
            //     break;
            if(i >= c[j] && dp[i - c[j]] != -1)
                dp[i] = min(dp[i], dp[i - c[j]] + 1);
        }
        if(dp[i] == INT_MAX)
            dp[i] = -1;
        // cout << i << " : " << dp[i] << " , ";
    }
    // cout << "\n";

    cout << dp[x] << "\n";

    
    return 0;
}