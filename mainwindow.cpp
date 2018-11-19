#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStringList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drag = nullptr;

    this->ui->plot->xAxis->setRange(-2, 2);
    this->ui->plot->yAxis->setRange(-2, 2);
    this->ui->plot->setInteraction(QCP::iRangeDrag, true);
    this->ui->plot->setInteraction(QCP::iRangeZoom, true);

    connect(this->ui->plot, SIGNAL(itemClick(QCPAbstractItem*,QMouseEvent*)), this, SLOT(onItemMouseclicked(QCPAbstractItem*,QMouseEvent*)));
    connect(this->ui->plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(onMousePress(QMouseEvent*)));
    connect(this->ui->plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMove(QMouseEvent*)));
    connect(this->ui->plot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(onMouseRelease(QMouseEvent*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Select DIMACS file"),tr("DIMACS file (*.clq);;All Files(*)"));
    if (filename.isEmpty()) {
        return;
    }

    else {
        loadGraph(filename);
    }
}

void MainWindow::onItemMouseclicked(QCPAbstractItem *item, QMouseEvent *ev)
{
    qDebug()<<item;
}

void MainWindow::onMousePress(QMouseEvent *ev)
{
    auto item = this->ui->plot->itemAt(ev->pos(), true);
    auto ellipse = dynamic_cast<QCPItemEllipse*>(item);
    qDebug()<<ellipse;
    if (ellipse) {
        drag = ellipse;
        this->ui->plot->setInteraction(QCP::iRangeDrag, false);
    }
}

void MainWindow::onMouseMove(QMouseEvent *ev)
{
    if (drag) {
        auto pos = QPointF(
            ui->plot->xAxis->pixelToCoord(ev->pos().x()),
            ui->plot->yAxis->pixelToCoord(ev->pos().y())
        );
        drag->topLeft->setCoords(pos + QPointF(0.02, 0.02));

        drag->bottomRight->setCoords(pos - QPointF(0.02, 0.02));
    }
    if (ev->buttons() & Qt::RightButton) {
        auto delta = ev->pos() - last_pos;
        auto r = sqrt(QPointF::dotProduct(delta, delta))/200;
        auto sign = delta.x() > 0?1:-1;
        rotate(sign*r);
    }
    last_pos = ev->pos();
    this->ui->plot->replot();
}

void MainWindow::onMouseRelease(QMouseEvent *ev)
{
    this->ui->plot->setInteraction(QCP::iRangeDrag, true);
    drag = nullptr;
}

void MainWindow::clearGraph()
{
    drag = nullptr;
    for (auto& vedges: edges) for (auto& edge: vedges) {
        if (edge) ui->plot->removeItem(edge);
    }
    for (auto& vertex: vertices) {
        ui->plot->removeItem(vertex.second);
    }
    vertices.clear();
    edges.clear();
}

void MainWindow::createNewGraph(const int V, const int E)
{
    QPointF initial(0, 1);
    double angle = 2*M_PI/V;
    vertices.clear();
    edges.clear();
    std::fill_n(std::back_inserter(edges), E, std::vector<QCPItemLine*>(E, nullptr));
    std::generate_n(std::back_inserter(vertices), V, [&](){
        int N = static_cast<int>(vertices.size());
        QPointF position = rotate(initial, N*angle);
        QCPItemEllipse *el = new QCPItemEllipse(this->ui->plot);
        el->setBrush(QBrush(Qt::red));
        el->setLayer(ui->plot->layer("main"));
        el->topLeft->setCoords(position + QPointF(0.02, 0.02));
        el->bottomRight->setCoords(position - QPointF(0.02, 0.02));
        el->setSelectable(true);
        return std::make_pair(N, el);
    });
    qDebug()<<"Plotting a new graph";
}

void MainWindow::addGraphEdge(const int V, const int U)
{
    auto edge = edges[V][U] = new QCPItemLine(this->ui->plot);
    edge->start->setParentAnchor(this->vertices[V].second->center);
    edge->end->setParentAnchor(this->vertices[U].second->center);
    edge->setLayer(this->ui->plot->layer("background"));
    edge->setSelectable(false);
}

void MainWindow::replotGraph()
{
}

void MainWindow::rotate(const double angle)
{
    for (auto& vertex: vertices) {
        QCPItemEllipse* v = vertex.second;
        if (v == drag) {
            continue;
        }
        QPointF old_pos = (v->topLeft->coords() + v->bottomRight->coords())/2;
        QPointF new_pos = rotate(old_pos, angle);
        v->topLeft->setCoords(new_pos + QPointF(0.02, 0.02));
        v->bottomRight->setCoords(new_pos - QPointF(0.02, 0.02));
        qDebug()<<old_pos<<new_pos;
    }
    this->ui->plot->replot();
}

QPointF MainWindow::rotate(const QPointF &old, const double angle) const
{
    return QPointF(
      old.x()*cos(angle) - old.y()*sin(angle),
      old.x()*sin(angle) + old.y()*cos(angle)
    );
}

void MainWindow::loadGraph(const QString &filename)
{
    clearGraph();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        parseLine(line);
    }
    this->ui->plot->replot();
}

void MainWindow::parseLine(const QString &line)
{
    if (!line.length()) {
        return;
    }

    if (line[0] == 'c') {
        return;
    }

    if (line[0] == 'p') {
        QStringList list = line.split(" ");
        auto V = list[2].toInt();
        auto E = list[3].toInt();
        createNewGraph(V, E);
        return;
    }

    if (line[0] == 'e') {
        QStringList list = line.split(" ");
        auto V = list[1].toInt();
        auto U = list[2].toInt();
        addGraphEdge(V-1, U-1);
        return;
    }
}
