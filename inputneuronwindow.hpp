#ifndef INPUTNEURONWINDOW_HPP
#define INPUTNEURONWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class InputNeuronWindow;
}

class InputNeuronWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InputNeuronWindow(QWidget *parent = 0);
    ~InputNeuronWindow();

private:
    Ui::InputNeuronWindow *ui;
};

#endif // INPUTNEURONWINDOW_HPP
