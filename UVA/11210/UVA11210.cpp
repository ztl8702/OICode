#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <algorithm>
const char* tile[]={"","1T","2T","3T","4T","5T","6T","7T","8T","9T",
                       "1S","2S","3S","4S","5S","6S","7S","8S","9S",
                       "1W","2W","3W","4W","5W","6W","7W","8W","9W",
                       "DONG","NAN","XI","BEI",
                       "ZHONG","FA","BAI"
                    };
int find(char *s)
{
    for (int i=1; i<=34; ++i)
        if (strcmp(s,tile[i])==0)
            return i;
    return 0;
}

int count[40];

int ma[20];
char rd[1000];
int testcase;
bool Ting;

bool search(const int totPair)
{
    if (totPair>=4)
    {
        return true;
    }
    int i;
    bool ret;
    for (i=1; i<=34; ++i)
        if (count[i]>=3)
        {
            count[i]-=3;
            ret=search(totPair+1);
            count[i]+=3;
            if (ret)
                return true;
        }
    for (i=1; i<=27; ++i)
        if ('1'<=tile[i][0]&&tile[i][0]<='7' && count[i]>0 && count[i+1]>0 && count[i+2]>0)
        {
            count[i]--;
            count[i+1]--;
            count[i+2]--;
            ret=search(totPair+1);
            count[i]++;
            count[i+1]++;
            count[i+2]++;
            if (ret)
                return true;
        }
    return false;
}

bool check()
{
    int i;
    for (i=1; i<=34; i++)
        if (count[i]>=2)
        {
            count[i]-=2;
            if (search(0))
            {
                count[i]+=2;
                return true;
            }
            count[i]+=2;
        }
    return false;
    
}

int main()
{
    int i,j;
    while (scanf("%s", &rd)!=EOF)
    {
        if (rd[0]=='0') break;
        printf("Case %d:", ++testcase);
        memset(count,0,sizeof(count));
        ma[1]=find(rd);
        ++count[ma[1]];
        for (i=2; i<=13; ++i)
        {
            scanf("%s", &rd);
            ma[i]=find(rd);
            count[ma[i]]++;
        }
        Ting=false;
        for (j=1; j<=34; ++j)
            if (count[j]<4)
            {
                ++count[j];
                if (check())
                {
                    Ting=true;
                    printf(" %s", tile[j]);
                }
                --count[j];    
            }
        if (!Ting)
            printf(" Not ready");
        printf("\n");
    }
    return 0;
    
}
