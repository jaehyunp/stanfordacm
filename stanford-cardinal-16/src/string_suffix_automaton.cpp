//Suffix Automaton
const int C=4;
const int maxn=100005;
struct SAM{int len;SAM *child[C],*back;} *root,*tail,*p,*q,*w,*v;
int N,a[maxn];char st[maxn];
int main() {
  root=new SAM,root->back=0,root->len=0,tail=root;
  for (int i=0;i<C;i++) root->child[i]=0;
  //a[N] is the string begin with array-index 1
  for (int t=1;t<=N;t++){
    p=new SAM,p->len=tail->len+1;
    for (int i=0;i<C;i++) p->child[i]=0;
    tail->child[a[t]]=p,v=tail->back,tail=p;
    while ((v!=0)&&(v->child[a[t]]==0)) v->child[a[t]]=p,v=v->back;
    if (v==0) p->back=root; else{
      if (v->len+1==v->child[a[t]]->len)
        p->back=v->child[a[t]];
      else{
        q=v->child[a[t]],w=new SAM,w->back=q->back;
        for (int i=0;i<C;i++) w->child[i]=q->child[i];
        w->len=v->len+1,p->back=q->back=w;
        while ((v!=0)&&(v->child[a[t]]==q)) v->child[a[t]]=w,v=v->back;
      }
    }
  }
}
