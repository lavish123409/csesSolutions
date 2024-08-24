#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 4 2 1 5 3
/*

    _ _ 1 _ _
    _ 2 _ _ 3
    4 _ _ 5 _

    2 -> 2i < 1i => r1+1
         2i > 1i => r1

    a, b

    ra is changed or r(a+1) is changed
    rb is changed or r(b+1) is changed
*/

int main()
{
    int i, j, n, m;
    cin >> n >> m;

    int pos[n+1], val[n+1];
    for(i=1;i<=n;i++) {
        int x;
        cin >> x;

        val[i] = x;
        pos[x] = i;
    }

    int ans = 1;
    for(i=1;i<n;i++) {
        ans += (pos[i+1] < pos[i]);
    }

    while(m--) {
        int l, r;
        cin >> l >> r;

        set<pair<int,int>> invPairs;
        if(val[l] + 1 <= n) {
            invPairs.insert({val[l] , val[l] + 1});
        }
        if(val[l] - 1 >= 1) {
            invPairs.insert({val[l] - 1 , val[l]});
        }
        if(val[r] + 1 <= n) {
            invPairs.insert({val[r] , val[r] + 1});
        }
        if(val[r] - 1 >= 1) {
            invPairs.insert({val[r] - 1 , val[r]});
        }

        for(auto cp : invPairs) {
            ans -= (pos[cp.second] < pos[cp.first]);
        }

        swap(val[l], val[r]);

        pos[val[l]] = l;
        pos[val[r]] = r;
        
        for(auto cp : invPairs) {
            ans += (pos[cp.second] < pos[cp.first]);
        }

        cout << ans << "\n";
    }
    // int arr[n];
    // pair<int,int> ni[n];
    // for(i=0;i<n;i++) {
    //     int x;
    //     cin >> x;

    //     ni[i] = {x, i};
    //     arr[i] = x;
    // }

    // sort(ni, ni+n);
    
    // int ans=1;
    // for(i=1;i<n;i++) {
    //     ans += (ni[i].second < ni[i-1].second);
    // }

    // while(m--) {
    //     cout << "ans1 : " << ans << "\n";

    //     for(i=0;i<n;i++) {
    //         cout << arr[i] << " ";
    //     }
    //     cout << "\n";
    //     int ai, bi;
    //     cin >> ai >> bi;

    //     ai--;
    //     bi--;

    //     cout << ai << " , " << bi << "\n";
    //     int a = arr[ai];
    //     int b = arr[bi];
    //     cout << a << " , " << b << "\n";

    //     int pai = ni[a-1].second;
    //     int pam1i = -1;
    //     if(a != 1) {
    //         pam1i = ni[a-2].second;
    //     }
    //     int pap1i = n;
    //     if(a != n) {
    //         pap1i = ni[a].second;
    //     }
        
    //     int pbi = ni[b-1].second;
    //     int pbm1i = -1;
    //     if(b != 1) {
    //         pbm1i = ni[b-2].second;
    //     }
    //     int pbp1i = n;
    //     if(b != n) {
    //         pbp1i = ni[b].second;
    //     }
    //     cout << "pa : (" << a-1 << " , " << pam1i << ") , (" << a << " , " << pai << ") , (" << a+1 << " , " << pap1i << ")\n";
    //     cout << "pb : (" << b-1 << " , " << pbm1i << ") , (" << b << " , " << pbi << ") , (" << b+1 << " , " << pbp1i << ")\n";

    //     swap(arr[ai], arr[bi]);
    //     ni[a-1].second = bi;
    //     ni[b-1].second = ai;
        
    //     int nai = ni[a-1].second;
    //     int nam1i = -1;
    //     if(a != 1) {
    //         nam1i = ni[a-2].second;
    //     }
    //     int nap1i = n;
    //     if(a != n) {
    //         nap1i = ni[a].second;
    //     }
        
    //     int nbi = ni[b-1].second;
    //     int nbm1i = -1;
    //     if(b != 1) {
    //         nbm1i = ni[b-2].second;
    //     }
    //     int nbp1i = n;
    //     if(b != n) {
    //         nbp1i = ni[b].second;
    //     }

    //     cout << "na : (" << a-1 << " , " << nam1i << ") , (" << a << " , " << nai << ") , (" << a+1 << " , " << nap1i << ")\n";
    //     cout << "nb : (" << b-1 << " , " << nbm1i << ") , (" << b << " , " << nbi << ") , (" << b+1 << " , " << nbp1i << ")\n";

    //     // cout << "ac1 - " << (pai < pam1i && nai > nam1i) << "\n";
    //     // cout << "ac2 - " << (pap1i < pai && nap1i > nai) << "\n";
    //     // cout << "ac3 - " << (pai > pam1i && nai < nam1i) << "\n";
    //     // cout << "ac4 - " << (pap1i > pai && nap1i < nai) << "\n";
    //     if(pai < pam1i && nai > nam1i) {
    //         ans--;
    //         cout << "ad1\n";
    //     }
    //     if(pap1i < pai && nap1i > nai) {
    //         ans--;
    //         cout << "ad2\n";
    //     }
    //     if((pai > pam1i && nai < nam1i)) {
    //         ans++;
    //         cout << "ai1\n";
    //     }
    //     if(pap1i > pai && nap1i < nai) {
    //         ans++;
    //         cout << "ai2\n";
    //     }

    //     // cout << "bc1 - " << (pbi < pbm1i && nbi > nbm1i) << "\n";
    //     // cout << "bc2 - " << (pbp1i < pbi && nbp1i > nbi) << "\n";
    //     // cout << "bc3 - " << (pbi > pbm1i && nbi < nbm1i) << "\n";
    //     // cout << "bc4 - " << (pbp1i > pbi && nbp1i < nbi) << "\n";
    //     if(pbi < pbm1i && nbi > nbm1i) {
    //         ans--;
    //         cout << "bd1\n";
    //     }
    //     if(pbp1i < pbi && nbp1i > nbi) {
    //         ans--;
    //         cout << "bd2\n";
    //     }
    //     if((pbi > pbm1i && nbi < nbm1i)) {
    //         ans++;
    //         cout << "bi1\n";
    //     }
    //     if(pbp1i > pbi && nbp1i < nbi) {
    //         ans++;
    //         cout << "bi2\n";
    //     }

    //     cout << "ans2 : " << ans << "\n";

        // cout << ans << " <- 0\n";
        // if(a != 1) {
        //     int am1i = ni[a-2].second;
        //     if(ai < am1i && bi > am1i)
        //         ans--;
        //     else if(ai > am1i && bi < am1i)
        //         ans++;
        // }
        // cout << ans << " <- 1\n";

        // if(a != n) {
        //     int ap1i = ni[a].second;
        //     if(ap1i < ai && ap1i > bi)
        //         ans--;
        //     else if(ap1i > ai && ap1i < bi)
        //         ans++;
        // }
        // cout << ans << " <- 2\n";
        
        // if(b != 1) {
        //     int bm1i = ni[b-2].second;
        //     if(bi < bm1i && ai > bm1i)
        //         ans--;
        //     else if(bi > bm1i && ai < bm1i)
        //         ans++;
        // }
        // cout << ans << " <- 3\n";

        // if(b != n) {
        //     int bp1i = ni[b].second;
        //     if(bp1i < bi && bp1i > ai)
        //         ans--;
        //     else if(bp1i > bi && bp1i < ai)
        //         ans++;
        // }
        // cout << ans << " <- 4\n";
        
        // swap(arr[ai], arr[bi]);
        // ni[a-1].second = bi;
        // ni[b-1].second = ai;

        // cout << ans << "\n";
    // }

    return 0;
}