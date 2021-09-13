#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>
#include <QGraphicsSceneMouseEvent>
#include "box.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    void openFile(QString file);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<box*> obj;
    int _boxSize;
    int _currentBox;
};
#endif // MAINWINDOW_H
