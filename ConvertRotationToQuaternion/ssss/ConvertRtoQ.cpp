#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
using namespace std;


#define m 1461  //行数

void main()
{
	double R[m][16];    //定义数组，用来存放旋转矩阵 Rotation Matrix
	double Q[m][4];     //定义数组，用来存放四元数   Quaternion
	double E[m][3];     //定义数组，用来存放欧拉角   Euler Angles

	double T[m][16] ={0};
	//double D[m][16] ={0};

	ifstream ifile("1.txt");   //打开文件
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<16;j++)
		{
			ifile>>R[i][j];   //将txt文件里数据读到数组a[][]
		}
	}

	for (int hh=0;hh<m;hh++)
	{
		double tr, s;

		//将旋转矩阵转化为四元数
		tr =1.0 + R[hh][0] + R[hh][5] + R[hh][10];   // 计算矩阵的迹
		if(tr>0.0)
		{
			s = sqrt(tr)*2.0;
			Q[hh][0] = (R[hh][9] - R[hh][6]) / s;   //x
			Q[hh][1] = (R[hh][2] - R[hh][8]) / s;   //y
			Q[hh][2] = (R[hh][4] - R[hh][1]) / s;   //z
			Q[hh][3] = s * 0.25;                    //w
		}
		else if((R[hh][0]>R[hh][5])&&(R[hh][0]>R[hh][10]))
		{
			s =sqrt( 1.0 + R[hh][0] - R[hh][5] - R[hh][10] ) * 2.0;
			Q[hh][0] = s * 0.25;                    //x		
			Q[hh][1] = (R[hh][4] + R[hh][1]) / s;   //y
			Q[hh][2] = (R[hh][2] + R[hh][8]) / s;   //z
			Q[hh][3] = (R[hh][9] - R[hh][6]) / s;   //w
		}
		else if(R[hh][5]>R[hh][10])
		{
			s =sqrt( 1.0 + R[hh][5] - R[hh][0] - R[hh][10] ) * 2.0;
			Q[hh][0] = (R[hh][4] + R[hh][1]) / s;   //x
			Q[hh][1] = s * 0.25;                    //y		
			Q[hh][2] = (R[hh][9] + R[hh][6]) / s;   //z
			Q[hh][3] = (R[hh][2] - R[hh][8]) / s;   //w
		}
		else
		{
			s =sqrt( 1.0 + R[hh][10] - R[hh][0] - R[hh][5] ) * 2.0;
			Q[hh][0] = (R[hh][2] + R[hh][8]) / s;   //x
			Q[hh][1] = (R[hh][9] + R[hh][6]) / s;   //y
			Q[hh][2] = s * 0.25;                    //z	
			Q[hh][3] = (R[hh][4] - R[hh][1]) / s;   //w
		}

		//将四元数转化为欧拉角
		const double r2d = 57.29577951308;
		double x = Q[hh][0];
		double y = Q[hh][1];
		double z = Q[hh][2];
		double w = Q[hh][3];
		double r11 = 2 * (x*y + w*z);
		double r12 = w*w + x*x - y*y - z*z;
		double r21 = 2 * (w*y - x*z);
		double r31 = 2 * (y*z + w*x);
		double r32 = w*w - x*x - y*y + z*z;
				
		E[hh][0] = (double)atan2(r31, r32) * r2d;   //Yaw
		E[hh][1] = (double)asin(r21) * r2d;         //Pitch
		E[hh][2] = (double)atan2(r11, r12) * r2d;   //Roll

		//将四元数转化为旋转矩阵
		//T[hh][0]= (1-2*(y*y+z*z));
		//T[hh][1]= 2 * (x*y - w*z);
		//T[hh][2]= 2 * (x*z + w*y);
		//T[hh][4]= 2 * (x*y + w*z);
		//T[hh][5]= (1-2*(x*x+z*z));
		//T[hh][6]= 2 * (z*y - w*x);
		//T[hh][8]= 2 * (x*z - w*y);
		//T[hh][9]= 2 * (z*y + w*x);
		//T[hh][10]=(1-2*(x*x+y*y));
	}

  
   	ofstream out("outeulera6.txt");//打开文件。
    for(int i = 0; i < m ; i ++)
    {
        for(int j = 0; j < 3; j ++)
        {
            out<<E[i][j]<<' ';//将每个元素写入文件，以空格分隔。
        }
        out << endl;//每行输出结束，添加换行。
    }
	ifile.close();
} 