#ifndef PLOTWIDGET_HPP
#define PLOTWIDGET_HPP

#include <atomic>
#include <thread>
#include <iostream>
#include <vector>
#include <QWidget>
#include <QPainter>

namespace Ui {
class PlotWidget;
}

class PlotWidget : public QWidget
{
    Q_OBJECT

private:
    std::thread *m_paintingThread;
    std::atomic<bool> m_canUpdate;
    void paintLoop();
    std::vector<double> m_dots;
    Ui::PlotWidget *ui;
    double m_biggestScale;
    static constexpr double xMargin = 50.;
    static constexpr double yMargin = 30.;

protected:
    void paintEvent(QPaintEvent*);

public:
    explicit PlotWidget(QWidget *parent = 0);
    ~PlotWidget();
    void addDot(double p_dot);
    void clearDots();

};

#endif // PLOTWIDGET_HPP
