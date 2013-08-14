#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
int n,len;
char str[2526];
int letterCount[27];
int main()
{
    gets(str);
    len=strlen(str);
    scanf("%d", &n);
    memset(letterCount, 0, sizeof(letterCount));
    for (int i=0; i<len; ++i)
    {
        if (str[i]>='a')
            ++letterCount[str[i]-'a'];
        else
            ++letterCount[str[i]-'A'];
    }
    int usedLetter=0;
    for (int i=0; i<26; ++i)
        if (letterCount[i]>0)
            ++usedLetter;
    if (n<usedLetter)
    {
        printf("-1\n");
    }
    else
    {
        int sheet[27]={0};
        int sheetSpace=n;
        for (int i=0; i<26; ++i)
            if (letterCount[i]>0)
            {
                --sheetSpace;
                ++sheet[i];
            }
        while (sheetSpace>0)
        {
            int max=-1,maxi=-1;
            for (int i=0; i<26; ++i)
                if (letterCount[i]>0 && (int)ceil(((double)letterCount[i])/sheet[i])>max)
                {
                    max=(int)ceil(((double)letterCount[i])/sheet[i]);
                    maxi=i;
                }
            if (maxi!=-1)
            {
                ++sheet[maxi];
                --sheetSpace;
            }
            else
            {
                ++sheet[0];
            }
        }
        int ans=-1;
        for (int i=0; i<26; ++i)
        {
            if (letterCount[i]>0 && (int)ceil(((double)letterCount[i])/sheet[i])>ans)
            {
                ans=(int)ceil(((double)letterCount[i])/sheet[i]);
            }
        }
        printf("%d\n", ans);
        for (int i=0; i<26; ++i)
        {
            for (int j=1; j<=sheet[i]; ++j)
                printf("%c", i+'a');
        }
        puts("");
    }
}
