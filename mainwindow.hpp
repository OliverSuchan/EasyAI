#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <vector>
#include <QMainWindow>
#include <QFileDialog>
#include <QPaintEvent>
#include <QMouseEvent>
#include "setvaluewindow.hpp"
#include "createnetworkwindow.hpp"
#include "feedforwardnetwork.hpp"
#include "connection.hpp"
#include "neuronwidget.hpp"
#include "inputneuron.hpp"
#include "outputneuron.hpp"
#include "dataio.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    DataIO *m_dataIO;
    std::vector<Connection*> m_connections;
    FeedForwardNetwork *m_FNN;
    std::vector<NeuronWidget*> m_neurons;
    Ui::MainWindow *ui;
    void mousePressEvent(QMouseEvent *p_mouseEvent);
    void paintEvent(QPaintEvent *);
    void initNetwork();
    void initConnections();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void execDrag();
    void createNetwork(QString p_network);
    void neuralObjectClicked();
    void on_actionLaden_triggered();
    void on_actionSpeichern_triggered();
    void on_actionNeues_Netzwerk_triggered();
};

#endif // MAINWINDOW_HPP
