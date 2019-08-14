#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "imgoperator.cpp"
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QProcess>
#include <string>
#include "imgcmp.cpp"
#include "encodeimg.h"
#include "decodeimg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_PicChange_clicked();

    void on_OpenFileButton_clicked();

    void on_Button_saveimg_clicked();

    void on_imgcmp_1_clicked();

    void on_imgcmp_2_clicked();

    void on_slider_times_actionTriggered(int action);

    void on_comboBox_diffformat_activated(const QString &arg1);

    void on_spinBox_Time_valueChanged(const QString &arg1);

    void on_EncodePath_clicked();

    void on_saveEncodePath_clicked();

    void on_encodebutton_clicked();

    void on_DecodePath_clicked();

    void on_saveDecodePath_clicked();

    void on_decodebutton_clicked();

    void on_test_clicked();

    void on_lineEdit_imgformat_cursorPositionChanged(int arg1, int arg2);

    void on_comboBox_Outputformat_activated(const QString &arg1);

    void on_combox_Inputformat_activated(const QString &arg1);

    void on_Diffformat1_activated(const QString &arg1);

    void on_Diffformat2_activated(const QString &arg1);

private:
    void Setrgbadata(int datalength);

    bool Freergbadata();

    void Setdiffdata(int datalen);

    bool Freediffdata();

    bool Savergbadatafile(std::string path,int datalen) const;

    void showdiff(int Height,int Width,QString format,int times);

private:
    unsigned char* rgbadata;//show on Label_image
    unsigned char* diffdata;//show on Label_cmoimg_3
    Imgoperator<unsigned char,unsigned short> *Imgcs;
    Imgoperator<unsigned char,unsigned char> *Imgcc;
    Imgoperator<unsigned short,unsigned short> *Imgss;
    Imgoperator<unsigned short,unsigned char> *Imgsc;
    QString file_path;//open file path
    Imgcmp<unsigned char>* uimgdiff1;
    Imgcmp<unsigned char>* uimgdiff2;
    Imgcmp<unsigned short>* simgdiff1;
    Imgcmp<unsigned short>* simgdiff2;
    encodeimg* encodeinfo;
    decodeimg* decodeinfo;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
