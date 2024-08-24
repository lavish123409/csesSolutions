#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

// void printPQ(auto pq) {
//     cout << "[";
//     while(!pq.empty()) {
//         int d = pq.top().first;
//         int u = pq.top().second;
//         pq.pop();
//         cout << "(" << d << " : " << u << ") , ";
//     }
//     cout << "]\n";
// }

/*

    I approach
    using DSU
    we know that using DSU, we can find number of components, and using depth array we can also find that how many nodes are present under a parent or representative

    - when we are joining components, decrease number of components by 1
    - when we are joining components, we count the depth of larger component and store it if it is larger than current maximum

*/

const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

int par[MAXN], depth[MAXN];
int maxSizeOfComponent, noOfComponents;

int parent(int n) {
    if(par[n] == -1) {
        return n;
    }
    return par[n] = parent(par[n]);
}

void join(int a, int b) {
    a = parent(a);
    b = parent(b);

    // if(a == -1 || b == -1) {
    //     noOfComponents--;
    // }
    if(a != b) {
        noOfComponents--;
        if(depth[a] < depth[b]) {
            swap(a, b);
        }

        depth[a] += depth[b];
        par[b] = a;
        maxSizeOfComponent = max(maxSizeOfComponent, depth[a]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int i, n, m;
    cin >> n >> m;
    maxSizeOfComponent = 0;
    noOfComponents = n;

    for(i=0;i<n;i++) {
        par[i] = -1;
        depth[i] = 1;
    }

    for(i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;

        join(u, v);
        cout << noOfComponents << " " << maxSizeOfComponent << "\n";
    }

    return 0;

}