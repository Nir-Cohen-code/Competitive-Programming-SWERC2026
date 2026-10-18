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

int log2_floor(unsigned long long i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,m,k;

    cin >> n >> m >> k;

    vvll data(m,vll(n));

    for (ll i=0;i<n;i++)
    {
        for (ll j=0;j<m;j++)
        {
            cin >> data[j][i];
        }
    }
    ll n_log=log2_floor(n);
    vector<vvll> st(m,vvll(n_log+1,vll(n)));
    for(ll mm=0;mm<m;mm++)
    {
        st[mm][0]=data[mm];
        for (int i = 1; i <= n_log; i++)
            for (int j = 0; j + (1 << i) <= n; j++)
                st[mm][i][j] = max(st[mm][i - 1][j], st[mm][i - 1][j + (1 << (i - 1))]);
    }

    auto get_st_val = [&](ll mm, ll L, ll R)
    {
        ll i = log2_floor(R - L + 1);
        return  max(st[mm][i][L], st[mm][i][R - (1 << i) + 1]);
    };

    ll a=0,b=0,best=0;
    ll best_a=0,best_b=0;

    while(b < n)
    {
        ll cur=0;
        for(ll mm=0;mm<m;mm++)
        {
            cur+=get_st_val(mm,a,b);
        }
        if(cur <= k)
        {
            if (b-a+1>best)
            {
                best = b-a+1;
                best_a = a;
                best_b = b;
            }
            b++;
        }
        else
        {
            if (a==b)b++;
            a++;
        }
    }


    for (ll mm=0;mm<m;mm++)
    {
        if (best==0)
            cout<<"0";
        else
            cout<< get_st_val(mm,best_a,best_b) ;
        if (mm!=m-1) cout<<" ";
    }
}