#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}

template<typename T>
void printa(T a[], int l, int r) {int f = 0; cerr << '{'; for (int i=l;i<=r;i++) cerr << (f++ ? "," : ""), __print(a[i]); cerr << "}]\n";}
template<typename T>
void printma(T a[], T b[], int l, int r, function<ll(ll,ll)> merge) {int f = 0; cerr << '{'; for (int i=l;i<=r;i++) cerr << (f++ ? "," : ""), __print(merge(a[i],b[i])); cerr << "}]\n";}
// #define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#define debuga(x, l, r) cerr << "[" << #x << "] = ["; printa(x, l, r)
#define debugma(x, y, l, r, merge) cerr << "[" << #x << "," << #y << "] = ["; printma(x, y, l, r, merge)
#else
#define debug(x...)
#define debuga(x, l, r)
#define debugma(x, y, l, r, merge)
#endif
 
 
 
/*
 
    I approach
    we would use binary lifting on the tree
    in order to turn O(n) to O(logn), we can represent it terms of power of 2 if it allows and then solve it
    so, in this case we would have to represent distance in the tree in terms of power of 2
    we can precalculate the 2^nth ancestor for a node
    and then represent every distance in binary and go to 2^kth ancestor if kth bit is set
    that is, suppose we want to find 13th ancestor of a node
    we can write, 13 = 8 + 4 + 1, so we need to go first 8th, then 4th and then 1st ancestor of nodes


*/
string ps = "\n";

// class Tree {
//   private:
// 	const int log2dist;
// 	vector<int> par;
// 	vector<vector<int>> pow2ends;
//   public:
// 	Tree(const vector<int> &parents)
// 	    : log2dist(std::ceil(std::log2(parents.size() + 1))),
// 	      par(parents.size() + 1),
// 	      pow2ends(par.size(), vector<int>(log2dist + 1)) {
// 		par[0] = -1;
// 		for (int i = 0; i < parents.size(); i++) { par[i + 1] = parents[i]; }
// 		// pow2ends[n][k] contains the 2^kth parent of node n
// 		// if there is no 2^kth parent, the value is -1
// 		for (int n = 0; n < par.size(); n++) { pow2ends[n][0] = par[n]; }
// 		for (int p = 1; p <= log2dist; p++) {
// 			for (int n = 0; n < par.size(); n++) {
// 				int halfway = pow2ends[n][p - 1];
// 				if (halfway == -1) {
// 					pow2ends[n][p] = -1;
// 				} else {
// 					pow2ends[n][p] = pow2ends[halfway][p - 1];
// 				}
// 			}
// 		}
// 	}
// 	/** @return the kth parent of node n */
// 	int kth_parent(int n, int k) {
// 		int at = n;
// 		// break down k into powers of 2 by looping through its bits
// 		for (int pow = 0; pow <= log2dist; pow++) {
// 			if ((k & (1 << pow)) != 0) {
// 				at = pow2ends[at][pow];
// 				if (at == -1) {
// 					break;  // stop when we're past the root
// 				}
// 			}
// 		}
// 		return at;
// 	}
// };

void solve() {
    int i, n, q;
    cin >> n >> q;
    debug(n);

    int lgn = ceil(log2(n)) + 1;
    debug(n, lgn);
    vector<vector<int>> anc(n, vector<int>(lgn, -1));
    for(i=0;i<n-1;i++) {
        int x;
        cin >> x;
        anc[i+1][0] = x-1;
    }



    for(i=1;i<lgn;i++) {
        for(int node=0;node<n;node++) {
            if(anc[node][i-1] != -1) {
                anc[node][i] = anc[anc[node][i-1]][i-1];
            }
        }
    }
    // debug(anc);

    while(q--) {
        int node, dis;
        cin >> node >> dis;
        node--;

        for(i=0;(1<<i) <= dis; i++) {
            debug("c", node, dis);
            if((1 << i) & dis) {
                debug(i, (1 << i), node);
                debug(anc[node]);
                node = anc[node][i];
                debug(i, (1 << i), node);
            }

            if(node == -1) {
                break;
            }
            debug("g", node, dis);
        }

        if(node == -1) {
            cout << "-1\n";
        }
        else {
            cout << node+1 << "\n";
        }
    }

}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);
    // int t;
    // cin >> t;
 
    // while(t--)
    // {
        solve();
    // }
 
    return 0;
}