#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool isValid(int i, int j, int n, int m)
{
    return (i >= 0 && i < n && j >= 0 && j < m);
}

void dfs(vector<vector<char>>& grd, int i, int j, int n, int m, vector<vector<bool>>& vis)
{
    // if(!isValid(i, j, n, m) || grd[i][j] == '#' || vis[i][j])
    //     return;

    vis[i][j] = 1;
    int dirs[] = {-1, 0, 1, 0, 0, -1, 0, 1};
    int k;
    for(k=0;k<4;k++)
    {
        int ni = i + dirs[2*k];
        int nj = j + dirs[2*k+1];

        if(isValid(ni, nj, n, m) && grd[ni][nj] != '#' && !vis[ni][nj])
            dfs(grd, ni, nj, n, m, vis);
    }
}


int main()
{
    int i, j, n, m;
    cin >> n >> m;

    vector<vector<char>> grd(n, vector<char>(m));
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
            cin >> grd[i][j];
    }

    // for(i=0;i<n;i++)
    // {
    //     for(j=0;j<m;j++)
    //         cout << grd[i][j] << " ";
    //     cout << "\n";
    // }

    int ans = 0;
    vector<vector<bool>> vis(n, vector<bool>(m));
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            if(grd[i][j] != '#' && !vis[i][j])
            {
                dfs(grd, i, j, n, m, vis);
                // cout << i << " , " << j << "\n";
                ans ++;
            }

    cout << ans << "\n";

    return 0;
}