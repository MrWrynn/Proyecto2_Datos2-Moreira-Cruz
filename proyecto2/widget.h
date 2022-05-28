#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class widget; }
QT_END_NAMESPACE

class widget : public QWidget
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    int x=0;
    int y=0;
    ~widget();

private slots:
    void on_ancho_clicked();

    void on_altura_clicked();

private:
    Ui::widget *ui;
};
#endif // WIDGET_H
