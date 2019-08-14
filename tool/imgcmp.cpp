#include "imgcmp.h"
template <typename T>
Imgcmp<T>::Imgcmp()
{
    this->file_path = "";
    this->datalen = 0;
    this->data = nullptr;
    this->rgbadata = nullptr;
    this->rgbadatalen = 0;
    cout<<"Imgcmp create"<<endl;
}
template <typename T>
Imgcmp<T>::~Imgcmp()
{
    if(this->data != nullptr)
        delete [] data;
    this->data = nullptr;
    if(this->rgbadata != nullptr)
        delete [] this->rgbadata;
    this->rgbadata = nullptr;
    cout<<"Imgcmp delete"<<endl;
}
template <typename T>
Imgcmp<T>::Imgcmp(const Imgcmp<T>& Img)
{
    cout<<"copy"<<endl;
    if(this != &Img)
    {
        this->file_path = Img.file_path;
        cout<<"file_path pass"<<endl;
        this->datalen = Img.datalen;
        this->rgbadatalen = Img.rgbadatalen;
        cout<<"datalen pass"<<endl;
        cout<<(this->data == nullptr)<<endl;
        if(this->data != nullptr)
        {
            cout<<"delete data"<<endl;
            delete []  this->data;
            this->data = nullptr;
        }
        this->data = new T[this->datalen];
        memcpy(this->data,Img.data,this->datalen);
        cout<<datalen<<"copy cnstructor"<<endl;
        if(this->rgbadata != nullptr)
        {
            cout<<"delete rgbadata"<<endl;
            delete [] this->rgbadata;
            this->rgbadata = nullptr;
        }
        this->rgbadata = new unsigned char[this->rgbadatalen];
        memcpy(this->rgbadata,Img.rgbadata,this->rgbadatalen);
        cout<<"end"<<endl;
    }
    else {
            cout<<"Same img"<<endl;
    }
}
template <typename T>
Imgcmp<T>& Imgcmp<T>::operator=(const Imgcmp<T> &Img)
{
    cout<<"operator ="<<endl;
    if(this != &Img)
    {
        this->file_path = Img.file_path;
        cout<<"file_path pass"<<endl;
        this->datalen = Img.datalen;
        this->rgbadatalen = Img.rgbadatalen;
        cout<<"datalen pass"<<endl;
        cout<<(this->data == nullptr)<<endl;
        if(this->data != nullptr)
        {
            cout<<"delete data"<<endl;
            delete []  this->data;
            this->data = nullptr;
        }
        this->data = new T[this->datalen];
        memcpy(this->data,Img.data,this->datalen);
        cout<<datalen<<"copy cnstructor"<<endl;
        if(this->rgbadata != nullptr)
        {
            cout<<"delete rgbadata"<<endl;
            delete [] this->rgbadata;
            this->rgbadata = nullptr;
        }
        this->rgbadata = new unsigned char[this->rgbadatalen];
        memcpy(this->rgbadata,Img.rgbadata,this->rgbadatalen);
        cout<<"end"<<endl;
    }
    return *this;
}
template <typename T>
void Imgcmp<T>::Setfilepath(const QString& str)
{
    this->file_path = str;
}
template <typename T>
void Imgcmp<T>::readfile(T *data, string &path, int datalen)
{
    FILE* fp = nullptr;
    fp = fopen(path.c_str(),"rb+");
    if(!fp)
    {
        cout<<"Fail to open file"<<endl;
    }
    fread(data,sizeof (T),datalen,fp);
    fclose(fp);
    fp = nullptr;
}
template <typename T>
QString Imgcmp<T>::Getfilepath() const
{
    return  this->file_path;
}
template <typename T>
void Imgcmp<T>::Setdata(QString& path,int datalen)
{
    this->datalen = datalen;
    if(this->data != nullptr)
    {
        delete [] this->data;
        this->data = nullptr;
    }
    this->data = new T[datalen];
    string str = path.toStdString();
    readfile(this->data,str,datalen);
}
template <typename T>
T* Imgcmp<T>::Getdata() const
{
    if(this->data == nullptr)
    {
        cout<<"empty pointer"<<endl;
    }
    return this->data;
}
template <typename T>
void Imgcmp<T>::copydata(T* ptr,int datalen)
{
    memcpy(ptr,this->data,datalen);
}
template <typename T>
void Imgcmp<T>::Print()
{
    cout<<this->datalen<<endl;
    for(int i = 0;i < this->datalen;++i)
    {
        cout<<static_cast<int>(this->data[i])<<" ";
        if(i%20 == 0)
            cout<<endl;
    }
    cout<<"end";
}
template <typename T>
unsigned char* Imgcmp<T>::Getrgbadata() const
{
    if(this->rgbadata == nullptr)
    {
        cout<<"empty point"<<endl;
    }
    return this->rgbadata;
}
template <typename T>
void Imgcmp<T>::Setrgbadata(int len)
{
    if(this->rgbadata != nullptr)
    {
        delete [] this->rgbadata;
        this->rgbadata = nullptr;
    }
    this->rgbadata = new unsigned char[len];
}
template <typename T>
void Imgcmp<T>::Imgdiffgray(unsigned char* rgbasrc,unsigned char* rgbadst,unsigned char* graydata,int Height,int Width)
{
    Mat Srcimg = cv::Mat(Height,Width,CV_8UC4);
    memcpy(Srcimg.data,rgbasrc,Height*Width*4);
    Mat Dstimg = cv::Mat(Height,Width,CV_8UC4);
    memcpy(Dstimg.data,rgbadst,Height*Width*4);
    Mat imgdiff = cv::Mat(Height,Width,CV_8UC1);
    cvtColor(Srcimg,Srcimg,CV_RGBA2GRAY);
    cvtColor(Dstimg,Dstimg,CV_RGBA2GRAY);
    absdiff(Srcimg,Dstimg,imgdiff);
    memcpy(graydata,imgdiff.data,Height*Width);
}
template <typename T>
void Imgcmp<T>::ImgdiffRGB(unsigned char* rgbasrc,unsigned char* rgbadst,unsigned char* rgbdata,int Height,int Width)
{
    Mat Srcimg = cv::Mat(Height,Width,CV_8UC4);
    memcpy(Srcimg.data,rgbasrc,Height*Width*4);
    Mat Dstimg = cv::Mat(Height,Width,CV_8UC4);
    memcpy(Dstimg.data,rgbadst,Height*Width*4);
    Mat imgdiff = cv::Mat(Height,Width,CV_8UC4);
    for(int i = 0;i < Height;++i)
    {
        for(int j = 0;j < Width;++j)
        {
            imgdiff.at<Vec4b>(i,j)[0] = ABS(Srcimg.at<Vec4b>(i,j)[0],Dstimg.at<Vec4b>(i,j)[0]);
            imgdiff.at<Vec4b>(i,j)[1] = ABS(Srcimg.at<Vec4b>(i,j)[1],Dstimg.at<Vec4b>(i,j)[1]);
            imgdiff.at<Vec4b>(i,j)[2] = ABS(Srcimg.at<Vec4b>(i,j)[2],Dstimg.at<Vec4b>(i,j)[2]);
            imgdiff.at<Vec4b>(i,j)[3] = ABS(Srcimg.at<Vec4b>(i,j)[3],Dstimg.at<Vec4b>(i,j)[3]);
        }
    }
    cvtColor(imgdiff,imgdiff,CV_BGRA2RGB);
    memcpy(rgbdata,imgdiff.data,Height*Width*3);
}
template <typename T>
void Imgcmp<T>::ImgdiffTimes(unsigned char* imgdiff,int datalen,int Time)
{
    for(int i = 0;i < datalen;++i)
    {
        int data = imgdiff[i];
        data *= Time;
        if(data > 255)
            data = 0;
        imgdiff[i] = static_cast<unsigned char>(data);
    }
}

