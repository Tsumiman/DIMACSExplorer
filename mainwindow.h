#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Graph;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionContract_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    Graph *G;
};

#endif // MAINWINDOW_H
