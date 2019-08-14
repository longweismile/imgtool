/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *LabelHeight;
    QLabel *LabelWidth;
    QLineEdit *LineEdit_Height;
    QLineEdit *lineEdit_Width;
    QPushButton *PicChange;
    QPushButton *OpenFileButton;
    QLineEdit *lineEdit_FileName;
    QComboBox *combox_Inputformat;
    QLineEdit *lineEdit_imgformat;
    QLabel *label;
    QPushButton *Button_saveimg;
    QGraphicsView *graphicsView;
    QLabel *Label_img;
    QLabel *Label_imgcmp_1;
    QGraphicsView *graphicsView_2;
    QGraphicsView *graphicsView_3;
    QLabel *Label_imgcmp_2;
    QPushButton *imgcmp_1;
    QPushButton *imgcmp_2;
    QLabel *Label_imgcmp_3;
    QGraphicsView *graphicsView_4;
    QComboBox *comboBox_diffformat;
    QSlider *slider_times;
    QSpinBox *spinBox_Time;
    QPushButton *EncodePath;
    QLineEdit *line_encodepath;
    QPushButton *saveEncodePath;
    QLineEdit *line_saveencodepath;
    QPushButton *encodebutton;
    QPushButton *DecodePath;
    QPushButton *decodebutton;
    QLineEdit *line_decodepath;
    QPushButton *saveDecodePath;
    QLineEdit *line_savedecodepath;
    QComboBox *comboBox_Outputformat;
    QPushButton *test;
    QRadioButton *savepng;
    QComboBox *Diffformat1;
    QComboBox *Diffformat2;
    QLineEdit *diffimg1_lineedit;
    QLineEdit *diffimg1_lineedit_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFormat_change;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(895, 750);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        LabelHeight = new QLabel(centralWidget);
        LabelHeight->setObjectName(QString::fromUtf8("LabelHeight"));
        LabelHeight->setGeometry(QRect(20, 100, 101, 31));
        LabelHeight->setFrameShape(QFrame::Panel);
        LabelHeight->setFrameShadow(QFrame::Sunken);
        LabelWidth = new QLabel(centralWidget);
        LabelWidth->setObjectName(QString::fromUtf8("LabelWidth"));
        LabelWidth->setGeometry(QRect(20, 150, 101, 31));
        LabelWidth->setFrameShape(QFrame::Panel);
        LabelWidth->setFrameShadow(QFrame::Sunken);
        LineEdit_Height = new QLineEdit(centralWidget);
        LineEdit_Height->setObjectName(QString::fromUtf8("LineEdit_Height"));
        LineEdit_Height->setGeometry(QRect(130, 100, 141, 31));
        lineEdit_Width = new QLineEdit(centralWidget);
        lineEdit_Width->setObjectName(QString::fromUtf8("lineEdit_Width"));
        lineEdit_Width->setGeometry(QRect(130, 150, 141, 31));
        PicChange = new QPushButton(centralWidget);
        PicChange->setObjectName(QString::fromUtf8("PicChange"));
        PicChange->setGeometry(QRect(20, 300, 251, 35));
        OpenFileButton = new QPushButton(centralWidget);
        OpenFileButton->setObjectName(QString::fromUtf8("OpenFileButton"));
        OpenFileButton->setGeometry(QRect(20, 10, 251, 35));
        lineEdit_FileName = new QLineEdit(centralWidget);
        lineEdit_FileName->setObjectName(QString::fromUtf8("lineEdit_FileName"));
        lineEdit_FileName->setGeometry(QRect(20, 50, 251, 35));
        combox_Inputformat = new QComboBox(centralWidget);
        combox_Inputformat->addItem(QString());
        combox_Inputformat->addItem(QString());
        combox_Inputformat->addItem(QString());
        combox_Inputformat->addItem(QString());
        combox_Inputformat->addItem(QString());
        combox_Inputformat->addItem(QString());
        combox_Inputformat->addItem(QString());
        combox_Inputformat->setObjectName(QString::fromUtf8("combox_Inputformat"));
        combox_Inputformat->setGeometry(QRect(20, 200, 120, 35));
        combox_Inputformat->setFocusPolicy(Qt::ClickFocus);
        lineEdit_imgformat = new QLineEdit(centralWidget);
        lineEdit_imgformat->setObjectName(QString::fromUtf8("lineEdit_imgformat"));
        lineEdit_imgformat->setGeometry(QRect(20, 250, 251, 35));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(350, 269, 211, 21));
        Button_saveimg = new QPushButton(centralWidget);
        Button_saveimg->setObjectName(QString::fromUtf8("Button_saveimg"));
        Button_saveimg->setGeometry(QRect(300, 300, 111, 35));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(300, 10, 256, 256));
        Label_img = new QLabel(centralWidget);
        Label_img->setObjectName(QString::fromUtf8("Label_img"));
        Label_img->setGeometry(QRect(300, 10, 256, 256));
        Label_imgcmp_1 = new QLabel(centralWidget);
        Label_imgcmp_1->setObjectName(QString::fromUtf8("Label_imgcmp_1"));
        Label_imgcmp_1->setGeometry(QRect(20, 350, 256, 256));
        graphicsView_2 = new QGraphicsView(centralWidget);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(20, 350, 256, 256));
        graphicsView_3 = new QGraphicsView(centralWidget);
        graphicsView_3->setObjectName(QString::fromUtf8("graphicsView_3"));
        graphicsView_3->setGeometry(QRect(300, 350, 256, 256));
        Label_imgcmp_2 = new QLabel(centralWidget);
        Label_imgcmp_2->setObjectName(QString::fromUtf8("Label_imgcmp_2"));
        Label_imgcmp_2->setGeometry(QRect(300, 350, 256, 256));
        imgcmp_1 = new QPushButton(centralWidget);
        imgcmp_1->setObjectName(QString::fromUtf8("imgcmp_1"));
        imgcmp_1->setGeometry(QRect(20, 610, 130, 35));
        imgcmp_2 = new QPushButton(centralWidget);
        imgcmp_2->setObjectName(QString::fromUtf8("imgcmp_2"));
        imgcmp_2->setGeometry(QRect(300, 610, 130, 35));
        Label_imgcmp_3 = new QLabel(centralWidget);
        Label_imgcmp_3->setObjectName(QString::fromUtf8("Label_imgcmp_3"));
        Label_imgcmp_3->setGeometry(QRect(580, 350, 256, 256));
        graphicsView_4 = new QGraphicsView(centralWidget);
        graphicsView_4->setObjectName(QString::fromUtf8("graphicsView_4"));
        graphicsView_4->setGeometry(QRect(580, 350, 256, 256));
        comboBox_diffformat = new QComboBox(centralWidget);
        comboBox_diffformat->addItem(QString());
        comboBox_diffformat->addItem(QString());
        comboBox_diffformat->setObjectName(QString::fromUtf8("comboBox_diffformat"));
        comboBox_diffformat->setGeometry(QRect(580, 610, 261, 35));
        comboBox_diffformat->setFocusPolicy(Qt::ClickFocus);
        slider_times = new QSlider(centralWidget);
        slider_times->setObjectName(QString::fromUtf8("slider_times"));
        slider_times->setGeometry(QRect(840, 390, 41, 215));
        slider_times->setMaximumSize(QSize(41, 16777215));
        slider_times->setStyleSheet(QString::fromUtf8(""));
        slider_times->setMinimum(1);
        slider_times->setMaximum(10);
        slider_times->setOrientation(Qt::Vertical);
        spinBox_Time = new QSpinBox(centralWidget);
        spinBox_Time->setObjectName(QString::fromUtf8("spinBox_Time"));
        spinBox_Time->setGeometry(QRect(840, 350, 48, 26));
        spinBox_Time->setMinimum(1);
        spinBox_Time->setMaximum(10);
        EncodePath = new QPushButton(centralWidget);
        EncodePath->setObjectName(QString::fromUtf8("EncodePath"));
        EncodePath->setGeometry(QRect(580, 10, 131, 31));
        line_encodepath = new QLineEdit(centralWidget);
        line_encodepath->setObjectName(QString::fromUtf8("line_encodepath"));
        line_encodepath->setGeometry(QRect(720, 10, 167, 31));
        saveEncodePath = new QPushButton(centralWidget);
        saveEncodePath->setObjectName(QString::fromUtf8("saveEncodePath"));
        saveEncodePath->setGeometry(QRect(580, 60, 131, 31));
        line_saveencodepath = new QLineEdit(centralWidget);
        line_saveencodepath->setObjectName(QString::fromUtf8("line_saveencodepath"));
        line_saveencodepath->setGeometry(QRect(720, 60, 167, 31));
        encodebutton = new QPushButton(centralWidget);
        encodebutton->setObjectName(QString::fromUtf8("encodebutton"));
        encodebutton->setGeometry(QRect(580, 110, 307, 31));
        DecodePath = new QPushButton(centralWidget);
        DecodePath->setObjectName(QString::fromUtf8("DecodePath"));
        DecodePath->setGeometry(QRect(580, 170, 131, 31));
        decodebutton = new QPushButton(centralWidget);
        decodebutton->setObjectName(QString::fromUtf8("decodebutton"));
        decodebutton->setGeometry(QRect(580, 270, 307, 31));
        line_decodepath = new QLineEdit(centralWidget);
        line_decodepath->setObjectName(QString::fromUtf8("line_decodepath"));
        line_decodepath->setGeometry(QRect(720, 170, 167, 31));
        saveDecodePath = new QPushButton(centralWidget);
        saveDecodePath->setObjectName(QString::fromUtf8("saveDecodePath"));
        saveDecodePath->setGeometry(QRect(580, 220, 131, 31));
        line_savedecodepath = new QLineEdit(centralWidget);
        line_savedecodepath->setObjectName(QString::fromUtf8("line_savedecodepath"));
        line_savedecodepath->setGeometry(QRect(720, 220, 167, 31));
        comboBox_Outputformat = new QComboBox(centralWidget);
        comboBox_Outputformat->addItem(QString());
        comboBox_Outputformat->addItem(QString());
        comboBox_Outputformat->addItem(QString());
        comboBox_Outputformat->addItem(QString());
        comboBox_Outputformat->addItem(QString());
        comboBox_Outputformat->addItem(QString());
        comboBox_Outputformat->addItem(QString());
        comboBox_Outputformat->setObjectName(QString::fromUtf8("comboBox_Outputformat"));
        comboBox_Outputformat->setGeometry(QRect(151, 200, 120, 35));
        comboBox_Outputformat->setFocusPolicy(Qt::ClickFocus);
        test = new QPushButton(centralWidget);
        test->setObjectName(QString::fromUtf8("test"));
        test->setGeometry(QRect(580, 310, 89, 31));
        savepng = new QRadioButton(centralWidget);
        savepng->setObjectName(QString::fromUtf8("savepng"));
        savepng->setGeometry(QRect(420, 302, 112, 31));
        Diffformat1 = new QComboBox(centralWidget);
        Diffformat1->addItem(QString());
        Diffformat1->addItem(QString());
        Diffformat1->addItem(QString());
        Diffformat1->addItem(QString());
        Diffformat1->addItem(QString());
        Diffformat1->addItem(QString());
        Diffformat1->addItem(QString());
        Diffformat1->setObjectName(QString::fromUtf8("Diffformat1"));
        Diffformat1->setGeometry(QRect(170, 610, 106, 35));
        Diffformat2 = new QComboBox(centralWidget);
        Diffformat2->addItem(QString());
        Diffformat2->addItem(QString());
        Diffformat2->addItem(QString());
        Diffformat2->addItem(QString());
        Diffformat2->addItem(QString());
        Diffformat2->addItem(QString());
        Diffformat2->addItem(QString());
        Diffformat2->setObjectName(QString::fromUtf8("Diffformat2"));
        Diffformat2->setGeometry(QRect(450, 610, 106, 35));
        diffimg1_lineedit = new QLineEdit(centralWidget);
        diffimg1_lineedit->setObjectName(QString::fromUtf8("diffimg1_lineedit"));
        diffimg1_lineedit->setGeometry(QRect(20, 650, 256, 31));
        diffimg1_lineedit_2 = new QLineEdit(centralWidget);
        diffimg1_lineedit_2->setObjectName(QString::fromUtf8("diffimg1_lineedit_2"));
        diffimg1_lineedit_2->setGeometry(QRect(300, 650, 256, 31));
        MainWindow->setCentralWidget(centralWidget);
        LabelHeight->raise();
        LabelWidth->raise();
        LineEdit_Height->raise();
        lineEdit_Width->raise();
        PicChange->raise();
        OpenFileButton->raise();
        lineEdit_FileName->raise();
        combox_Inputformat->raise();
        lineEdit_imgformat->raise();
        label->raise();
        Button_saveimg->raise();
        graphicsView->raise();
        Label_img->raise();
        graphicsView_2->raise();
        graphicsView_3->raise();
        Label_imgcmp_2->raise();
        imgcmp_1->raise();
        imgcmp_2->raise();
        graphicsView_4->raise();
        comboBox_diffformat->raise();
        Label_imgcmp_1->raise();
        Label_imgcmp_3->raise();
        slider_times->raise();
        spinBox_Time->raise();
        EncodePath->raise();
        line_encodepath->raise();
        saveEncodePath->raise();
        line_saveencodepath->raise();
        encodebutton->raise();
        DecodePath->raise();
        decodebutton->raise();
        line_decodepath->raise();
        saveDecodePath->raise();
        line_savedecodepath->raise();
        comboBox_Outputformat->raise();
        test->raise();
        savepng->raise();
        Diffformat1->raise();
        Diffformat2->raise();
        diffimg1_lineedit->raise();
        diffimg1_lineedit_2->raise();
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 895, 22));
        menuFormat_change = new QMenu(menuBar);
        menuFormat_change->setObjectName(QString::fromUtf8("menuFormat_change"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFormat_change->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        LabelHeight->setText(QApplication::translate("MainWindow", "Height\357\274\232", nullptr));
        LabelWidth->setText(QApplication::translate("MainWindow", "Width \357\274\232", nullptr));
        PicChange->setText(QApplication::translate("MainWindow", "Change format", nullptr));
        OpenFileButton->setText(QApplication::translate("MainWindow", "Open file", nullptr));
        combox_Inputformat->setItemText(0, QApplication::translate("MainWindow", "Input format", nullptr));
        combox_Inputformat->setItemText(1, QApplication::translate("MainWindow", "YUVI420", nullptr));
        combox_Inputformat->setItemText(2, QApplication::translate("MainWindow", "YUV422sp", nullptr));
        combox_Inputformat->setItemText(3, QApplication::translate("MainWindow", "NV12", nullptr));
        combox_Inputformat->setItemText(4, QApplication::translate("MainWindow", "RGB565", nullptr));
        combox_Inputformat->setItemText(5, QApplication::translate("MainWindow", "RGB888", nullptr));
        combox_Inputformat->setItemText(6, QApplication::translate("MainWindow", "RGBA8888", nullptr));

        label->setText(QApplication::translate("MainWindow", "source picture\357\274\210RGBA\357\274\211", nullptr));
        Button_saveimg->setText(QApplication::translate("MainWindow", "Save picture", nullptr));
        Label_img->setText(QString());
        Label_imgcmp_1->setText(QString());
        Label_imgcmp_2->setText(QString());
        imgcmp_1->setText(QApplication::translate("MainWindow", "Choose a picture", nullptr));
        imgcmp_2->setText(QApplication::translate("MainWindow", "Choose a picture", nullptr));
        Label_imgcmp_3->setText(QString());
        comboBox_diffformat->setItemText(0, QApplication::translate("MainWindow", "Gray", nullptr));
        comboBox_diffformat->setItemText(1, QApplication::translate("MainWindow", "RGB", nullptr));

        EncodePath->setText(QApplication::translate("MainWindow", "Chose encode img", nullptr));
        saveEncodePath->setText(QApplication::translate("MainWindow", "Save encode img ", nullptr));
        encodebutton->setText(QApplication::translate("MainWindow", "Encode", nullptr));
        DecodePath->setText(QApplication::translate("MainWindow", "Chose decode img", nullptr));
        decodebutton->setText(QApplication::translate("MainWindow", "Decode", nullptr));
        saveDecodePath->setText(QApplication::translate("MainWindow", "Save decode img ", nullptr));
        comboBox_Outputformat->setItemText(0, QApplication::translate("MainWindow", "output format", nullptr));
        comboBox_Outputformat->setItemText(1, QApplication::translate("MainWindow", "YUVI420", nullptr));
        comboBox_Outputformat->setItemText(2, QApplication::translate("MainWindow", "YUV422sp", nullptr));
        comboBox_Outputformat->setItemText(3, QApplication::translate("MainWindow", "NV12", nullptr));
        comboBox_Outputformat->setItemText(4, QApplication::translate("MainWindow", "RGB565", nullptr));
        comboBox_Outputformat->setItemText(5, QApplication::translate("MainWindow", "RGB888", nullptr));
        comboBox_Outputformat->setItemText(6, QApplication::translate("MainWindow", "RGBA8888", nullptr));

        test->setText(QApplication::translate("MainWindow", "test", nullptr));
        savepng->setText(QApplication::translate("MainWindow", "Save as png", nullptr));
        Diffformat1->setItemText(0, QApplication::translate("MainWindow", "Format", nullptr));
        Diffformat1->setItemText(1, QApplication::translate("MainWindow", "YUVI420", nullptr));
        Diffformat1->setItemText(2, QApplication::translate("MainWindow", "YUV422SP", nullptr));
        Diffformat1->setItemText(3, QApplication::translate("MainWindow", "NV12", nullptr));
        Diffformat1->setItemText(4, QApplication::translate("MainWindow", "RGB565", nullptr));
        Diffformat1->setItemText(5, QApplication::translate("MainWindow", "RGB", nullptr));
        Diffformat1->setItemText(6, QApplication::translate("MainWindow", "RGBA", nullptr));

        Diffformat2->setItemText(0, QApplication::translate("MainWindow", "Format", nullptr));
        Diffformat2->setItemText(1, QApplication::translate("MainWindow", "YUVI420", nullptr));
        Diffformat2->setItemText(2, QApplication::translate("MainWindow", "YUV422SP", nullptr));
        Diffformat2->setItemText(3, QApplication::translate("MainWindow", "NV12", nullptr));
        Diffformat2->setItemText(4, QApplication::translate("MainWindow", "RGB565", nullptr));
        Diffformat2->setItemText(5, QApplication::translate("MainWindow", "RGB", nullptr));
        Diffformat2->setItemText(6, QApplication::translate("MainWindow", "RGBA", nullptr));

        menuFormat_change->setTitle(QApplication::translate("MainWindow", "Format change", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
