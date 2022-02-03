#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
     afc(new AlbumsFilesController(this)),
     setts_loader(new SettingsLoader(this))
{
    ui->setupUi(this);
    ui->fr_add->hide();
    connect(ui->btn_add, &QPushButton::clicked, this, &MainWindow::add_album);
    connect(ui->fr_btn_continue, &QPushButton::clicked, this, &MainWindow::adding_album_continue);
    connect(ui->fr_btn_cancel, &QPushButton::clicked, this, &MainWindow::adding_album_cancel);
    connect(ui->btn_delete, &QPushButton::clicked, this, &MainWindow::delete_album);
}

MainWindow::~MainWindow()
{
    QList<QString> list_of_albums{};
    qDebug() << ui->lw_albums->count();
    int num_of_albums = ui->lw_albums->count();
    if(num_of_albums)
    {
        for(int i = 0; i < num_of_albums; ++i)
        {
           list_of_albums.append(ui->lw_albums->item(i)->text());
        }
    }
    setts_loader->save_albums_names(list_of_albums);
    delete ui;
}

void MainWindow::add_album()
{
    ui->fr_add->show();
}

void MainWindow::delete_album()
{
    if(ui->lw_albums->currentRow() >= 0)
    {
        QListWidgetItem* item = ui->lw_albums->takeItem(ui->lw_albums->currentRow());
        QString album_name = item->text();
        afc->remove_album_directory(album_name);
        delete item;
    }
}

void MainWindow::rename_album()
{

}

void MainWindow::open_album()
{

}

void MainWindow::adding_album_cancel()
{
    ui->le_album_name->clear();
    ui->fr_add->hide();
}

void MainWindow::adding_album_continue()
{
    if(ui->le_album_name->text().isEmpty())
        adding_album_cancel();
    else
    {
        QString current_album_name = ui->le_album_name->text(); //текущее имя альбома
        int rows = ui->lw_albums->count(); //количество альбомов в списке
        if(rows)
        {
            for(int i = 0; i < rows; ++i) //линейная проверка на повторение названия
            {
                const QListWidgetItem* item = ui->lw_albums->item(i);
                if(current_album_name == item->text())
                {
                    QMessageBox::warning(this, "Неудачное добавление объекта", "Данный альбом уже существует");
                }
                else
                {
                    ui->lw_albums->addItem(ui->le_album_name->text());
                    afc->add_album_directory(current_album_name);
                    adding_album_cancel();
                }
            }
        }
        else
        {
            ui->lw_albums->addItem(ui->le_album_name->text());
            afc->add_album_directory(current_album_name);
            adding_album_cancel();
        }
    }
}

