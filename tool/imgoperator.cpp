#include "imgoperator.h"
template <typename T1,typename T2>
Imgoperator<T1,T2>::Imgoperator()
{
    cout<<"Imgoperator Create"<<endl;
    file_path = "";
    this->srcdata = nullptr;
    this->dstdata = nullptr;
}
template <typename T1,typename T2>
Imgoperator<T1,T2>::~Imgoperator<T1,T2>()
{
    if(this->srcdata != nullptr)
        delete [] this->srcdata;
    if(this->dstdata != nullptr)
        delete [] this->dstdata;
    cout<<"Imgoperator data relesed"<<endl;
    this->srcdata = nullptr;
    this->dstdata = nullptr;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::test()
{
    std::cout<<"test"<<std::endl;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::readfile(T1* data,string& path,int datalen)
{
    FILE* fp = nullptr;
    fp = fopen(path.c_str(),"rb+");
    if(!fp)
    {
        cout<<"Fail to open file"<<endl;
    }
    fread(data,sizeof (T1),datalen,fp);
    fclose(fp);
    fp = nullptr;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::Setdata(string& path,int datalen)
{
    if(this->srcdata != nullptr)
        delete [] this->srcdata;
    this->srcdata = new T1[datalen];
    readfile(this->srcdata,path,datalen);
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::Setfilepath(QString str)
{
    this->file_path = str;
}
template <typename T1,typename T2>
QString Imgoperator<T1,T2>::Getfilepath() const
{
    return file_path;
}

template <typename T1,typename T2>
T1* Imgoperator<T1,T2>::Getdata() const
{
    if(this->srcdata == nullptr)
    {
        cout<<"empty pointer"<<endl;
    }
    return this->srcdata;
}
//deal with T2 data
template <typename T1,typename T2>
T2* Imgoperator<T1,T2>::Getdstdata() const
{
    if(this->dstdata == nullptr)
    {
        cout<<"empty pointer"<<endl;
    }
    return this->dstdata;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::Setdstdata(int datalen)
{
    if(this->dstdata != nullptr)
        delete [] this->dstdata;
    this->dstdata = new T2[datalen];
}
template <typename T1,typename T2>
bool Imgoperator<T1,T2>::Savedstdata(string path,int len)
{
    FILE* fp;
    fp = fopen(path.c_str(),"wb+");
    if(!fp)
    {
        cout<<"Fail to open fail"<<endl;
        return false;
    }
    fwrite(dstdata,1,sizeof(T2) * len,fp);
    fclose(fp);
    fp = nullptr;
    return true;
}

template <typename T1,typename T2>
void Imgoperator<T1,T2>::showyuv420(unsigned char* yuv420,int Height,int Width)
{
    Mat yuv420img = cv::Mat(Height*3/2,Width,CV_8UC1);
    memcpy(yuv420img.data,yuv420,Height*Width*3/2);
    imshow("yuv420",yuv420img);
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::showyuv422(unsigned char* yuv422,int Height,int Width)
{
    Mat yuv422img = Mat(Height*2,Width,CV_8UC1);
    memcpy(yuv422img.data,yuv422,static_cast<size_t>(Height*Width*2));
    imshow("yuv422",yuv422img);
}
//yuvI420
template <typename T1,typename T2>
//change yuv420 to yun422p
void Imgoperator<T1,T2>::yuvI4202yuv422p(unsigned char* yuv420,unsigned char* yuv422,int Height,int Width)
{
    //copy Y element
    Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
    memcpy(yuvI420img.data,yuv420,Height*Width*3/2);
    //imshow("yuv420img",yuvI420img);
    int Ylen = Height * Width;
    memcpy(yuv422,yuv420,Ylen);
    //copy u element
    unsigned char* pU422 = yuv422 + Ylen;
    unsigned char* pU420 = yuv420 + Ylen;
    int Uwidth = Width>>1;
    int Uheight = Height>>1;
    for(int y = 0;y < Uheight;++y)
    {
        memcpy(pU422+y*Width,pU420+y*Uwidth,Uwidth);
        memcpy(pU422+y*Width+Uwidth,pU420+y*Uwidth,Uwidth);
    }
    //copy v element
    unsigned char* pV422 = yuv422 + Ylen + (Ylen>>1);
    unsigned char* pV420 = pU420 + (Ylen>>2);
    int Vwidth = Uwidth;
    int Vheight = Uheight;
    for(int y = 0;y < Vheight;++y)
    {
        memcpy(pV422+y*Width,pV420+y*Vwidth,Vwidth);
        memcpy(pV422+y*Width+Vwidth,pV420+y*Vwidth,Vwidth);
    }
    Mat yuv422spimg = Mat(Height*2,Width,CV_8UC1);
    memcpy(yuv422spimg.data,yuv422,Height*Width*2);
    //imshow("yuv422sp",yuv422spimg);
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::yuv422p2yuv422sp(unsigned char* yuv422p,unsigned char* yuv422sp,int Height,int Width)
{
    int y_size;
    int uv_size;
    unsigned char* p_y1;
    unsigned char* p_uv;

    unsigned char* p_y2;
    unsigned char* p_u;
    unsigned char* p_v;

    y_size = uv_size = Width*Height;
    p_y1 = yuv422p;
    p_y2 = yuv422sp;
    p_u = p_y1 + y_size;
    p_v = p_u + Width*Height/2;
    p_uv = p_y2 + y_size;
    memcpy(p_y2,p_y1,static_cast<size_t>(y_size));
    for(int i = 0;i < uv_size/2;++i)
    {
        *(p_uv++) = *(p_u++);
        *(p_uv++) = *(p_v++);
    }
}
template <typename T1,typename T2>
//change yuvI420 to yuv422sp
void Imgoperator<T1,T2>::yuvI4202yuv422sp(unsigned char* yuvI420,unsigned char* yuv422sp,int Height,int Width)
{
    unsigned char* yuv422p = new unsigned char[Height*Width*2];
    yuvI4202yuv422p(yuvI420,yuv422p,Height,Width);
    yuv422p2yuv422sp(yuv422p,yuv422sp,Height,Width);
    delete [] yuv422p;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::yuvI4202nv12(unsigned char* yuv420,unsigned char* nv12,int Height,int Width)
{
    int Ylen = Height*Width;
    int Ulen = Height*Width/4;
    unsigned char* yuv420_u = yuv420 + Ylen;
    unsigned char* yuv420_v = yuv420_u + Ulen;
    unsigned char* nv12_uv = nv12 + Ylen;
    memcpy(nv12,yuv420,Ylen);
    for(int i = 0;i < Ulen;++i)
    {
        *(nv12_uv++) = *(yuv420_u++);
        *(nv12_uv++) = *(yuv420_v++);
    }
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::yuvI4202rgb565(unsigned char* yuv420,unsigned short* rgb565,int Height,int Width)
{
    Mat rgb888img = cv::Mat(Height,Width,CV_8UC3);
    Mat yuv420img = cv::Mat(Height*3/2,Width,CV_8UC1);
    memcpy(yuv420img.data,yuv420,Height*Width*3/2);
    cvtColor(yuv420img,rgb888img,CV_YUV2RGB_I420);
    rgb2rgb565(rgb888img.data,rgb565,Height,Width);
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::yuvI4202rgb888(unsigned char* yuvI420,unsigned char* rgb888,int Height,int Width)
{
    Mat yuvI420img = cv::Mat(Height*3/2,Width,CV_8UC1);
    Mat rgb888img = cv::Mat(Height,Width,CV_8UC3);
    memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
    cvtColor(yuvI420img,rgb888img,CV_YUV2RGB_I420);
    memcpy(rgb888,rgb888img.data,Height*Width*3);
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::yuvI4202RGB32(unsigned char* yuvI420,unsigned char* rgb32,int Height,int Width)
{
    Mat MatyuvI420 = cv::Mat(Height*3/2,Width,CV_8UC1);
    memcpy(MatyuvI420.data,yuvI420,Height*Width*3/2);
    Mat Matrgb32;
    cvtColor(MatyuvI420,Matrgb32,CV_YUV2RGBA_I420);
    memcpy(rgb32,Matrgb32.data,Height*Width*4);
}

//yuv422sp
template <typename T1,typename T2>
void Imgoperator<T1,T2>::yuv422sp2yuvI420(unsigned char* yuv422sp,unsigned char* yuvI420,int Height,int Width)
{
    unsigned char* rgb888 = new unsigned char[Height*Width*3];
    yuv422sp2rgb24(yuv422sp,rgb888,Height,Width);
    Mat rgb888img = cv::Mat(Height,Width,CV_8UC3);
    memcpy(rgb888img.data,rgb888,Height*Width*3);
    Mat yuvI420img = cv::Mat(Height*3/2,Width,CV_8UC1);
    cvtColor(rgb888img,yuvI420img,CV_RGB2YUV_I420);
    memcpy(yuvI420,yuvI420img.data,Height*Width*3/2);
    delete [] rgb888;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::yuv422sp2nv12(unsigned char* yuv422sp,unsigned char* nv12,int Height,int Width)
{
    unsigned char* yuvI420 = new unsigned char[Height*Width*3/2];
    yuv422sp2yuvI420(yuv422sp,yuvI420,Height,Width);
    yuvI4202nv12(yuvI420,nv12,Height,Width);
    Mat nv12img = Mat(Height*3/2,Width,CV_8UC1);
    memcpy(nv12img.data,nv12,Height*Width*3/2);
    Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
    memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
    delete [] yuvI420;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::yuv422sp2rgb24(unsigned char* yuv422sp,unsigned char* rgb24,int Height,int Width)
{
    int Y,U,V;
    int R,G,B;
    unsigned char* p_y;
    unsigned char* p_uv;
    unsigned char* p_rgb;
    p_y = yuv422sp;
    p_uv = p_y + Height*Width;
    p_rgb = rgb24;
    for(int i = 0;i < Height*Width/2;++i)
    {
        Y = *(p_y++);
        U = *(p_uv++);
        V = *(p_uv++);
        R = YUV2R(Y,U,V);
        G = YUV2G(Y,U,V);
        B = YUV2B(Y,U,V);
        *(p_rgb++) = static_cast<unsigned char>(R);
        *(p_rgb++) = static_cast<unsigned char>(G);
        *(p_rgb++) = static_cast<unsigned char>(B);
        Y = *(p_y++);
        *(p_rgb++) = static_cast<unsigned char>(R);
        *(p_rgb++) = static_cast<unsigned char>(G);
        *(p_rgb++) = static_cast<unsigned char>(B);
    }
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::yuv422sp2rgb32(unsigned char* yuv422sp,unsigned char* rgba32,int Height,int Width)
{
    //first step change yuv422sp to rgb24
    unsigned char* rgbdata = new unsigned char[Height*Width*3];
    yuv422sp2rgb24(yuv422sp,rgbdata,Height,Width);
    Mat rgb = cv::Mat(Height,Width,CV_8UC3);
    rgb.data = rgbdata;
    Mat rgba = cv::Mat(Height,Width,CV_8UC4);
    cvtColor(rgb,rgba,CV_RGB2RGBA);
    memcpy(rgba32,rgba.data,Height*Width*4);
    delete [] rgbdata;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::yuv422sp2rgb565(unsigned char* yuv422sp,unsigned short* rgb565,int Height,int Width)
{
    unsigned char* rgb = new unsigned char[Height*Width*3];
    yuv422sp2rgb24(yuv422sp,rgb,Height,Width);
    rgb2rgb565(rgb,rgb565,Height,Width);
    delete [] rgb;
}

//NV12
template <typename T1,typename T2>
void Imgoperator<T1,T2>::NV122RGBA(unsigned char* nv12,unsigned char* rgba,int Height,int Width)
{
    Mat nv12img;
    Mat rgbaimg;
    nv12img = cv::Mat(Height * 3/2,Width,CV_8UC1);
    rgbaimg = cv::Mat(Height,Width,CV_8UC4);
    memcpy(nv12img.data,nv12,Height*Width*3/2);
    cvtColor(nv12img,rgbaimg,CV_YUV2RGBA_NV12);
    cvtColor(rgbaimg,rgbaimg,CV_BGRA2RGBA);
    memcpy(rgba,rgbaimg.data,Height*Width*4);
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::NV122RGB(unsigned char* nv12,unsigned char* rgb,int Height,int Width)
{
    Mat nv12img = Mat(Height*3/2,Width,CV_8UC1);
    Mat rgbimg = Mat(Height,Width,CV_8UC3);
    memcpy(nv12img.data,nv12,Height*Width*3/2);
    cvtColor(nv12img,rgbimg,CV_YUV2RGB_NV12);
    cvtColor(rgbimg,rgbimg,CV_BGR2RGB);
    memcpy(rgb,rgbimg.data,Height*Width*3);

}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::NV122yuvI420(unsigned char* nv12,unsigned char* yuvI420,int Height,int Width)
{
    cout<<"NV122yuvI420"<<endl;
    int Ylen = Height*Width;
    int Ulen = Height*Width/4;
    unsigned char* yuvI420_u = yuvI420 + Ylen;
    unsigned char* yuvI420_v = yuvI420_u + Ulen;
    unsigned char* nv12_uv = nv12 + Ylen;
    memcpy(yuvI420,nv12,Ylen);
    for(int i = 0;i < Height*Width/4;++i)
    {
        *(yuvI420_u++) = *(nv12_uv++);
        *(yuvI420_v++) = *(nv12_uv++);
    }
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::NV1222yuv422sp(unsigned char* nv12,unsigned char* yuv422sp,int Height,int Width)
{
    unsigned char* yuvI420 = new unsigned char[Height*Width*3/2];
    NV122yuvI420(nv12,yuvI420,Height,Width);
    yuvI4202yuv422sp(yuvI420,yuv422sp,Height,Width);
    Mat yuv422spimg = Mat(Height*2,Width,CV_8UC1);
    yuv422spimg.data = yuv422sp;

    delete [] yuvI420;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::NV122RGB565(unsigned char* nv12,unsigned short* rgb565,int Height,int Width)
{
    unsigned char* rgb = new unsigned char[Height*Width*3];
    NV122RGB(nv12,rgb,Height,Width);
    rgb2rgb565(rgb,rgb565,Height,Width);
    delete [] rgb;
}

//rgb565
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgb5652rgb888(unsigned short* rgb565,unsigned char* rgb888,int Height,int Width)
{
    cout<<"rgb5652rgb888"<<endl;
    int rgb565len = Height*Width;
    for(int i = 0;i < rgb565len;++i)
    {
        unsigned short RGB565 = *rgb565;
        int r = ((RGB565 >> 11) & 0x1F);
        int g = ((RGB565 >> 5) & 0x3F);
        int b = ((RGB565) & 0x1F);
        r = ((r * 255) / 31) - 4;
        g = ((g * 255) / 63) - 2;
        b = ((b * 255) / 31) - 4;
        rgb888[i*3+0] = r;
        rgb888[i*3+1] = g;
        rgb888[i*3+2] = b;
        ++rgb565;
    }
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgb5652rgba(unsigned short* rgb565data,unsigned char* rgbadata,int Height,int Width)
{
    unsigned char* rgb = new unsigned char[Height*Width*3];
    rgb5652rgb888(rgb565data,rgb,Height,Width);
    Mat rgbimg = cv::Mat(Height,Width,CV_8UC3);
    rgbimg.data = rgb;
    //imshow("rgb",rgbimg);
    Mat rgbaimg = cv::Mat(Height,Width,CV_8UC4);
    cvtColor(rgbimg,rgbaimg,CV_RGB2RGBA);
    //imshow("rgba",rgbaimg);
    memcpy(rgbadata,rgbaimg.data,Height*Width*4);
    delete [] rgb;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgb5652yuvI420(unsigned short* rgb565,unsigned char* yuvI420,int Height,int Width)
{
    cout<<"rgb5652yuvI420"<<endl;
    unsigned char* rgb = new unsigned char[Height*Width*3];
    rgb5652rgb888(rgb565,rgb,Height,Width);
    rgb2yuvI420(rgb,yuvI420,Height,Width);
    Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
    memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
    delete [] rgb;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgb5652yuv422sp(unsigned short* rgb565,unsigned char* yuv422sp,int Height,int Width)
{
    unsigned char* rgb = new unsigned char[Height*Width*3];
    rgb5652rgb888(rgb565,rgb,Height,Width);
    rgb2yuv422sp(rgb,yuv422sp,Height,Width);
    delete [] rgb;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgb5652nv12(unsigned short* rgb565,unsigned char* nv12,int Height,int Width)
{
    unsigned char* rgb = new unsigned char[Height*Width*3];
    rgb5652rgb888(rgb565,rgb,Height,Width);
    Mat rgbimg = Mat(Height,Width,CV_8UC3);
    rgbimg.data = rgb;
    rgb2nv12(rgb,nv12,Height,Width);
    Mat nv12img = Mat(Height*3/2,Width,CV_8UC1);
    nv12img.data = nv12;
    delete [] rgb;
}

//rgb888
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgb2rgb565(unsigned char* rgb,unsigned short* rgb565,int Height,int Width)
{
    int size = Height*Width;
    for(int i = 0;i < size;++i)
    {
        unsigned short RGB565Color = 0;
        unsigned char red = rgb[i*3+0];
        unsigned char green = rgb[i*3+1];
        unsigned char blue = rgb[i*3+2];
        rgb565[i] = (static_cast<unsigned short>(red&0xF8)<<8) + (static_cast<unsigned char>(green&0xFC)<<3)
                + (static_cast<unsigned short>(blue&0xF8)>>3);
    }
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgb8882rgba(unsigned char* rgb888data,unsigned char* rgba,int Height,int Width)
{
    Mat rgbimg = cv::Mat(Height,Width,CV_8UC3);
    memcpy(rgbimg.data,rgb888data,Height*Width*3);
    Mat rgbaimg = cv::Mat(Height,Width,CV_8UC4);
    cvtColor(rgbimg,rgbaimg,CV_RGB2RGBA);
    memcpy(rgba,rgbaimg.data,Height*Width*4);
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgb2nv12(unsigned char* rgb,unsigned char* nv12,int Height,int Width)
{
    Mat rgbimg = cv::Mat(Height,Width,CV_8UC3);
    memcpy(rgbimg.data,rgb,Height*Width*3);
    Mat yuvI420 = cv::Mat(Height*3/2,Width,CV_8UC1);
    cvtColor(rgbimg,yuvI420,CV_RGB2YUV_I420);
    yuvI4202nv12(yuvI420.data,nv12,Height,Width);
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgb2yuvI420(unsigned char* rgb,unsigned char* yuvI420,int Height,int Width)
{
    Mat rgbimg = cv::Mat(Height,Width,CV_8UC3);
    memcpy(rgbimg.data,rgb,Height*Width*3);
    Mat yuvI420img = cv::Mat(Height*3/2,Width,CV_8UC1);
    cvtColor(rgbimg,yuvI420img,CV_RGB2YUV_I420);
    memcpy(yuvI420,yuvI420img.data,Height*Width*3/2);
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgb2yuv422sp(unsigned char* rgb888,unsigned char* yuv422sp,int Height,int Width)
{
    unsigned char* yuvI420 = new unsigned char[Height*Width*3/2];
    rgb2yuvI420(rgb888,yuvI420,Height,Width);
    yuvI4202yuv422sp(yuvI420,yuv422sp,Height,Width);
    delete [] yuvI420;
}

//rgba
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgba2rgb(unsigned char* rgba,unsigned char* rgb,int Height,int Width)
{
    Mat rgbaimg = Mat(Height,Width,CV_8UC4);
    memcpy(rgbaimg.data,rgba,Height*Width*4);
    Mat rgbimg = Mat(Height,Width,CV_8UC3);
    cvtColor(rgbaimg,rgbimg,CV_RGBA2RGB);
    memcpy(rgb,rgbimg.data,Height*Width*3);
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgba2yuvI420(unsigned char* rgba,unsigned char* yuvI420,int Height,int Width)
{
    Mat rgbaimg = Mat(Height,Width,CV_8UC4);
    memcpy(rgbaimg.data,rgba,Height*Width*4);
    Mat rgbimg = Mat(Height,Width,CV_8UC3);
    cvtColor(rgbaimg,rgbimg,CV_RGBA2RGB);
    unsigned char* rgb = new unsigned char[Height*Width*3];
    memcpy(rgb,rgbimg.data,Height*Width*3);
    rgb2yuvI420(rgb,yuvI420,Height,Width);
    Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
    memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgba2yuv422sp(unsigned char* rgba,unsigned char* yuv422sp,int Height,int Width)
{
    unsigned char* rgb = new unsigned char[Height*Width*3];
    rgba2rgb(rgba,rgb,Height,Width);
    rgb2yuv422sp(rgb,yuv422sp,Height,Width);
    Mat yuv422spimg = Mat(Height*2,Width,CV_8UC1);
    yuv422spimg.data = yuv422sp;
    delete [] rgb;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgba2nv12(unsigned char* rgba,unsigned char* nv12,int Height,int Width)
{
    unsigned char* rgb = new unsigned char[Height*Width*3];
    rgba2rgb(rgba,rgb,Height,Width);
    rgb2nv12(rgb,nv12,Height,Width);
    delete [] rgb;
}
template <typename T1,typename T2>
void Imgoperator<T1,T2>::rgba2rgb565(unsigned char* rgba,unsigned short* rgb565,int Height,int Width)
{
    unsigned char* rgb = new unsigned char[Height*Width*3];
    rgba2rgb(rgba,rgb,Height,Width);
    rgb2rgb565(rgb,rgb565,Height,Width);
    Mat rgb565img = Mat(Height,Width,CV_16SC1);
    memcpy(rgb565img.data,rgb565,Height*Width*2);
    //imshow("rgb565img",rgb565img);
    delete [] rgb;
}
