#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <qmessagebox.h>
#include <vector>
#include "street.h"
#include "graph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //carrega as ruas
    void chargeStreets(std::vector<Street> *streets);
    //carrega as distancias
    void chargeDistance();
    //cria o grafo
    Graph graph;
    int isVisible;
public slots:
//show hello world!
    void searchClick();
private slots:

    void on_matrizBT_clicked();

    void on_todoscaminhosCB_clicked(bool checked);

    void on_caminhosalterCB_clicked(bool checked);

    void on_menorCaminhoCB_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
