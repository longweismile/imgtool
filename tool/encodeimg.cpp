#include "encodeimg.h"

encodeimg::encodeimg()
{
    this->src = "";
    this->dst = "";
}

encodeimg::~encodeimg()
{

}

void encodeimg::Setsrc(QString str)
{
    this->src = str;
}

QString encodeimg::Getsrc() const
{
    return this->src;
}

void encodeimg::Setdst(QString str)
{
    this->dst = str;
}

QString encodeimg::Getdst() const
{
    return this->dst;
}
