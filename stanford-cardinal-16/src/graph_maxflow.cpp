const int maxn=100005;
struct ljb {
  int dest,flow;
  ljb *next,*other;
} *head[maxn],*tail[maxn],*vi[maxn],*back[maxn],*p,*q;
int S;
int dist[maxn],vh[maxn],flow[maxn];
void mpush(int x,int y,int w) {
  ljb *p,*q;
  p=new ljb;
  p->dest=y,p->flow=w;
  p->next=0;
  tail[x]->next=p,tail[x]=p;
  q=new ljb;
  q->dest=x,q->flow=0;
  q->next=0;
  tail[y]->next=q,tail[y]=q;
  p->other=q,q->other=p;
}
int getSAP(int S) {
  memset(dist,0,sizeof(dist));
  for (int i=0; i<=S; i++) {
    vi[i]=head[i]->next;
  }
  memset(vh,0,sizeof(vh));
  memset(flow,0,sizeof(flow));
  int arg=maxlongint,e=0,uu,minc;
  int ttflow=0;
  bool flag;
  ljb *p,*mink;
  vh[0]=S+1;
  while (dist[0]<=S) {
    flow[e]=arg;
    flag=false;
    p=vi[e];
    while (p!=0) {
      if ((p->flow>0)&&(dist[p->dest]+1==dist[e])) {
        flag=true;
        back[p->dest]=p;
        arg=min(arg,p->flow);
        vi[e]=p;
        e=p->dest;
        if (e==S) {
          ttflow+=arg;
          uu=S;
          while (uu!=0) {
            back[uu]->flow-=arg;
            back[uu]->other->flow+=arg;
            uu=back[uu]->other->dest;
          }
          e=0;
          arg=maxlongint;
        }
        break;
      }
      p=p->next;
    }
    if (flag==false) {
      p=head[e]->next;
      minc=S,mink=0;
      while (p!=0) {
        if ((p->flow>0)&&(dist[p->dest]<minc))
          minc=dist[p->dest],mink=p;
        p=p->next;
      }
      vi[e]=mink;
      --vh[dist[e]];
      if (vh[dist[e]]==0) break;
      dist[e]=minc+1;
      ++vh[dist[e]];
      if (e>0) {
        e=back[e]->other->dest;
        arg=flow[e];
      }
    }
  }
  return ttflow;
}
int main() {
  //S+1 is the total number of nodes in Maxflow graph
  //0 is source and S is sink
  for (int i=0; i<=S; i++) {
    p=new ljb;
    p->dest=0,p->flow=0;
    p->next=0,p->other=0;
    head[i]=p,tail[i]=p;
  }
  return 0;
}

