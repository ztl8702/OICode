#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
const int MAXLEN=1005;
struct TItem
{
    int left,right,pr;
    char op;
} item[MAXLEN];
char s[MAXLEN];
int p, count;

int createItem(const int left, const int right, const char op, const int pr)
{
    ++count;
    item[count].left=left;
    item[count].right=right;
    item[count].op=op;
    item[count].pr=pr;
    return count;
}

int parseExpr();  // <Term> | <Expr> + <Term> | <Expr> - <Term>
int parseFactor(); // a..z | (<Expr>)
int parseTerm();  // <Factor> | <Term> * <Factor> | <Term> / <Factor>

int parseFactor() // a..z | <Expr>
{
    int ans;
    if (s[p]=='(')
    {
        ++p;
        ans=parseExpr();
        ++p; // ')'
    }
    else
    {
        ans=createItem(0,0,s[p],3);
        ++p;
    }
    return ans;
}

int parseExpr()
{
    int a=parseTerm(), b;
    char op;
    while (s[p]=='+' || s[p]=='-')
    {
        op=s[p];
        ++p;
        b=parseTerm();
        a=createItem(a,b,op,1);
    }
    return a;
}

int parseTerm()
{
    int a, b;
    char op;
    a=parseFactor();
    while (s[p]=='*' || s[p]=='/')
    {
        op=s[p];
        ++p;
        b=parseFactor();
        a=createItem(a,b,op,2);
    }
    return a;
}

void print(const int now, const bool inverse)
{
    if ('a'<=item[now].op && item[now].op<='z')
        printf("%c", item[now].op);
    else
    {
        /*left*/
        if (item[item[now].left].pr>item[now].pr)
            print(item[now].left, false);
        else if (item[item[now].left].pr<item[now].pr)
        {
            printf("(");
            print(item[now].left,false);
            printf(")");
        }
        else
            print(item[now].left,inverse);
        /*OPERATOR*/
        if (!inverse)
            printf("%c", item[now].op);
        else
        {
            if (item[now].op=='+') printf("-");
            if (item[now].op=='-') printf("+");
            if (item[now].op=='*') printf("/");
            if (item[now].op=='/') printf("*");
        }
        /*right*/
        if (item[item[now].right].pr>item[now].pr)
            print(item[now].right, false);
        else if (item[item[now].right].pr<item[now].pr)
        {
            printf("(");
            print(item[now].right,false);
            printf(")");
        }
        else
        {
            if (item[now].op=='/' || item[now].op=='-')
                print(item[now].right, !inverse);
            else
                print(item[now].right, inverse);
        }
    }
}

int main()
{
    gets(s);
    p=0;
    print(parseExpr(), false);
    printf("\n");
    return 0;
}
