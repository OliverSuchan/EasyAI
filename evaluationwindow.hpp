#ifndef EVALUATIONWINDOW_HPP
#define EVALUATIONWINDOW_HPP

#include <QMainWindow>
#include "feedforwardnetwork.hpp"

namespace Ui {
class EvaluationWindow;
}

class EvaluationWindow : public QMainWindow
{
    Q_OBJECT

public:
    void setNetwork(FeedForwardNetwork *p_network);
    explicit EvaluationWindow(QWidget *parent = 0);
    ~EvaluationWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    FeedForwardNetwork *m_FNN;
    Ui::EvaluationWindow *ui;
};

#endif // EVALUATIONWINDOW_HPP
