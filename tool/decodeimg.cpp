#include "decodeimg.h"

decodeimg::decodeimg()
{
    this->src = "";
    this->dst = "";
}

decodeimg::~decodeimg()
{

}

void decodeimg::Setsrc(QString str)
{
    this->src = str;
}

QString decodeimg::Getsrc() const
{
    return this->src;
}

void decodeimg::Setdst(QString str)
{
    this->dst = str;
}

QString decodeimg::Getdst() const
{
    return this->dst;
}
