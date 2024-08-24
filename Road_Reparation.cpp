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
    seems like standard MST problem, all cities need to be connected with minimum possible cost to connect all the vertices
    // Prim's algorithm

    make a priority queue to get minimum distance in current cut
    make a set to find whether some node is already in mst or not
    push node 1 with 0 incoming edge weight
    mstSet[1] = 1
    while priority queue is not empty:
        extract node with minimum incoming edge weight = min(priorty queue)
        pop from priority queue

        ans += minimum incoming edge weight
        for all neighbors v with weight w of node in adj:
            push in priority queue if v is not in mstSet:
                mstSet[v] = 1
                priority queue.push({w, v})

    print ans

    problem in appraoch - here we are considering only first edge incoming to the node as minimum, which is not true as for following test case
    1 3 7
    1 2 1
    2 3 4

    store the minimum incoming edge weight in mstSet, and update if some other edge with less weight comes
    at last, sum all the minimum incoming edge weight

    problem in approach - on any node, some edge weight coming from child can be less than coming from source, which would result in wrong answer
    tc : 1 2 7
         2 3 5
    
    in this approach, after storing 7 weight for node 2, weight of 5 would come from 3 and being less than 7 the approach would store 5 as minimum incoming edge weight, breaking the link from source 1

    1st approach is correct - we have to think like the weight of complete mst is pushed in priority queue
    one by one when an edge is added, the weight of mst increases
    Now, if we would observe, we can see that 
        - there are 2 sets: one set of nodes in mst and other is not
        - if we reach any vertex, we have already chosen minimum weight from mst to that node
        - if we have not reached some vertex, there are multiple edges from mst to that node in priority queue, from which we would chose smallest one only

    so, we should not check that some vertex is in mst at the time of looking (for v in adj[u]), as it can happen that there are multiple edges from mst to that vertex, with distance 7, 2 4 from which we have to choose smallest one,i.e, 2
    and if we have reached some vertex, we should check that vertex is in mst, and then add the incoming edge weight to mst, as we have pushed multiple incoming edges form mst to that vertex

    make a priority queue to get minimum distance in current cut
    make a set to find whether some node is already in mst or not
    push node 1 with 0 incoming edge weight
    while priority queue is not empty:
        extract node with minimum incoming edge weight = min(priorty queue)
        pop from priority queue

        if(node is in mstSet):
            continue

        ans += minimum incoming edge weight
        put node in mstSet

        for all neighbors v with weight w of node in adj:
            push in priority queue if v is not in mstSet:
                priority queue.push({w, v})

    print ans

    II approach
    // Kruskal algorithm
    - sort all the edges according to weight
    - make DSU data structure, for union and find to detect cycle
    - check every edge, and add it to the mst weight if does not create the cycle

    sort(edges)

    for edge in edges:
        u, v = edge
        if u and v are in same set in DSU:
            continue

        ans += edge.weight
        union u and v in DSU


*/

const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

int par[MAXN], depth[MAXN];

int parent(int n) {
    if(par[n] == -1) {
        return n;
    }
    return par[n] = parent(par[n]);
}

bool inSameSet(int a, int b) {
    a = parent(a);
    b = parent(b);

    return a == b;
}

void join(int a, int b) {
    a = parent(a);
    b = parent(b);

    if(a != b) {
        if(depth[a] < depth[b]) {
            swap(a, b);
        }

        depth[a] += depth[b];
        par[b] = a;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int i, n, m;
    cin >> n >> m;

    ll ans = 0ll;
    for(i=0;i<n;i++) {
        par[i] = -1;
        depth[i] = 1;
    }

    array<int,3> edges[m];
    for(i=0;i<m;i++) {
        // int u, v, w;
        // cin >> u >> v >> w;

        // edges[i] = {u, v, w};
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    sort(edges, edges+m, [](array<int,3>& a, array<int,3>& b) {
        return a[2] < b[2];
    });

    for(i=0;i<m;i++) {
        // cout << edges[i][0] << " , " << edges[i][1] << " = " << edges[i][2] << "\n";
        if(inSameSet(edges[i][0], edges[i][1])) continue;
        // cout << "niss\n";

        ans += edges[i][2];
        join(edges[i][0], edges[i][1]);
    }

    int prnt = parent(1);
    for(i=1;i<n;i++) {
        if(prnt != parent(i)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    cout << ans << "\n";
    return 0;

}