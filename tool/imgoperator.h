#ifndef IMGOPERATOR_H
#define IMGOPERATOR_H
#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDebug>
using namespace std;
using namespace cv;
#define RGB888_RED      0x00ff0000
#define RGB888_GREEN    0x0000ff00
#define RGB888_BLUE     0x000000ff

#define RGB565_RED      0xf800
#define RGB565_GREEN    0x07e0
#define RGB565_BLUE     0x001f

template <typename T1,typename T2>
//unsigned char unsigned short
class Imgoperator
{
public:
    enum Data_type{
      CHAR_TYPE,
      SHORT_TYPE
    };
    Imgoperator();
    ~Imgoperator();
    Imgoperator(const Imgoperator& p) = delete;
    Imgoperator& operator=(const Imgoperator& p) = delete ;
    void test();
    //T1 data
    void readfile(T1* data,string& path,int datalen);//read data from file
    void Setdata(string& path,int datalen);//set data from file
    void Setfilepath(QString str);//set path
    QString Getfilepath() const;
    T1* Getdata() const;//get data
    //T2 data
    T2* Getdstdata() const;//get dst data
    void Setdstdata(int datalen);//set T2 data
    bool Savedstdata(string path,int len);
    //YUV element to RGB
    int YUV2R(int Y,int U,int V)
    {
        int R = Y + 1.402*(V - 128);
        if(R < 0)
            return 0;
        else if(R > 255)
            return 255;
        else
            return R;
    }
    int YUV2G(int Y,int U,int V)
    {
        int G = Y - 0.34414*(U - 128) - 0.71414*(V - 128);
        if(G < 0)
            return 0;
        else if(G > 255)
            return 255;
        else
            return G;
    }
    int YUV2B(int Y,int U,int V)
    {
        int B = Y + 1.779*(U - 128);
        if(B < 0)
            return 0;
        else if(B > 255)
            return 255;
        else
            return B;
    }

    void showyuv420(unsigned char* yuv420,int Height,int Width);//show yuv420 format img
    void showyuv422(unsigned char* yuv422,int Height,int Width);//show yuv422 format img
    //yuvI420 to other format
    void yuvI4202yuv422p(unsigned char* yuv420,unsigned char* yuv422,int Height,int Width);//change yuvI420 to yuv422p
    void yuvI4202yuv422sp(unsigned char* yuvI420,unsigned char* yuv422sp,int Height,int Width);//change yuvI420 to yuv422sp
    void yuv422p2yuv422sp(unsigned char* yuv422p,unsigned char* yuv422sp,int Height,int Width);//change yuv422p to yuv422sp
    void yuvI4202nv12(unsigned char* yuvI420,unsigned char* nv12,int Height,int Width);//change yuvI420 to nv12
    void yuvI4202rgb565(unsigned char* yuvI420,unsigned short* rgb565,int Height,int Width);//change yuvI420 to rgb565
    void yuvI4202rgb888(unsigned char* yuvI420,unsigned char* rgb888,int Height,int Width);//change yuvI420 to rgb888
    void yuvI4202RGB32(unsigned char* yuvI420,unsigned char* rgb32,int Height,int Width);//change yuvI420 to rgb8888

    //yuv422sp to other format
    void yuv422sp2yuvI420(unsigned char* yuv422sp,unsigned char* yuvI420,int Height,int Width);//chage yuv422sp to yuvI420
    void yuv422sp2nv12(unsigned char* yuv422sp,unsigned char* nv12,int Height,int Width);//change yuv422sp to nv12
    void yuv422sp2rgb565(unsigned char* yuv422sp,unsigned short* rgb565,int Height,int Width);//change yuv422sp to rgb565
    void yuv422sp2rgb24(unsigned char* yuv422sp,unsigned char* rgb24,int Height,int Width);//change yuv422sp to rgb888
    void yuv422sp2rgb32(unsigned char* yuv422sp,unsigned char* rgba32,int Height,int Width);//change yuv422sp to rgba8888

    //nv12 to other format
    void NV122RGB(unsigned char* nv12,unsigned char* rgb,int Height,int Width);//change nv12 to rgb
    void NV122RGBA(unsigned char* nv12,unsigned char* rgba,int Height,int Width);//change nv12 to rgba
    void NV122yuvI420(unsigned char* nv12,unsigned char* yuvI420,int Height,int Width);//change nv12 to yuvI420
    void NV1222yuv422sp(unsigned char* nv12,unsigned char* yuv422sp,int Height,int Width);//change nv12 to yuv422sp
    void NV122RGB565(unsigned char* nv12,unsigned short* rgb565,int Height,int Width);//change nv12 to rgb565

    //rgb565 to other format
    void rgb5652yuvI420(unsigned short* rgb565,unsigned char* yuvI420,int Height,int Width);//change rgb565 to yuvI420
    void rgb5652rgb888(unsigned short* rgb565,unsigned char* rgb888,int Height,int Width);//change rgb565 to rgb888
    void rgb5652rgba(unsigned short* rgb565data,unsigned char* rgba,int Height,int Width);//change rgb565 to rgb8888
    void rgb5652yuv422sp(unsigned short* rgb565,unsigned char* yuv422sp,int Height,int Width);//change rgb565 to yuv422sp
    void rgb5652nv12(unsigned short* rgb565,unsigned char* nv12,int Height,int Width);//change rgb565 to nv12

    //rgb to other format
    void rgb2rgb565(unsigned char* rgb,unsigned short* rgb565,int Height,int Width);//change rgb888 to rgb565
    void rgb2nv12(unsigned char* rgb,unsigned char* nv12,int Height,int Width);//change rgb to nv12
    void rgb2yuvI420(unsigned char* rgb,unsigned char* yuvI420,int Height,int Width);//change rgb to yuvI420
    void rgb8882rgba(unsigned char* rgbd888ata,unsigned char* rgba,int Height,int Width);//change rgb888 to rgba
    void rgb2yuv422sp(unsigned char* rgb888,unsigned char* yuv422sp,int Height,int Width);//change rgb888 to yuv422sp

    //rgba to other format
    void rgba2rgb(unsigned char* rgba,unsigned char* rgb,int Height,int Width);//change rgba to rgb
    void rgba2yuvI420(unsigned char* rgba,unsigned char* yuvI420,int Height,int Width);//change rgba to yuvI420
    void rgba2yuv422sp(unsigned char* rgba,unsigned char* yuv422sp,int Height,int Width);//change rgba to yuv422sp
    void rgba2nv12(unsigned char* rgba,unsigned char* nv12,int Height,int Width);//change rgba to nv12
    void rgba2rgb565(unsigned char* rgba,unsigned short* rgb565,int Height,int Width);//change rgba to rgb565
private:
    T1* srcdata;//source data
    T2* dstdata;//destination data
    QString file_path;
};

#endif // IMGOPERATOR_H
