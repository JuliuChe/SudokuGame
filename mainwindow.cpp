#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(300, 300);

        qDebug() << "Initializing grid in main constructor...";

       // Créer le widget central et le layout
       centralWidget = new QWidget(this);
       mainLayout = new QVBoxLayout(centralWidget);
       gridLayout = new QGridLayout();
       // Delete spacing between grid cases and add margins around grid
        gridLayout->setContentsMargins(10, 10, 10, 10);
        gridLayout->setSpacing(0);


       // Créer le layout des boutons
       buttonLayout = new QHBoxLayout();
       start9Button = new QPushButton("Start 9x9", this);
       start9Button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
       start16Button = new QPushButton("Start 16x16", this);
       start16Button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
       start25Button = new QPushButton("Start 25x25", this);
       start25Button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

       buttonLayout->addWidget(start9Button);
       buttonLayout->addWidget(start16Button);
       buttonLayout->addWidget(start25Button);

       buttonLayout2 = new QHBoxLayout();
       easyButton = new QPushButton("Easy", this);
       easyButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
       easyButton->setEnabled(false);
       mediumButton = new QPushButton("Medium", this);
       mediumButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
       mediumButton->setEnabled(false);
       hardButton = new QPushButton("Hard", this);
       hardButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
       hardButton->setEnabled(false);

       buttonLayout2->addWidget(easyButton);
       buttonLayout2->addWidget(mediumButton);
       buttonLayout2->addWidget(hardButton);

       buttonLayout3 = new QHBoxLayout();
       restartButton = new QPushButton("Restart", this);
       restartButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
       restartButton->setEnabled(false);
       errorButton = new QPushButton("Check", this);
       errorButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
       errorButton->setEnabled(false);
       solveButton = new QPushButton("Solve", this);
       solveButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
       solveButton->setEnabled(false);
       clearButton = new QPushButton("New Game", this);
       clearButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
       clearButton->setEnabled(false);

       buttonLayout3->addWidget(restartButton);
       buttonLayout3->addWidget(errorButton);
       buttonLayout3->addWidget(solveButton);
       buttonLayout3->addWidget(clearButton);

       // Ajouter la grille et les boutons au layout principal
       mainLayout->addLayout(buttonLayout);
       mainLayout->addLayout(buttonLayout2);
       mainLayout->addLayout(buttonLayout3);

       mainLayout->addLayout(gridLayout);


       // Configurer le widget central
       centralWidget->setLayout(mainLayout);
       this->setCentralWidget(centralWidget);
       this->adjustSize();


       //connecter les boutons avec leur slots
       connect(start9Button, &QPushButton::clicked, [this](){
           int gridSize = 9; //passer 9 comme argument pour initialiser une grille de 9x9
           this->initializeGrid(gridSize);
       });
       connect(start16Button, &QPushButton::clicked, [this](){
           int gridSize = 16; //passer 16 comme argument pour initialiser une grille de 16x16
           this->initializeGrid(gridSize);
       });
       connect(start25Button, &QPushButton::clicked, [this](){
           int gridSize = 25; //passer 25 comme argument pour initialiser une grille de 25x25
           this->initializeGrid(gridSize);
       });

       connect(easyButton, &QPushButton::clicked, [this](){
           int level=1; //passer 25 comme argument pour initialiser une grille de 25x25
           this->fillFromLevel(level);
       });
       connect(mediumButton, &QPushButton::clicked, [this](){
           int level=2; //passer 25 comme argument pour initialiser une grille de 25x25
           this->fillFromLevel(level);
       });
       connect(hardButton, &QPushButton::clicked, [this](){
           int level=3; //passer 25 comme argument pour initialiser une grille de 25x25
           this->fillFromLevel(level);
       });
       connect(solveButton, &QPushButton::clicked, this, &MainWindow::solverGrid);
       connect(clearButton, &QPushButton::clicked, this, &MainWindow::restartGame);
       connect(restartButton, &QPushButton::clicked, this, &MainWindow::restartGrid);
       connect(errorButton, &QPushButton::clicked, this, &MainWindow::checkGrid);


}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::applyBorderStyles(Case *caseWidget, int row, int col, int size)
{

    QString style = "QLineEdit { border: 1px solid black; font-size: 24px;";

    // Ajouter des bordures plus épaisses pour séparer les sous-grilles de 3x3
    if (col % size == 0) {
        style += " border-left: 3px solid black;";
    }

    if(col==(size*size-1)){
        style += " border-right: 3px solid black;";
    }

    if (row % size == 0 || row == 0) {
        style += " border-top: 3px solid black;";
    }

    if(row==(size*size-1)){
        style += " border-bottom: 3px solid black;";
    }

    style+= "color: black;";

    style += " }";
    caseWidget->setStyleSheet(style);
}




void MainWindow::initializeGrid(int size)
{
    // Delete previous grid Layout
    restartGame();

    start9Button->setEnabled(false);
    start16Button->setEnabled(false);
    start25Button->setEnabled(false);
    easyButton->setEnabled(true);
    mediumButton->setEnabled(true);
    hardButton->setEnabled(true);


    myGridSize=size;
    int subGridSize = int(sqrt(myGridSize));//useful for bold borders and population of the grid



    //Draw and initialize table of the grid with empty values
    cases.resize(myGridSize);
    for (int row = 0; row < myGridSize; ++row) {
        cases[row].resize(myGridSize);
        for (int col = 0; col < myGridSize; ++col) {
            cases[row][col] = new Case(this, Position(row,col), myGridSize);
            cases[row][col]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            applyBorderStyles(cases[row][col], row, col, subGridSize);
            gridLayout->addWidget(cases[row][col], row, col);
        }
    }

    // Add stretch factors to the grid so that it is a square grid
    for (int i = 0; i < myGridSize; i++) {
        gridLayout->setColumnStretch(i, 1);
        gridLayout->setRowStretch(i, 1);
    }

    // Redimensionner la fenêtre pour s'adapter à la nouvelle grille si différente de 9x9
    int newSize = 44 * myGridSize; // Ajustez ce facteur en fonction de vos besoins
    this->setMinimumSize(newSize, newSize);
    this->resize(newSize, newSize);
    this->updateGeometry();

    //Initialize a single row with shuffled values
    qDebug()<< "Initializing grid...";
    createPrimitiveArray();



    //Populate grid with adequate values
    int f=0;
    for(int k=0; k<subGridSize;k++){
    for (int i = 0+k*subGridSize; i < subGridSize+k*subGridSize; i++) {
        for(int j=0; j<size;j++){
            f=f%size;
           // cases[i][j]->setText(QString::number((*myPrimArr[f])));
            cases[i][j]->setValue((*(myPrimArr[f])));
            f+=1;
        }
        f+=subGridSize;
    }
    f+=1;}


}

void MainWindow:: fillFromLevel(int level){
    int nbDigit = (6-level)*myGridSize;
    int totalDigit = myGridSize*myGridSize;

    random_device rd;  // a seed source for the random number engine
    mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> distrib(1, totalDigit);


    for (int row = 0; row < myGridSize; ++row) {
        for (int col = 0; col < myGridSize; ++col) {
            if(distrib(gen)<nbDigit)
            {
                cases[row][col]->setText(QString::number(cases[row][col]->getValue()));
                cases[row][col]->setType(Case::FULL);
                cases[row][col]->setReadOnly(true);
            }
            else{
                cases[row][col]->setType(Case::GUESS);
            }
        }
    }
    easyButton->setEnabled(false);
    mediumButton->setEnabled(false);
    hardButton->setEnabled(false);
    restartButton->setEnabled(true);
    errorButton->setEnabled(true);
    solveButton->setEnabled(true);
    clearButton->setEnabled(true);

}

void MainWindow::restartGame()
{
    // Delete previous grid Layout
    QLayoutItem *child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    int newHSize = 400;
    int newVSize=300;
    this->setMinimumSize(newHSize, newVSize);
    this->resize(newHSize, newVSize);
    this->updateGeometry();

    start9Button->setEnabled(true);
    start16Button->setEnabled(true);
    start25Button->setEnabled(true);
    easyButton->setEnabled(false);
    mediumButton->setEnabled(false);
    hardButton->setEnabled(false);

    restartButton->setEnabled(false);
    errorButton->setEnabled(false);
    solveButton->setEnabled(false);
    clearButton->setEnabled(false);


}

void MainWindow::restartGrid()
{
    for(int i=0;i<myGridSize;i++){
        for(int j=0; j<myGridSize; j++){
            QString currentStyle = cases[i][j]->styleSheet();
            QRegularExpression regex("color:\\s*[^;]+;");
            cases[i][j]->setStyleSheet(currentStyle.replace(regex, "color: black;"));
            if(cases[i][j]->getType()==Case::GUESS)
            {
                cases[i][j]->setText("");
            }
        }
    }
}

void MainWindow::checkGrid()
{
    for(int i=0;i<myGridSize;i++){
        for(int j=0; j<myGridSize; j++){
            if(cases[i][j]->getType()==Case::GUESS)
            {

                QString myStrVal = cases[i][j]->text();
                QString currentStyle = cases[i][j]->styleSheet();
                QRegularExpression regex("color:\\s*[^;]+;");
                if(myStrVal != nullptr){
                    int myIntVal = myStrVal.toInt();
                    if(cases[i][j]->getValue()==myIntVal){

                        cases[i][j]->setStyleSheet(currentStyle.replace(regex, "color: green;"));
                    }
                    else{
                        cases[i][j]->setStyleSheet(currentStyle.replace(regex, "color: red;"));
                    }
                }
            }
        }
    }

}

void MainWindow::createPrimitiveArray()
{
    myPrimArr.resize(myGridSize);
     for(int i=0; i<myGridSize; i++){
         myPrimArr[i]=new int(i+1);}
     QString arrayStr;
     shuffleArray();
     for(int j=0; j<myGridSize;j++){
         arrayStr += QString::number((*myPrimArr[j])) + " ";
     }
     qDebug() << arrayStr;
}

void MainWindow::shuffleArray(){
    srand(time(nullptr));
    for(int i=0; i<myGridSize; i++){
        int j=rand()%myGridSize;
        qSwap(myPrimArr[i], myPrimArr[j]);
    }
}



void MainWindow::solverGrid()
{

    //Code with static table
    for(int i=0;i<myGridSize;i++){
        for(int j=0; j<myGridSize; j++){

            if(cases[i][j]->getType()==Case::GUESS){
            QString currentStyle = cases[i][j]->styleSheet();
            QRegularExpression regex("color:\\s*[^;]+;");
            cases[i][j]->setStyleSheet(currentStyle.replace(regex, "color: green;"));
            cases[i][j]->setText(QString::number(cases[i][j]->getValue()));
            }
        }
    }
    //end of code with static table


    //checkSquares();
    //checkRow();
    //checkColumn();

}



/*void MainWindow:: checkSquares(){

    //Code with static table
    qDebug()<<"Check Squares";
    int subGridSize = int(sqrt(myGridSize));
    int square=0;
    int g=0;
    int k=0;
    for(int f=0; f<myGridSize;f++){
    for(int i=0+g;i<subGridSize+g;i++){
        for(int j=0+k; j<subGridSize+k;j++){
        square += cases[i][j]->getValue();
        }
    }
    g+=subGridSize;
    if(g>=myGridSize){
        k+=subGridSize;
        g=0;
    }
    qDebug() << "square value number :" << f+1 << square;
    square = 0;
 }
}*/

/*void MainWindow:: checkRow(){

    int row =0;
    for(int i=0;i<myGridSize;i++){
        for(int j=0; j<myGridSize; j++){
            row+=cases[j][i]->getValue();
        }
        qDebug() << "row value : " <<i+1<<row;
        row=0;
    }
}*/

/*void MainWindow::checkColumn()
{
    int line =0;
    for(int i=0;i<myGridSize;i++){
        for(int j=0; j<myGridSize; j++){
            line+=cases[i][j]->getValue();
        }
        qDebug() << "line value : " <<i+1<<line;
        line =0;
    }
    //End of Static table code

}*/
