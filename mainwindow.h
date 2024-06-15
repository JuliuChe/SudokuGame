#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "case.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void applyBorderStyles(Case *caseWidget, int row, int col, int size);

private slots:
    void initializeGrid(int size);
    void solverGrid();
    void restartGame();
    void restartGrid();
    void checkGrid();
    void fillFromLevel(int level);


protected:
    Ui::MainWindow *ui;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QHBoxLayout *buttonLayout2;
    QHBoxLayout *buttonLayout3;


    QVector<QVector<Case*>> cases;
    QVector<int*> myPrimArr;

    QPushButton *start9Button;
    QPushButton *start16Button;
    QPushButton *start25Button;

    QPushButton *easyButton;
    QPushButton *mediumButton ;
    QPushButton *hardButton;

    QPushButton *clearButton;
    QPushButton *solveButton;
    QPushButton *errorButton;
    QPushButton *restartButton;


private:
    void createPrimitiveArray();
    void shuffleArray();
    void populateGride(int subGridSize);
    //void checkSquares();
    //void checkRow();
    //void checkColumn();
    int myGridSize;

};
#endif // MAINWINDOW_H
