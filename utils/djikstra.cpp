#include <bits/stdc++.h>
using namespace std;

void djikstra(vector<array<int,2>> adj[], int n, int s, vector<int>& dis, vector<int>& par) {
	dis = vector<int>(n, INT_MAX);
	par = vector<int>(n, -1);
	priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> mnq;

	mnq.push({0, 0});

	while(!mnq.empty()) {
		int cdis = mnq.top()[0];
		int u = mnq.top()[1];
		mnq.pop();

		// if(u == n-1) return cdis; // if you want to return minimum distance to n-1

		// We are not writing like this because it will lead to many unnecessary larger path values in minHeap
		// if(dis[u] > cdis) {
        //     dis[u] = cdis;
        //     for(auto [v, w] : adj[u]) {
        //         mnq.push({cdis + w, v});
        //     }
        // }

		if(dis[u] < cdis) continue;

		for(auto [v, w] : adj[u]) {
			if(cdis + w < dis[v]) { // this is needed because we do not store unnecessary values in minHeap
				dis[v] = cdis + w; // for storing min distance; using this also we will stop many higher values path also
				par[v] = u; // for storing the parent; we can backtrack through the nodes to get the shortest path
				mnq.push({cdis + w, v});
			}
		}
	}
}

// djikstra will fail if there is a negative cycle in the graph
// djikstra cannot detect negative weight edge also

// For ex: V={A,B,C} ; E = {(A,C,2), (A,B,5), (B,C,-10)}
// Dijkstra from A will first develop C, and will later fail to find A->B->C
// Note that this is important, because in each relaxation step, the algorithm assumes the "cost" to the "closed" nodes is indeed minimal, and thus the node that will next be selected is also minimal.

// The idea of it is: If we have a vertex in open such that its cost is minimal - by adding any positive number to any vertex - the minimality will never change.
// Without the constraint on positive numbers - the above assumption is not true.

// Since we do "know" each vertex which was "closed" is minimal - we can safely do the relaxation step - without "looking back". If we do need to "look back" - Bellman-Ford offers a recursive-like (DP) solution of doing so.


int main() {

	return 0;
}
