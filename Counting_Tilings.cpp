#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

// 4 7
/*

    n x m

    I approach
    recurse(n, m):
        if (n == 1 && m == 2) || (n == 2 && m == 1):
            return 1

        put21 = recurse(n-2, m-1)
        put12 = recurse(n-1, m-2)

        return put21 + put12 % mod

    this approach cannot work because we are not sure how ways would be subdivided
    like you can subdivide problem into
        - (n-2 * m-1) , (2 * m-1) , (n-2 * 1)
        - (2 * m-1) , (n-2 * m)
        - (n-2 * 1) , (n * m-1)
    and in all cases there is no clear boundary to differentiate ways (its not even clear to me whether these are only cases of subdivision)

    II approach
    think of it as counting towers but with n towers

    - at every step we would pass a mask indicating state of last column, 0 for closed and 1 for open
    - if it was open, we only have 1 choice to close it
    - if it was closed, we have 2 choices
        - as 2 closed rows would always come, so we can open 2 rows, or
        - we can continue with adding 2 closed rows

    recurse(mask, in, n, m):
        if in == m:
            return mask == 0

        ans = 0
        store all occurences of 00 in mask into closedPositions = []
        new_mask = inverted(mask)
        make 0 at all closedPositions because we would put choice on that

        for all subset of closedPositions:
            for all positions in closedPositions:
                if position's bit in subset is 1: // goal is that for every 00 we have 2 choices that is 00 and 11
                    new_mask[position] = 11
                    ans += recurse(new_mask, in+1, n, m)
                    new_mask[position] = 00

        return ans

    this implementation would not work and even if it works, it would be too messy
    0000 -> we would first negate it
            then we would put all 0s at closedPostions, it would again become 0000
            now, if we would change at position (2,3), it would become 0110, even though 1st and 4th 0 should have been 1

    YT Solution - Kartik arora
    - generate all possible next masks through recursions
    - rest everything is same




*/

int multiplyWays(int a, int b) {
    if(a == 0) {
        return b;
    }
    else if(b == 0) {
        return a;
    }
    else {
        return a * b;
    }
}

int solve(int n, int m) {

    if((n == 1 && m == 2) || (n == 2 && m == 1)) {
        return 1;
    }

    if(m < 1 || n < 1) {
        return 0;
    }

    ps.push_back('\t');
    cout << ps << n << " , " << m;

    int put12 = 0;
    if(m >= 2) {
        put12 = multiplyWays(put12, solve(n-1, 2));
    }
    if(n >= 1) {
        put12 = multiplyWays(put12, solve(1, m-2));
    }
    // if(n > 1 && m > 2) {
    //     put12 *= solve(n-1, m-2);
    // }
    put12 = multiplyWays(put12, solve(n-1, m-2));
    
    int put21 = 0;
    if(m >= 1) {
        put21 = multiplyWays(put21, solve(n-2, 1));
    }
    if(n >= 2) {
        put21 = multiplyWays(put21, solve(2, m-1));
    }
    // if(n > 2 && m > 1) {
    //     put21 *= solve(n-2, m-1);
    // }
    put21 = multiplyWays(put21, solve(n-2, m-1));

    // int put12 = solve(1, m-2);
    // if(n > 1) {
    //     put12 += solve(n-1, m-2) * solve(n-1, 2);
    // }
    // int put21 = solve(n-2, m-1) * solve(2, m-1) * solve(n-2, 1);
    cout << ps << put12 << " : " << put21;

    ps.pop_back();

    return put12 + put21;

}

bool maskAt(int mask, int p) {
    return (mask & (1 << p)) > 0;
}

void generateNextMasks(int mask, int in, int n, vector<int>& next_masks) {
    if(in == n) {
        next_masks.push_back(mask);
        return;
    }

    if(maskAt(mask, in)) {
        mask ^= (1 << in);
        generateNextMasks(mask, in+1, n, next_masks);
    }
    else {
        if(in < n-1 && !maskAt(mask, in+1)) {
            generateNextMasks(mask, in+2, n, next_masks);
        }
        mask ^= (1 << in);
        generateNextMasks(mask, in+1, n, next_masks);
    }
}

int dp[1<<10][1000];

int solve(int mask, int in, int n, int m) {
    if(in == m) {
        return mask == 0;
    }

    if(dp[mask][in] != -1) {
        return dp[mask][in];
    }

    int ans = 0, i;
    // vector<pair<int,int>> closedPositions;
    // for(i=0;i<n-1;i++) {
    //     if(maskAt(mask, i) == 0 && maskAt(mask, i+1) == 0) {
    //         closedPositions.push_back({i, i+1});
    //     } 
    // }

    // int new_mask = 

    // ps.push_back('\t');
    // cout << ps << bitset<4>(mask) << " , " << in;

    vector<int> next_masks;
    generateNextMasks(mask, 0, n, next_masks);

    for(int next_mask : next_masks) {
        ans = (1ll * ans + solve(next_mask, in+1, n, m)) % int(1e9+7);
    }
    // cout << ps << ans;
    // ps.pop_back();

    return dp[mask][in] = ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, n, m;
    
    cin >> n >> m;
    memset(dp, -1, sizeof(dp));

    // int ans = solve(n, m);
    // cout << "\n" << ans << "\n";
    
    // vector<int> next_masks;
    // generateNextMasks(0, 0, 4, next_masks);

    // for(int mask : next_masks) {
    //     cout << bitset<4>(mask) << "\n";
    // }

    cout << solve(0, 0, n, m) << "\n";

    return 0;
}

// #include <bits/stdc++.h>
// using namespace std;

// typedef long long ll;

// // dp array to memoize results of subproblems
// ll dp[1050][2050]; // dp[i][mask] stores the number of ways to fill the grid starting from column i with the mask representing the current state of filled cells

// const int MOD = 1e9 + 7;

// // Function to generate the next possible mask based on the current mask and position
// void generateNextMask(int n, int curr_mask, int new_mask, int j, vector<int> &nextMask)
// {
//     if (j == n)
//     {
//         nextMask.push_back(new_mask);
//         return;
//     }
//     // If there's enough space and cells are empty, place a 2x1 tile
//     if (j + 1 < n && (((1 << j) & (curr_mask)) == 0) && (((1 << (j + 1)) & (curr_mask)) == 0))
//     {
//         generateNextMask(n, curr_mask, new_mask, j + 2, nextMask);
//     }
//     // Place a 1x2 tile if the cell is empty
//     if ((((1 << j) & (curr_mask)) == 0))
//     {
//         generateNextMask(n, curr_mask, new_mask + (1 << j), j + 1, nextMask);
//     }
//     // Move to the next cell if the current cell is already filled
//     if ((((1 << j) & (curr_mask)) != 0))
//     {
//         generateNextMask(n, curr_mask, new_mask, j + 1, nextMask);
//     }
// }

// // Recursive function to compute the number of ways to fill the grid
// ll countWays(int n, int m, int i, int mask)
// {
//     // Base case: reached the end of the grid
//     if (i == m)
//     {
//         // If the entire grid is filled, return 1, otherwise return 0
//         if (mask == 0)
//             return 1;
//         else
//             return 0;
//     }

//     // If the result for the current state is already computed, return it
//     if (dp[i][mask] != -1)
//         return dp[i][mask];

//     // Generate next possible masks for the current column
//     vector<int> nextMask;
//     generateNextMask(n, mask, 0, 0, nextMask);

//     // Initialize the answer for the current state
//     long long ans = 0;

//     // Iterate over all possible next masks and recursively compute the answer
//     for (auto x : nextMask)
//     {
//         ans = (ans % MOD + countWays(n, m, i + 1, x) % MOD) % MOD;
//     }

//     // Memoize the result and return it
//     dp[i][mask] = ans;
//     return dp[i][mask];
// }

// // Driver Code
// int main()
// {
//     // ll n=2, m=2;
//     int n, m;
//     cin >> n >> m;
    

//     // Initialize dp array with -1
//     memset(dp, -1, sizeof(dp));

//     // Compute and print the number of ways to fill the grid
//     cout << countWays(n, m, 0, 0) << endl;
//     return 0;
// }
