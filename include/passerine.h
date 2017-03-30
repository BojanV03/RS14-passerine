#ifndef PASSERINE_H
#define PASSERINE_H

#include <QMainWindow>

namespace Ui {
class Passerine;
}

class Passerine : public QMainWindow
{
    Q_OBJECT

public:
    explicit Passerine(QWidget *parent = 0);
    ~Passerine();

private slots:
    void on_actionClose_triggered();

    void on_actionAbout_Passerine_triggered();

    void on_actionAbout_Qt_triggered();

private:
    Ui::Passerine *ui;
};

#endif // PASSERINE_H
