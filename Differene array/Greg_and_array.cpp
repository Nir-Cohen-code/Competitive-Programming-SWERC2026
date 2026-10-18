//
// Created by cohen on 08/10/2026.
//

#include "Greg_and_array.h"
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    ll n,m,k;
    cin>>n>>m>>k;

    vll data(n);
    for(ll i=0;i<n;i++)
    {
        cin>>data[i];
    }

    vvll ops(m, vll(3));
    for(ll i=0;i<m;i++)
    {
        cin>>ops[i][0]>>ops[i][1]>>ops[i][2];
        ops[i][0]--;ops[i][1]--;
    }
    vll ops_diff(m+1);
    for (ll i=0;i<k;i++)
    {
        ll x,y;
        cin>>x>>y;
        x--;y--;
        ops_diff[x]++;ops_diff[y+1]--;
    }

    vll data_diff(n+1);
    ll amount=0;
    for(ll i=0;i<m;i++)
    {
        amount+=ops_diff[i];
        ll x,y,d;
        x=ops[i][0];
        y=ops[i][1];
        d=ops[i][2]*amount;
        data_diff[x]+=d;data_diff[y+1]-=d;
    }
    amount=0;
    for(ll i=0;i<n;i++)
    {
        amount+=data_diff[i];
        cout<<data[i]+amount;
        if(i!=n-1)cout<<" ";
    }
    cout<<'\n';


    return 0;
}