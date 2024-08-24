#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

int dp[int(1e5+1)];

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
    - use djikstra with 3 properties, <currentDistance, currentNode, edgesCoveredSoFar>
    - if we reach destination, we would check if currentDistance is minimum
        - if it is less than minimum, then put 
            minimum price = currentDistance
            number of minimum price routes = 1
            minimum number of flights = edgesCoveredSoFar
            maximum number of flights = edgesCoveredSoFar
        - if it is equal to minimum, then put 
            number of minimum price routes = number of minimum price routes + 1
            minimum number of flights = min(edgesCoveredSoFar, minimum number of flights)
            maximum number of flights = max(edgesCoveredSoFar, maximum number of flights)

    TLE1 - It think it is taking lot of time for large test cases, if distances are same it would push every vertex with same distance which might be extra
    - 0m1.817s for >= at if(mndis[v] >= cdis + w)
    - 0m1.609s for > at if(mndis[v] > cdis + w)

    II approach
    - use djikstra to find minimum path
    - traverse the graph using dfs, and find how many routes have same minimum distance
    - update accordingly 4 properties
        - minimum price
        - number of minimum price routes
        - minimum number of flights
        - maximum number of flights

    WA1  - (self) as we cannot visit some vertex again, it can happen that there is one minimum path from that node(u) to dest and might me more than 1 minimum path from src to u
            but when we would reach u second time we would return without any operation

    YT solution - Dardev
    - I approach is correct, just we do not have to calculate the 4 properties for last node, instead we should calculate it for every node
    - do it like dp
    - if we are calculating minimum distance for every node, we can avoid adding node every time we encounter that node with same distance
    
*/
int numberOfMinimumPriceRoutes, minNoOfFlights, maxNoOfFlights;

void dfs(vector<array<int,2>> adj[], int u, int dest, ll currPrice, ll minPrice, int noOfEdges, vector<bool>& vis) {
    // cout << u << "\n";
    if(vis[u]) {
        return;
    }

    if(u == dest) {
        if(currPrice == minPrice) {
            numberOfMinimumPriceRoutes = (numberOfMinimumPriceRoutes + 1) % int(1e9+7);
            minNoOfFlights = min(minNoOfFlights, noOfEdges);
            maxNoOfFlights = max(maxNoOfFlights, noOfEdges);
        }
        return;
    }

    vis[u] = 1;
    for(auto vw : adj[u]) {
        int v = vw[0];
        int w = vw[1];
        dfs(adj, v, dest, currPrice + w, minPrice, noOfEdges+1, vis);
    }
}

int main()
{
    int n, m, i;
    cin >> n >> m;

    vector<array<int,2>> adj[n];

    for(i=0;i<m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;

        // if(u == v) continue;
        adj[u].push_back({v, w});
    }

    // ll minPrice = LONG_LONG_MAX;
    // numberOfMinimumPriceRoutes=0;
    // minNoOfFlights=m+1;
    // maxNoOfFlights=0;

    // // I approach
    // priority_queue<tuple<ll,int,int>, vector<tuple<ll,int,int>>, greater<tuple<ll,int,int>>> mnq;
    // vector<ll> mndis(n, LONG_LONG_MAX);

    // mndis[0] = 0;
    // mnq.push({0, 0, 0});

    // while(!mnq.empty()) {
    //     ll cdis = get<0>(mnq.top());
    //     int cnode = get<1>(mnq.top());
    //     int noOfEdges = get<2>(mnq.top());
    //     mnq.pop();
    //     // cout << cdis << " , ";
    //     // cout << cnode+1 << " , ";
    //     // cout << noOfEdges << "\n";

    //     for(auto vw : adj[cnode]) {
    //         int v = vw[0];
    //         int w = vw[1];
    //         if(mndis[v] > cdis + w) {
    //             mnq.push({cdis + w, v, noOfEdges+1});

    //             if(v == n-1) {
    //                 // cout << "inc: " << v << " , " << mndis[v] << "\n";
    //                 if(cdis + w < mndis[n-1]) {
    //                     minPrice = cdis + w;
    //                     numberOfMinimumPriceRoutes = 1;
    //                     minNoOfFlights = noOfEdges + 1;
    //                     maxNoOfFlights = noOfEdges + 1;
    //                 }
    //                 else if(cdis + w == mndis[n-1]) {
    //                     numberOfMinimumPriceRoutes++;
    //                     minNoOfFlights = min(minNoOfFlights, noOfEdges + 1);
    //                     maxNoOfFlights = max(maxNoOfFlights, noOfEdges + 1);
    //                 }
    //             }
    //             mndis[v] = cdis + w;
    //         }
    //     }
    // }

    // // II approach
    // priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> mnq;
    // vector<ll> mndis(n, LONG_LONG_MAX);

    // mnq.push({0, 0});
    // mndis[0] = 0;

    // while(!mnq.empty()) {
    //     ll cdis = mnq.top().first;
    //     int u = mnq.top().second;
    //     mnq.pop();

    //     if(u == n-1) {
    //         minPrice = cdis;
    //         break;
    //     }

    //     for(auto vw : adj[u]) {
    //         int v = vw[0];
    //         int w = vw[1];
    //         if(mndis[v] > cdis + w) {
    //             mndis[v] = cdis + w;
    //             mnq.push({mndis[v], v});
    //         }
    //     }
    // }

    // vector<bool> vis(n);
    // dfs(adj, 0, n-1, 0ll, minPrice, 0, vis);

    // cout << minPrice << " ";
    // cout << numberOfMinimumPriceRoutes << " ";
    // cout << minNoOfFlights << " ";
    // cout << maxNoOfFlights << "\n";

    // YT Solution
    vector<ll> mndis(n, LONG_LONG_MAX);
    vector<int> routes(n), minFlights(n, m+1), maxFlights(n);

    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> mnq;
    minFlights[0] = maxFlights[0] = mndis[0] = 0;
    routes[0] = 1;

    mnq.push({0, 0});
    while(!mnq.empty()) {
        ll cdis = mnq.top().first;
        int u = mnq.top().second;
        mnq.pop();
        // cout << u << " : " << cdis << " -> \n";

        for(auto [v, w] : adj[u]) {
            // cout << v << " , " << w << " - ";
            // cout << cdis + w << " : " <<  mndis[v] << "\n";
            if(cdis + w > mndis[v]) continue;

            else if(cdis + w == mndis[v]) {
                routes[v] += routes[u];
                routes[v] %= int(1e9 + 7);
                minFlights[v] = min(minFlights[v], 1 + minFlights[u]);
                maxFlights[v] = max(maxFlights[v], 1 + maxFlights[u]);
            }
            else {
                mndis[v] = cdis + w;
                routes[v] = routes[u];
                mnq.push({mndis[v], v});
                minFlights[v] = 1 + minFlights[u];
                maxFlights[v] = 1 + maxFlights[u];
            }
        }
    }

    cout << mndis[n-1] << " ";
    cout << routes[n-1] << " ";
    cout << minFlights[n-1] << " ";
    cout << maxFlights[n-1] << "\n";

    return 0;

}