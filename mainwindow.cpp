#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"
//#include <QDesktopWidget>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDir>
#include <QDialog>
#include <QLabel>

Field field;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir::setCurrent(qApp->applicationDirPath());
    _boxSize=80;
    _currentBox=0;
    setStyleSheet("background-color:gray;");
    setAutoFillBackground( true );
    setWindowTitle("Planetarium");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPoint viewPoint = ui->graphicsView->mapFromGlobal(QCursor::pos());
        QPointF scenePoint = ui->graphicsView->mapToScene(viewPoint);
        int newEl = field.changeBox(obj,scenePoint.rx(),scenePoint.ry());
        if(newEl != -1)
            _currentBox=newEl;
    }
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(obj.size()>0)
    {
        switch(event->key())
        {
        case Qt::Key_D:
            if(field.checkCollusion(obj,_currentBox, 1 , 0))
            {
                field.deleteBox(obj[_currentBox]);
                obj[_currentBox]->_posX+=_boxSize;
                field.printBox(obj[_currentBox]);
            }
            break;
        case Qt::Key_A:
            if(field.checkCollusion(obj,_currentBox, -1 , 0))
            {
                field.deleteBox(obj[_currentBox]);
                obj[_currentBox]->_posX-=_boxSize;
                field.printBox(obj[_currentBox]);
            }
            break;
        case Qt::Key_W:
            if(field.checkCollusion(obj,_currentBox, 0 , -1))
            {
                field.deleteBox(obj[_currentBox]);
                obj[_currentBox]->_posY-=_boxSize;
                field.printBox(obj[_currentBox]);
            }
            break;
        case Qt::Key_S:
            if(field.checkCollusion(obj,_currentBox, 0 , 1))
            {
                field.deleteBox(obj[_currentBox]);
                obj[_currentBox]->_posY+=_boxSize;
                field.printBox(obj[_currentBox]);
            }
            break;
        }
    }
    if(field.checkRule(obj, _boxSize) == 1) field.endGame();
}
void MainWindow::on_pushButton_clicked()
{
    obj.clear();
    QDialog *dialog = new QDialog(this);
    QPushButton *ok = new QPushButton("Ok");
    QPushButton *lvl1 = new QPushButton("Level 1");
    QPushButton *lvl2 = new QPushButton("Level 2");
    QPushButton *lvl3 = new QPushButton("Level 3");
    QPushButton *lvl4 = new QPushButton("Level 4");
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(lvl1);
    layout->addWidget(lvl2);
    layout->addWidget(lvl3);
    layout->addWidget(lvl4);
    layout->addWidget(ok);
    dialog->setLayout(layout);
    dialog->show();
    connect(ok, &QPushButton::clicked, [dialog](){dialog->close();});
    connect(lvl1, &QPushButton::clicked, [this](){this->openFile("Material/lvl0.txt");});
    connect(lvl2, &QPushButton::clicked, [this](){this->openFile("Material/lvl2.txt");});
    connect(lvl3, &QPushButton::clicked, [this](){this->openFile("Material/lvl3.txt");});
    connect(lvl4, &QPushButton::clicked, [this](){this->openFile("Material/lvl4.txt");});
}
void MainWindow::openFile(QString file)
{
    obj = field.loadMap(_boxSize, file);
    field.print(ui, this, _boxSize);
    for(int i=0; i< obj.size();i++)
        field.printBox(obj[i]);
}
