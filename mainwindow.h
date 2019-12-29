#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "generate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFileButton_clicked();

    void on_generateButton_clicked();

private:
    Ui::MainWindow *ui;
    QDir curFile;
    QString stopWord = "(end)";
};

#endif // MAINWINDOW_H
