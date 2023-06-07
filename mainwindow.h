#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QPushButton"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton *button;

public slots:
    void  buttonClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
