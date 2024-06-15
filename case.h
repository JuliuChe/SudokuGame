#ifndef CASE_H
#define CASE_H
#include "qvalidator.h"
#include <position.h>
#include <QObject>
#include <QLineEdit>

class Case : public QLineEdit
{
    Q_OBJECT

public:
    enum type{FULL,GUESS};
    Case(QWidget *parent = nullptr, Position pos=Position(), int size=9);
    void setValue(int x);
    int getValue();
    Position getPos();
    void setPos(Position pos);
    type getType();
    void setType(type mytype);
    void setShape(int x, int y);

signals:

private:
    Position myPos;
    int value;
    type tp;
   QRegularExpressionValidator* validator;
};

#endif // CASE_H
