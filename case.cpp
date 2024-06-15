#include "case.h"

Case::Case(QWidget *parent, Position pos)
    : QLineEdit(parent)
{
    myPos = pos;
    tp = GUESS;



    // Instancier QIntValidator et l'associer à QLineEdit
    // intValidator = new QIntValidator(1, 9, this); // Limite les valeurs de 0 à 100

    validator = new QRegularExpressionValidator(QRegularExpression("[1-9]"),this);
    //validator->setRange(1,9);
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
