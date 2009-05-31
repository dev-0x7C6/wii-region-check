#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextCodec>

class QFileDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();

private:
    QString filename;
    QFileDialog FileDialog;
    Ui::MainWindowClass ui;

private slots:
    void slotCancelClicked();
    void slotLoadClicked();
};

#endif // MAINWINDOW_H
