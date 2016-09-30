void dfs(int s)
{
    ++o,indx[s]=mlik[s]=o;
    ++top,stk[top]=s;
    for (int i=0;i<F[s].size();i++)
    {
        if (indx[F[s][i]]==0) dfs(F[s][i]);
        mlik[s]=min(mlik[s],mlik[F[s][i]]);
    }
    if (indx[s]==mlik[s])
    {
        ++tot;
        while (stk[top]!=s)
        {
            where[stk[top]]=tot;
            mlik[stk[top]]=maxlongint;
            --top;
        }
        where[s]=tot;
        mlik[s]=maxlongint;
        --top;
    }
}

	o=0;
	tot=0;
	top=0;
	memset(indx,0,sizeof(indx));
	memset(mlik,0,sizeof(mlik));
	memset(where,0,sizeof(where));
	for (int e=1;e<=52;e++)
		if (indx[e]==0) dfs(e);
