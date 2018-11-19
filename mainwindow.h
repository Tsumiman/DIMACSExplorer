#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <algorithm>

class QCPGraph;
class QCPItemLine;
class QCPItemEllipse;
class QCPAbstractItem;

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
    void on_actionOpen_triggered();
    void onItemMouseclicked(QCPAbstractItem* item,QMouseEvent* ev);
    void onMousePress(QMouseEvent* ev);
    void onMouseMove(QMouseEvent* ev);
    void onMouseRelease(QMouseEvent* ev);

private:
    Ui::MainWindow *ui;
    std::vector<std::pair<int, QCPItemEllipse*>> vertices;
    std::vector<std::vector<QCPItemLine*>> edges;
    QCPItemEllipse *drag;
    QPointF last_pos;

    void clearGraph();
    void createNewGraph(const int V, const int E);
    void addGraphEdge(const int V, const int U);
    void replotGraph();

    void rotate(const double angle);
    QPointF rotate(const QPointF& old, const double angle) const;

    void loadGraph(const QString& filename);
    void parseLine(const QString& line);
};

#endif // MAINWINDOW_H
