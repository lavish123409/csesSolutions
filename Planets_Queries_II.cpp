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

    USACO solution -> https://usaco.guide/problems/cses-1160-planets-queries-ii/solution
    It is a standard problem of functional graphs, where each node have 1 outgoing edge
    - it forms a inverted tree
    - and one edge from root node forms a cycle (see usaco guide for better explanation)

    our problem have 3 cases, for u -> v
    1 - if u nd v are both on cycle
        a - if cycle index of u < cycle index of v, then we can reach v directly from u, dist = cycle index of v - cycle index of u
        b - if cycle index of u > cycle index of v, then we have to circle the cycle to reach v from u, dist = cycle length - (cycle index of u - cycle index of v)
    2 - if u is in cycle, and v is in tree
        a - we cannot reach any tree node from cycle
    3 - if u is in tree and v is in cycle
        a - we can do binary lifting to reach the cycle node, and find distance using 1st step

    
*/

const int MAXN = 2e5+5;
const int MAXD = 30;
int anc[MAXN][MAXD];

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int planet_num, q;
    cin >> planet_num >> q;
    // cout << planet_num << " , " << q << "\n";

    // cout << "yo0\n";
    vector<int> next(planet_num);
    vector<vector<int>> before(planet_num);
    for(int p=0;p<planet_num;p++) {
        cin >> next[p];
        next[p]--;
        before[next[p]].push_back(p);
    }

    // cout << "yo1\n";
    vector<int> cycleIndex(planet_num, -2);
    vector<map<int,int>> cycles;
    for(int p=0;p<planet_num;p++) {
        if(cycleIndex[p] != -2) continue;

        int currNode = p;
        vector<int> path;
        while(cycleIndex[currNode] == -2) {
            cycleIndex[currNode] = -3;
            path.push_back(currNode);
            currNode = next[currNode];
        }

        map<int,int> currCycle;
        int nodeNoInCycle = 0;
        bool isInCycle = 0;
        for(int node : path) {
            isInCycle = isInCycle || (node == currNode);
            if(isInCycle) {
                currCycle[node] = nodeNoInCycle++;
            }
            cycleIndex[node] = isInCycle ? cycles.size() : -1;
        }
        cycles.push_back(currCycle);
    }

    // cout << "yo2\n";
    vector<int> cycleDist(planet_num);
    for(int p=0;p<planet_num;p++) {
        if(cycleIndex[p] != -1 || cycleIndex[next[p]] == -1) continue;

        cycleDist[p] = 1;
        vector<int> stack(before[p]);
        while(!stack.empty()) {
            int currNode = stack.back();
            stack.pop_back();
            cycleDist[currNode] = cycleDist[next[currNode]] + 1;

            stack.insert(stack.end(), before[currNode].begin(), before[currNode].end());
        }
    }

    // cout << "yo3\n";
    int log2Max = ceil(log2(planet_num));
    vector<vector<int>> anc(planet_num, vector<int>(log2Max));
    for(int p=0;p<planet_num;p++) {
        anc[p][0] = next[p];
    }
    for(int ancno=1;ancno<log2Max;ancno++) {
        for(int p=0;p<planet_num;p++) {
            anc[p][ancno] = anc[anc[p][ancno-1]][ancno-1];
        }
    }

    // cout << "yo4\n";
    auto advance = [&](int u, int dis) {
        for(int ancno=log2Max; ancno >= 0; ancno--) {
            if((dis & (1 << ancno)) > 0) {
                u = anc[u][ancno];
            }
        }
        return u;
    };

    // cout << "yo5\n";
    while(q--) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;
        // cout << q << " - " << u << " : " << v << "\n";

        if(cycleIndex[advance(u, planet_num)] != cycleIndex[advance(v, planet_num)]) {
            cout << "-1\n";
            // return 0;
            continue;
        }

        if(cycleIndex[u] != -1 || cycleIndex[v] != -1) {
            if(cycleIndex[u] != -1 && cycleIndex[v] == -1) {
                cout << "-1\n";
                continue;
            }

            int uInCyc = advance(u, cycleDist[u]);
            if(cycleIndex[uInCyc] != cycleIndex[v]) {
                cout << "-1\n";
                continue;
            }

            map<int,int> &currCycle = cycles[cycleIndex[v]];
            int totalDist = cycleDist[u];
            if(currCycle[uInCyc] <= currCycle[v]) {
                totalDist += (currCycle[v] - currCycle[uInCyc]);
            }
            else {
                totalDist += (currCycle.size() - (currCycle[uInCyc] - currCycle[v]));
            }
            cout << totalDist << "\n";
        }
        else {
            // cout << u << " : " << v << "\n";
            // cout << cycleDist[v] << " , " << cycleDist[u] << "\n";
            if(cycleDist[v] > cycleDist[u]) {
                cout << "-1\n";
                continue;
            }

            int advancedU = advance(u, cycleDist[u] - cycleDist[v]);
            if (advancedU != v) {
                cout << "-1\n";
                continue;
            }

            cout << cycleDist[u] - cycleDist[v] << "\n";

        }
    }

    return 0;

}

// #include <cmath>
// #include <iostream>
// #include <map>
// #include <vector>

// using std::cout;
// using std::endl;
// using std::vector;

// int main() {
// 	int planet_num;
// 	int query_num;
// 	std::cin >> planet_num >> query_num;
// 	vector<int> next(planet_num);
// 	vector<vector<int>> before(planet_num);
// 	for (int p = 0; p < planet_num; p++) {
// 		std::cin >> next[p];
// 		next[p]--;
// 		before[next[p]].push_back(p);
// 	}

// 	/*
// 	 * -2 = We haven't even got to processing this planet yet.
// 	 * -1 = This node is part of a tree.
// 	 * >= 0: the ID of the cycle the planet belongs to.
// 	 */
// 	vector<int> cycle_id(planet_num, -2);
// 	// Each map, given a planet #, returns the index of that planet in the
// 	// cycle.
// 	vector<std::map<int, int>> cycles;
// 	for (int p = 0; p < planet_num; p++) {
// 		if (cycle_id[p] != -2) { continue; }
// 		vector<int> path{p};
// 		int at = p;
// 		while (cycle_id[at] == -2) {
//             // cout << at << " <- incyc\n";
// 			cycle_id[at] = -3;  // Leave breadcrumbs for this iteration
// 			path.push_back(at);
// 			at = next[at];
// 		}

// 		std::map<int, int> cycle;
// 		bool in_cycle = false;
// 		for (int i : path) {
// 			in_cycle = in_cycle || i == at;
// 			if (in_cycle) { cycle[i] = cycle.size(); }
// 			cycle_id[i] = in_cycle ? cycles.size() : -1;
// 		}
// 		cycles.push_back(cycle);
// 	}

//     // for(int i=0;i<planet_num;i++) {
//     //     cout << i+1 << " : " << cycle_id[i] << " - ";
//     // }
//     // cout << "\n";
    
//     // for(int i=0;i<cycles.size();i++) {
//     //     cout << i << " : ";
//     //     for(auto it : cycles[i]) {
//     //         cout << "(" << it.first+1 << " , " << it.second << ") - ";
//     //     }
//     //     cout << "\n";
//     // }

// 	/*
// 	 * Precalculate the distance from each planet to its cycle with BFS.
// 	 * (cyc_dist[p] = 0) if p is part of a cycle.
// 	 */
// 	vector<int> cyc_dist(planet_num);
// 	for (int p = 0; p < planet_num; p++) {
// 		// Check if this planet is part of a cycle.
// 		if (cycle_id[next[p]] == -1 || cycle_id[p] != -1) { continue; }
// 		cyc_dist[p] = 1;
// 		vector<int> stack(before[p]);
// 		while (!stack.empty()) {
// 			int curr = stack.back();
// 			stack.pop_back();
// 			cyc_dist[curr] = cyc_dist[next[curr]] + 1;
// 			stack.insert(stack.end(), before[curr].begin(), before[curr].end());
// 		}
// 	}

//     // for(int i=0;i<planet_num;i++) {
//     //     cout << i+1 << " : " << cyc_dist[i] << " - ";
//     // }
//     // cout << "\n";

// 	// Intialize the binary jumping arrays.
// 	int log2 = std::ceil(std::log2(planet_num));
// 	vector<vector<int>> pow2_ends(planet_num, vector<int>(log2 + 1));
// 	for (int p = 0; p < planet_num; p++) { pow2_ends[p][0] = next[p]; }
// 	for (int i = 1; i <= log2; i++) {
// 		for (int p = 0; p < planet_num; p++) {
// 			pow2_ends[p][i] = pow2_ends[pow2_ends[p][i - 1]][i - 1];
// 		}
// 	}

// 	/*
// 	 * Given a starting planet & dist, returns the planet we end up at
// 	 * if we use the teleporter dist times.
// 	 */
// 	auto advance = [&](int pos, int dist) {
// 		for (int pow = log2; pow >= 0; pow--) {
// 			if ((dist & (1 << pow)) != 0) { pos = pow2_ends[pos][pow]; }
// 		}
// 		return pos;
// 	};
// 	for (int q = 0; q < query_num; q++) {
// 		int u, v;  // going from u to v
// 		std::cin >> u >> v;
// 		u--;
// 		v--;
// 		if (cycle_id[pow2_ends[u][log2]] != cycle_id[pow2_ends[v][log2]]) {
// 			cout << -1 << '\n';
// 			continue;
// 		}
// 		if (cycle_id[u] != -1 || cycle_id[v] != -1) {
// 			if (cycle_id[v] == -1 && cycle_id[u] != -1) {
// 				cout << -1 << '\n';
// 				continue;
// 			}
// 			// Handle the 2nd & 3rd cases at the same time.
// 			int dist = cyc_dist[u];
// 			int u_cyc = advance(u, cyc_dist[u]);  // The root of u's tree

// 			std::map<int, int> &cyc =
// 			    cycles[cycle_id[u_cyc]];  // u and v's cycle
// 			int u_ind = cyc[u_cyc];
// 			int v_ind = cyc[v];
// 			int diff =
// 			    u_ind <= v_ind ? v_ind - u_ind : cyc.size() - (u_ind - v_ind);
// 			cout << dist + diff << '\n';
// 		} else {
// 			if (cyc_dist[v] > cyc_dist[u]) {
// 				cout << -1 << '\n';
// 				continue;
// 			}
// 			int diff = cyc_dist[u] - cyc_dist[v];
// 			cout << (advance(u, diff) == v ? diff : -1) << '\n';
// 		}
// 	}
// }