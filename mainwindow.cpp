#include <QTextCodec>
#include <QFile>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoadFile_();
    FillCommandList_();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: FillCommandList_(void)
{
    for(QMap<QString, QString>::ConstIterator ci = Content.constBegin() ;
        ci != Content.constEnd() ; ++ci)
    {
        ui->CommandList->addItem(ci.key());
    }
}

void MainWindow::on_CommandList_itemClicked(QListWidgetItem *item)
{
    if( !item ) return;

    ui->DescText->setText( Content[item->text()] );
}

void MainWindow :: LoadFile_(void)
{
    QTextCodec *codec = QTextCodec::codecForName("IBM 866");
    QFile file("cmd.txt");
    if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        char line[1024];
        QString     cmd, desc;
        bool cmd_available = false;
        file.readLine(line,1024);
        setWindowTitle(codec->toUnicode(line));
        while( !file.atEnd() )
        {
            file.readLine(line,1024);
            if( line[0] == ':')
            {
                if( cmd_available )
                {
                    desc.trimmed();
                    Content.insert(cmd, desc);
                    desc.clear();
                }
                cmd = codec->toUnicode(line);
                cmd = cmd.remove(0,1).trimmed();
                cmd_available = true;
                continue;
            }
            desc.append(codec-> toUnicode(line));
        }
        if( cmd_available )
        {
            Content.insert(cmd,desc);
        }
    }
}
