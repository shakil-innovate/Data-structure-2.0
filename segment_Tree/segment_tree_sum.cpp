#include<bits/stdc++.h>
using namespace std;

class Segment
{
    public:

  vector<int>tree,seg;
  int n;

  Segment(int v)
  {
    n=v;
    tree.resize(n);
    seg.resize(4*n);
  }

  void build(int low,int high,int pos)
  {
    if(low==high)
    {
        seg[pos]=tree[low];
    }
    else
    {
        int mid=(low+high)>>1;
        build(low,mid,pos*2+1);
        build(mid+1,high,pos*2+2);
         
        seg[pos]=seg[pos*2+1]+seg[pos*2+2];
    }
  }

  void update(int low,int high,int pos,int ind,int val)
  {
    if(low==high)
       seg[pos]=val;
    else
    {
        int mid=(low+high)>>1;
        if(ind<=mid)
            update(low,mid,pos*2+1,ind,val);
        else
          update(mid+1,high,pos*2+2,ind,val);

        seg[pos]=seg[pos*2+1]+seg[pos*2+2];
    }
  }

  int rangeQuery(int qlow,int qhigh,int low,int high,int pos)
  {
    if(qlow>high || qhigh<low)
       return 0;

    if(qlow<=low && qhigh>=high)
       return seg[pos];

    int mid=(low+high)>>1;
    return (rangeQuery(qlow,qhigh,low,mid,pos*2+1)+rangeQuery(qlow,qhigh,mid+1,high,pos*2+2));
  }

};

int main()
{
    int n,q;  cin>>n>>q;

    Segment g(n);

    for(int i=0;i<n;i++)
    {
        cin>>g.tree[i];
    }

    g.build(0,n-1,0);

    for(int i=0;i<q;i++)
    {
        string command; cin>>command;

        if(command=="sum")
        {
            int l,r;    cin>>l>>r;
            cout<<g.rangeQuery(l,r,0,n-1,0)<<endl;
        }
        else if(command=="up")
        {
            int ind,val;        cin>>ind>>val;
            g.update(0,n-1,0,ind,val);
        }
    }


}