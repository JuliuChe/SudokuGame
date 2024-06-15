#include "case.h"

Case::Case(QWidget *parent, Position pos, int size)
    : QLineEdit(parent)
{
    myPos = pos;
    tp = GUESS;



    // Instancier QIntValidator et l'associer à QLineEdit
    // intValidator = new QIntValidator(1, 9, this); // Limite les valeurs de 0 à 100
    // ou toute autre valeur que vous souhaitez
    //QString regexPattern = QString("[1-%1]").arg(size);



    QString regexPattern;
    if (size <= 9) {
        regexPattern = QString("[1-%1]").arg(size);
    } else if (size <= 16) {
        regexPattern = QString("(?:[1-9]|1[0-%1])").arg(size%10);
    } else if (size <= 25) {
        regexPattern = "(?:[1-9]|1[0-9]|2[0-5])";
    } else {
        qDebug() << "Size not supported";
    }





    validator = new QRegularExpressionValidator(QRegularExpression(regexPattern),this);
    this->setValidator(validator);

    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet("QLineEdit {border:none}");
    this->setStyleSheet("QLineEdit { background-color: red; }");

}

void Case::setShape(int x, int y){
    this->setGeometry(this->getPos().getXPos(), this->getPos().getYPos(),x,y);
}

void Case::setValue(int x){
    value = x;
}

int Case::getValue(){
    return value;
}

Position Case::getPos()
{
    return this->myPos;
}

void Case::setPos(Position pos)
{
    this->myPos=pos;
}

Case::type Case::getType(){
    return this->tp;
}

void Case::setType(type mytype)
{
    this->tp=mytype;
}
