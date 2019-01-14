#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include "graph/edge.h"
#include "items/qgraphicsvertexitem.h"
#include "items/qgraphicsedgeitem.h"
#include "statistics/commonneighborhoodstatistic.h"
#include "graph/graph.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->canvas->setScene(new QGraphicsScene(this));
    ui->canvas->setRenderHint(QPainter::Antialiasing);
    G = new Graph(ui->canvas->scene());
    auto V = G->addVertex();
    auto U = G->addVertex();
    auto K = G->addVertex();
    auto P = G->addVertex();
    Edge* E = G->addEdge(V, U);
    Edge* I = G->addEdge(U, K);
    I->repr()->setText("2");
    G->addEdge(K, P);
    G->addEdge(P, V);
    G->setEdgeStatistic(new CommonNeighborhoodStatistic());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionContract_triggered()
{
    QList<QGraphicsItem*> selected = ui->canvas->scene()->selectedItems();
    QList<QGraphicsVertexItem*> filtered;
    for (QGraphicsItem* item: selected) {
        QGraphicsVertexItem* conv = dynamic_cast<QGraphicsVertexItem*>(item);
        if (conv) {
            filtered.push_back(conv);
        }
    }
    while (filtered.size() > 1) {
        QGraphicsVertexItem* back = filtered[filtered.size() - 1];
        QGraphicsVertexItem* backback = filtered[filtered.size() - 2];
        G->contractVertices(backback->getModel(), back->getModel());
        filtered.pop_back();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Select DIMACS file"),tr("DIMACS file (*.clq);;All Files(*)"));
    if (filename.isEmpty()) {
        return;
    }

    else {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }
        G->readFromDIMACS(file);
    }
}
