#include<stdio.h>
#include<string.h>

char *uprav(char *c)
{
    char *a,*b;
    for (a=c; (*a==' ')&&*a; a++);
    for (b=c; *a; b++)
        if (*a==' ')
        {
            for (; (*a==' ')&&*a; a++);
            if (*a) *b=' ';
            else b--;
        }
        else
            *b=*(a++);
    *b=0;
    return c;
}

int jsem(int aven,int strt,int dav,int dst)
{
    return (dav&&!(strt%25))||(dst&&!(aven%25))||(dav&&dst&&!((strt+aven)%50))||(dav&&dst&&!((strt-aven)%50));
}

char vstup[500],*a,*b;
int i,j;
int aven,strt,dav,dst;
int av2,st2,da2,ds2,chyb;
int main()
{
    while (strcmp(uprav(gets(vstup)),"END"))
    {
        i=0;
        switch(vstup[i++])
        {
        case 'A':
            aven=0;
            for (; (vstup[i]>='0')&&(vstup[i]<='9'); i++) aven=aven*10+(vstup[i]-'0');
            if (vstup[i++]=='W') aven=-aven;
            i++;
            break;
        case 'S':
            strt=0;
            for (; (vstup[i]>='0')&&(vstup[i]<='9'); i++) strt=strt*10+(vstup[i]-'0');
            if (vstup[i++]=='S') strt=-strt;
            i++;
            break;
        }
        switch(vstup[i++])
        {
        case 'A':
            aven=0;
            for (; (vstup[i]>='0')&&(vstup[i]<='9'); i++) aven=aven*10+(vstup[i]-'0');
            if (vstup[i++]=='W') aven=-aven;
            i++;
            break;
        case 'S':
            strt=0;
            for (; (vstup[i]>='0')&&(vstup[i]<='9'); i++) strt=strt*10+(vstup[i]-'0');
            if (vstup[i++]=='S') strt=-strt;
            i++;
            break;
        }
        
        dav=0;
        dst=0;
        switch (vstup[i++])
        {
        case 'N':
            dst=+1;
            break;
        case 'S':
            dst=-1;
            break;
        case 'W':
            dav=-1;
            break;
        case 'E':
            dav=+1;
            break;
        }
        if (vstup[i])
            switch (vstup[i++])
            {
            case 'N':
                dst=+1;
                break;
            case 'S':
                dst=-1;
                break;
            case 'W':
                dav=-1;
                break;
            case 'E':
                dav=+1;
                break;
            }
            
        while (strcmp(uprav(gets(vstup)),"STOP"))
        {
            if (vstup[0]&&vstup[1]&&(vstup[2]==' ')&&(vstup[3]=='S')&&
                    (vstup[4]=='T')&&(vstup[5]=='R')&&(vstup[6]=='A')&&(vstup[7]=='I')&&
                    (vstup[8]=='G')&&(vstup[9]=='H')&&(vstup[10]=='T'))
                for (a=&vstup[2],b=&vstup[11]; *b; *(++a)=*(++b));

            if ((vstup[0]=='G')&&(vstup[1]=='O')&&(vstup[2]==' ')&&vstup[3])
            {
                if (((!vstup[4])&&(vstup[3]>='0')&&(vstup[3]<='9')&&(i=vstup[3]-'0'))||
                        (vstup[4]&&(!vstup[5])&&(vstup[3]>='0')&&(vstup[3]<='9')&&
                         (vstup[4]>='0')&&(vstup[4]<='9')&&(i=(vstup[3]-'0')*10+vstup[4]-'0')))
                {
                    aven+=i*dav;
                    strt+=i*dst;
                }
            }
            else
            {
                av2=aven+dav;
                st2=strt+dst;
                da2=0;
                ds2=0;
                chyb=1;
                if (!strcmp(vstup,"TURN LEFT"))
                {
                    chyb=0;
                    ds2=dav;
                    da2=-dst;
                }
                if (!strcmp(vstup,"TURN RIGHT"))
                {
                    chyb=0;
                    da2=dst;
                    ds2=-dav;
                }
                if (!strcmp(vstup,"TURN SHARP LEFT"))
                {
                    chyb=0;
                    if ((dav==+1)&&(dst==0))
                    {
                        da2=-1;
                        ds2=+1;
                    }
                    if ((dav==-1)&&(dst==0))
                    {
                        da2=+1;
                        ds2=-1;
                    }
                    if ((dav==0)&&(dst==+1))
                    {
                        da2=-1;
                        ds2=-1;
                    }
                    if ((dav==0)&&(dst==-1))
                    {
                        da2=+1;
                        ds2=+1;
                    }
                    if ((dav==+1)&&(dst==+1))
                    {
                        da2=-1;
                        ds2=0;
                    }
                    if ((dav==+1)&&(dst==-1))
                    {
                        da2=0;
                        ds2=+1;
                    }
                    if ((dav==-1)&&(dst==+1))
                    {
                        da2=0;
                        ds2=-1;
                    }
                    if ((dav==-1)&&(dst==-1))
                    {
                        da2=+1;
                        ds2=0;
                    }
                }
                if (jsem(aven,strt,dav,dst)) chyb=1;
                if (jsem(av2,st2,da2,ds2)) chyb=1;
                if (!strcmp(vstup,"TURN LEFT")) chyb=0;
                if (dav&&dst) chyb=1;
                if (da2&&ds2) chyb=1;
                if (!strcmp(vstup,"TURN SHARP LEFT")) chyb=0;
                if ((da2==ds2)&&(!((av2+st2)%50))) chyb=1;
                if ((da2==-ds2)&&(!((av2-st2)%50))) chyb=1;
                if (da2&&ds2&&((av2+st2)%50)&&((av2-st2)%50)) chyb=1;
                
                if (!chyb)
                {
                    aven=av2;
                    strt=st2;
                    dav=da2;
                    dst=ds2;
                }
            }
        }
        
        if (jsem(aven,strt,dav,dst))
            printf("Illegal stopping place\n");
        else
        {
            printf("A%d%c S%d%c ",(aven>=0)?aven:-aven,(aven>=0)?'E':'W',
                   (strt>=0)?strt:-strt,(strt>=0)?'N':'S');
            if (dst==+1) printf("N");
            if (dst==-1) printf("S");
            if (dav==+1) printf("E");
            if (dav==-1) printf("W");
            printf("\n");
        }
    }
    return 0;
}
