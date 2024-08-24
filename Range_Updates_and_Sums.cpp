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
template<typename T>
void printa2(T* a, int l1, int r1, int l2, int r2, int m) {int f = 0; cerr << '{'; for (int i=l1;i<=r1;i++) cerr << (f++ ? "," : ""), printa(a + i * m, l2, r2); cerr << "}]\n";}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#define debuga(x, l, r) cerr << "[" << #x << "] = ["; printa(x, l, r)
#define debuga2(x, l1, r1, l2, r2, m) cerr << "[" << #x << "] = [\n"; printa2(x, l1, r1, l2, r2, m); cerr << "}]\n";
#define debugma(x, y, l, r, merge) cerr << "[" << #x << "," << #y << "] = ["; printma(x, y, l, r, merge)
#else
#define debug(x...)
#define debuga(x, l, r)
#define debuga2(x, l1, r1, l2, r2, m)
#define debugma(x, y, l, r, merge)
#endif
 
 
 
/*
 
    I approach
    just like we do lazy propagation for update, we can do same for set value with some tweaks
    for lazy propagation in updates, we would update like this for a range
    segTree[in] += (end - start + 1) * dff;
    lazy[children] = dff;
    arr[ind] += dff;
    for lazy propagation in setting value, we would update like this for a range
    segTree[in] = (end - start + 1) * val;
    lazy[children] = val;
    arr[ind] = val;
 
    PROBLEM
    if there are any pending updates to any node, after setting value for that node, those updates would become 0
    if there are any pending "setting values" update to any node, the incoming updates would update the latest value
    if there are any pending updates to any node, then setting value for any of its descendants would nullfy its update, while that update would still be applicable for other descendants
    if there are any pending updates to any node, then setting value for any of its ancestors would nullfy its update
    many others
 
    we can take a vector of lazy array and push back all the updates and set values to it
    for one node, there can be 4 cases
    first update then set value, then we have to only set the value and push it to children
    first set value then update, then we have to do both operations on current node and push both operations to children
    first update then another update, then we can combine both updates and push it to children
    first set value and then set another value, then we have to only set the second value and push it to children
 
    if one operation is on current node and another operation is on its ancestors
 
    the solution is becoming too complex, do not feel that it is correct
    I would try it once anyways
 
    RE1 - while adding new updates vector to old updates vector, we are checking with the last update of old vector
    we should also check whether old vector is empty or not

    WA1 - wahi integer overflow
    in array, after update it can go beyond INT_MAX (maybe they have not checked it)
    in lazy array, multiple updates can go beyond INT_MAX

    WA2 - when I made array<int,2> to pair<bool, ll>, I should also change the value given to set value in updates vector
 
*/
string ps = "\n";
 
const int MAXN = 2e5+5;
ll segTree[4*MAXN];
vector<pair<bool,ll>> lazy[4*MAXN];
int arr[MAXN];
int arraySize;
 
void createSegmentTree(int in, int cl ,int cr) {
    if(cl == cr) {
        segTree[in] = arr[cl];
        return; 
    }
 
    int m = cl + (cr - cl) / 2;
    createSegmentTree(2*in+1, cl, m);
    createSegmentTree(2*in+2, m+1, cr);
 
    segTree[in] = segTree[2*in+1] + segTree[2*in+2];
}
 
void getEffectiveUpdate(vector<pair<bool,ll>>& old, vector<pair<bool,ll>>& nw) {
    for(pair<bool,ll>& upd : nw) {
        if(upd.first == 1 && !old.empty()) {
            if(old.back().first == 1) {
                old.back().second += upd.second;
            }
            else {
                old.push_back(upd);
            }
        }
        else {
            old.clear();
            old.push_back(upd);
        }
    }
}
 
void update(int in, int cl, int cr, vector<pair<bool,ll>>& updates) {
    for(pair<bool,ll>& upd : updates) {
        if(upd.first == 1) {
            segTree[in] += 1ll * (cr - cl + 1) * upd.second;
            if(cl == cr) {
                arr[cl] += upd.second;
            }
        }
        else {
            segTree[in] = 1ll * (cr - cl + 1) * upd.second;
            if(cl == cr) {
                arr[cl] = upd.second;
            }
        }
    }
}
 
void updateR(int in, int cl, int cr, int ql, int qr, int dff) {
 
    if(!lazy[in].empty()) {
        update(in, cl, cr, lazy[in]);
        if(cl != cr) {
            getEffectiveUpdate(lazy[2*in+1], lazy[in]);
            getEffectiveUpdate(lazy[2*in+2], lazy[in]);
        }
        lazy[in].clear();
    }
 
    if(cr < ql || cl > qr) {
        return;
    }
 
    if(ql <= cl && cr <= qr) {
        segTree[in] += 1ll * (cr - cl + 1) * dff;
        if(cl == cr) {
            arr[cl] += dff;
        }
        else {
            vector<pair<bool,ll>> newUpdates = {{1, dff}};
            getEffectiveUpdate(lazy[2*in+1], newUpdates);
            getEffectiveUpdate(lazy[2*in+2], newUpdates);
        }
        return;
    }
 
    int m = cl + (cr - cl) / 2;
    updateR(2*in+1, cl, m, ql, qr, dff);
    updateR(2*in+2, m+1, cr, ql, qr, dff);
 
    segTree[in] = segTree[2*in+1] + segTree[2*in+2];
}
 
void setValueR(int in, int cl, int cr, int ql, int qr, int val) {
    if(!lazy[in].empty()) {
        update(in, cl, cr, lazy[in]);
        if(cl != cr) {
            getEffectiveUpdate(lazy[2*in+1], lazy[in]);
            getEffectiveUpdate(lazy[2*in+2], lazy[in]);
        }
        lazy[in].clear();
    }
 
    if(cr < ql || cl > qr) {
        return;
    }
 
    if(ql <= cl && cr <= qr) {
        segTree[in] = 1ll * (cr - cl + 1) * val;
        if(cl == cr) {
            arr[cl] = val;
        }
        else {
            vector<pair<bool,ll>> newUpdates = {{0, val}};
            getEffectiveUpdate(lazy[2*in+1], newUpdates);
            getEffectiveUpdate(lazy[2*in+2], newUpdates);
        }
        return;
    }
 
    int m = cl + (cr - cl) / 2;
    setValueR(2*in+1, cl, m, ql, qr, val);
    setValueR(2*in+2, m+1, cr, ql, qr, val);
 
    segTree[in] = segTree[2*in+1] + segTree[2*in+2];
}
 
ll query(int in, int cl, int cr, int ql, int qr) {
    if(!lazy[in].empty()) {
        update(in, cl, cr, lazy[in]);
        if(cl != cr) {
            getEffectiveUpdate(lazy[2*in+1], lazy[in]);
            getEffectiveUpdate(lazy[2*in+2], lazy[in]);
        }
        lazy[in].clear();
    }
 
    if(cr < ql || cl > qr) {
        return 0;
    }
 
    if(ql <= cl && cr <= qr) {
        return segTree[in];
    }
 
    int m = cl + (cr - cl) / 2;
    return query(2*in+1, cl, m, ql, qr) + query(2*in+2, m+1, cr, ql, qr);
}
 
void solve() {
 
    int i, j, n, q;
    cin >> n >> q;
    
    for(i=0;i<n;i++) {
        cin >> arr[i];
    }
 
    createSegmentTree(0, 0, n-1);
 
    while(q--) {
        int t;
        cin >> t;
 
        switch(t) {
            int a, b, x;
            case 1:
                cin >> a >> b >> x;
 
                a--;
                b--;
 
                updateR(0, 0, n-1, a, b, x);
                break;
            case 2:
                cin >> a >> b >> x;
 
                a--;
                b--;
 
                setValueR(0, 0, n-1, a, b, x);    
                break;
            case 3:
                cin >> a >> b;
 
                a--;
                b--;
 
                // cout << a << " " << b << "\n";
                cout << query(0, 0, n-1, a, b) << "\n";
                break;
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