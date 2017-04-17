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

    void on_actionOpen_triggered();

    void on_label_linkActivated(const QString &link);

    void on_lblLabela_linkActivated(const QString &link);

private:
    Ui::Passerine *ui;
};

#endif // PASSERINE_H
