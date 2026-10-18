//
// Created by cohen on 08/10/2026.
//

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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n,c;
    cin>>n>>c;

    vector<vll> fences(n,vll(4));
    vpll cows(c);
    set<ll> xs,ys;
    for(ll i=0;i<n;i++)
    {
        cin>>fences[i][0]>>fences[i][1]>>fences[i][2]>>fences[i][3];
        xs.insert(fences[i][0]);
        ys.insert(fences[i][1]);
        xs.insert(fences[i][2]);
        ys.insert(fences[i][3]);
    }
    for(ll i=0;i<c;i++)
    {
        cin>>cows[i].first>>cows[i].second;
        xs.insert(cows[i].first);
        ys.insert(cows[i].second);
    }
    map<ll,ll> mapx,mapy;
    ll indx=0;
    for(ll i:xs)
    {
        mapx[i]=indx;
        indx++;
    }
    ll indy=0;
    for(ll i:ys)
    {
        mapy[i]=indy;
        indy++;
    }

    vvll graph(indx,vll(indy));
    for (ll i=0;i<n;i++)
    {
        ll x1=mapx[fences[i][0]],y1=mapy[fences[i][1]],
            x2=mapx[fences[i][2]],y2=mapy[fences[i][3]];
        if
    }

}

