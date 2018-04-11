#include "tree.h"
#include <iostream>
using namespace std;

class mat22
{
public:
  static const long long MOD = 1000000009;
  long long tab[2][2];
  mat22(int x)
  {
    if(x != 0)
      return;
    tab[0][0] = 1;
    tab[1][0] = 0;
    tab[0][1] = 0;
    tab[1][1] = 1;
  }

  mat22(int a, int b, int c, int d)
  {
    tab[0][0] = a;
    tab[0][1] = b;
    tab[1][0] = c;
    tab[1][1] = d;
  }

  mat22()
  {
    mat22(0);
  }

  mat22 operator = (mat22 b)
  {
    tab[0][0] = b.tab[0][0];
    tab[0][1] = b.tab[0][1];
    tab[1][0] = b.tab[1][0];
    tab[1][1] = b.tab[1][1];
    return *this;
  }

  mat22 operator + (mat22 b)
  {
    mat22 ret((this->tab[0][0] * b.tab[0][0] + this->tab[0][1] * b.tab[1][0]) % MOD,
              (this->tab[0][0] * b.tab[0][1] + this->tab[0][1] * b.tab[1][1]) % MOD,
              (this->tab[1][0] * b.tab[0][0] + this->tab[1][1] * b.tab[1][0]) % MOD,
              (this->tab[1][0] * b.tab[0][1] + this->tab[1][1] * b.tab[1][1]) % MOD);
    return ret;
  }

  mat22 operator ^ (int b)
  {
    mat22 ret(0);
    if (b == 0)
      return ret;
    if (b % 2 == 1)
    {
      ret = ret + *this;
    }
    if (b == 1)
    {
      return ret;
    }
    return (ret + ((*this + *this) ^ (b/2)));
  }

  void print()
  {
    cout<<tab[0][0]<<" "<<tab[0][1]<<endl<<tab[1][0]<<" "<<tab[1][1]<<endl;
  }
};


int main()
{
  int type, size, n;
  cin>>type>>size>>n;
  if (type == 0)
  {
    // Regular integer addition on a segment.
    Tree<int> tree(size);
    for (int i = 0; i < n; i++)
    {
      int a;
      cin>>a;
      if (a == 0)
      {
        int b, c, d;
        cin>>b>>c>>d;
        tree.add(b, c, d);
      }
      else
      {
        int b;
        cin>>b;
        int odp = tree.get(b);
        cout<<odp<<endl;
      }
    }
  }
  else
  {
    Tree<mat22> tree(size);
    // Adding a value on a segment means multiplying the
    // matrices by Fibonacci sequence matrix raised to the
    // given power.
    mat22 unit(1, 1, 1, 0);

    for (int i = 0; i < n; i++)
    {
      int a;
      cin>>a;
      if (a == 0)
      {
        int b, c, d;
        cin>>b>>c>>d;
        tree.add(b, c, unit ^ d);
      }
      else
      {
        int b;
        cin>>b;
        mat22 odp = tree.get(b);
        odp.print();
      }
    }
  }
}
