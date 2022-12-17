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


#include "mainwindow.h"

const char REGION_JAPAN_CODE = 0x4A;
const char REGION_USA_CODE = 0x45;
const char REGION_EUROPE_CODE = 0x50;

const QString REGION_JAPAN_MODE = "NTSC-J";
const QString REGION_USA_MODE = "NTSC";
const QString REGION_EUROPE_MODE = "PAL";
const QString REGION_UNKNOWN_REGION = "UNKNOWN";

const QString DEFAULT_CDROM_DEVICE="/dev/cdrom";
const quint32 DEFAULT_CHECK_TIMEOUT=1000;

const QString DEFAULT_TEMP_FILENAME="/tmp/block.dat";

MainWindow::MainWindow(QWidget *parent)
		: QMainWindow(parent) {
	timer.setInterval(DEFAULT_CHECK_TIMEOUT);
    ui.setupUi(this);
    setVisible(false);
    connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(slotCancelClicked()));
    connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(slotLoadClicked()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
    tray.setIcon(QIcon(":/icons/icons/wiiregioncheck16.png"));
    tray.show();
    //slotTimeout();
    timer.start();
}

void MainWindow::slotTimeout()
{
    QProcess process;
    process.start("/bin/dd", QString("if=%1|of=%2|count=1").arg(DEFAULT_CDROM_DEVICE, DEFAULT_TEMP_FILENAME).split('|'));
    process.waitForFinished(-1);
    checkISO(DEFAULT_TEMP_FILENAME);
}

void MainWindow::checkISO(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite))
        return;

    if (file.size() < 512)
        return;

    QDataStream readfile(&file);
    char id[6];
    readfile.readRawData(id, 0x06);
    QString gameId = id;
    file.seek(0);
    readfile.skipRawData(0x03);
    quint8 region;
    readfile >> region;

    readfile.skipRawData(0x018 - (0x03 + 1));
    quint32 magicword;
    readfile >> magicword;

    if (magicword != 0x5D1C9EA3)
    {
        file.close();
        QMessageBox::information(this, trUtf8("Information"), trUtf8("Incorrect Wii disk image"));
        return;
    }

    switch (region)
    {
        case REGION_JAPAN_CODE:
            ui.labelRegion->setText(REGION_JAPAN_MODE);
            break;
        case REGION_EUROPE_CODE:
            ui.labelRegion->setText(REGION_EUROPE_MODE);
            break;
        case REGION_USA_CODE:
            ui.labelRegion->setText(REGION_USA_MODE);
            break;
        default:
            ui.labelRegion->setText(REGION_UNKNOWN_REGION);
    }

    char title[63];
    readfile.skipRawData(0x04);
    readfile.readRawData(title, 64);

    ui.gameTitle->setText(QString("<font color='#0a84f6'><b>%1</b></font>").arg(title));
    tray.setToolTip(ui.labelRegion->text() + " " + title);
    file.close();
    tray.showMessage(DEFAULT_CDROM_DEVICE, QString("%1: %3 (%2)").arg(gameId, ui.labelRegion->text(), title), QSystemTrayIcon::Information, 5000);
}

MainWindow::~MainWindow()
{
}

void MainWindow::slotCancelClicked()
{
    close();
}

void MainWindow::slotLoadClicked()
{
    QString filename = FileDialog.getOpenFileName();

    if (!filename.isEmpty())
        checkISO(filename);
}
