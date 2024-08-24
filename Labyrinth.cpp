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

// void dfs(vector<vector<char>>& grd, pair<int,int> u, pair<int,int> dst, int n, int m, vector<vector<bool>>& vis, string& cpath, string& ans)
// {
//     int i = u.first, j = u.second;
//     if(!isValid(i, j, n, m) || grd[i][j] == '#' || vis[i][j])
//         return;

//     if(i == dst.first && j == dst.second)
//     {
//         if(ans.empty() || cpath.size() < ans.size())
//             ans = cpath;
//         return;
//     }

//     vis[i][j] = 1;

//     cpath.push_back('D');
//     dfs(grd, make_pair(i+1, j), dst, n, m, vis, cpath, ans);
//     cpath.pop_back();
    
//     cpath.push_back('U');
//     dfs(grd, make_pair(i-1, j), dst, n, m, vis, cpath, ans);
//     cpath.pop_back();
    
//     cpath.push_back('R');
//     dfs(grd, make_pair(i, j+1), dst, n, m, vis, cpath, ans);
//     cpath.pop_back();
    
//     cpath.push_back('L');
//     dfs(grd, make_pair(i, j-1), dst, n, m, vis, cpath, ans);
//     cpath.pop_back();
// }


int main()
{
    int i, j, n, m;
    cin >> n >> m;

    vector<vector<char>> grd(n, vector<char>(m));
    pair<int,int> src={-1, -1} , dst={-1, -1};
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            cin >> grd[i][j];
            if(grd[i][j] == 'A')
                src = {i, j};
            if(grd[i][j] == 'B')
                dst = {i, j};
        }
    }

    if(src.first == -1 || src.second == -1 || dst.first == -1 || dst.second == -1)
    {
        cout << "NO\n";
        return 0;
    }

    int ans = 0;
    vector<vector<int>> par(n, vector<int>(m));
    queue<pair<int,int>> q;
    q.push(src);
    par[src.first][src.second] = -1;

    int found = 0;
    // cout << src.first << " , " << src.second << "\n";
    // cout << dst.first << " , " << dst.second << "\n";

    while(!q.empty())
    {
        int cqs = q.size();
        while(cqs--)
        {

            // int x = get<0>(q.front());
            // int y = get<1>(q.front());
            // string cpath = get<2>(q.front());
            int ci = q.front().first;
            int cj = q.front().second;
            q.pop();
            // cout << x << " , " << y << " : " << cpath << "\n";

            if(ci == dst.first && cj == dst.second)
            {
                found = 1;
                break;
            }

            // if(x == dst.first && y == dst.second)
            // {
            //     cout << "YES\n";
            //     cout << ans << "\n";
            //     cout << cpath << "\n";
            //     found = 1;
            //     break;
            // }

            if(isValid(ci+1, cj, n, m) && grd[ci+1][cj] != '#' && !par[ci+1][cj])
            {
                // D
                q.push({ci+1, cj});
                par[ci+1][cj] = 1;
            }
            if(isValid(ci-1, cj, n, m) && grd[ci-1][cj] != '#' && !par[ci-1][cj])
            {
                // U
                q.push({ci-1, cj});
                par[ci-1][cj] = 2;
            }
            if(isValid(ci, cj+1, n, m) && grd[ci][cj+1] != '#' && !par[ci][cj+1])
            {
                // R
                q.push({ci, cj+1});
                par[ci][cj+1] = 3;
            }
            if(isValid(ci, cj-1, n, m) && grd[ci][cj-1] != '#' && !par[ci][cj-1])
            {
                // L
                q.push({ci, cj-1});
                par[ci][cj-1] = 4;
            }
        }
        if(found)
            break;
        ans++;
    }

    // for(i=0;i<n;i++)
    // {
    //     for(j=0;j<m;j++)
    //         cout << par[i][j] << " ";
    //     cout << "\n";
    // }

    if(!found)
        cout << "NO\n";
    else
    {
        int ci = dst.first;
        int cj = dst.second;

        string path = "";
        while(par[ci][cj] != -1)
        {
            if(par[ci][cj] == 1)
            {
                path.push_back('D');
                ci--;
            }
            else if(par[ci][cj] == 2)
            {
                path.push_back('U');
                ci++;
            }
            else if(par[ci][cj] == 3)
            {
                path.push_back('R');
                cj--;
            }
            else if(par[ci][cj] == 4)
            {
                path.push_back('L');
                cj++;
            }
        }

        reverse(path.begin(), path.end());
        cout << "YES\n";
        cout << ans << "\n";
        cout << path << "\n";
    }
    // queue<tuple<int,int,string>> q;
    // q.push({src.first, src.second, ""});
    // par[src.first][src.second] = -1;

    // int found = 0;
    // // cout << src.first << " , " << src.second << "\n";
    // // cout << dst.first << " , " << dst.second << "\n";

    // while(!q.empty())
    // {
    //     int cqs = q.size();
    //     while(cqs--)
    //     {

    //         int x = get<0>(q.front());
    //         int y = get<1>(q.front());
    //         string cpath = get<2>(q.front());
    //         q.pop();
    //         // cout << x << " , " << y << " : " << cpath << "\n";

    //         if(x == dst.first && y == dst.second)
    //         {
    //             cout << "YES\n";
    //             cout << ans << "\n";
    //             cout << cpath << "\n";
    //             found = 1;
    //             break;
    //         }

    //         if(isValid(x+1, y, n, m) && grd[x+1][y] != '#' && !par[x+1][y])
    //         {
    //             // cpath.push_back('D');
    //             q.push({x+1, y, cpath});
    //             cpath.pop_back();
    //             par[x+1][y] = 1;
    //         }
    //         if(isValid(x-1, y, n, m) && grd[x-1][y] != '#' && !par[x-1][y])
    //         {
    //             cpath.push_back('U');
    //             q.push({x-1, y, cpath});
    //             cpath.pop_back();
    //             par[x-1][y] = 1;
    //         }
    //         if(isValid(x, y+1, n, m) && grd[x][y+1] != '#' && !par[x][y+1])
    //         {
    //             cpath.push_back('R');
    //             q.push({x, y+1, cpath});
    //             cpath.pop_back();
    //             par[x][y+1] = 1;
    //         }
    //         if(isValid(x, y-1, n, m) && grd[x][y-1] != '#' && !par[x][y-1])
    //         {
    //             cpath.push_back('L');
    //             q.push({x, y-1, cpath});
    //             cpath.pop_back();
    //             par[x][y-1] = 1;
    //         }
    //     }
    //     if(found)
    //         break;
    //     ans++;
    // }

    // if(!found)
    //     cout << "NO\n";


    // for(i=0;i<n;i++)
    // {
    //     for(j=0;j<m;j++)
    //         cout << grd[i][j] << " ";
    //     cout << "\n";
    // }

    // for(i=0;i<n;i++)
    //     for(j=0;j<m;j++)
    //         if(grd[i][j] != '#' && !vis[i][j])
    //         {
    //             dfs(grd, i, j, n, m, vis);
    //             // cout << i << " , " << j << "\n";
    //             ans ++;
    //         }

    // cout << ans << "\n";

    // string cpath = "", ans = "";
    // dfs(grd, src, dst, n, m, vis, cpath, ans);

    return 0;
}