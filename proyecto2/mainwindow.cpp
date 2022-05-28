#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "image.hpp"
#include <QInputDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_colNegro_clicked()
{
    color={(BYTE) 0,(BYTE) 0,(BYTE) 0 };
    col="otro";
    figura=false;
}


void MainWindow::on_colRojo_clicked()
{
    color={(BYTE) 255,(BYTE) 0,(BYTE) 0 };
    col="otro";
    figura=false;
}


void MainWindow::on_colVerde_clicked()
{
    color={(BYTE) 0,(BYTE) 255,(BYTE) 0 };
    col="otro";
    figura=false;
}


void MainWindow::on_colAzul_clicked()
{
    color={(BYTE) 0,(BYTE) 0,(BYTE) 255};
    col="otro";
    figura=false;
}


void MainWindow::on_colGris_clicked()
{
    color={(BYTE) 127,(BYTE) 127,(BYTE) 127};
    col="otro";
    figura=false;
}


void MainWindow::on_colMorado_clicked()
{
    color={(BYTE) 75,(BYTE) 0,(BYTE) 130};
    col="otro";
    figura=false;
}


void MainWindow::on_colTurquesa_clicked()
{
    color={(BYTE) 93,(BYTE) 193,(BYTE) 185};
    col="otro";
    figura=false;
}


void MainWindow::on_pushButton_5_clicked()
{
    color={(BYTE) 255,(BYTE) 255,(BYTE) 255};
    col="blanco";
    figura=false;
}


void MainWindow::on_triangulo_clicked()
{
    figura=true;
    esFigura="triangulo";
}


void MainWindow::on_rombo_clicked()
{
    figura=true;
    esFigura="rombo";
}


void MainWindow::on_rectangulo_clicked()
{
    figura=true;
    esFigura="rectangulo";
}


void MainWindow::on_linea_clicked()
{
    figura=true;
    esFigura="linea";
}


void MainWindow::on_negativo_clicked()
{
    filtro=true;
    esFiltro="negativo";
}


void MainWindow::on_gris_clicked()
{
    filtro=true;
    esFiltro="gris";
}


void MainWindow::on_oscuro_clicked()
{
    filtro=true;
    esFiltro="oscuro";
}

void MainWindow::on_mix_clicked()
{
    filtro=true;
    esFiltro="mix";
}

void MainWindow::on_pintar_clicked()
{
    figura=true;
    esFigura="pintar";
    modo="pintar";
}

void MainWindow::on_selBFS_clicked()
{
    figura=true;
    esFigura="pintar";
    modo="seleccionar";
}

void MainWindow::on_selRectangular_clicked()
{
    figura=true;
    esFigura="seleccion";
}


void MainWindow::on_guardar_clicked()
{
    texto=true;
    nombre=QInputDialog::getText(this,"Nombre archivo","Digite el nombre del archivo: ");
    tipo="guardar";

}


void MainWindow::on_cargar_clicked()
{
    tipo="cargar";
    texto=true;
    nombre=QInputDialog::getText(this,"Nombre archivo","Digite el nombre del archivo: ");
}


void MainWindow::on_colPicker_clicked()
{
    figura=true;
    esFigura="picker";
}

