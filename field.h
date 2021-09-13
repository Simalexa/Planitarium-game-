#ifndef FIELD_H
#define FIELD_H
#include "mainwindow.h"
#include "box.h"
#include <QGraphicsScene>
//#include <QDesktopWidget>
#include <QMap>
#include <QDebug>

class Field
{
public:
    Field();
    void print(Ui::MainWindow *ui, MainWindow *m, int boxSize);
    void printBorder(int X, int Y, int H, int W);
    void printBox(box* newBox);
    void deleteBox(box* newBox);
    bool checkCollusion(QVector<struct box*> massive, int number, int newX, int newY);
    int changeBox(QVector<struct box*> massive, int posX, int posY);
    QVector<box*> loadMap(int boxSize, QString file);
    bool checkRule(QVector<struct box*> massive,int bosXize);
    void endGame();
private:
    QVector<box*> setRule(QStringList value, int boxSize);
    QGraphicsScene *scene;
    QVector<int> _rule;
    QMap<int, QString> colorMap = {{-1,"Material/BG.jpg"},{0,"Material/BlockBG.png"},{1,"Material/UpiterBG.png"},{2,"Material/EarthBG.png"},{3,"Material/PlutonBG.png"},{4,"Material/MarsBG.png"},{5,"Material/BlackHoleBG.png"}};
    int _maxX;
    int _maxY;
    int _maxNumber;
};

#endif // FIELD_H
