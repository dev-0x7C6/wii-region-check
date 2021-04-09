/***************************************************************************
 *   Copyright (C) 2008-2009 by Bartlomiej Burdukiewicz                    *
 *   dev.strikeu@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextCodec>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QProcess>

class QFileDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();

private:
    QSystemTrayIcon tray;
    QFileDialog FileDialog;
    QTimer timer;
    Ui::MainWindowClass ui;
    void checkISO(QString filename);

private slots:
    void slotCancelClicked();
    void slotLoadClicked();
    void slotTimeout();
};

#endif // MAINWINDOW_H
