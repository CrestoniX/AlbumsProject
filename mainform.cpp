#include "mainform.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QSettings>
#include <QTextStream>
#include <QFile>
MainForm::MainForm(QWidget *parent)
    : QWidget(parent)

{
    Qt::Alignment align;
    align.operator|(Qt::AlignHCenter);
    photoform = new PhotoForm();
    QHBoxLayout *hbox = new QHBoxLayout(this);
    QVBoxLayout *vbox = new QVBoxLayout(this);
    add = new QPushButton("New Album", this);
    rename = new QPushButton("Rename", this);
    dlt = new QPushButton("Delete", this);
    open = new QPushButton("Open", this);
    albums = new QListWidget(this);
    vbox->addWidget(add, Qt::AlignRight, Qt::AlignTop);
    vbox->addWidget(dlt, Qt::AlignRight, Qt::AlignTop);
    vbox->addWidget(rename, Qt::AlignRight, Qt::AlignTop);
    vbox->addWidget(open, Qt::AlignRight, Qt::AlignTop);
    hbox->addWidget(albums, Qt::AlignVCenter, align);
    hbox->addLayout(vbox);
    connect(add, &QPushButton::clicked, this, &MainForm::addAlbum);
    connect(dlt, &QPushButton::clicked, this, &MainForm::deleteAlbum);
    connect(open, &QPushButton::clicked, this, &MainForm::openAlbum);
    MainForm::readSetting();
}
MainForm::~MainForm()
{
    MainForm::writeSetting();
    QTextStream out(stdout);
    out << photoform->currentDirectory << Qt::endl;
}

void MainForm::addAlbum()
{
    QString text = QInputDialog::getText(this, "Name your new album", "New album");
    QString s_text = text.simplified();
    if(!s_text.isEmpty())
    {
    albums->addItem(s_text);
    int r = albums->count()-1;
    albums->setCurrentRow(r);
    }
    QDir album_dir;
    QString d_text = "D:\\QT\\Projects\\AlbumsProject\\";
    d_text.append(s_text);
    album_dir.mkdir(d_text);

}
void MainForm::deleteAlbum()
{
    int r = albums->currentRow();
    if(r != -1)
    {
        QListWidgetItem *item = albums->takeItem(r);
        QString s_text = item->text();
        QString d_text = "D:\\QT\\Projects\\AlbumsProject\\";
        d_text.append(s_text);
        QDir album_dir;
        album_dir.rmdir(d_text);
        delete item;
    }

}
void MainForm::openAlbum()
{
    int r = albums->currentRow();
    if(r != -1)
    {

        QListWidgetItem *item = albums->currentItem();
        QString s_text = item->text();
        QString d_text = "D:\\QT\\Projects\\AlbumsProject\\";
        d_text.append(s_text);
        photoform->setCurrentDirectory(d_text);
        photoform->resize(500, 300);
        photoform->show();
        photoform->left->disconnect();
        photoform->right->disconnect();
        photoform->paths_to_photos.clear();
        MainForm::ReadPhotoSettings();
        photoform->num = 0;
        if(photoform->paths_to_photos.isEmpty())
        {
            photoform->photo->setText("There are no photos!\n\
         Add some by pressing \"add\"");
        }
        else
        {
            photoform->prevNnext_buttonConnector();
            photoform->photo->setPixmap(QPixmap(photoform->paths_to_photos.at(photoform->num)));
        }
        if(photoform->paths_to_photos.isEmpty())
        {
        photoform->phNum->setText(QString::number(photoform->num) + "/" + QString::number(photoform->paths_to_photos.size()));
        }
        else
        {
         photoform->phNum->setText(QString::number(photoform->num+1) + "/" + QString::number(photoform->paths_to_photos.size()));
        }
    }
}
void MainForm::writeSetting()
 {
    QString filename = "D:\\QT\\Projects\\AlbumsProject\\albums.txt";
     QFile file(filename);
     if(file.open(QIODevice::WriteOnly))
     {
     QTextStream out(&file);
     auto cnt = albums->count();
     for(int i = 0; i < cnt; ++i)
     {
         out << albums->item(i)->text() << Qt::endl;
     }
 }
 }
void MainForm::readSetting()
{
    QString filename = "D:\\QT\\Projects\\AlbumsProject\\albums.txt";
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            albums->addItem(line);
        }
    }
}

void MainForm::ReadPhotoSettings()
{
    QString filename = photoform->currentDirectory + ".txt";
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            photoform->paths_to_photos.push_back(line);
        }
    }
}
