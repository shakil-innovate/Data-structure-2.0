#include<bits/stdc++.h>
using namespace std;

struct Node
{
  Node* links[26];
  int cnt=0;
  bool flag=false;

  void put(char ch,Node* node)
  {
    links[ch-'a']=node;
  }
  bool isContain(char ch)
  {
    return links[ch-'a']!=nullptr;
  }

  Node* getLink(char ch)
  {
    return links[ch-'a'];
  }

};

Node* root=new Node();

void insert(string s)
{
    Node* node=root;

    for(int i=0;i<s.size();i++)
    {
        if(!node->isContain(s[i]))
        {
            node->put(s[i],new Node());
        }
        node=node->getLink(s[i]);
        node->cnt++;
    }
    node->flag=true;
}

int  check(string s)
{
    Node* node=root;

    for(int i=0;i<s.size();i++)
    {
      node=node->getLink(s[i]);
    }

    return node->cnt;
}

int main()
{
  int n;    cin>>n;

  vector<string>v(n);

  for(int i=0;i<n;i++)  {cin>>v[i];insert(v[i]);}

  for(int i=0;i<n;i++)
  {
    cout<<v[i] <<" pref "<<check(v[i])-1<<endl;
  }


}