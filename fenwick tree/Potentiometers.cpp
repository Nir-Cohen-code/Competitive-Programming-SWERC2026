//
// Created by cohen on 13/10/2026.
//

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

using vs = vector<string>;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using ld = long double;
using vld = vector<ld>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using pld = pair<ld, ld>;
using vpld = vector<pld>;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())


struct FenwickTree {
    vll bit;  // binary indexed tree
    ll n;

    FenwickTree(ll n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vll const &a) : FenwickTree(a.size()){
        for (ll i = 0; i < n; i++) {
            bit[i] += a[i];
            ll r = i | (i + 1);
            if (r < n) bit[r] += bit[i];
        }
    }

    ll sum(ll r) {
        ll ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    ll sum(ll l, ll r) {
        return sum(r) - sum(l - 1);
    }

    void add(ll idx, ll delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};


/**
 * Updates the BIT by adding 'val' to the element at 'index'
 * and propagating the change to all responsible ancestors.
 */
void updateBIT(vll &BITree, ll n, ll index, ll val) {
    index = index + 1; // Convert 0-indexed to 1-indexed

    while (index <= n) {
        BITree[index] += val;
        index += index & (-index); // Move to next ancestor
    }
}

/**
 * Returns the prefix sum of the original array from index 0 to 'index'.
 */
int getSum(vll &BITree, ll index) {
    ll sum = 0;
    index = index + 1; // Convert 0-indexed to 1-indexed

    while (index > 0) {
        sum += BITree[index];
        index -= index & (-index); // Move to parent node
    }
    return sum;
}

/**
 * Initializes the BIT and populates it using the input array.
 */
void buildBIT(vll &arr, vll &BIT, ll n) {
    for(int i = 1; i <= n; i++) {
        BIT[i] += arr[i-1];

        int parent = i + (i & -i);
        if(parent <= n)
            BIT[parent] += BIT[i];
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n,t=1;
    while (cin>>n)
    {
        if (n==0)
        {
            return 0;
        }
        if (t!=1)cout<<"\n";
        cout<<"Case "<<t++<<":\n";
        vll data(n);

        for (ll i=0;i<n;i++)
        {
            cin>>data[i];
        }
        FenwickTree ft(data);
        //buildBIT(data,BIT,n);
        string command;
        cin>>command;
        while(command != "END")
        {
            if(command == "S")
            {
                ll x,r;
                cin>>x>>r;
                x--;
                //updateBIT(BIT,n,x-1,r);
                ft.add(x,r-data[x]);
                data[x] = r;
            }
            else
            {
                ll x,y;
                cin>>x>>y;
                x--,y--;

                //cout<<getSum(BIT,y)-getSum(BIT,x-1)<<endl;
                cout<<ft.sum(x,y)<<"\n";
            }
            cin>>command;
        }

    }
}
