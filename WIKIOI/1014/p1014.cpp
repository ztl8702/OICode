#include <cstdio>
#include <cstring>
#include <cstdlib>
int v, n;
bool checked[20005];
int volume[200];
int main()
{
    memset(checked,false, sizeof(checked));
    scanf("%d%d", &v, &n);
    for (int i=1; i<=n; ++i)
        scanf("%d", &volume[i]);
    checked[0]=true;
    int ans=0;
    for (int i=1; i<=n; ++i)
    {
        for (int j=v-volume[i]; j>=0; --j)
            if (checked[j])
            {
                checked[j+volume[i]]=true;
                if (j+volume[i]>ans)
                    ans=j+volume[i];
            }
    }
    printf("%d\n", v-ans);
    return 0;
}
