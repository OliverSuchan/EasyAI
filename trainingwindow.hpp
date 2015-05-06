#ifndef TRAININGWINDOW_HPP
#define TRAININGWINDOW_HPP

#include <atomic>
#include <thread>
#include <mutex>
#include <QMainWindow>
#include <QCloseEvent>
#include "plotwidget.hpp"
#include "feedforwardnetwork.hpp"

namespace Ui {
class TrainingWindow;
}

class TrainingWindow : public QMainWindow
{
    Q_OBJECT

public:
    void setNetwork(FeedForwardNetwork *p_network);
    explicit TrainingWindow(QWidget *parent = 0);
    ~TrainingWindow();

signals:
    void closed();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    FeedForwardNetwork *m_FNN;
    std::mutex m_mutex;
    std::thread *m_trainingThread;
    std::atomic<bool> m_train;
    PlotWidget *m_plotWidget;
    Ui::TrainingWindow *ui;
    void closeEvent(QCloseEvent *p_closeEvent);
    void train();
};

#endif // TRAININGWINDOW_HPP
