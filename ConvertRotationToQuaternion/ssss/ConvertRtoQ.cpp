#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
using namespace std;


#define m 1400  //行数
#define n 16  //列数

void main()
{
	double a[m][n];
	double c[1400][4];
	double e[1400][3];

	ifstream ifile("1.txt");   //打开文件
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			ifile>>a[i][j];   //将txt文件里数据读到数组a[][]
		}
	}

	for (int hh=0;hh<1400;hh++)
	{
		double tr, s;

		// 计算矩阵轨迹
		tr =1.0 + a[hh][0] + a[hh][5] + a[hh][10];
		// 检查矩阵轨迹是正还是负
		if(tr>0.0)
		{
			s = sqrt(tr)*2.0;
			c[hh][0] = (a[hh][9] - a[hh][6]) / s;   //x
			c[hh][1] = (a[hh][2] - a[hh][8]) / s;   //y
			c[hh][2] = (a[hh][4] - a[hh][1]) / s;   //z
			c[hh][3] = s * 0.25;                    //w
		}
		else if((a[hh][0]>a[hh][5])&&(a[hh][0]>a[hh][10]))
		{
			s =sqrt( 1.0f + a[hh][0] - a[hh][5] - a[hh][10] ) * 2.0;
			c[hh][0] = s * 0.25;                    //x		
			c[hh][1] = (a[hh][4] + a[hh][1]) / s;   //y
			c[hh][2] = (a[hh][2] + a[hh][8]) / s;   //z
			c[hh][3] = (a[hh][9] - a[hh][6]) / s;   //w
		}
		else if(a[hh][5]>a[hh][10])
		{
			s =sqrt( 1.0f + a[hh][5] - a[hh][0] - a[hh][10] ) * 2.0;
			c[hh][0] = (a[hh][4] + a[hh][1]) / s;   //x
			c[hh][1] = s * 0.25;                    //y		
			c[hh][2] = (a[hh][9] + a[hh][6]) / s;   //z
			c[hh][3] = (a[hh][2] - a[hh][8]) / s;   //w
		}
		else
		{
			s =sqrt( 1.0f + a[hh][10] - a[hh][0] - a[hh][5] ) * 2.0;
			c[hh][0] = (a[hh][2] + a[hh][8]) / s;   //x
			c[hh][1] = (a[hh][9] + a[hh][6]) / s;   //y
			c[hh][2] = s * 0.25;                    //z	
			c[hh][3] = (a[hh][4] - a[hh][1]) / s;   //w
		}

		const double r2d = 57.29577951308;
		double x = c[hh][0];
		double y = c[hh][1];
		double z = c[hh][2];
		double w = c[hh][3];
		double r11 = 2 * (x*y + w*z);
		double r12 = w*w + x*x - y*y - z*z;
		double r21 = -2 * (x*z - w*y);
		double r31 = 2 * (y*z + w*x);
		double r32 = w*w - x*x - y*y + z*z;
		e[hh][2] = (double)atan2(r11, r12) * r2d;
		e[hh][1] = (double)asin(r21) * r2d;
		e[hh][0] = (double)atan2(r31, r32) * r2d;
	}

  
   	ofstream out("outeulera6.txt");//打开文件。
    for(int i = 0; i < 1400; i ++)
    {
        for(int j = 0; j < 3; j ++)
        {
            out<<e[i][j]<<' ';//将每个元素写入文件，以空格分隔。
        }
        out << endl;//每行输出结束，添加换行。
    }
	ifile.close();
} 