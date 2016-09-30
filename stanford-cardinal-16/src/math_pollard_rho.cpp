const int data[11]={2,3,5,7,11,13,17,61,1231,24251,314159};
const int maxn=1000005;

int ps[maxn];int tt;LL N;

LL gcd(LL a,LL b) {
  if (b==0) return a; else return gcd(b,a%b);
}

LL mul(LL a,LL b,LL p) {
  LL e=0;
  while (b>0) {
    if (b-((b>>1)<<1)==1) e=(e+a)%p;
    b=(b>>1);
    a=(a<<1)%p;
  }
  return e;
}

LL powc(LL a,LL b,LL p) {
  if (b==0) return 1;
  LL d=powc(a,b/2,p);
  d=mul(d,d,p);
  if (b%2==1) d=mul(d,a,p);
  return d;
}

bool prime(LL N) {
  for (int i=0;i<=10;i++) {
    if (N==data[i]) return true;
    if (N%data[i]==0) return false;
  }
  if (N==1) return false;
  LL c=N-1;
  LL g=0;
  while (c%2==0) c/=2,g++;
  for (int i=0;i<=10;i++) {
    LL k=powc(data[i],c,N),k1;
    for (int j=1;j<=g;j++) {
      k1=mul(k,k,N);
      if ((k1==1)&&(k!=1)&&(k!=N-1)) return false;
      k=k1;
    }
    if (k1!=1) return false;
  }
  return true;
}

LL getrand(LL maxp) {
  // on a Unix system this should be changed
  LL w1=((LL)rand())<<45;
  LL w2=((LL)rand())<<30;
  LL w3=((LL)rand())<<15;
  return ((w1+w2+w3+rand())%maxp+maxp)%maxp;
}

LL myabs(LL s) {
  if (s<0) return -s; else return s;
}

LL find(LL N) {
  if (N<=maxn) return ps[N];
  LL x=getrand(N);
  LL y=x;
  int i=1,k=2;
  while (true)
  {
    ++i;
    x=mul(x,x,N)-1;
    if (x==-1) x+=N;
    LL d=gcd(myabs(y-x),N);
    if ((d!=1)&&(d!=N)) return d;
    if (i==k) y=x,k*=2;
  }
}

int main() {
  srand(time(0));
  memset(ps,0,sizeof(ps));
  ps[1]=1;
  for (int i=2;i*i<maxn;i++)
    if (ps[i]==0)
      for (int j=i;j<=(maxn-1)/i;j++)
        if (ps[i*j]==0) ps[i*j]=i;

  return 0;
}
