const int maxn=3000005;
// maxn is the number of vertex generated during the process; it's about O(NlogN)

// size calculation for a given root
void dfs(int s,int fa,int leb) {
  size[s]=1;
  for (int i=0;i<f[s].size();i++)
    if ((f[s][i]!=fa)&&(label[f[s][i]]==leb)) {
      dfs(f[s][i],s,leb);
      size[s]+=size[f[s][i]];
    }
}

// find the central of the tree; tt is the total number of vertex of tree
void dfs2(int s,int fa,int tt,int leb) {
  int maxc=0;
  for (int i=0;i<f[s].size();i++)
    if ((f[s][i]!=fa)&&(label[f[s][i]]==leb)) {
      dfs2(f[s][i],s,tt,leb);
      maxc=max(maxc,size[f[s][i]]);
    }
  maxc=max(maxc,tt-size[s]);
  if (maxc<mingl) mingl=maxc,center=s;
}

// we label the nodes to avoid deleting edges when split a tree into two
void pushlabel(int s,int fa,int lold,int lnew,int avoid) {
  label[s]=lnew;
  for (int i=0;i<f[s].size();i++) {
    int cs=f[s][i];
    if ((cs!=fa)&&(cs!=avoid)&&(label[cs]==lold)) pushlabel(cs,s,lold,lnew,avoid);
  }
}

void divide(int root) {
  // find the central of the tree rooted 'root'
  dfs(root,0,root);
  if (size[root]<=2) return;

  center=0,mingl=maxlongint;
  dfs2(root,0,size[root],root);
  dfs(center,0,root);

  vector<PII> tmp;
  tmp.clear();
  for (int i=0;i<f[center].size();i++)
    if (label[f[center][i]]==root) tmp.p_b(m_p(size[f[center][i]],f[center][i]));
  sort(tmp.begin(),tmp.end(),cmp);

  vector<PII> tmp1,tmp2;
  tmp1.clear();
  tmp2.clear();
  int ss=0;
  for (int i=0;i<tmp.size();i++) {
    if (ss+tmp[i].w1>size[center]/2) {
      for (int j=i;j<tmp.size();j++) tmp2.p_b(tmp[j]);
      break;
    }
    ss+=tmp[i].w1;
    tmp1.p_b(tmp[i]);
  }

  ++o;
  ori[o]=ori[center];
  // ori[i] represents the original index of vertex i (which vertex it represents)
  for (int i=0;i<tmp1.size();i++) {
    f[o].p_b(tmp1[i].w2);
    f[tmp1[i].w2].p_b(o);
  }
  pushlabel(o,0,root,o,center);

  ++o;
  ori[o]=ori[center];
  for (int i=0;i<tmp2.size();i++) {
    f[o].p_b(tmp2[i].w2);
    f[tmp2[i].w2].p_b(o);
  }
  pushlabel(o,0,root,o,center);

  // Do calculation passing center Here

  int bakup=o;
  divide(bakup-1);
  divide(bakup);
}

int main() {
  scanf("%d",&N);
  // vertex 1 is the root by default
  for (int i=1;i<=N;i++) ori[i]=i,label[i]=1;
  for (int i=1;i<N;i++) {
    scanf("%d %d",&xc,&yc);
    f[xc].p_b(yc);
    f[yc].p_b(xc);
  }
  o=N;
  divide(1);

  return 0;
}
