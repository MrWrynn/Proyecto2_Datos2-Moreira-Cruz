#include "widget.h"
#include "./ui_widget.h"
#include <QInputDialog>

widget::widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);    
}

widget::~widget()
{
    delete ui;

}


void widget::on_ancho_clicked()
{
    x=QInputDialog::getInt(this,"Inicio","Digite el valor del ancho: ");
}


void widget::on_altura_clicked()
{
    y=QInputDialog::getInt(this,"Inicio","Digite el valor de la altura: ");
}

