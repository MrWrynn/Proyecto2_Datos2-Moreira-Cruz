#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "image.hpp"
#include <QMainWindow>
#include <string>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    image bitmap;
    RGBTRIPLE color={(BYTE) 0,(BYTE) 0,(BYTE) 0};
    RGBTRIPLE lastColor={(BYTE) 0,(BYTE) 0,(BYTE) 0};
    bool filtro=false;
    bool figura=false;
    bool texto=false;
    QString mensaje;
    QString esFigura;
    QString esFiltro;
    QString col;
    QString nombre;
    string tipo;
    string modo;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_colRojo_clicked();
    void on_colNegro_clicked();

    void on_colVerde_clicked();

    void on_colAzul_clicked();

    void on_colGris_clicked();

    void on_colMorado_clicked();

    void on_colTurquesa_clicked();

    void on_pushButton_5_clicked();

    void on_triangulo_clicked();

    void on_rombo_clicked();

    void on_rectangulo_clicked();

    void on_linea_clicked();

    void on_negativo_clicked();

    void on_gris_clicked();

    void on_oscuro_clicked();

    void on_selBFS_clicked();

    void on_mix_clicked();

    void on_pintar_clicked();

    void on_selRectangular_clicked();

    void on_guardar_clicked();

    void on_cargar_clicked();

    void on_colPicker_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
