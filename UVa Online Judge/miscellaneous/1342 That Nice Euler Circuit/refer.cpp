#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const double eps =1e-10;
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x<0?-1:1;
}

struct Point
{
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}
    bool operator<(const Point &b)const
    {
        return x<b.x||(x==b.x && y<b.y);
    }
    bool operator==(const Point &b)const
    {
        return dcmp(x-b.x)==0 && dcmp(y-b.y)==0;
    }
};

typedef Point Vector;
Vector operator +(Vector A,Vector B)
{
    return Vector(A.x+B.x, A.y+B.y);
}
Vector operator -(Point A,Point B)
{
    return Vector(A.x-B.x, A.y-B.y);
}
Vector operator *(Vector A,double p)
{
    return Vector(A.x*p, A.y*p);
}
Vector operator /(Vector A,double p)
{
    return Vector(A.x/p, A.y/p);
}
double Dot(Vector A,Vector B)
{
    return A.x*B.x+A.y*B.y;
}
double Length(Vector A)
{
    return sqrt(Dot(A,A));
}
double Angle(Vector A,Vector B)
{
    return acos(Dot(A,B)/Length(A)/Length(B));
}
double Cross(Vector A,Vector B)
{
    return A.x*B.y-A.y*B.x;
}
bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2)//判断线段规范相交
{
    double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1);
    double c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}
bool OnSegment(Point P,Point a1,Point a2)//判断点P是否在选段a1a2内
{
    return dcmp( Cross(a1-P,a2-P) )==0 && dcmp(Dot(a1-P,a2-P))<0;
}
Point GetLineIntersection(Point P,Vector v,Point Q,Vector w)//求直线交点
{
    Vector u=P-Q;
    double t=Cross(w,u)/Cross(v,w);
    return P+v*t;
}
/***以上为刘汝佳模板***/

const int maxn=90000+5;
Point p[maxn];//原始点
Point v[maxn];//所有点

int main()
{
    int n;
    int kase=0;
    while(scanf("%d",&n)==1 && n)
    {
        int point_num=n-1;//点数目
        int edge_num=n-1;//边数目
        for(int i=0;i<n;++i)
        {
            scanf("%lf%lf",&p[i].x,&p[i].y);
            v[i]=p[i];
        }

        --n;
        //求线段两两相交的交点
        for(int i=0;i<n;++i)
        for(int j=i+1;j<n;++j)
        {
            Point &a1=p[i];
            Point &a2=p[(i+1)%n];
            Point &b1=p[j];
            Point &b2=p[(j+1)%n];
            if(SegmentProperIntersection(a1,a2,b1,b2))
            {
                v[point_num++]=GetLineIntersection(a1,a2-a1,b1,b2-b1);
            }
        }

        sort(v,v+point_num);
        point_num = unique(v,v+point_num)-v;
        for(int i=0;i<n;++i)//原始线段
        for(int j=0;j<point_num;++j)//遍历所有点
        {
            if(OnSegment(v[j],p[i],p[(i+1)%n])) ++edge_num;//若该点在该线段内部
        }
        printf("Case %d: There are %d pieces.\n",++kase,edge_num+2-point_num);
    }
    return 0;
}
