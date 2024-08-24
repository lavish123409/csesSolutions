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
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif



/*

    Solution - USACO guide: https://usaco.guide/problems/cses-1144-salary-queries/solution
    idea is that, we can use index compression because number of elements is in 10^5 range and also, we have to perform queries on number of elements only
    but, we would have to store all elements previously and do offline queries, because we want index to be sorted on inserting new elements

*/
string ps = "\n";


// const int MAXN = 4e5+5;
// int arr[MAXN];
// ll segTree[4 * MAXN];
// ll lazy[4 * MAXN];
// int arraySize;
// vector<int> vals;

// int getIndex(int n) {
//     int ind = lower_bound(vals.begin(), vals.end(), n) - vals.begin();

//     return ind;
// }

// void updateUtil(int in, int cl, int cr, int ind, int val) {
//     if(cl == cr) {
//         segTree[in] += val;
//         return;
//     }

//     int m = cl + (cr - cl) / 2;
//     if(ind <= m) {
//         updateUtil(2*in+1, cl, m, ind, val);
//     }
//     else {
//         updateUtil(2*in+2, m+1, cr, ind, val);
//     }

//     segTree[in] = segTree[2*in+1] + segTree[2*in+2];
// }

// void update(int ind, int val) {
//     updateUtil(0, 0, int(vals.size()) - 1, ind, val);
// }

// int query(int in, int cl, int cr, int ql, int qr) {
//     // cout << cl << " , " << cr << " : ";
//     // cout << ql << " , " << qr << "\n";
//     if(ql <= cl && cr <= qr) {
//         return segTree[in];
//     }

//     if(cr < ql || cl > qr) {
//         return 0;
//     }

//     int m = cl + (cr - cl) / 2;
//     return query(2*in+1, cl, m, ql, qr) + query(2*in+2, m+1, cr, ql, qr);
// }

// void printSegTree() {
//     int layer = arraySize; // n smallest power of 2 that great than or equal to the size of seg_tree
//     for (int i = 0; i < 2 * arraySize - 1; i++) {
//         cout << setw(layer) << segTree[i] << " ";
//         if (__builtin_popcount(i + 2) == 1) {
//             layer /= 2;
//             cout << "\n";
//         }

//     }
//     cout << "\n";
// }

// void solve() {

//     vals = vector<int>();
//     int i, n, q;
//     cin >> n >> q;

//     int ar[n];
//     for(i=0;i<n;i++) {
//         cin >> ar[i];
//         vals.push_back(ar[i]);
//     }

//     vector<array<int,3>> qrs(q);
//     for(i=0;i<q;i++) {
//         char t;
//         int a, b;
//         cin >> t >> a >> b;

//         if(t == '!') {
//             vals.push_back(b);
//         }

//         qrs[i] = {t == '?', a, b};
//     }

//     sort(vals.begin(), vals.end());
//     vals.erase(unique(vals.begin(), vals.end()), vals.end());

//     for(i=0;i<n;i++) {
//         update(getIndex(ar[i]), 1);
//     }

//     // for(int it : vals) {
//     //     cout << it << " ";
//     // }
//     // cout << "\n";
//     arraySize = int(vals.size());

//     for(i=0;i<q;i++) {
//         int t = qrs[i][0];
//         int a = qrs[i][1];
//         int b = qrs[i][2];

//         // debug(t, a, b);
//         if(t) {
//             int geai = lower_bound(vals.begin(), vals.end(), a) - vals.begin();
//             int lebi = upper_bound(vals.begin(), vals.end(), b) - vals.begin() - 1;
//             if(geai > lebi) {
//                 cout << "0\n";
//             }
//             else {
//                 // printSegTree();
//                 cout << query(0, 0, int(vals.size())-1, geai, lebi) << "\n";
//             }
//             // cout << query(0, 0, int(vals.size())-1, 0, getIndex(b)) - query(0, 0, int(vals.size())-1, 0, getIndex(a-1)) << "\n";
//             // cout << "==================================================================================================================\n";
//         }
//         else {
//             a--;
//             int segInd = getIndex(ar[a]);
//             update(segInd, -1);
//             ar[a] = b;

//             segInd = getIndex(ar[a]);
//             update(segInd, 1);
//         }
//     }

// }

// int main()
// {
//     ios_base::sync_with_stdio(false);
// 	cin.tie(NULL);
//     cout.tie(NULL);
//     // int t;
//     // cin >> t;

//     // while(t--)
//     // {
//         solve();
//     // }

//     return 0;
// }

const int MAXN = 4e5+5;
int bit[MAXN];
int arraySize;
vector<int> vals;

int getIndex(int n) {
    int ind = upper_bound(vals.begin(), vals.end(), n) - vals.begin();

    return ind;
}

void update(int ind, int val) {
    for(;ind < MAXN; ind += (ind & (-ind))) {
        bit[ind] += val;
    }
}

int query(int ind) {
    int ans = 0;
    for(;ind>0; ind -= (ind & (-ind))) {
        ans += bit[ind];
    }

    return ans;
}

void solve() {

    vals = vector<int>();
    int i, n, q;
    cin >> n >> q;

    int ar[n];
    for(i=0;i<n;i++) {
        cin >> ar[i];
        vals.push_back(ar[i]);
    }

    vector<array<int,3>> qrs(q);
    for(i=0;i<q;i++) {
        char t;
        int a, b;
        cin >> t >> a >> b;

        if(t == '!') {
            vals.push_back(b);
        }

        qrs[i] = {t == '?', a, b};
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    for(i=0;i<n;i++) {
        update(getIndex(ar[i]), 1);
    }

    for(int it : vals) {
        cout << it << " ";
    }
    cout << "\n";
    arraySize = int(vals.size());

    for(i=0;i<q;i++) {
        int t = qrs[i][0];
        int a = qrs[i][1];
        int b = qrs[i][2];

        // debug(t, a, b);
        if(t) {
            // int geai = lower_bound(vals.begin(), vals.end(), a) - vals.begin();
            // int lebi = upper_bound(vals.begin(), vals.end(), b) - vals.begin() - 1;
            // if(geai > lebi) {
            //     cout << "0\n";
            // }
            // else {
                // printSegTree();
                cout << getIndex(b) << " : " << b << "\n";
                cout << getIndex(a-1) << " : " << a << "\n";
                cout << query(getIndex(b)) << " <- qb\n";
                cout << query(getIndex(a-1)) << " <- qa\n";
                cout << query(getIndex(b)) - query(getIndex(a-1)) << "\n";
            // }
            // cout << query(0, 0, int(vals.size())-1, 0, getIndex(b)) - query(0, 0, int(vals.size())-1, 0, getIndex(a-1)) << "\n";
            // cout << "==================================================================================================================\n";
        }
        else {
            a--;
            int segInd = getIndex(ar[a]);
            update(segInd, -1);
            ar[a] = b;

            segInd = getIndex(ar[a]);
            update(segInd, 1);
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

