#include <cstdio>
#include <cstring>
#include <cstdlib>

char code[2000],key[2000];

int main()
{
    gets(key);
    gets(code);
    int keyLen=strlen(key);
    int codeLen=strlen(code);
    for (int i=0; i<codeLen; ++i)
    {
        int ori, keyi;
        if (code[i]>='a')
        {
            ori=code[i]-'a';
        }
        else
        {
            ori=code[i]-'A';
        }
        if (key[i%keyLen]>='a')
            keyi=key[i%keyLen]-'a';
        else
            keyi=key[i%keyLen]-'A';
        int ans=(ori-keyi+26)%26;
        if (code[i]>='a')
            printf("%c", ans+'a');
        else
            printf("%c",ans+'A');                
    }
    puts("");
    return 0;
} 
