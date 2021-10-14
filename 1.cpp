#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<stdlib.h>
#include<assert.h>
#include<malloc.h>
#include<sys/time.h>
#define For(i,j,n) for(int i=j;i<n;++i)
using namespace std;
int flag=0,Na=0,Nb=0,N=0,Type=0;
int pos(int x,int y){return y+N*x;}

template<class T>
T get_num(FILE* fd,T a)
{
    char t[1];
    T sum=0;a=0;
    fread(t,1,1,fd);
    while(t[0]<'0'||t[0]>'9')fread(t,1,1,fd);
    //sum=t[0]-'0';
    while(t[0]>='0'&&t[0]<='9')sum=sum*10+t[0]-'0',fread(t,1,1,fd);
    
    //cout<<sum<<endl;
    return sum;
}

template<class T>
void Read(T*a,FILE *fa)
{ 
   T k;k=0;
   For(i,0,N)For(j,0,N)a[pos(i,j)]=get_num(fa,k);
}

char buf[20];
int L=0;
template<class T>
void Writebuf(T x)
{
    L=0;
    //cout<<x<<endl;
    if(x==0){buf[0]='0';buf[1]='\0';L=1;return;}
    while(x>0)
    {
        buf[L]=x%10+'0';x/=10;++L;
    }
    //cout<<L<<endl;
    //cout<<buf<<endl;
    For(i,0,L/2){char t=buf[i];buf[i]=buf[L-1-i];buf[L-1-i]=t;}
    buf[L]=' ';++L;
    buf[L]='\0';
    //cout<<buf<<endl;
}
template<class T>
void Printing(T*c,FILE*fc)
{
    //long long z=0,size=sizeof(long long);
    For(i,0,N)
    {
        //For(j,0,N)z=c[pos(i,j)],fprintf(fc,"%lld ",z);
        //fprintf(fc,"\n");
        For(j,0,N)
        {
            //z=c[pos(i,j)];
            Writebuf(c[pos(i,j)]);
            //fwrite(z,size,1,fc);
            fwrite(buf,1,L,fc);
        }
        fwrite("\n",1,1,fc);
    }
}

template<class T>
void ijk(T*a,T*b,T*c)
{
    For(i,0,N)For(j,0,N)
    {
        T sum=0;
        For(k,0,N)sum+=a[pos(i,k)]*b[pos(k,j)];
        c[pos(i,j)]=sum;
    }
}

template<class T>
void jik(T*a,T*b,T*c)
{
    For(j,0,N)For(i,0,N)
    {
        T sum=0;
        For(k,0,N)sum+=a[pos(i,k)]*b[pos(k,j)];
        c[pos(i,j)]=sum;
    }
}

template<class T>
void ikj(T*a,T*b,T*c)
{
    For(i,0,N)For(k,0,N)
    {
        T r=a[pos(i,k)];
        For(j,0,N)c[pos(i,j)]+=r*b[pos(k,j)];
    }
}

template<class T>
void kij(T*a,T*b,T*c)
{
    For(k,0,N)For(i,0,N)
    {
        T r=a[pos(i,k)];
        For(j,0,N)c[pos(i,j)]+=r*b[pos(k,j)];
    }
}

template<class T>
void jki(T*a,T*b,T*c)
{
    For(j,0,N)For(k,0,N)
    {
        T r=b[pos(k,j)];
        For(i,0,N)c[pos(i,j)]+=r*a[pos(i,k)];
    }
}

template<class T>
void kji(T*a,T*b,T*c)
{
    For(k,0,N)For(j,0,N)
    {
        T r=b[pos(k,j)];
        For(i,0,N)c[pos(i,j)]+=r*a[pos(i,k)];
    }
}

template<class T>
void work(T*a,T*b,T*c,FILE *fc)
{
    struct timeval start;
    struct timeval end;
    gettimeofday(&start,NULL);
    
    switch(Type)
    {
        case 0:
           ijk(a,b,c);
           break;
        case 1:
           ikj(a,b,c);
           break;
        case 2:
           kij(a,b,c);
           break;
        case 3:
           jik(a,b,c);
           break;
        case 4:
           jki(a,b,c);
           break;
        case 5:
           kji(a,b,c);
           break;
        default:
           cout<<"Type error."<<endl;
    }

    Printing(c,fc);
    gettimeofday(&end,NULL);
    long long ss=start.tv_sec*1000000+start.tv_usec;
    long long ee=end.tv_sec*1000000+end.tv_usec;
    double ans_T=ee-ss;
    ans_T/=1000000.0;
    printf("total time: %.10lf\n",ans_T);
}

int main(int argc,char**argv)
{
    //char type_a[10],type_b[10];
    Type=atoi(argv[4]);
    FILE *fa=fopen(argv[1],"r");
    if(fa==NULL){printf("file a error\n");return 1;}
    FILE *fb=fopen(argv[2],"r");
    if(fb==NULL){printf("file b error\n");return 1;}
    FILE *fc=fopen(argv[3],"w");
    if(fc==NULL){printf("file c error\n");return 1;}
    char type_a[1],type_b[1];
    fread(type_a,1,1,fa);//fflush(fa);
    //fread(t,1,1,fa);
    fread(type_b,1,1,fb);
    //fread(t,1,1,fa);
    Na=get_num(fa,Na);
    Nb=get_num(fb,Nb);
    //cout<<Na<<endl;
    //cout<<Nb<<endl;
    //fscanf(fa,"%s",type_a);
    //fscanf(fa,"%d",&Na);
    //fscanf(fb,"%s",type_b);
    //fscanf(fb,"%d",&Nb);
    
    N=max(Na,Nb);
    if(type_a[0]=='l'&&type_b[0]=='l')flag=1;

    cout<<"N="<<N<<endl;
    cout<<"flag="<<flag<<endl;
    cout<<"Type="<<Type<<endl;

    if(flag)
    {
        long long*a,*b,*c;
        a=(long long*)malloc(N*N*sizeof(long long));
        b=(long long*)malloc(N*N*sizeof(long long));
        c=(long long*)malloc(N*N*sizeof(long long));
        For(i,0,N)For(j,0,N)c[pos(i,j)]=0;
        Read(a,fa);Read(b,fb);

        cout<<"a="<<endl;
        For(i,0,N){For(j,0,N)cout<<a[pos(i,j)]<<" ";cout<<endl;}
        cout<<"b="<<endl;
        For(i,0,N){For(j,0,N)cout<<b[pos(i,j)]<<" ";cout<<endl;}

        work(a,b,c,fc);
        
        cout<<"c="<<endl;
        For(i,0,N){For(j,0,N)cout<<c[pos(i,j)]<<" ";cout<<endl;}
    
    }
    else
    {
        int*a,*b,*c;
        a=(int*)malloc(N*N*sizeof(int));
        b=(int*)malloc(N*N*sizeof(int));
        c=(int*)malloc(N*N*sizeof(int));
        Read(a,fa);Read(b,fb);

        cout<<"a="<<endl;
        For(i,0,N){For(j,0,N)cout<<a[pos(i,j)]<<" ";cout<<endl;}
        cout<<"b="<<endl;
        For(i,0,N){For(j,0,N)cout<<b[pos(i,j)]<<" ";cout<<endl;}

        work(a,b,c,fc);
        cout<<"c="<<endl;
        For(i,0,N){For(j,0,N)cout<<c[pos(i,j)]<<" ";cout<<endl;}
    }
    //rewind(fc);
    //fseek(fc,0,SEEK_SET);
    fflush(fc);
    fclose(fa);fclose(fb);fclose(fc);
    return 0;
}
