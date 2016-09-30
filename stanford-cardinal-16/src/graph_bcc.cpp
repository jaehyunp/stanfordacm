//Biconnected Components(Points)
const int maxn=100005;
int N,tot,top,o;vector<int> f[maxn],two[maxn];
int dfn[maxn],low[maxn],father[maxn],nei[maxn],stack[maxn],which[maxn],pia[maxn];
void search(int s) {
  int i,c;++o;dfn[s]=low[s]=o;++top;stack[top]=s;
  for (int i=0;i<f[s].size();i++){
    c=f[s][i];if (father[s]==c) continue;
    if (dfn[c]==0){
      father[c]=s;search(c);low[s]=min(low[s],low[c]);
      if (low[c]>=dfn[s]){
        ++tot;
        while (true) {
          two[tot].p_b(stack[top]);which[stack[top]]=tot;
          low[stack[top]]=maxlongint;--top;
          if ((stack[top+1]==s)||(father[stack[top+1]]==s)) break;
        }
        if (stack[top+1]!=s){two[tot].p_b(s);pia[tot]=s;}
      }
    }
    else low[s]=min(low[s],dfn[c]);
  }
}
// same(a,b) returns the index of the common component of a and b
// (-1 if in different components)
int same(int a,int b) {
  if (which[a]==which[b]) return which[a];
  if (pia[which[a]]==b) return which[a];
  if (pia[which[b]]==a) return which[b];
  return -1;
}
int main() {
  tot=0;top=0;o=0;
  memset(dfn,0,sizeof(dfn));memset(low,0,sizeof(low));memset(nei,0,sizeof(nei));
  memset(father,0,sizeof(father));memset(which,0,sizeof(which));
  for (int i=1;i<=N;i++) two[i].clear();
  for (int i=1;i<=N;i++) if (dfn[i]==0) search(i);
  for (int i=1;i<=N;i++)
    for (int j=0;j<f[i].size();j++)
      if ((i<f[i][j])&&(same(i,f[i][j])!=-1))
        ++nei[same(i,f[i][j])];
  // vector two[i] contains all the points(except the cut-vertex) in the i-th component
  // array which[i] indicate which component node i belongs to(doesn't work if i is cut-vertex)
  // array pia[i] contains the cut-vertex related to the i-th component
  // notice that a cut-vertex may belong to more than one component
  // array nei[i] contains the number of edges within a component
}
