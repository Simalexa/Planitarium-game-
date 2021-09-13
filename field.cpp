#include "field.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QVector>
#include <QMessageBox>
#include <QFileDialog>
#include <QPainterPath>

Field::Field()
{
    _maxNumber=5;
}
void Field::endGame()
{
    QMessageBox box;
            box.setWindowTitle("Window");
            box.setText("Victory!");
            box.exec();
    scene->clear();
    _rule.clear();
}
void Field::print(Ui::MainWindow *ui, MainWindow *m, int boxSize)
{
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    printBorder(0, 0, _maxY, _maxX);
    printBorder(0,-2 * _maxX/_maxNumber,_maxX/_maxNumber,_maxX);
    m->setFixedSize(QSize(_maxX*1.2,(_maxY+boxSize)*1.5));
}
void Field::printBorder(int X, int Y, int H, int W)
{
    QPen pen(Qt::black);
    QGraphicsRectItem *it= new QGraphicsRectItem;
    it->setRect(X,Y,W,H);
    QBrush q;
    QImage pic(colorMap[-1]);
    pic = pic.scaled(W,H);
    q.setTextureImage(pic);
    it->setBrush(q);
    it->setPen(pen);
    scene->addItem(it);
}
void Field::printBox(box* newBox)
{
    QPen pen(Qt::black);
    QGraphicsRectItem *it= new QGraphicsRectItem;
    it->setRect(newBox->_posX,newBox->_posY,newBox->_size,newBox->_size);
    QBrush q;
    QImage pic(colorMap[newBox->_color]);
    pic = pic.scaled(newBox->_size,newBox->_size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    q.setTextureImage(pic);
    it->setBrush(q);
    it->setPen(pen);
    newBox->item = it;
    scene->addItem(it);
}
void Field::deleteBox(box* newBox)
{
    scene->removeItem(newBox->item);
}
QVector<box*> Field::setRule(QStringList value, int boxSize)
{
    QVector<box*> newMassive;
    for(int i=1; i < value.size();i++)
    {
        box *newBox;
        newBox = new box;
        newBox->_size = boxSize;
        newBox->_posX = (i-1) * boxSize;
        newBox->_posY = -2 * boxSize;
        newBox->_move = 0;
        newBox->_color = value[i].toInt();
        newMassive.push_back(newBox);
        _rule.push_back(value[i].toInt());
    }
    return newMassive;
}
QVector<box*> Field::loadMap(int boxSize, QString file)
{
    QFile List(file);
    int lineCounter = 0;
    QVector<box*> newMassive;
    _rule.clear();
    if(List.open(QIODevice::ReadOnly))
    {
        QTextStream in(&List);
        while(!in.atEnd())
        {
            QStringList value = in.readLine().split(" ");
            if(lineCounter == 0) newMassive = setRule(value, boxSize);
            if(lineCounter == 1)
            {
                _maxX = value[1].toInt() * boxSize;
                _maxY = value[2].toInt() * boxSize;
            }
            if(lineCounter > 2)
            {
                box *newBox;
                newBox = new box;
                newBox->_size = boxSize;
                newBox->_posX = value[0].toInt()* boxSize;
                newBox->_posY = value[1].toInt()* boxSize;
                newBox->_move = value[3].toInt();
                newBox->_color = value[2].toInt();
                newMassive.push_back(newBox);
            }
            lineCounter++;
        }
    }
    return newMassive;
}
int Field::changeBox(QVector<struct box*> massive, int posX, int posY)
{
    for(int i=0; i< massive.size();i++)
        if(posX>massive[i]->_posX && posX<massive[i]->_posX+massive[i]->_size && posY>massive[i]->_posY && posY<massive[i]->_posY+massive[i]->_size && massive[i]->_move==1)
            return i;
    return -1;
}
bool Field::checkCollusion(QVector<struct box*> massive, int number, int newX, int newY)
{
    int boxSize= massive[number]->_size;
    if(massive[number]->_posX + newX*boxSize < 0 || massive[number]->_posY + newY*boxSize < 0 || massive[number]->_posX + newX*boxSize > _maxX - boxSize|| massive[number]->_posY + newY*boxSize > _maxY
            - boxSize)
        return false;
    for(int i=0; i < massive.size();i++)
        if(i != number)
            if(massive[i]->_posX == massive[number]->_posX + newX*boxSize && massive[i]->_posY == massive[number]->_posY + newY*boxSize)
                return false;
    return true;
}
bool Field::checkRule(QVector<struct box*> massive, int boxSize)
{
    for(int i=0 ; i< massive.size() ; i++)
    {
        for(int j=0 ; j < _rule.size() ; j++)
        {
            if(massive[i]->_color == _rule[j] && massive[i]->_posX != j * boxSize && massive[i]->_move == 1)
                return false;
        }
     }
     return true;
}

