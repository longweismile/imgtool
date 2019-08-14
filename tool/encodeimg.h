#ifndef DECODEIMG_H
#define DECODEIMG_H
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QProcess>
#include <string>

class encodeimg
{
public:
    encodeimg();
    ~encodeimg();
    void Setsrc(QString str);
    QString Getsrc() const;
    void Setdst(QString str);
    QString Getdst() const;
private:
    QString src;//source img path
    QString dst;//after encode ,save img to this path
};

#endif // DECODEIMG_H
