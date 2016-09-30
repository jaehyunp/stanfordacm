map<int,int> lsh;
map<int,int>::iterator lsg;
char st[maxn];
int N,o,e,p,u,v;
int a[maxn],b[maxn],over[maxn],biao[maxn];
int c[maxn],d[maxn],c1[maxn],d1[maxn],mark[maxn],t[maxn];
PII ls[maxn];

int main() {
  scanf("%s",st);
  N=strlen(st);
  for (int i=1;i<=N;i++) a[i]=st[i-1];
  for (int i=1;i<=N;i++) lsh.insert(m_p(a[i],0));
  for (o=1,lsg=lsh.begin();lsg!=lsh.end();++o,++lsg) lsg->w2=o;
  for (int i=1;i<=N;i++) a[i]=lsh.l_b(a[i])->w2;

  for (int i=1;i<=N;i++) ls[i]=m_p(a[i],i);
  sort(ls+1,ls+N+1);
  for (int i=1;i<=N;i++) c[i]=ls[i].w2,mark[i]=ls[i].w1,d[c[i]]=i;
  e=1;
  while (e<=N) {
    memset(biao,0,sizeof(biao));
    over[N]=N;
    for (int i=N-1;i>=1;i--)
      if (mark[i]!=mark[i+1]) over[i]=i; else over[i]=over[i+1];
    for (int i=N;i>=1;i--) {
      p=c[i]; if (p<=e) continue;
      p=d[p-e];u=over[p];v=u-biao[u];c1[v]=c[i]-e;
      d1[c[i]-e]=v;b[v]=mark[i];++biao[u];
    }
    for (int i=N+1;i<=N+e;i++) {
      p=d[i-e];
      u=over[p];v=u-biao[u];c1[v]=c[p];d1[c[p]]=v;b[v]=0;++biao[u];
    }
    t[0]=0;
    for (int i=1;i<=N;i++) {
      if ((mark[i]==mark[i-1])&&(b[i]==b[i-1])) t[i]=t[i-1]; else t[i]=t[i-1]+1;
      c[i]=c1[i],d[i]=d1[i];
    }
    for (int i=1;i<=N;i++) mark[i]=t[i];
    if (mark[N]==N) break;
    e=e*2;
  }
  //the i-th ranked suffix begins with index c[i]
  for (int i=1;i<=N;i++) printf("%d\n",c[i]-1);

  return 0;
}
