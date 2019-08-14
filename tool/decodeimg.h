#ifndef DECODEINFO_H
#define DECODEINFO_H
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QProcess>
#include <string>

class decodeimg
{
public:
    decodeimg();
    ~decodeimg();
    void Setsrc(QString str);
    QString Getsrc() const;
    void Setdst(QString str);
    QString Getdst() const;
private:
    QString src;
    QString dst;
};

#endif // DECODEINFO_H
