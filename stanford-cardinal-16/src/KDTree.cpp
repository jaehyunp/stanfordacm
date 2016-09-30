const int maxn=200005;

struct kdtree
{
	int xl,xr,yl,yr,zl,zr,max,flag; // flag=0:x axis  1:y 2:z
} tree[5000005];

int N,M,lastans,xq,yq;
int a[maxn],pre[maxn],nxt[maxn];
int x[maxn],y[maxn],z[maxn],wei[maxn];
int xc[maxn],yc[maxn],zc[maxn],wc[maxn],hash[maxn],biao[maxn];

bool cmp1(int a,int b)
{
	return x[a]<x[b];
}

bool cmp2(int a,int b)
{
	return y[a]<y[b];
}

bool cmp3(int a,int b)
{
	return z[a]<z[b];
}

void makekdtree(int node,int l,int r,int flag)
{
	if (l>r)
	{
		tree[node].max=-maxlongint;
		return;
	}
	int xl=maxlongint,xr=-maxlongint;
	int yl=maxlongint,yr=-maxlongint;
	int zl=maxlongint,zr=-maxlongint,maxc=-maxlongint;
	for (int i=l;i<=r;i++)
		xl=min(xl,x[i]),xr=max(xr,x[i]),
		yl=min(yl,y[i]),yr=max(yr,y[i]),
		zl=min(zl,z[i]),zr=max(zr,z[i]),
		maxc=max(maxc,wei[i]),
		xc[i]=x[i],yc[i]=y[i],zc[i]=z[i],wc[i]=wei[i],biao[i]=i;
	tree[node].flag=flag;
	tree[node].xl=xl,tree[node].xr=xr,tree[node].yl=yl;
	tree[node].yr=yr,tree[node].zl=zl,tree[node].zr=zr;
	tree[node].max=maxc;
	if (l==r) return;
	if (flag==0) sort(biao+l,biao+r+1,cmp1);
	if (flag==1) sort(biao+l,biao+r+1,cmp2);
	if (flag==2) sort(biao+l,biao+r+1,cmp3);
	for (int i=l;i<=r;i++)
		x[i]=xc[biao[i]],y[i]=yc[biao[i]],
		z[i]=zc[biao[i]],wei[i]=wc[biao[i]];
	makekdtree(node*2,l,(l+r)/2,(flag+1)%3);
	makekdtree(node*2+1,(l+r)/2+1,r,(flag+1)%3);
}

int getmax(int node,int xl,int xr,int yl,int yr,int zl,int zr)
{	
	xl=max(xl,tree[node].xl);
	xr=min(xr,tree[node].xr);
	yl=max(yl,tree[node].yl);
	yr=min(yr,tree[node].yr);
	zl=max(zl,tree[node].zl);
	zr=min(zr,tree[node].zr);
	if (tree[node].max==-maxlongint) return 0;
	if ((xr<tree[node].xl)||(xl>tree[node].xr)) return 0;
	if ((yr<tree[node].yl)||(yl>tree[node].yr)) return 0;
	if ((zr<tree[node].zl)||(zl>tree[node].zr)) return 0;
	if ((tree[node].xl==xl)&&(tree[node].xr==xr)&&
		(tree[node].yl==yl)&&(tree[node].yr==yr)&&
		(tree[node].zl==zl)&&(tree[node].zr==zr)) 
	return tree[node].max; 
	else
	return max(getmax(node*2,xl,xr,yl,yr,zl,zr),
				getmax(node*2+1,xl,xr,yl,yr,zl,zr));
}

int main()
{
	// N 3D-rect with weights
	// find the maximum weight containing the given 3D-point
	return 0;
}
