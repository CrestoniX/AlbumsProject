#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "albumsfilescontroller.h"
#include "settings_loader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AlbumsFilesController* afc;
    SettingsLoader* setts_loader;
    void add_album();
    void delete_album();
    void rename_album();
    void open_album();
    void adding_album_cancel();
    void adding_album_continue();
};
#endif // MAINWINDOW_H
