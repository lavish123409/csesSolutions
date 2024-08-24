#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// For Ordered Set
// Header files, namespaces, 
// macros as defined above 
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
  
template <typename T>
using ordered_set = tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update> ;

// 7 2
/*

    take a queue

    takeIt = 1

    for element in queue:
        if takeIt == 0:
            cout << queue.front()
            queue.pop()
        else:
            q.push(q.front())
            q.pop()
        takeIt = (takeIt + 1) % (k + 1)
    
*/

int main()
{

    int i, n, k;
    cin >> n >> k;

    // queue<int> nums;

    // for(i=1;i<=n;i++) {
    //     nums.push(i);
    // }

    // int takeIt = 0;
    // while(!nums.empty()) {
    //     int j=0, sz=nums.size();
    //     takeIt = k == 0 ? 0 : 1;
    //     int effectiveJump = k+1;
    //     if(!nums.empty() && k+1 >= nums.size()) {
    //         effectiveJump = (k + 1) % nums.size();
    //         if(!effectiveJump) {
    //             effectiveJump = k+1;
    //         }
    //     }

    //     while(sz--) {
    //         if(takeIt % effectiveJump == 0) {
    //             continue;
    //         }


    //     }
    //     // for(j=0;j<sz;j++) {
    //     //     if(takeIt)
    //     // }
    // }

    // int takeIt = k == 0 ? 0 : 1;
    // while(!nums.empty()) {
    //     if(takeIt == 0) {
    //         cout << nums.front() << " ";
    //         nums.pop();
    //     }
    //     else {
    //         nums.push(nums.front());
    //         nums.pop();
    //     }

    //     int effectiveJump = (k + 1);
    //     if(!nums.empty() && k+1 >= nums.size()) {
    //         effectiveJump = (k + 1) % nums.size();
    //         if(!effectiveJump) {
    //             effectiveJump = k+1;
    //         }
    //     }
    //     takeIt = (takeIt + 1) % effectiveJump;
    // }
    // cout << "\n";

    ordered_set<int> nums;

    for(i=1;i<=n;i++) {
        nums.insert(i);
    }

    int currInd = 0;
    while(!nums.empty()) {
        currInd = (currInd + k) % nums.size();
        
        auto it = nums.find_by_order(currInd);
        cout << *(it) << " ";
        
        nums.erase(it);
    }
    cout << "\n";

    return 0;
}