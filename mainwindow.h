#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QMap>
#include <QByteArray>
#include <QListWidgetItem>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_CommandList_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QMap<QString, QString>    Content;

    void LoadFile_(void);
    void FillCommandList_(void);
};

#endif // MAINWINDOW_H
