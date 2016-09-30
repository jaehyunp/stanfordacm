const int maxn=300005;
const int g=3,bigp=479*(1<<21)+1,x=21;
int LA,LB;
int a[maxn],b[maxn],w[maxn];
int C,N,L;
int powc(int a,int b) {
  int d;
  if (b==0) return 1;
  d=powc(a,b/2);
  d=(LL)d*d%bigp;
  if (b%2==1) d=(LL)d*a%bigp;
  return d;
}
inline void FFT(int x[],int K,int v){
  //K is the length of x[]
  //v=0 : DFT,  v=1 : IDFT
  w[0]=1;
  int G=powc(g,(bigp-1)/K);
  for (int i=1;i<=K;i++) w[i]=(LL)w[i-1]*G%bigp;
  for (int i=0,j=0;i<K;i++) {
    if (i>j) swap(x[i],x[j]);
    for (int l=K>>1;(j^=l)<l;l>>=1);
  }
  for (int i=2;i<=K;i<<=1)
    for (int j=0;j<K;j+=i)
      for (int l=0;l<i>>1;l++) {
        int t;
        if (v==0)
          t=(LL)x[j+l+(i>>1)]*w[(K/i)*l]%bigp;
        else
          t=(LL)x[j+l+(i>>1)]*w[K-(K/i)*l]%bigp;
        x[j+l+(i>>1)]=((LL)x[j+l]-t+bigp)%bigp;
        x[j+l]+=t;
        x[j+l]%=bigp;
      }
  if (v==1) {
    int r=powc(N,bigp-2);
    for (int i=0;i<N;i++) a[i]=(LL)a[i]*r%bigp;
  }
}
void calculate() {
  //LA,LB are length of a[] and b[] (include a[0] and b[0])
  N=1,C=LA+LB,L=0;
  while (N<=C) N*=2,++L;
  for (int i=LA;i<N;i++) a[i]=0;
  for (int i=LB;i<N;i++) b[i]=0;
  FFT(a,N,0);FFT(b,N,0);
  for (int i=0;i<N;i++) a[i]=(LL)a[i]*b[i]%bigp;
  FFT(a,N,1);
}
