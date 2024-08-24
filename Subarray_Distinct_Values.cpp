#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 2 4 1 2 7
/*

    brute force
    for every element
    - start from that index and traverse right for k elements, and add elements in a set
    - if some element is already in the set, then stop the operation and start from next index of current element's previous index
    - increment the index and repeat 1st step

    O(n*n*logn)

    I approach
    take a map to store previous indexes of elements
    take a variable to store last good index,i.e, at which another element is there which is present in current subarray
    for ex, 2 1 3 4 2, here last good index would be 0 for index 4
    so, we can take any subarray whose length is k from current index to last good index
    so, in total (length - k + 1) subarrays would be there, if length >= k

    lgi = -1
    map of previous indexes; mpi = {}
    for index, element in array:
        lgi = max(lgi, mpi[element])
        length = index - lgi

        if(length >= k):
            ans += (length - k + 1)
        
        mpi[element] = index

    WA - sample test case - thought about solution for finding number of sub arrays having at least k distinct subarrays, but number of sub arrays having at most k distinct subarrays was asked

    II approach
    we would keep a running subarray, and keep adding elements to it
    we can use set to check how many distinct elements we have in the subarray
    if number of distinct elements exceeds k, then
    - we can see that there would be many numbers with different frequencies and indexes inside running subarray
    for ex, for 1 1 2 1 2 3, if k is 2
    then on reaching 3, we would have to remove all occurences of 1, because it is only one to finish first

    so, to get last good index, we would have to find the ending (or the last index) indexes of elements
    and, then find the element which is ending first, i.e, its last index is smallest among all elements
    update the length of current subarray from last good index and find new subarrays fulfilling required criteria
    we can add (current_index - last_good_index) because we can add every subarray from last_good_index+1 to current_index

    we can take map of element->index, to store number of unique elements and their last indexes
    we can take map of index->element, to store minimum index of last index and its corresponding element

    mei = {}
    mie = {}
    for index, element in array:
        if mei contains element:
            pli = mei[element]
            mie.remove(pli)
        mei[element] = index
        mie[index] = element

        if mei.size > k:
            lgi, etr = mie.smallest
            mei.remove(etr)

        ans += (index - lgi)

    print ans

    III approach
    all these complexities is not needed, if we would use multiset
    - we would add elements one by one in multiset as current running sum
    - if number of elements in multiset is > k, then remove the elements from starting unless number of elements in multiset is <= k

    Not possible - because multiset have no way to get number of unique elements in less than O(n), probably because you have to iterate over all elements of multiset
*/

int main()
{

    int i, n, k;
    cin >> n >> k;

    int lgi = -1;
    map<int,int> mei, mie;
    ll ans = 0ll;
    for(i=0;i<n;i++) {
        int x;
        cin >> x;

        if(mei.count(x)) {
            int pli = mei[x];
            mie.erase(pli);
        }
        mei[x] = i;
        mie[i] = x;

        if(mei.size() > k) {
            lgi = mie.begin()->first;
            int etr = mie.begin()->second;
            // cout << lgi << " : " << etr << " <-\n";

            mie.erase(lgi);
            mei.erase(etr);
        }

        ans += (i - lgi);
        // cout << i << " : " << lgi << " = " << ans << "\n";
    }

    cout << ans << "\n";

    // multiset<int> crs;
    // int a[n];
    // for(i=0;i<n;i++) {
    //     cin >> a[i];
    // }

    // int l=0, r=0;
    // ll ans = 0ll;
    // for(r=0;r<n;r++) {
    //     crs.insert(a[r]);
    //     while(l < r && crs.size() > k) {
    //         auto itr = crs.find(a[l]);
    //         if(itr != crs.end()) {
    //             crs.erase(itr);
    //         }
    //         l++;
    //     }

    //     for(int it : crs) {
    //         cout << it << " ";
    //     }
    //     cout << "\n";

    //     ans += (r - l);
    // }

    // cout << ans << "\n";
    return 0;
}