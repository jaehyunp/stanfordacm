const int bigp=8388067;

ULL hash[10000007];
int hash2[10000007];

void pushhash(ULL s)
{
    int e=s&bigp;
    while ((hash[e]!=0)&&(hash[e]!=s)) ++e;
    if (hash[e]==0) hash[e]=s,hash2[e]=1; else hash2[e]++;
}

int findhash(ULL s)
{
    int e=s&bigp;
    while ((hash[e]!=0)&&(hash[e]!=s)) ++e;
    if (hash[e]==0) return 0; else return hash2[e];
}
