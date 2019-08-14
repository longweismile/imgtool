#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->file_path = "";
    this->rgbadata = nullptr;
    this->diffdata = nullptr;
    Imgcc = new Imgoperator<unsigned char,unsigned char>();
    Imgcs = new Imgoperator<unsigned char,unsigned short>();
    Imgsc = new Imgoperator<unsigned short,unsigned char>();
    Imgss = new Imgoperator<unsigned short,unsigned short>();
    uimgdiff1 = new Imgcmp<unsigned char>();
    uimgdiff2 = new Imgcmp<unsigned char>();
    simgdiff1 = new Imgcmp<unsigned short>();
    simgdiff2 = new Imgcmp<unsigned short>();
    encodeinfo = new encodeimg();
    decodeinfo = new decodeimg();
}

MainWindow::~MainWindow()
{
    Freergbadata();
    Freediffdata();
    if(Imgcc != nullptr)
    {
        delete Imgcc;
        Imgcc = nullptr;
    }
    if(Imgcs != nullptr)
    {
        delete Imgcs;
        Imgcs = nullptr;
    }
    if(Imgsc != nullptr)
    {
        delete Imgsc;
        Imgsc = nullptr;
    }
    if(Imgss != nullptr)
    {
        delete Imgss;
        Imgss = nullptr;
    }
    if(uimgdiff1 != nullptr)
    {
        delete uimgdiff1;
        uimgdiff1 = nullptr;
    }
    if(uimgdiff2 != nullptr)
    {
        delete uimgdiff2;
        uimgdiff2 = nullptr;
    }
    if(simgdiff1 != nullptr)
    {
        delete simgdiff1;
        simgdiff1 = nullptr;
    }
    if(simgdiff2 != nullptr)
    {
        delete simgdiff2;
        simgdiff2 = nullptr;
    }
    delete encodeinfo;
    delete decodeinfo;
    delete ui;
}

void MainWindow::Setrgbadata(int datalength)
{
    if(this->rgbadata != nullptr)
    {
        delete [] rgbadata;
        rgbadata = nullptr;
    }
    rgbadata = new unsigned char[datalength];
}

bool MainWindow::Freergbadata()
{
    if(rgbadata != nullptr)
    {
        delete [] rgbadata;
    }
    rgbadata = nullptr;
    return rgbadata == nullptr;
}

void MainWindow::Setdiffdata(int datalen)
{
    if(this->diffdata != nullptr)
    {
        delete [] this->diffdata;
        this->diffdata = nullptr;
    }
    this->diffdata = new unsigned char[datalen];
}

bool MainWindow::Freediffdata()
{
    if(this->diffdata != nullptr)
    {
        delete [] this->diffdata;
    }
    this->diffdata = nullptr;
    return this->diffdata == nullptr;
}

bool MainWindow::Savergbadatafile(std::string path,int datalen) const
{
    FILE* fp;
    fp = fopen(path.c_str(),"wb+");
    if(!fp)
    {
        cout<<"Fail to open fail"<<endl;
        return false;
    }
    fwrite(this->rgbadata,1,sizeof(unsigned char) * datalen,fp);
    fclose(fp);
    fp = nullptr;
    return true;
}

//choose file---Open file
void MainWindow::on_OpenFileButton_clicked()
{
    this->file_path  = QFileDialog::getOpenFileName(NULL,"标题",".","*");
    qDebug() << this->file_path;
    //show file name
    string file_name = this->file_path.toStdString();
    int pos = file_name.find_last_of('/');
    file_name = file_name.substr(pos+1);
    ui->lineEdit_FileName->setText(QString::fromStdString(file_name));
}

void MainWindow::on_lineEdit_imgformat_cursorPositionChanged(int arg1, int arg2)
{
    QString Inputformat = ui->combox_Inputformat->currentText();
    QString Outformat = ui->comboBox_Outputformat->currentText();
    ui->lineEdit_imgformat->setText(Inputformat + "->" + Outformat);
}


//Change Picture format
void MainWindow::on_PicChange_clicked()
{

    QString Inputformat = ui->combox_Inputformat->currentText();
    QString Outformat = ui->comboBox_Outputformat->currentText();
    int Height = ui->LineEdit_Height->text().toInt();
    int Width = ui->lineEdit_Width->text().toInt();
    int rgbalen = Height*Width*4;
    Setrgbadata(rgbalen);

    if(Inputformat == "YUVI420")
    {
        if(Outformat == "YUVI420")
        {
            cout<<"same format"<<endl;
        }
        else if(Outformat == "YUV422sp")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int yuv422splen = Height*Width*2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(yuv422splen);
            unsigned char* yuvI420 = Imgcc->Getdata();
            unsigned char* yuv422sp = Imgcc->Getdstdata();
            Imgcc->yuvI4202yuv422sp(yuvI420,yuv422sp,Height,Width);
            Imgcc->yuvI4202RGB32(yuvI420,this->rgbadata,Height,Width);
            Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
            imshow("yuvI420",yuvI420img);
            Mat yuv422spimg = Mat(Height*2,Width,CV_8UC1);
            memcpy(yuv422spimg.data,yuv422sp,Height*Width*2);
            imshow("yuv422sp",yuv422spimg);
        }
        else if(Outformat == "NV12")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int nv12len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(nv12len);
            unsigned char* yuvI420 = Imgcc->Getdata();
            unsigned char* nv12 = Imgcc->Getdstdata();
            Imgcc->yuvI4202nv12(yuvI420,nv12,Height,Width);
            Imgcc->yuvI4202RGB32(yuvI420,this->rgbadata,Height,Width);
            Mat nv12img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(nv12img.data,nv12,Height*Width*3/2);
            imshow("nv12img",nv12img);
            Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
            imshow("yuvI420",yuvI420img);
        }
        else if(Outformat == "RGB565")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int rgb565len = Height*Width*3/2;
            Imgcs->Setdata(path,datalen);
            Imgcs->Setdstdata(rgb565len);
            unsigned char* yuvI420 = Imgcs->Getdata();
            unsigned short* rgb565 = Imgcs->Getdstdata();
            Imgcs->yuvI4202rgb565(yuvI420,rgb565,Height,Width);
            Imgcc->yuvI4202RGB32(yuvI420,this->rgbadata,Height,Width);
            Mat rgb565img = Mat(Height,Width,CV_16SC1);
            memcpy(rgb565img.data,rgb565,Height*Width*2);
            imshow("nv12img",rgb565img);
            Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
            imshow("yuvI420",yuvI420img);
        }
        else if(Outformat == "RGB888")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int rgb888len = Height*Width*3;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(rgb888len);
            unsigned char* yuvI420 = Imgcc->Getdata();
            unsigned char* rgb888 = Imgcc->Getdstdata();
            Imgcc->yuvI4202rgb888(yuvI420,rgb888,Height,Width);
            Imgcc->yuvI4202RGB32(yuvI420,this->rgbadata,Height,Width);
            Mat rgb888img = Mat(Height,Width,CV_8UC3);
            memcpy(rgb888img.data,rgb888,Height*Width*3);
            cvtColor(rgb888img,rgb888img,CV_RGB2BGR);
            imshow("rgb888img",rgb888img);
            Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
            imshow("yuvI420",yuvI420img);
        }
        else if(Outformat == "RGBA8888")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int rgbalen = Height*Width*4;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(rgbalen);
            unsigned char* yuvI420 = Imgcc->Getdata();
            unsigned char* rgba = Imgcc->Getdstdata();
            Imgcc->yuvI4202RGB32(yuvI420,rgba,Height,Width);
            Imgcc->yuvI4202RGB32(yuvI420,this->rgbadata,Height,Width);
            Mat rgbaimg = Mat(Height,Width,CV_8UC4);
            memcpy(rgbaimg.data,rgba,Height*Width*4);
            cvtColor(rgbaimg,rgbaimg,CV_RGBA2BGRA);
            imshow("rgba",rgbaimg);
            Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
            imshow("yuvI420",yuvI420img);
        }
        else {
            cout<<"Invalid Output"<<endl;
        }
        //show rgbadata
        QImage Qimg;
        Qimg = QImage(this->rgbadata,Width,Height,Width*4,QImage::Format_RGBA8888);
        QPixmap pix(QPixmap::fromImage(Qimg));
        pix.scaled(ui->Label_img->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->Label_img->setScaledContents(true);
        ui->Label_img->setPixmap(pix);
        ui->Label_img->show();
    }
    else if(Inputformat == "YUV422sp")
    {
        if(Outformat == "YUVI420")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*2;
            int YUVI420len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(YUVI420len);
            unsigned char* yuv422sp = Imgcc->Getdata();
            unsigned char* yuvI420 = Imgcc->Getdstdata();
            Imgcc->yuv422sp2yuvI420(yuv422sp,yuvI420,Height,Width);
            Imgcc->yuv422sp2rgb32(yuv422sp,this->rgbadata,Height,Width);
            Mat yuv422spimg = Mat(Height*2,Width,CV_8UC1);
            memcpy(yuv422spimg.data,yuv422sp,Height*Width*2);
            imshow("yuv422sp",yuv422spimg);
            Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
            imshow("yuvI420",yuvI420img);
        }
        else if(Outformat == "YUV422sp")
        {
            cout<<"same image"<<endl;
        }
        else if(Outformat == "NV12")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*2;
            int NV12len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(NV12len);
            unsigned char* yuv422sp = Imgcc->Getdata();
            unsigned char* NV12 = Imgcc->Getdstdata();
            Imgcc->yuv422sp2nv12(yuv422sp,NV12,Height,Width);
            Imgcc->yuv422sp2rgb32(yuv422sp,this->rgbadata,Height,Width);
            Mat yuv422spimg = Mat(Height*2,Width,CV_8UC1);
            memcpy(yuv422spimg.data,yuv422sp,Height*Width*2);
            imshow("yuv422sp",yuv422spimg);
            Mat NV12img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(NV12img.data,NV12,Height*Width*3/2);
            imshow("NV12",NV12img);
        }
        else if(Outformat == "RGB565")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*2;
            int rgb565len = Height*Width;
            Imgcs->Setdata(path,datalen);
            Imgcs->Setdstdata(rgb565len);
            unsigned char* yuv422sp = Imgcs->Getdata();
            unsigned short* rgb565 = Imgcs->Getdstdata();
            Imgcs->yuv422sp2rgb565(yuv422sp,rgb565,Height,Width);
            Imgcc->yuv422sp2rgb32(yuv422sp,this->rgbadata,Height,Width);
            Mat yuv422spimg = Mat(Height*2,Width,CV_8UC1);
            memcpy(yuv422spimg.data,yuv422sp,Height*Width*2);
            imshow("yuv422sp",yuv422spimg);
            Mat rgb565img = Mat(Height,Width,CV_16SC1);
            memcpy(rgb565img.data,rgb565,Height*Width*2);
            imshow("rgb565",rgb565img);
        }
        else if(Outformat == "RGB888")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*2;
            int rgb888len = Height*Width*3;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(rgb888len);
            unsigned char* yuv422sp = Imgcc->Getdata();
            unsigned char* rgb888 = Imgcc->Getdstdata();
            Imgcc->yuv422sp2rgb24(yuv422sp,rgb888,Height,Width);
            Imgcc->yuv422sp2rgb32(yuv422sp,this->rgbadata,Height,Width);
            Mat yuv422spimg = Mat(Height*2,Width,CV_8UC1);
            memcpy(yuv422spimg.data,yuv422sp,Height*Width*2);
            imshow("yuv422sp",yuv422spimg);
            Mat rgbimg = Mat(Height,Width,CV_8UC3);
            memcpy(rgbimg.data,rgb888,Height*Width*3);
            cvtColor(rgbimg,rgbimg,CV_RGB2BGR);
            imshow("rgb",rgbimg);
        }
        else if(Outformat == "RGBA8888")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*2;
            int rgbalen = Height*Width*4;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(rgbalen);
            unsigned char* yuv422sp = Imgcc->Getdata();
            unsigned char* rgba = Imgcc->Getdstdata();
            Imgcc->yuv422sp2rgb32(yuv422sp,rgba,Height,Width);
            Imgcc->yuv422sp2rgb32(yuv422sp,this->rgbadata,Height,Width);
            Mat yuv422spimg = Mat(Height*2,Width,CV_8UC1);
            memcpy(yuv422spimg.data,yuv422sp,Height*Width*2);
            imshow("yuv422sp",yuv422spimg);
            Mat rgbaimg = Mat(Height,Width,CV_8UC4);
            memcpy(rgbaimg.data,rgba,Height*Width*4);
            cvtColor(rgbaimg,rgbaimg,CV_RGBA2BGRA);
            imshow("rgba",rgbaimg);
        }
        else {
            cout<<"Invalid Outputformat"<<endl;
        }
        QImage Qimg;
        Qimg = QImage(this->rgbadata,Width,Height,Width*4,QImage::Format_RGBA8888);
        QPixmap pix(QPixmap::fromImage(Qimg));
        pix.scaled(ui->Label_img->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->Label_img->setScaledContents(true);
        ui->Label_img->setPixmap(pix);
        ui->Label_img->show();
    }
    else if(Inputformat == "NV12")
    {
        if(Outformat == "YUVI420")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int YUVI420len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(YUVI420len);
            unsigned char* nv12 = Imgcc->Getdata();
            unsigned char* yuvI420 = Imgcc->Getdstdata();
            Imgcc->NV122yuvI420(nv12,yuvI420,Height,Width);
            Imgcc->NV122RGBA(nv12,this->rgbadata,Height,Width);
            Mat nv12img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(nv12img.data,nv12,Height*Width*3/2);
            imshow("nv12",nv12img);
            Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
            imshow("yuvI420",yuvI420img);
        }
        else if(Outformat == "YUV422sp")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int yuv422splen = Height*Width*2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(yuv422splen);
            unsigned char* nv12 = Imgcc->Getdata();
            unsigned char* yuv422sp = Imgcc->Getdstdata();
            Imgcc->NV1222yuv422sp(nv12,yuv422sp,Height,Width);
            Imgcc->NV122RGBA(nv12,this->rgbadata,Height,Width);
            Mat nv12img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(nv12img.data,nv12,Height*Width*3/2);
            imshow("nv12",nv12img);
            Mat yuv422spimg = Mat(Height*2,Width,CV_8UC1);
            memcpy(yuv422spimg.data,yuv422sp,Height*Width*2);
            imshow("yuv422sp",yuv422spimg);
        }
        else if(Outformat == "NV12")
        {
            cout<<"same format"<<endl;
        }
        else if(Outformat == "RGB565")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int rgb565len = Height*Width;
            Imgcs->Setdata(path,datalen);
            Imgcs->Setdstdata(rgb565len);
            unsigned char* nv12 = Imgcs->Getdata();
            unsigned short* rgb565 = Imgcs->Getdstdata();
            Imgcs->NV122RGB565(nv12,rgb565,Height,Width);
            Imgcs->NV122RGBA(nv12,this->rgbadata,Height,Width);
            Mat nv12img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(nv12img.data,nv12,Height*Width*3/2);
            imshow("nv12",nv12img);
            Mat rgb565img = Mat(Height,Width,CV_16SC1);
            memcpy(rgb565img.data,rgb565,Height*Width*2);
            imshow("rgb565",rgb565img);
        }
        else if(Outformat == "RGB888")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int rgb888len = Height*Width*3;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(rgb888len);
            unsigned char* nv12 = Imgcc->Getdata();
            unsigned char* rgb888 = Imgcc->Getdstdata();
            Imgcc->NV122RGB(nv12,rgb888,Height,Width);
            Imgcc->NV122RGBA(nv12,this->rgbadata,Height,Width);
            Mat nv12img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(nv12img.data,nv12,Height*Width*3/2);
            imshow("nv12",nv12img);
            Mat rgb888img = Mat(Height,Width,CV_8UC3);
            memcpy(rgb888img.data,rgb888,Height*Width*3);
            cvtColor(rgb888img,rgb888img,CV_RGB2BGR);
            imshow("rgb888",rgb888img);
        }
        else if(Outformat == "RGBA8888")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int rgbalen = Height*Width*4;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(rgbalen);
            unsigned char* nv12 = Imgcc->Getdata();
            unsigned char* rgba = Imgcc->Getdstdata();
            Imgcc->NV122RGBA(nv12,rgba,Height,Width);
            Imgcc->NV122RGBA(nv12,this->rgbadata,Height,Width);
            Mat nv12img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(nv12img.data,nv12,Height*Width*3/2);
            imshow("nv12",nv12img);
            Mat rgbaimg = Mat(Height,Width,CV_8UC4);
            memcpy(rgbaimg.data,rgba,Height*Width*4);
            cvtColor(rgbaimg,rgbaimg,CV_RGBA2BGRA);
            imshow("rgba",rgbaimg);
        }
        else {
            cout<<"Invalid Outputformat"<<endl;
        }
        QImage Qimg;
        Qimg = QImage(this->rgbadata,Width,Height,Width*4,QImage::Format_RGBA8888);
        QPixmap pix(QPixmap::fromImage(Qimg));
        pix.scaled(ui->Label_img->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->Label_img->setScaledContents(true);
        ui->Label_img->setPixmap(pix);
        ui->Label_img->show();
    }
    else if(Inputformat == "RGB565")
    {
        if(Outformat == "YUVI420")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width;
            int YUVI420len = Height*Width*3/2;
            Imgsc->Setdata(path,datalen);
            Imgsc->Setdstdata(YUVI420len);
            unsigned short* rgb565 = Imgsc->Getdata();
            unsigned char* yuvI420 = Imgsc->Getdstdata();
            Imgsc->rgb5652yuvI420(rgb565,yuvI420,Height,Width);
            Imgsc->rgb5652rgba(rgb565,this->rgbadata,Height,Width);
            Mat rgb565img = Mat(Height,Width,CV_16SC1);
            memcpy(rgb565img.data,rgb565,Height*Width*2);
            imshow("rgb565",rgb565img);
            Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
            imshow("yuvI420",yuvI420img);
        }
        else if(Outformat == "YUV422sp")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width;
            int yuv422splen = Height*Width*2;
            Imgsc->Setdata(path,datalen);
            Imgsc->Setdstdata(yuv422splen);
            unsigned short* rgb565 = Imgsc->Getdata();
            unsigned char* yuv422sp = Imgsc->Getdstdata();
            Imgsc->rgb5652yuv422sp(rgb565,yuv422sp,Height,Width);
            Imgsc->rgb5652rgba(rgb565,this->rgbadata,Height,Width);
            Mat rgb565img = Mat(Height,Width,CV_16SC1);
            memcpy(rgb565img.data,rgb565,Height*Width*2);
            imshow("rgb565",rgb565img);
            Mat yuv422spimg = Mat(Height*2,Width,CV_8UC1);
            memcpy(yuv422spimg.data,yuv422sp,Height*Width*2);
            imshow("yuv422sp",yuv422spimg);
        }
        else if(Outformat == "NV12")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width;
            int nv12len = Height*Width*3/2;
            Imgsc->Setdata(path,datalen);
            Imgsc->Setdstdata(nv12len);
            unsigned short* rgb565 = Imgsc->Getdata();
            unsigned char* nv12 = Imgsc->Getdstdata();
            Imgsc->rgb5652nv12(rgb565,nv12,Height,Width);
            Imgsc->rgb5652rgba(rgb565,this->rgbadata,Height,Width);
            Mat rgb565img = Mat(Height,Width,CV_16SC1);
            memcpy(rgb565img.data,rgb565,Height*Width*2);
            imshow("rgb565",rgb565img);
            Mat nv12img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(nv12img.data,nv12,Height*Width*3/2);
            imshow("nv12",nv12img);
        }
        else if(Outformat == "RGB565")
        {
            cout<<"same format"<<endl;
        }
        else if(Outformat == "RGB888")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width;
            int rgb888len = Height*Width*3;
            Imgsc->Setdata(path,datalen);
            Imgsc->Setdstdata(rgb888len);
            unsigned short* rgb565 = Imgsc->Getdata();
            unsigned char* rgb888 = Imgsc->Getdstdata();
            Imgsc->rgb5652rgb888(rgb565,rgb888,Height,Width);
            Imgsc->rgb5652rgba(rgb565,this->rgbadata,Height,Width);
            Mat rgb565img = Mat(Height,Width,CV_16SC1);
            memcpy(rgb565img.data,rgb565,Height*Width*2);
            imshow("rgb565",rgb565img);
            Mat rgb888img = Mat(Height,Width,CV_8UC3);
            memcpy(rgb888img.data,rgb888,Height*Width*3);
            cvtColor(rgb888img,rgb888img,CV_RGB2BGR);
            imshow("rgb888",rgb888img);
        }
        else if(Outformat == "RGBA8888")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width;
            int rgbalen = Height*Width*4;
            Imgsc->Setdata(path,datalen);
            Imgsc->Setdstdata(rgbalen);
            unsigned short* rgb565 = Imgsc->Getdata();
            unsigned char* rgba = Imgsc->Getdstdata();
            Imgsc->rgb5652rgba(rgb565,rgba,Height,Width);
            Imgsc->rgb5652rgba(rgb565,this->rgbadata,Height,Width);
            Mat rgb565img = Mat(Height,Width,CV_16SC1);
            memcpy(rgb565img.data,rgb565,Height*Width*2);
            imshow("rgb565",rgb565img);
            Mat rgbaimg = Mat(Height,Width,CV_8UC4);
            memcpy(rgbaimg.data,rgba,Height*Width*3);
            cvtColor(rgbaimg,rgbaimg,CV_RGBA2BGRA);
            imshow("rgba",rgbaimg);
        }
        else {
            cout<<"Invalid Input"<<endl;
        }
        QImage Qimg;
        Qimg = QImage(this->rgbadata,Width,Height,Width*4,QImage::Format_RGBA8888);
        QPixmap pix(QPixmap::fromImage(Qimg));
        pix.scaled(ui->Label_img->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->Label_img->setScaledContents(true);
        ui->Label_img->setPixmap(pix);
        ui->Label_img->show();
    }
    else if(Inputformat == "RGB888")
    {
        if(Outformat == "YUVI420")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3;
            int YUVI420len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(YUVI420len);
            unsigned char* rgb888 = Imgcc->Getdata();
            unsigned char* yuvI420 = Imgcc->Getdstdata();
            Imgcc->rgb2yuvI420(rgb888,yuvI420,Height,Width);
            Imgcc->rgb8882rgba(rgb888,this->rgbadata,Height,Width);
            Mat rgbimg = Mat(Height,Width,CV_8UC3);
            memcpy(rgbimg.data,rgb888,Height*Width*2);
            cvtColor(rgbimg,rgbimg,CV_RGB2BGR);
            imshow("rgb888",rgbimg);
            Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
            imshow("yuvI420",yuvI420img);
        }
        else if(Outformat == "YUV422sp")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3;
            int yuv422splen = Height*Width*2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(yuv422splen);
            unsigned char* rgb888 = Imgcc->Getdata();
            unsigned char* yuv422sp = Imgcc->Getdstdata();
            Imgcc->rgb2yuv422sp(rgb888,yuv422sp,Height,Width);
            Imgcc->rgb8882rgba(rgb888,this->rgbadata,Height,Width);
            Mat rgbimg = Mat(Height,Width,CV_8UC3);
            memcpy(rgbimg.data,rgb888,Height*Width*2);
            cvtColor(rgbimg,rgbimg,CV_RGB2BGR);
            imshow("rgb888",rgbimg);
            Mat yuv422spimg = Mat(Height*2,Width,CV_8UC1);
            memcpy(yuv422spimg.data,yuv422sp,Height*Width*2);
            imshow("yuv422sp",yuv422spimg);
        }
        else if(Outformat == "NV12")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3;
            int nv12len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(nv12len);
            unsigned char* rgb888 = Imgcc->Getdata();
            unsigned char* nv12 = Imgcc->Getdstdata();
            Imgcc->rgb2nv12(rgb888,nv12,Height,Width);
            Imgcc->rgb8882rgba(rgb888,this->rgbadata,Height,Width);
            Mat rgbimg = Mat(Height,Width,CV_8UC3);
            memcpy(rgbimg.data,rgb888,Height*Width*2);
            cvtColor(rgbimg,rgbimg,CV_RGB2BGR);
            imshow("rgb888",rgbimg);
            Mat nv12img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(nv12img.data,nv12,Height*Width*3/2);
            imshow("nv12",nv12img);
        }
        else if(Outformat == "RGB565")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3;
            int rgb565len = Height*Width;
            Imgcs->Setdata(path,datalen);
            Imgcs->Setdstdata(rgb565len);
            unsigned char* rgb888 = Imgcs->Getdata();
            unsigned short* rgb565 = Imgcs->Getdstdata();
            Imgcs->rgb2rgb565(rgb888,rgb565,Height,Width);
            Imgcc->rgb8882rgba(rgb888,this->rgbadata,Height,Width);
            Mat rgbimg = Mat(Height,Width,CV_8UC3);
            memcpy(rgbimg.data,rgb888,Height*Width*2);
            cvtColor(rgbimg,rgbimg,CV_RGB2BGR);
            imshow("rgb888",rgbimg);
            Mat rgb565img = Mat(Height,Width,CV_16SC1);
            memcpy(rgb565img.data,rgb565,Height*Width*2);
            imshow("rgb565",rgb565img);
        }
        else if(Outformat == "RGB888")
        {
            cout<<"same format"<<endl;
        }
        else if(Outformat == "RGBA8888")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3;
            int rgbalen = Height*Width*4;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(rgbalen);
            unsigned char* rgb888 = Imgcc->Getdata();
            unsigned char* rgba = Imgcc->Getdstdata();
            Imgcc->rgb8882rgba(rgb888,rgba,Height,Width);
            Imgcc->rgb8882rgba(rgb888,this->rgbadata,Height,Width);
            Mat rgbimg = Mat(Height,Width,CV_8UC3);
            memcpy(rgbimg.data,rgb888,Height*Width*2);
            cvtColor(rgbimg,rgbimg,CV_RGB2BGR);
            imshow("rgb888",rgbimg);
            Mat rgbaimg = Mat(Height,Width,CV_8UC4);
            memcpy(rgbaimg.data,rgba,Height*Width*4);
            cvtColor(rgbaimg,rgbaimg,CV_RGBA2BGRA);
            imshow("rgba",rgbaimg);
        }
        else {
            cout<<"Invalid Input"<<endl;
        }
        QImage Qimg;
        Qimg = QImage(this->rgbadata,Width,Height,Width*4,QImage::Format_RGBA8888);
        QPixmap pix(QPixmap::fromImage(Qimg));
        pix.scaled(ui->Label_img->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->Label_img->setScaledContents(true);
        ui->Label_img->setPixmap(pix);
        ui->Label_img->show();
    }
    else if(Inputformat == "RGBA8888")
    {
        if(Outformat == "YUVI420")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*4;
            int YUVI420len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(YUVI420len);
            unsigned char* rgba = Imgcc->Getdata();
            unsigned char* yuvI420 = Imgcc->Getdstdata();
            Imgcc->rgba2yuvI420(rgba,yuvI420,Height,Width);
            memcpy(this->rgbadata,rgba,Height*Width*4);
            Mat rgbaimg = Mat(Height,Width,CV_8UC4);
            memcpy(rgbaimg.data,rgba,Height*Width*4);
            cvtColor(rgbaimg,rgbaimg,CV_RGBA2BGRA);
            imshow("rgba",rgbaimg);
            Mat yuvI420img = Mat(Height*3/2,Width,CV_8UC1);
            memcpy(yuvI420img.data,yuvI420,Height*Width*3/2);
            imshow("yuvI420",yuvI420img);
        }
        else if(Outformat == "YUV422sp")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*4;
            int yuv422splen = Height*Width*2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(yuv422splen);
            unsigned char* rgba = Imgcc->Getdata();
            unsigned char* yuv422sp = Imgcc->Getdstdata();
            Imgcc->rgba2yuv422sp(rgba,yuv422sp,Height,Width);
            memcpy(this->rgbadata,rgba,Height*Width*4);
            Mat rgbaimg = Mat(Height,Width,CV_8UC4);
            memcpy(rgbaimg.data,rgba,Height*Width*4);
            cvtColor(rgbaimg,rgbaimg,CV_RGBA2BGRA);
            imshow("rgba",rgbaimg);
            Mat yuv422spimg = Mat(Height*2,Width,CV_8UC1);
            memcpy(yuv422spimg.data,yuv422sp,Height*Width*2);
            imshow("yuv422sp",yuv422spimg);
        }
        else if(Outformat == "NV12")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*4;
            int nv12len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(nv12len);
            unsigned char* rgba = Imgcc->Getdata();
            unsigned char* nv12 = Imgcc->Getdstdata();
            Imgcc->rgba2nv12(rgba,nv12,Height,Width);
            memcpy(this->rgbadata,rgba,Height*Width*4);
            Mat rgbaimg = Mat(Height,Width,CV_8UC4);
            memcpy(rgbaimg.data,rgba,Height*Width*4);
            cvtColor(rgbaimg,rgbaimg,CV_RGBA2BGRA);
            imshow("rgba",rgbaimg);
            Mat nv12img = Mat(Height*2,Width,CV_8UC1);
            memcpy(nv12img.data,nv12,Height*Width*3/2);
            imshow("nv12",nv12img);
        }
        else if(Outformat == "RGB565")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*4;
            int rgb565len = Height*Width;
            Imgcs->Setdata(path,datalen);
            Imgcs->Setdstdata(rgb565len);
            unsigned char* rgba = Imgcs->Getdata();
            unsigned short* rgb565 = Imgcs->Getdstdata();
            Imgcs->rgba2rgb565(rgba,rgb565,Height,Width);
            memcpy(this->rgbadata,rgba,Height*Width*4);
            Mat rgbaimg = Mat(Height,Width,CV_8UC4);
            memcpy(rgbaimg.data,rgba,Height*Width*4);
            cvtColor(rgbaimg,rgbaimg,CV_RGBA2BGRA);
            imshow("rgba",rgbaimg);
            Mat rgb565img = Mat(Height,Width,CV_16SC1);
            memcpy(rgb565img.data,rgb565,Height*Width*2);
            imshow("rgb565",rgb565img);
        }
        else if(Outformat == "RGB888")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*4;
            int rgb888len = Height*Width*3;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(rgb888len);
            unsigned char* rgba = Imgcc->Getdata();
            unsigned char* rgb888 = Imgcc->Getdstdata();
            Imgcc->rgba2rgb(rgba,rgb888,Height,Width);
            memcpy(this->rgbadata,rgba,Height*Width*4);
            Mat rgbaimg = Mat(Height,Width,CV_8UC4);
            memcpy(rgbaimg.data,rgba,Height*Width*4);
            cvtColor(rgbaimg,rgbaimg,CV_RGBA2BGRA);
            imshow("rgba",rgbaimg);
            Mat rgbimg = Mat(Height,Width,CV_8UC3);
            memcpy(rgbimg.data,rgb888,Height*Width*3);
            cvtColor(rgbimg,rgbimg,CV_RGB2BGR);
            imshow("rgb888",rgbimg);
        }
        else if(Outformat == "RGBA8888")
        {
            cout<<"same format"<<endl;
        }
        else {
            cout<<"Invalid format"<<endl;
        }
        QImage Qimg;
        Qimg = QImage(this->rgbadata,Width,Height,Width*4,QImage::Format_RGBA8888);
        QPixmap pix(QPixmap::fromImage(Qimg));
        pix.scaled(ui->Label_img->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->Label_img->setScaledContents(true);
        ui->Label_img->setPixmap(pix);
        ui->Label_img->show();
    }
    else {
        cout<<"Invalid Inputformat"<<endl;
    }
}

void MainWindow::on_Button_saveimg_clicked()
{
    QString Inputformat = ui->combox_Inputformat->currentText();
    QString Outformat = ui->comboBox_Outputformat->currentText();
    int Height = ui->LineEdit_Height->text().toInt();
    int Width = ui->lineEdit_Width->text().toInt();
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,tr("Open Config"), "", tr("Config Files (*)"));
    string pngname = fileName.toStdString();
    int pos = pngname.find_last_of('.');
    if(pos != fileName.size())
        pngname = pngname.substr(0,pos);
    pngname += ".png";
    cout<<pngname<<endl;
    if(Inputformat == "YUVI420")
    {
        if(Outformat == "YUVI420")
        {
            cout<<"same format"<<endl;
        }
        else if(Outformat == "YUV422sp")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int yuv422splen = Height*Width*2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(yuv422splen);
            unsigned char* yuvI420 = Imgcc->Getdata();
            unsigned char* yuv422sp = Imgcc->Getdstdata();
            Imgcc->yuvI4202yuv422sp(yuvI420,yuv422sp,Height,Width);
            Imgcc->Savedstdata(fileName.toStdString(),Height*Width*2);
        }
        else if(Outformat == "NV12")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int nv12len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(nv12len);
            unsigned char* yuvI420 = Imgcc->Getdata();
            unsigned char* nv12 = Imgcc->Getdstdata();
            Imgcc->yuvI4202nv12(yuvI420,nv12,Height,Width);
            Imgcc->Savedstdata(fileName.toStdString(),Height*Width*2);
        }
        else if(Outformat == "RGB565")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int rgb565len = Height*Width*3/2;
            Imgcs->Setdata(path,datalen);
            Imgcs->Setdstdata(rgb565len);
            unsigned char* yuvI420 = Imgcs->Getdata();
            unsigned short* rgb565 = Imgcs->Getdstdata();
            Imgcs->yuvI4202rgb565(yuvI420,rgb565,Height,Width);
            Imgcs->Savedstdata(fileName.toStdString(),Height*Width);
        }
        else if(Outformat == "RGB888")
        {
            if(ui->savepng->isChecked())
            {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*3/2;
                int rgb888len = Height*Width*3;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgb888len);
                unsigned char* yuvI420 = Imgcc->Getdata();
                unsigned char* rgb888 = Imgcc->Getdstdata();
                Imgcc->yuvI4202rgb888(yuvI420,rgb888,Height,Width);
                Imgcc->Savedstdata(pngname,Height*Width*3);
            }
            else {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*3/2;
                int rgb888len = Height*Width*3;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgb888len);
                unsigned char* yuvI420 = Imgcc->Getdata();
                unsigned char* rgb888 = Imgcc->Getdstdata();
                Imgcc->yuvI4202rgb888(yuvI420,rgb888,Height,Width);
                Imgcc->Savedstdata(fileName.toStdString(),Height*Width*3);
            }
        }
        else if(Outformat == "RGBA8888")
        {
            if(ui->savepng->isChecked())
            {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*3/2;
                int rgbalen = Height*Width*4;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgbalen);
                unsigned char* yuvI420 = Imgcc->Getdata();
                unsigned char* rgba = Imgcc->Getdstdata();
                Imgcc->yuvI4202RGB32(yuvI420,rgba,Height,Width);
                Imgcc->Savedstdata(pngname,Height*Width*4);
            }
            else {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*3/2;
                int rgbalen = Height*Width*4;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgbalen);
                unsigned char* yuvI420 = Imgcc->Getdata();
                unsigned char* rgba = Imgcc->Getdstdata();
                Imgcc->yuvI4202RGB32(yuvI420,rgba,Height,Width);
                Imgcc->Savedstdata(fileName.toStdString(),Height*Width*4);
            }
        }
        else {
            cout<<"Invalid Output"<<endl;
        }
    }
    else if(Inputformat == "YUV422sp")
    {
        if(Outformat == "YUVI420")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*2;
            int YUVI420len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(YUVI420len);
            unsigned char* yuv422sp = Imgcc->Getdata();
            unsigned char* yuvI420 = Imgcc->Getdstdata();
            Imgcc->yuv422sp2yuvI420(yuv422sp,yuvI420,Height,Width);
            Imgcc->Savedstdata(fileName.toStdString(),Height*Width*3/2);
        }
        else if(Outformat == "YUV422sp")
        {
            cout<<"same image"<<endl;
        }
        else if(Outformat == "NV12")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*2;
            int NV12len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(NV12len);
            unsigned char* yuv422sp = Imgcc->Getdata();
            unsigned char* NV12 = Imgcc->Getdstdata();
            Imgcc->yuv422sp2nv12(yuv422sp,NV12,Height,Width);
            Imgcc->Savedstdata(fileName.toStdString(),Height*Width*3/2);
        }
        else if(Outformat == "RGB565")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*2;
            int rgb565len = Height*Width;
            Imgcs->Setdata(path,datalen);
            Imgcs->Setdstdata(rgb565len);
            unsigned char* yuv422sp = Imgcs->Getdata();
            unsigned short* rgb565 = Imgcs->Getdstdata();
            Imgcs->yuv422sp2rgb565(yuv422sp,rgb565,Height,Width);
            Imgcs->Savedstdata(fileName.toStdString(),Height*Width);
        }
        else if(Outformat == "RGB888")
        {
            if(ui->savepng->isChecked())
            {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*2;
                int rgb888len = Height*Width*3;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgb888len);
                unsigned char* yuv422sp = Imgcc->Getdata();
                unsigned char* rgb888 = Imgcc->Getdstdata();
                Imgcc->yuv422sp2rgb24(yuv422sp,rgb888,Height,Width);
                Imgcc->Savedstdata(pngname,Height*Width*3);
            }
            else {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*2;
                int rgb888len = Height*Width*3;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgb888len);
                unsigned char* yuv422sp = Imgcc->Getdata();
                unsigned char* rgb888 = Imgcc->Getdstdata();
                Imgcc->yuv422sp2rgb24(yuv422sp,rgb888,Height,Width);
                Imgcc->Savedstdata(fileName.toStdString(),Height*Width*3);
            }
        }
        else if(Outformat == "RGBA8888")
        {
            if(ui->savepng->isChecked())
            {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*2;
                int rgbalen = Height*Width*4;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgbalen);
                unsigned char* yuv422sp = Imgcc->Getdata();
                unsigned char* rgba = Imgcc->Getdstdata();
                Imgcc->yuv422sp2rgb32(yuv422sp,rgba,Height,Width);
                Imgcc->Savedstdata(pngname,Height*Width*4);
            }
            else {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*2;
                int rgbalen = Height*Width*4;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgbalen);
                unsigned char* yuv422sp = Imgcc->Getdata();
                unsigned char* rgba = Imgcc->Getdstdata();
                Imgcc->yuv422sp2rgb32(yuv422sp,rgba,Height,Width);
                Imgcc->Savedstdata(fileName.toStdString(),Height*Width*4);
            }
        }
        else {
            cout<<"Invalid Outputformat"<<endl;
        }
    }
    else if(Inputformat == "NV12")
    {
        if(Outformat == "YUVI420")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int YUVI420len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(YUVI420len);
            unsigned char* nv12 = Imgcc->Getdata();
            unsigned char* yuvI420 = Imgcc->Getdstdata();
            Imgcc->NV122yuvI420(nv12,yuvI420,Height,Width);
            Imgcc->Savedstdata(fileName.toStdString(),Height*Width*3/2);
        }
        else if(Outformat == "YUV422sp")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int yuv422splen = Height*Width*2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(yuv422splen);
            unsigned char* nv12 = Imgcc->Getdata();
            unsigned char* yuv422sp = Imgcc->Getdstdata();
            Imgcc->NV1222yuv422sp(nv12,yuv422sp,Height,Width);
            Imgcc->Savedstdata(fileName.toStdString(),Height*Width*3/2);
        }
        else if(Outformat == "NV12")
        {
            cout<<"same format"<<endl;
        }
        else if(Outformat == "RGB565")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3/2;
            int rgb565len = Height*Width;
            Imgcs->Setdata(path,datalen);
            Imgcs->Setdstdata(rgb565len);
            unsigned char* nv12 = Imgcs->Getdata();
            unsigned short* rgb565 = Imgcs->Getdstdata();
            Imgcs->NV122RGB565(nv12,rgb565,Height,Width);
            Imgcs->Savedstdata(fileName.toStdString(),Height*Width);
        }
        else if(Outformat == "RGB888")
        {
            if(ui->savepng->isChecked())
            {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*3/2;
                int rgbalen = Height*Width*3;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgbalen);
                unsigned char* nv12 = Imgcc->Getdata();
                unsigned char* rgb = Imgcc->Getdstdata();
                Imgcc->NV122RGB(nv12,rgb,Height,Width);
                Imgcc->Savedstdata(pngname,Height*Width*3);
            }
            else {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*3/2;
                int rgbalen = Height*Width*3;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgbalen);
                unsigned char* nv12 = Imgcc->Getdata();
                unsigned char* rgb = Imgcc->Getdstdata();
                Imgcc->NV122RGB(nv12,rgb,Height,Width);
                Imgcc->Savedstdata(fileName.toStdString(),Height*Width*3);
            }
        }
        else if(Outformat == "RGBA8888")
        {
            if(ui->savepng->isChecked())
            {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*3/2;
                int rgbalen = Height*Width*4;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgbalen);
                unsigned char* nv12 = Imgcc->Getdata();
                unsigned char* rgba = Imgcc->Getdstdata();
                Imgcc->NV122RGBA(nv12,rgba,Height,Width);
                Imgcc->Savedstdata(pngname,Height*Width*4);
            }
            else {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*3/2;
                int rgbalen = Height*Width*4;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgbalen);
                unsigned char* nv12 = Imgcc->Getdata();
                unsigned char* rgba = Imgcc->Getdstdata();
                Imgcc->NV122RGBA(nv12,rgba,Height,Width);
                Imgcc->Savedstdata(fileName.toStdString(),Height*Width*4);
            }
        }
        else {
            cout<<"Invalid Outputformat"<<endl;
        }
    }
    else if(Inputformat == "RGB565")
    {
        if(Outformat == "YUVI420")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width;
            int YUVI420len = Height*Width*3/2;
            Imgsc->Setdata(path,datalen);
            Imgsc->Setdstdata(YUVI420len);
            unsigned short* rgb565 = Imgsc->Getdata();
            unsigned char* yuvI420 = Imgsc->Getdstdata();
            Imgsc->rgb5652yuvI420(rgb565,yuvI420,Height,Width);
            Imgsc->Savedstdata(fileName.toStdString(),Height*Width*3/2);
        }
        else if(Outformat == "YUV422sp")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width;
            int yuv422splen = Height*Width*2;
            Imgsc->Setdata(path,datalen);
            Imgsc->Setdstdata(yuv422splen);
            unsigned short* rgb565 = Imgsc->Getdata();
            unsigned char* yuv422sp = Imgsc->Getdstdata();
            Imgsc->rgb5652yuv422sp(rgb565,yuv422sp,Height,Width);
            Imgsc->Savedstdata(fileName.toStdString(),Height*Width*2);
        }
        else if(Outformat == "NV12")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width;
            int nv12len = Height*Width*3/2;
            Imgsc->Setdata(path,datalen);
            Imgsc->Setdstdata(nv12len);
            unsigned short* rgb565 = Imgsc->Getdata();
            unsigned char* nv12 = Imgsc->Getdstdata();
            Imgsc->rgb5652nv12(rgb565,nv12,Height,Width);
            Imgsc->Savedstdata(fileName.toStdString(),Height*Width*3/2);
        }
        else if(Outformat == "RGB565")
        {
            cout<<"same format"<<endl;
        }
        else if(Outformat == "RGB888")
        {
            if(ui->savepng->isChecked())
            {
                string path = this->file_path.toStdString();
                int datalen = Height*Width;
                int rgb888len = Height*Width*3;
                Imgsc->Setdata(path,datalen);
                Imgsc->Setdstdata(rgb888len);
                unsigned short* rgb565 = Imgsc->Getdata();
                unsigned char* rgb888 = Imgsc->Getdstdata();
                Imgsc->rgb5652rgb888(rgb565,rgb888,Height,Width);
                Imgsc->Savedstdata(fileName.toStdString(),Height*Width*3);
            }
            else {
                string path = this->file_path.toStdString();
                int datalen = Height*Width;
                int rgb888len = Height*Width*3;
                Imgsc->Setdata(path,datalen);
                Imgsc->Setdstdata(rgb888len);
                unsigned short* rgb565 = Imgsc->Getdata();
                unsigned char* rgb888 = Imgsc->Getdstdata();
                Imgsc->rgb5652rgb888(rgb565,rgb888,Height,Width);
                Imgsc->Savedstdata(pngname,Height*Width*3);
            }
        }
        else if(Outformat == "RGBA8888")
        {
            if(ui->savepng->isChecked())
            {
                string path = this->file_path.toStdString();
                int datalen = Height*Width;
                int rgbalen = Height*Width*4;
                Imgsc->Setdata(path,datalen);
                Imgsc->Setdstdata(rgbalen);
                unsigned short* rgb565 = Imgsc->Getdata();
                unsigned char* rgba = Imgsc->Getdstdata();
                Imgsc->rgb5652rgba(rgb565,rgba,Height,Width);
                Imgsc->Savedstdata(fileName.toStdString(),Height*Width*4);
            }
            else {
                string path = this->file_path.toStdString();
                int datalen = Height*Width;
                int rgbalen = Height*Width*4;
                Imgsc->Setdata(path,datalen);
                Imgsc->Setdstdata(rgbalen);
                unsigned short* rgb565 = Imgsc->Getdata();
                unsigned char* rgba = Imgsc->Getdstdata();
                Imgsc->rgb5652rgba(rgb565,rgba,Height,Width);
                Imgsc->Savedstdata(pngname,Height*Width*4);
            }
        }
        else {
            cout<<"Invalid Input"<<endl;
        }
    }
    else if(Inputformat == "RGB888")
    {
        if(Outformat == "YUVI420")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3;
            int YUVI420len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(YUVI420len);
            unsigned char* rgb888 = Imgcc->Getdata();
            unsigned char* yuvI420 = Imgcc->Getdstdata();
            Imgcc->rgb2yuvI420(rgb888,yuvI420,Height,Width);
            Imgcc->Savedstdata(fileName.toStdString(),Height*Width*3/2);
        }
        else if(Outformat == "YUV422sp")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3;
            int yuv422splen = Height*Width*2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(yuv422splen);
            unsigned char* rgb888 = Imgcc->Getdata();
            unsigned char* yuv422sp = Imgcc->Getdstdata();
            Imgcc->rgb2yuv422sp(rgb888,yuv422sp,Height,Width);
            Imgcc->Savedstdata(fileName.toStdString(),Height*Width*2);
        }
        else if(Outformat == "NV12")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3;
            int nv12len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(nv12len);
            unsigned char* rgb888 = Imgcc->Getdata();
            unsigned char* nv12 = Imgcc->Getdstdata();
            Imgcc->rgb2nv12(rgb888,nv12,Height,Width);
            Imgcc->Savedstdata(fileName.toStdString(),Height*Width*3/2);
        }
        else if(Outformat == "RGB565")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*3;
            int rgb565len = Height*Width;
            Imgcs->Setdata(path,datalen);
            Imgcs->Setdstdata(rgb565len);
            unsigned char* rgb888 = Imgcs->Getdata();
            unsigned short* rgb565 = Imgcs->Getdstdata();
            Imgcs->rgb2rgb565(rgb888,rgb565,Height,Width);
            Imgcs->Savedstdata(fileName.toStdString(),Height*Width);
        }
        else if(Outformat == "RGB888")
        {
            cout<<"same format"<<endl;
        }
        else if(Outformat == "RGBA8888")
        {
            if(ui->savepng->isChecked())
            {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*3;
                int rgbalen = Height*Width*4;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgbalen);
                unsigned char* rgb888 = Imgcc->Getdata();
                unsigned char* rgba = Imgcc->Getdstdata();
                Imgcc->rgb8882rgba(rgb888,rgba,Height,Width);
                Imgcc->Savedstdata(pngname,Height*Width*4);
            }
            else {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*3;
                int rgbalen = Height*Width*4;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgbalen);
                unsigned char* rgb888 = Imgcc->Getdata();
                unsigned char* rgba = Imgcc->Getdstdata();
                Imgcc->rgb8882rgba(rgb888,rgba,Height,Width);
                Imgcc->Savedstdata(fileName.toStdString(),Height*Width*4);
            }
        }
        else {
            cout<<"Invalid Input"<<endl;
        }
    }
    else if(Inputformat == "RGBA8888")
    {
        if(Outformat == "YUVI420")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*4;
            int YUVI420len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(YUVI420len);
            unsigned char* rgba = Imgcc->Getdata();
            unsigned char* yuvI420 = Imgcc->Getdstdata();
            Imgcc->rgba2yuvI420(rgba,yuvI420,Height,Width);
            Imgcc->Savedstdata(fileName.toStdString(),Height*Width*3/2);
        }
        else if(Outformat == "YUV422sp")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*4;
            int yuv422splen = Height*Width*2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(yuv422splen);
            unsigned char* rgba = Imgcc->Getdata();
            unsigned char* yuv422sp = Imgcc->Getdstdata();
            Imgcc->rgba2yuv422sp(rgba,yuv422sp,Height,Width);
            Imgcc->Savedstdata(fileName.toStdString(),Height*Width*2);
        }
        else if(Outformat == "NV12")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*4;
            int nv12len = Height*Width*3/2;
            Imgcc->Setdata(path,datalen);
            Imgcc->Setdstdata(nv12len);
            unsigned char* rgba = Imgcc->Getdata();
            unsigned char* nv12 = Imgcc->Getdstdata();
            Imgcc->rgba2nv12(rgba,nv12,Height,Width);
            Imgcc->Savedstdata(fileName.toStdString(),Height*Width*3/2);
        }
        else if(Outformat == "RGB565")
        {
            string path = this->file_path.toStdString();
            int datalen = Height*Width*4;
            int rgb565len = Height*Width;
            Imgcs->Setdata(path,datalen);
            Imgcs->Setdstdata(rgb565len);
            unsigned char* rgba = Imgcs->Getdata();
            unsigned short* rgb565 = Imgcs->Getdstdata();
            Imgcs->rgba2rgb565(rgba,rgb565,Height,Width);
            Imgcs->Savedstdata(fileName.toStdString(),Height*Width);
        }
        else if(Outformat == "RGB888")
        {
            if(ui->savepng->isChecked())
            {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*4;
                int rgb888len = Height*Width*3;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgb888len);
                unsigned char* rgba = Imgcc->Getdata();
                unsigned char* rgb888 = Imgcc->Getdstdata();
                Imgcc->rgba2rgb(rgba,rgb888,Height,Width);
                Imgcc->Savedstdata(pngname,Height*Width*3);
            }
            else {
                string path = this->file_path.toStdString();
                int datalen = Height*Width*4;
                int rgb888len = Height*Width*3;
                Imgcc->Setdata(path,datalen);
                Imgcc->Setdstdata(rgb888len);
                unsigned char* rgba = Imgcc->Getdata();
                unsigned char* rgb888 = Imgcc->Getdstdata();
                Imgcc->rgba2rgb(rgba,rgb888,Height,Width);
                Imgcc->Savedstdata(fileName.toStdString(),Height*Width*3);
            }
        }
        else if(Outformat == "RGBA8888")
        {
            cout<<"same format"<<endl;
        }
        else {
            cout<<"Invalid format"<<endl;
        }
    }
    else {
        cout<<"Invalid Inputformat"<<endl;
    }
}

//show img diff part
//show pic diff in window
void MainWindow::showdiff(int Height,int Width,QString format,int times)
{
    QString format1 = ui->Diffformat1->currentText();
    QString format2 = ui->Diffformat2->currentText();
    if(format == "Gray")
    {
        if(format1 == "RGB565"&&format2 == "RGB565")
        {
            unsigned char* graydiff = new unsigned char[Height*Width];
            unsigned char* rgba1 = simgdiff1->Getrgbadata();
            unsigned char* rgba2 = simgdiff2->Getrgbadata();
            simgdiff1->Imgdiffgray(rgba1,rgba2,graydiff,Height,Width);
            simgdiff1->ImgdiffTimes(graydiff,Height*Width,times);
            QImage Qimg;
            Qimg = QImage(graydiff,Width,Height,Width,QImage::Format_Grayscale8);
            QPixmap pix(QPixmap::fromImage(Qimg));
            pix.scaled(ui->Label_imgcmp_3->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->Label_imgcmp_3->setScaledContents(true);
            ui->Label_imgcmp_3->setPixmap(pix);
            ui->Label_imgcmp_3->show();
            delete [] graydiff;
        }
        else if(format1 != "RGB565"&&format2 == "RGB565")
        {
            unsigned char* graydiff = new unsigned char[Height*Width];
            unsigned char* rgba1 = uimgdiff1->Getrgbadata();
            unsigned char* rgba2 = simgdiff2->Getrgbadata();
            uimgdiff1->Imgdiffgray(rgba1,rgba2,graydiff,Height,Width);
            uimgdiff1->ImgdiffTimes(graydiff,Height*Width,times);
            QImage Qimg;
            Qimg = QImage(graydiff,Width,Height,Width,QImage::Format_Grayscale8);
            QPixmap pix(QPixmap::fromImage(Qimg));
            pix.scaled(ui->Label_imgcmp_3->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->Label_imgcmp_3->setScaledContents(true);
            ui->Label_imgcmp_3->setPixmap(pix);
            ui->Label_imgcmp_3->show();
            delete [] graydiff;
        }
        else if(format1 == "RGB565"&&format2 != "RGB565")
        {
            unsigned char* graydiff = new unsigned char[Height*Width];
            unsigned char* rgba1 = simgdiff1->Getrgbadata();
            unsigned char* rgba2 = uimgdiff2->Getrgbadata();
            simgdiff1->Imgdiffgray(rgba1,rgba2,graydiff,Height,Width);
            simgdiff1->ImgdiffTimes(graydiff,Height*Width,times);
            QImage Qimg;
            Qimg = QImage(graydiff,Width,Height,Width,QImage::Format_Grayscale8);
            QPixmap pix(QPixmap::fromImage(Qimg));
            pix.scaled(ui->Label_imgcmp_3->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->Label_imgcmp_3->setScaledContents(true);
            ui->Label_imgcmp_3->setPixmap(pix);
            ui->Label_imgcmp_3->show();
            delete [] graydiff;
        }
        else if(format1 != "RGB565"&&format2 != "RGB565")
        {
            unsigned char* graydiff = new unsigned char[Height*Width];
            unsigned char* rgba1 = uimgdiff1->Getrgbadata();
            unsigned char* rgba2 = uimgdiff2->Getrgbadata();
            uimgdiff1->Imgdiffgray(rgba1,rgba2,graydiff,Height,Width);
            uimgdiff1->ImgdiffTimes(graydiff,Height*Width,times);
            QImage Qimg;
            Qimg = QImage(graydiff,Width,Height,Width,QImage::Format_Grayscale8);
            QPixmap pix(QPixmap::fromImage(Qimg));
            pix.scaled(ui->Label_imgcmp_3->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->Label_imgcmp_3->setScaledContents(true);
            ui->Label_imgcmp_3->setPixmap(pix);
            ui->Label_imgcmp_3->show();
            delete [] graydiff;
        }
        else {
            cout<<"Wrong format"<<endl;
        }
    }
    else if(format == "RGB")
    {
        if(format1 == "RGB565"&&format2 == "RGB565")
        {
            unsigned char* rgbdiff = new unsigned char[Height*Width*3];
            unsigned char* rgba1 = simgdiff1->Getrgbadata();
            unsigned char* rgba2 = simgdiff2->Getrgbadata();
            simgdiff1->ImgdiffRGB(rgba1,rgba2,rgbdiff,Height,Width);
            simgdiff1->ImgdiffTimes(rgbdiff,Height*Width*3,times);
            QImage Qimg;
            Qimg = QImage(rgbdiff,Width,Height,Width*3,QImage::Format_RGB888);
            QPixmap pix(QPixmap::fromImage(Qimg));
            pix.scaled(ui->Label_imgcmp_3->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->Label_imgcmp_3->setScaledContents(true);
            ui->Label_imgcmp_3->setPixmap(pix);
            ui->Label_imgcmp_3->show();
            delete [] rgbdiff;
        }
        else if(format1 != "RGB565"&&format2 == "RGB565")
        {
            unsigned char* rgbdiff = new unsigned char[Height*Width*3];
            unsigned char* rgba1 = uimgdiff1->Getrgbadata();
            unsigned char* rgba2 = simgdiff2->Getrgbadata();
            uimgdiff1->ImgdiffRGB(rgba1,rgba2,rgbdiff,Height,Width);
            uimgdiff1->ImgdiffTimes(rgbdiff,Height*Width*3,times);
            QImage Qimg;
            Qimg = QImage(rgbdiff,Width,Height,Width*3,QImage::Format_RGB888);
            QPixmap pix(QPixmap::fromImage(Qimg));
            pix.scaled(ui->Label_imgcmp_3->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->Label_imgcmp_3->setScaledContents(true);
            ui->Label_imgcmp_3->setPixmap(pix);
            ui->Label_imgcmp_3->show();
            delete [] rgbdiff;
        }
        else if(format1 == "RGB565"&&format2 != "RGB565")
        {
            unsigned char* rgbdiff = new unsigned char[Height*Width*3];
            unsigned char* rgba1 = simgdiff1->Getrgbadata();
            unsigned char* rgba2 = uimgdiff2->Getrgbadata();
            simgdiff1->ImgdiffRGB(rgba1,rgba2,rgbdiff,Height,Width);
            simgdiff1->ImgdiffTimes(rgbdiff,Height*Width*3,times);
            QImage Qimg;
            Qimg = QImage(rgbdiff,Width,Height,Width*3,QImage::Format_RGB888);
            QPixmap pix(QPixmap::fromImage(Qimg));
            pix.scaled(ui->Label_imgcmp_3->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->Label_imgcmp_3->setScaledContents(true);
            ui->Label_imgcmp_3->setPixmap(pix);
            ui->Label_imgcmp_3->show();
            delete [] rgbdiff;
        }
        else if(format1 != "RGB565"&&format2 != "RGB565")
        {
            unsigned char* rgbdiff = new unsigned char[Height*Width*3];
            unsigned char* rgba1 = uimgdiff1->Getrgbadata();
            unsigned char* rgba2 = uimgdiff2->Getrgbadata();
            uimgdiff1->ImgdiffRGB(rgba1,rgba2,rgbdiff,Height,Width);
            uimgdiff1->ImgdiffTimes(rgbdiff,Height*Width*3,times);
            QImage Qimg;
            Qimg = QImage(rgbdiff,Width,Height,Width*3,QImage::Format_RGB888);
            QPixmap pix(QPixmap::fromImage(Qimg));
            pix.scaled(ui->Label_imgcmp_3->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            ui->Label_imgcmp_3->setScaledContents(true);
            ui->Label_imgcmp_3->setPixmap(pix);
            ui->Label_imgcmp_3->show();
            delete [] rgbdiff;
        }
        else {
            cout<<"wrong format"<<endl;
        }
    }
}

void MainWindow::on_imgcmp_1_clicked()
{
    QString str1  = QFileDialog::getOpenFileName(NULL,"标题",".","*");
    uimgdiff1->Setfilepath(str1);
    simgdiff1->Setfilepath(str1);
    //show file name
    string file_name = str1.toStdString();
    int pos = file_name.find_last_of('/');
    file_name = file_name.substr(pos+1);
    ui->diffimg1_lineedit->setText(QString::fromStdString(file_name));
}

void MainWindow::on_imgcmp_2_clicked()
{
    QString str1  = QFileDialog::getOpenFileName(NULL,"标题",".","*");
    uimgdiff2->Setfilepath(str1);
    simgdiff2->Setfilepath(str1);
    //show file name
    string file_name = str1.toStdString();
    int pos = file_name.find_last_of('/');
    file_name = file_name.substr(pos+1);
    ui->diffimg1_lineedit_2->setText(QString::fromStdString(file_name));
}


void MainWindow::on_Diffformat1_activated(const QString &arg1)
{
    QString format = ui->Diffformat1->currentText();
    int Height = ui->LineEdit_Height->text().toInt();
    int Width = ui->lineEdit_Width->text().toInt();
    unsigned char* diffrgba;
    //change format to rgba
    if(format == "YUVI420")
    {
        QString str = uimgdiff1->Getfilepath();
        uimgdiff1->Setdata(str,Height*Width*3/2);
        uimgdiff1->Setrgbadata(Height*Width*4);
        unsigned char* yuvI420 = uimgdiff1->Getdata();
        diffrgba = uimgdiff1->Getrgbadata();
        Imgss->yuvI4202RGB32(yuvI420,diffrgba,Height,Width);
    }
    else if(format == "YUV422SP")
    {
        QString str = uimgdiff1->Getfilepath();
        uimgdiff1->Setdata(str,Height*Width*2);
        uimgdiff1->Setrgbadata(Height*Width*4);
        unsigned char* yuv422sp = uimgdiff1->Getdata();
        diffrgba = uimgdiff1->Getrgbadata();
        Imgss->yuv422sp2rgb32(yuv422sp,diffrgba,Height,Width);
    }
    else if(format == "NV12")
    {
        QString str = uimgdiff1->Getfilepath();
        uimgdiff1->Setdata(str,Height*Width*3/2);
        uimgdiff1->Setrgbadata(Height*Width*4);
        unsigned char* nv12 = uimgdiff1->Getdata();
        diffrgba = uimgdiff1->Getrgbadata();
        Imgss->NV122RGBA(nv12,diffrgba,Height,Width);
    }
    else if(format == "RGB565")
    {
        QString str = simgdiff1->Getfilepath();
        simgdiff1->Setdata(str,Height*Width);
        simgdiff1->Setrgbadata(Height*Width*4);
        unsigned short* rgb565 = simgdiff1->Getdata();
        diffrgba = simgdiff1->Getrgbadata();
        Imgss->rgb5652rgba(rgb565,diffrgba,Height,Width);
    }
    else if(format == "RGB")
    {
        QString str = uimgdiff1->Getfilepath();
        uimgdiff1->Setdata(str,Height*Width*3);
        uimgdiff1->Setrgbadata(Height*Width*4);
        unsigned char* rgb = uimgdiff1->Getdata();
        diffrgba = uimgdiff1->Getrgbadata();
        Imgss->rgb8882rgba(rgb,diffrgba,Height,Width);
    }
    else if(format == "RGBA")
    {
        QString str = uimgdiff1->Getfilepath();
        uimgdiff1->Setdata(str,Height*Width*4);
        uimgdiff1->Setrgbadata(Height*Width*4);
        unsigned char* rgba = uimgdiff1->Getdata();
        diffrgba = uimgdiff1->Getrgbadata();
        memcpy(diffrgba,rgba,Height*Width*4);
    }
    else {
        cout<<"Invalid format"<<endl;
    }
    if(diffrgba != nullptr)
    {
        QImage Qimg;
        Qimg = QImage(diffrgba,Width,Height,Width*4,QImage::Format_RGBA8888);
        QPixmap pix(QPixmap::fromImage(Qimg));
        pix.scaled(ui->Label_imgcmp_1->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->Label_imgcmp_1->setScaledContents(true);
        ui->Label_imgcmp_1->setPixmap(pix);
        ui->Label_imgcmp_1->show();
    }
}

void MainWindow::on_Diffformat2_activated(const QString &arg1)
{
    QString format = ui->Diffformat2->currentText();
    int Height = ui->LineEdit_Height->text().toInt();
    int Width = ui->lineEdit_Width->text().toInt();
    unsigned char* diffrgba;
    //change format to rgba
    if(format == "YUVI420")
    {
        QString str = uimgdiff2->Getfilepath();
        uimgdiff2->Setdata(str,Height*Width*3/2);
        uimgdiff2->Setrgbadata(Height*Width*4);
        unsigned char* yuvI420 = uimgdiff2->Getdata();
        diffrgba = uimgdiff2->Getrgbadata();
        Imgss->yuvI4202RGB32(yuvI420,diffrgba,Height,Width);
    }
    else if(format == "YUV422SP")
    {
        QString str = uimgdiff2->Getfilepath();
        uimgdiff2->Setdata(str,Height*Width*2);
        uimgdiff2->Setrgbadata(Height*Width*4);
        unsigned char* yuv422sp = uimgdiff2->Getdata();
        diffrgba = uimgdiff2->Getrgbadata();
        Imgss->yuv422sp2rgb32(yuv422sp,diffrgba,Height,Width);
    }
    else if(format == "NV12")
    {
        QString str = uimgdiff2->Getfilepath();
        uimgdiff2->Setdata(str,Height*Width*3/2);
        uimgdiff2->Setrgbadata(Height*Width*4);
        unsigned char* nv12 = uimgdiff2->Getdata();
        diffrgba = uimgdiff2->Getrgbadata();
        Imgss->NV122RGBA(nv12,diffrgba,Height,Width);
    }
    else if(format == "RGB565")
    {
        QString str = simgdiff2->Getfilepath();
        simgdiff2->Setdata(str,Height*Width);
        simgdiff2->Setrgbadata(Height*Width*4);
        unsigned short* rgb565 = simgdiff2->Getdata();
        diffrgba = simgdiff2->Getrgbadata();
        Imgss->rgb5652rgba(rgb565,diffrgba,Height,Width);
    }
    else if(format == "RGB")
    {
        QString str = uimgdiff2->Getfilepath();
        uimgdiff2->Setdata(str,Height*Width*3);
        uimgdiff2->Setrgbadata(Height*Width*4);
        unsigned char* rgb = uimgdiff2->Getdata();
        diffrgba = uimgdiff2->Getrgbadata();
        Imgss->rgb8882rgba(rgb,diffrgba,Height,Width);
    }
    else if(format == "RGBA")
    {
        QString str = uimgdiff1->Getfilepath();
        uimgdiff1->Setdata(str,Height*Width*4);
        uimgdiff1->Setrgbadata(Height*Width*4);
        unsigned char* rgba = uimgdiff1->Getdata();
        diffrgba = uimgdiff1->Getrgbadata();
        memcpy(diffrgba,rgba,Height*Width*4);
    }
    else {
        cout<<"Invalid format"<<endl;
    }
    QImage Qimg;
    Qimg = QImage(diffrgba,Width,Height,Width*4,QImage::Format_RGBA8888);
    QPixmap pix(QPixmap::fromImage(Qimg));
    pix.scaled(ui->Label_imgcmp_2->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->Label_imgcmp_2->setScaledContents(true);
    ui->Label_imgcmp_2->setPixmap(pix);
    ui->Label_imgcmp_2->show();
}


void MainWindow::on_slider_times_actionTriggered(int action)
{
    ui->slider_times->setMinimum(1);
    ui->slider_times->setMaximum(10);
    connect(ui->slider_times,SIGNAL(valueChanged(int)),ui->spinBox_Time,SLOT(setValue(int)));
    QString format = ui->comboBox_diffformat->currentText();
    int Height = ui->LineEdit_Height->text().toInt();
    int Width = ui->lineEdit_Width->text().toInt();
    int time = ui->slider_times->value();
    showdiff(Height,Width,format,time);
}

void MainWindow::on_comboBox_diffformat_activated(const QString &arg1)
{
    QString format = ui->comboBox_diffformat->currentText();
    int Height = ui->LineEdit_Height->text().toInt();
    int Width = ui->lineEdit_Width->text().toInt();
    ui->slider_times->setValue(1);
    showdiff(Height,Width,format,1);
}

void MainWindow::on_spinBox_Time_valueChanged(const QString &arg1)
{
    ui->spinBox_Time->setMinimum(1);
    ui->spinBox_Time->setMaximum(10);
    connect(ui->spinBox_Time,SIGNAL(valueChanged(int)),ui->slider_times,SLOT(setValue(int)));
    QString format = ui->comboBox_diffformat->currentText();
    int Height = ui->LineEdit_Height->text().toInt();
    int Width = ui->lineEdit_Width->text().toInt();
    int time = ui->spinBox_Time->value();
    showdiff(Height,Width,format,time);
}

//encode and decode part
void MainWindow::on_EncodePath_clicked()
{
    QString str = QFileDialog::getOpenFileName(NULL,"标题",".","*");
    encodeinfo->Setsrc(str);
    string file_name = str.toStdString();
    int pos = file_name.find_last_of('/');
    file_name = file_name.substr(pos+1);
    ui->line_encodepath->setText(QString::fromStdString(file_name));
}

void MainWindow::on_saveEncodePath_clicked()
{
    QString str = QFileDialog::getSaveFileName(this,tr("Open Config"), "", tr("Config Files (*)"));
    encodeinfo->Setdst(str);
    string file_name = str.toStdString();
    string path = str.toStdString();
    int pos = file_name.find_last_of('/');
    file_name = file_name.substr(pos + 1);
    ui->line_saveencodepath->setText(QString::fromStdString(file_name));
}

void MainWindow::on_encodebutton_clicked()
{
    //./afbcenc -i lena.png -o lena.afb
    string str = QCoreApplication::applicationDirPath().toStdString();
    int pos = str.find_last_of('/');
    string file_path = str.substr(0,pos);
    file_path = file_path + "/tool/encode.sh";
    int suffixpos = str.find_last_of('.');
    string suffixstr = str.substr(suffixpos + 1);
    cout<<suffixstr<<"houzhui"<<endl;
    //if input a png img
    if(suffixstr == "png"||suffixstr == "PNG")
    {
        cout<<"png"<<endl;
        QString path = QString::fromStdString(file_path);
        QProcess *proc = new QProcess;
        QString inputimg = encodeinfo->Getsrc();
        QString outputimg = encodeinfo->Getdst();
        QStringList strs = {"-i",inputimg,"-o",outputimg};
        if (QProcess::execute(path,strs) < 0)
                qDebug() << "Failed to run";
    }
    else if(suffixstr == "yuv"){//should input width and height
        cout<<"yuv"<<endl;
        QString path = QString::fromStdString(file_path);
        QProcess *proc = new QProcess;
        QString inputimg = encodeinfo->Getsrc();
        QString outputimg = encodeinfo->Getdst();
        QString Height = ui->LineEdit_Height->text();
        QString Width = ui->lineEdit_Width->text();
        QStringList strs = {"-w",Width,"-h",Height,"-i",inputimg,"-o",outputimg};
        if (QProcess::execute(path,strs) < 0)
                qDebug() << "Failed to run";
    }
    else {
        qDebug()<<"please choose a png or yuv img";
    }
}

void MainWindow::on_DecodePath_clicked()
{
    QString str = QFileDialog::getOpenFileName(NULL,"标题",".","*");
    decodeinfo->Setsrc(str);
    string file_name = str.toStdString();
    int pos = file_name.find_last_of('/');
    file_name = file_name.substr(pos+1);
    ui->line_decodepath->setText(QString::fromStdString(file_name));
}

void MainWindow::on_saveDecodePath_clicked()
{
    QString str = QFileDialog::getSaveFileName(this,tr("Open Config"), "", tr("Config Files (*)"));
    decodeinfo->Setdst(str);
    string file_name = str.toStdString();
    string path = str.toStdString();
    int pos = file_name.find_last_of('/');
    file_name = file_name.substr(pos + 1);
    ui->line_savedecodepath->setText(QString::fromStdString(file_name));
}

void MainWindow::on_decodebutton_clicked()
{
    string str = QCoreApplication::applicationDirPath().toStdString();
    int pos = str.find_last_of('/');
    string file_path = str.substr(0,pos);
    file_path = file_path + "/tool/decode.sh";
    QString path = QString::fromStdString(file_path);
    QString inputimg = decodeinfo->Getsrc();
    QString outputimg = decodeinfo->Getdst();
    cout<<path.toStdString()<<endl;
    cout<<inputimg.toStdString()<<endl;
    cout<<outputimg.toStdString()<<endl;
    QStringList strs = {"-i",inputimg,"-o",outputimg};
    if (QProcess::execute(path,strs) < 0)
            qDebug() << "Failed to run";
}


void MainWindow::on_test_clicked()
{
    Imgcmp<unsigned char> *img = new Imgcmp<unsigned char>();
    QString path = "//home//weilon01//pic//pic2//nv12.yuv";
    int Height = 512;
    int Width = 512;
    int len = Height*Width*3/2;
    img->Setdata(path,len);

    delete img;
}

void MainWindow::on_comboBox_Outputformat_activated(const QString &arg1)
{
    QString Inputformat = ui->combox_Inputformat->currentText();
    QString Outformat = ui->comboBox_Outputformat->currentText();
    ui->lineEdit_imgformat->setText(Inputformat + "->" + Outformat);
}

void MainWindow::on_combox_Inputformat_activated(const QString &arg1)
{
    QString Inputformat = ui->combox_Inputformat->currentText();
    QString Outformat = ui->comboBox_Outputformat->currentText();
    ui->lineEdit_imgformat->setText(Inputformat + "->" + Outformat);
}

