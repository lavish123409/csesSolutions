#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

bool isValid(int i, int j, int m, int n) {
    return (i >= 0 && i < m && j >= 0 && j < n);
}

void getLevels(queue<pair<int,int>>& q, vector<vector<char>>& mz, vector<vector<int>>& mopth, vector<vector<bool>>& vis, int m, int n) {
    
    // bool found = 0;
    int lvl = 0;
    while(!q.empty()) {
        int cqs = q.size();
        while(cqs--) {
            int ci = q.front().first;
            int cj = q.front().second;
            q.pop();

            mopth[ci][cj] = lvl;

            // if(ci == m-1 || ci == 0 || cj == n-1 || cj == 0) {
            //     found = 1;
            //     break;
            // }

            int dirs[] = {-1, 0, 1, 0, 0, 1, 0, -1};
            for(int k=0;k<4;k++) {
                int ni = ci + dirs[2*k];
                int nj = cj + dirs[2*k+1];

                if(isValid(ni, nj, m, n) && mz[ni][nj] != '#' && !vis[ni][nj]) {
                    q.push({ni, nj});
                    vis[ni][nj] = 1;
                }
            }
        }
        // if(found) break;
        lvl++;
    }
}

void printPath(vector<vector<int>>& mypth, int i, int j, int m, int n) {
    cout << "YES\n";
    cout << mypth[i][j] << "\n";
    string ans = "";
    string adirs = "DULR";
    while(mypth[i][j] != 0) {
        int clvl = mypth[i][j];
        int dirs[] = {-1, 0, 1, 0, 0, 1, 0, -1};
        for(int k=0;k<4;k++) {
            int ni = i + dirs[2*k];
            int nj = j + dirs[2*k+1];

            if(isValid(ni, nj, m, n) && mypth[ni][nj] + 1 == clvl) {
                i = ni;
                j = nj;
                ans.push_back(adirs[k]);
                break;
            }
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans << "\n";
}

int main()
{
    int i, j, n, m;
    cin >> m >> n;

    int si,sj;
    queue<pair<int,int>> q;
    vector<vector<bool>> vis(m, vector<bool>(n));
    vector<vector<char>> mz(m, vector<char>(n));
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++) {
            cin >> mz[i][j];
            if(mz[i][j] == 'A') {
                si = i;
                sj = j;
            }
            if(mz[i][j] == 'M') {
                q.push({i, j});
                vis[i][j] = 1;
            }
        }
    }

    vector<vector<int>> mopth(m, vector<int>(n, -1));
    getLevels(q, mz, mopth, vis, m, n);
    

    vis = vector<vector<bool>>(m, vector<bool>(n));
    vector<vector<int>> mypth(m, vector<int>(n, -1));

    q.push({si, sj});
    vis[si][sj] = 1;
    getLevels(q, mz, mypth, vis, m, n);

    // cout << "mopth : \n";
    // for(i=0;i<m;i++) {
    //     for(j=0;j<n;j++)
    //         cout << mopth[i][j] << " ";
    //     cout << "\n";
    // }
    
    // cout << "mypth : \n";
    // for(i=0;i<m;i++) {
    //     for(j=0;j<n;j++)
    //         cout << mypth[i][j] << " ";
    //     cout << "\n";
    // }

    int mpath = m * n, ai=-1, aj=-1;
    for(i=0;i<m;i++) {
        // cout << i << " , 0 - " << mypth[i][0] << " , " << mopth[i][0] << "(" << mpath << ") :: ";
        if(mypth[i][0] != -1 && (mopth[i][0] == -1 || mypth[i][0] < mopth[i][0])) {
            // printPath(mypth, i, 0, m, n);
            // return 0;
            if(mypth[i][0] < mpath) {
                mpath = mypth[i][0];
                ai = i;
                aj = 0;
            }
        }
        // cout << i << " , " << n-1 << " - " << mypth[i][n-1] << " , " << mopth[i][n-1] << "(" << mpath << ")\n";
        if(mypth[i][n-1] != -1 && (mopth[i][n-1] == -1 || mypth[i][n-1] < mopth[i][n-1])) {
            // printPath(mypth, i, n-1, m, n);
            // return 0;
            if(mypth[i][n-1] < mpath) {
                mpath = mypth[i][n-1];
                ai = i;
                aj = n-1;
            }
        }
    }
    
    for(i=0;i<n;i++) {
        // cout << 0 << " , " << i << " - " << mypth[0][i] << " , " << mopth[0][i] << "(" << mpath << ") :: ";
        if(mypth[0][i] != -1 && (mopth[0][i] == -1 || mypth[0][i] < mopth[0][i])) {
            // printPath(mypth, 0, i, m, n);
            // return 0;
            if(mypth[0][i] < mpath) {
                mpath = mypth[0][i];
                ai = 0;
                aj = i;
            }
        }
        // cout << m-1 << " , " << i << " - " << mypth[m-1][i] << " , " << mopth[m-1][i] << "(" << mpath << ")\n";
        if(mypth[m-1][i] != -1 && (mopth[m-1][i] == -1 || mypth[m-1][i] < mopth[m-1][i])) {
            // printPath(mypth, m-1, i, m, n);
            // return 0;
            if(mypth[m-1][i] < mpath) {
                mpath = mypth[m-1][i];
                ai = m-1;
                aj = i;
            }
        }
    }

    if(ai == -1 || aj == -1) {
        cout << "NO\n";
    }
    else {
        printPath(mypth, ai, aj, m, n);
    }

    
    return 0;
}