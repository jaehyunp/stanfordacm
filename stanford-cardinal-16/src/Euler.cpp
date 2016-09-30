const int maxn=500005;
vector<PII> f[maxn];
int N,M,xc,yc,o;
int use[maxn],ans[maxn],last[maxn];
void dfs(int s){
    for (;last[s]<f[s].size();last[s]++)
        if (use[f[s][last[s]].w2]==0)
        {
            use[f[s][last[s]].w2]=1;
            dfs(f[s][last[s]].w1);
        }
    ++o,ans[o]=s;
}

int main(){
    scanf("%d %d",&N,&M);
    for (int i=1;i<=M;i++){
        scanf("%d %d",&xc,&yc);
        f[xc].p_b(m_p(yc,i));
        f[yc].p_b(m_p(xc,i));
    }
    memset(use,0,sizeof(use));
    o=0;
    memset(last,0,sizeof(last));
    dfs(1);
    return 0;
}
