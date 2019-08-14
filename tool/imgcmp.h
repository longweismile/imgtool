#ifndef IMGCMP_H
#define IMGCMP_H
#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDebug>
using namespace std;
using namespace cv;
//rgba data
template <typename T>
class Imgcmp
{
public:
    Imgcmp();
    ~Imgcmp();
    Imgcmp(const Imgcmp& Img);
    Imgcmp& operator=(const Imgcmp& Img);
    //member function
    void Setfilepath(const QString& str);
    void readfile(T* data,string& path,int datalen);//read data from file
    QString Getfilepath() const;
    void Setdata(QString& path,int datalen);
    T* Getdata() const;
    void copydata(T* ptr,int datalen);//copy data in class
    void Setrgbadata(int len);
    unsigned char* Getrgbadata() const;


    void Print();
    void Imgdiffgray(unsigned char* rgbasrc,unsigned char* rgbadst,unsigned char* graydata,int Height,int Width);
    void ImgdiffRGB(unsigned char* rgbasrc,unsigned char* rgbadst,unsigned char* graydata,int Height,int Width);
    void ImgdiffTimes(unsigned char* imgdiff,int datalen,int Time);
    unsigned char ABS(unsigned char item1,unsigned char item2)
    {
        if(item1 < item2)
            return item2 - item1;
        else
            return item1 - item2;
    }
private:
    QString file_path;
    T* data;
    unsigned char* rgbadata;
    int datalen;
    int rgbadatalen;
};

#endif // IMGCMP_H
