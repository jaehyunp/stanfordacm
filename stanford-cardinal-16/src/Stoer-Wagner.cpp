    // a is a N*N matrix storing the graph we use; a[i][j]=a[j][i]
    memset(use,0,sizeof(use));
    ans=maxlongint;
    for (int i=1;i<N;i++)
    {
        memcpy(visit,use,505*sizeof(int));
        memset(reach,0,sizeof(reach));
        memset(last,0,sizeof(last));
        t=0;
        for (int j=1;j<=N;j++)
            if (use[j]==0) {t=j;break;}
        for (int j=1;j<=N;j++)
            if (use[j]==0) reach[j]=a[t][j],last[j]=t;
        visit[t]=1;
        for (int j=1;j<=N-i;j++)
        {
            maxc=maxk=0;
            for (int k=1;k<=N;k++)
                if ((visit[k]==0)&&(reach[k]>maxc)) maxc=reach[k],maxk=k;
            c2=maxk,visit[maxk]=1;
            for (int k=1;k<=N;k++)
                if (visit[k]==0) reach[k]+=a[maxk][k],last[k]=maxk;
        }
        c1=last[c2];
        sum=0;
        for (int j=1;j<=N;j++)
            if (use[j]==0) sum+=a[j][c2];
        ans=min(ans,sum);
        use[c2]=1;
        for (int j=1;j<=N;j++)
            if ((c1!=j)&&(use[j]==0)) {a[j][c1]+=a[j][c2];a[c1][j]=a[j][c1];}
    }

