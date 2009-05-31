#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    connect(ui.buttonCancel, SIGNAL(clicked()), this, SLOT(slotCancelClicked()));
    connect(ui.buttonLoad, SIGNAL(clicked()), this, SLOT(slotLoadClicked()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::slotCancelClicked()
{
}

void MainWindow::slotLoadClicked()
{
    filename = FileDialog.getOpenFileName();
    if (filename != QString(""))
    {
        QFile File(filename);
        if (!File.open(QIODevice::ReadOnly)) return;
        QDataStream readfile(&File);
        readfile.skipRawData(0x003);
        char region;
        readfile.readRawData(&region, sizeof(region));
        readfile.skipRawData(0x018 - (0x003 + 1));        
        quint32 magicword;
        readfile >> magicword;
        char title[63];
        readfile.readRawData(title, 64);
        if (magicword != 0x5D1C9EA3)
        {
            QMessageBox::information(this, trUtf8("Information"), trUtf8("Incorrect Wii disk image"));
        } else
        {
          if (QString(region) == QString("P")) ui.labelRegion->setText("PAL");
          if (QString(region) == QString("J")) ui.labelRegion->setText("NTSC-J");
          if (QString(region) == QString("E")) ui.labelRegion->setText("NTSC");
          QMessageBox::information(this, trUtf8("Information"), trUtf8("Wii disk checked"));
        }
        File.close();
    }
}
