bool find(int c){
    vx[c]=1;
    for (int i=N+1;i<=S;i++)
        if (vy[i]==0)
            if (dx[c]+dy[i]==a[c][i]){
                vy[i]=1;
                if ((last[i]==0)||(find(last[i]))){
                    last[i]=c;
                    return true;
                }
            }
            else{
                if (dx[c]+dy[i]-a[c][i]<slack[i])
                    slack[i]=dx[c]+dy[i]-a[c][i];
            }
    return false;
}
int main(){
    // the matrix a[] stores the graph
    // S is the total number of vertices
    // N is the total number of vertices on the left part
    for (int i=1;i<=N;i++) fill(a[i],a[i]+S+1,-maxlongint);
    // construct matrix a here

    memset(dx,0,sizeof(dx));
    memset(dy,0,sizeof(dy));
    for (int i=1;i<=N;i++){
        int maxc=-maxlongint;
        for (int j=1;j<=S;j++)
            maxc=max(maxc,a[i][j]);
        dx[i]=maxc;
    }
    memset(last,0,sizeof(last));
    for (int k=1;k<=N;k++){
        fill(slack,slack+S+1,maxlongint);
        while (true){
            memset(vx,0,sizeof(vx));
            memset(vy,0,sizeof(vy));
            if (find(k)) break;
            int d=maxlongint;
            for (int i=N+1;i<=S;i++)
                if ((vy[i]==0)&&(slack[i]<d)) d=slack[i];
            for (int i=1;i<=S;i++){
                if (vx[i]==1) dx[i]-=d;
                if (vy[i]==1) dy[i]+=d;
            }
            for (int i=N+1;i<=S;i++)
                if (vy[i]==0) slack[i]-=d;
        }
    }
    // for i in [N+1,S], (last[i],i) is a matching edge
}
