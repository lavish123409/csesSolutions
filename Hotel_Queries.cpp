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

    I approach
    we can take a map, with number and its index, then for every query of rooms required
    - find out a room which can accomodate current group -> find the lower bound of currently required rooms,i.e, query
    - print its index, and decrease room capacity by current group size

    map of hotel rooms and their index; hotelRooms = {}
    for groupSize in queries:
        roomsInHotel, hotelIndex = hotelRooms.lower_bound({groupSize, -1})
        print hotelIndex
        hotelRooms.remove

    this approach would not work because
    hotelRooms = [3, 2]
    hotelRoomsMap = {(2,1) (3,0)}
    if we would search for group size 1, then we would get (2,1), i.e, hotel with rooms 2, but according to the question, we should get 3 because it comes first from left

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Observation
    we can sort the array along with indexes, so at any point we know what all values are greater than current query
    then, for those values the indexes would be randomly ordered from which we have to find the mminimum index
    it can be done with segment tree

    problem
    after allocating rooms, we need to decrement number of rooms in that selected hotel, which would change its position in segment tree

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Peeking solution - segment tree is confirmed
    II approach
    we can find whether there is some number in array which is greater than current query
    we would make maximum segment tree
    we would check at root if maximum element of array is greater than current query
    if it is less, return -1
    (recursively) otherwise, check in left subarray if some element is greater than current query
    if it is, return index of that element and update it
    repeat same thing for right, only if left returned -1, and return index and update it(an number in right subarray should be greater, if some number is greater in complete array but not in left subarray)

    

*/
string ps = "\n";


const int MAXN = 2e5+5;
int arr[MAXN];
ll segTree[4 * MAXN];
ll lazy[4 * MAXN];
int arraySize;

void createSegmentTree(int in, int cl, int cr) {
    if(cl == cr) {
        segTree[in] = arr[cl];
        return;
    }

    int m = cl + (cr - cl) / 2;
    createSegmentTree(2*in+1, cl, m);
    createSegmentTree(2*in+2, m+1, cr);

    segTree[in] = max(segTree[2*in+1] , segTree[2*in+2]);
}

int query(int in, int cl, int cr, int val) {
    if(segTree[in] < val) {
        return -1;
    }

    if(cl == cr) {
        arr[cl] -= val;
        segTree[in] -= val;
        return cl;
    }

    int m = cl + (cr - cl) / 2;
    int ind = query(2*in+1, cl, m, val);
    if(ind != -1) {
        segTree[in] = max(segTree[2*in+1], segTree[2*in+2]);
        return ind;
    }

    ind = query(2*in+2, m+1, cr, val);
    // if(ind != -1) {
    segTree[in] = max(segTree[2*in+1], segTree[2*in+2]);
    return ind;
    // }
}

void printSegTree() {
    int layer = arraySize; // n smallest power of 2 that great than or equal to the size of seg_tree
    for (int i = 0; i < 2 * arraySize - 1; i++) {
        cout << setw(layer) << segTree[i] << " ";
        if (__builtin_popcount(i + 2) == 1) {
            layer /= 2;
            cout << "\n";
        }

    }
    cout << "\n";
}

void solve() {

    int n, m, i;
    cin >> n >> m;
    arraySize = n;

    for(i=0;i<n;i++) {
        cin >> arr[i];
    }

    createSegmentTree(0, 0, n-1);
    while(m--) {
        int roomsRequired;
        cin >> roomsRequired;

        cout << query(0, 0, n-1, roomsRequired) + 1 << " ";
        // printSegTree();
        // for (int i = 0; i < n; i++)
        // {
        //     cout << arr[i] << " , ";
        // }
        // cout << "\n";
        
    }
    cout << "\n";
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