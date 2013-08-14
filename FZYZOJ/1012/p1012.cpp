#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
const int MAXN=1005;
int n;
struct TData
{
    string names,num;
} person[MAXN];
int cmp(const string &a, const string &b)
{
    if (a.length()<b.length())
        return -1;
    else if (a.length()>b.length())
        return 1;
    else
    {
        for (int i=0; i<a.length(); ++i)
        {
            if (a[i]<b[i])
                return -1;
            else if (a[i]>b[i])
                return 1;
        }
    }
    return 0;
    
}
inline bool stringcmp(const TData &a, const TData &b)
{
    return (cmp(a.num,b.num)>0 || (cmp(a.num,b.num)==0 && a.names<b.names));
}




int main()
{
    int i;
    cin>>n;
    for (i=1; i<=n; ++i)
    {
        cin>>person[i].names>>person[i].num;
    }
    std::sort(person+1, person+1+n, stringcmp);
    for (i=1; i<=n; ++i)
        cout<<person[i].names<<endl;
        system("pause");
    return 0;
} 
