#include "photoform.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFont>
#include <QTextStream>
#include <QStringList>
#include <QFileDialog>

PhotoForm::PhotoForm(QWidget *parent) : QWidget(parent)
{
    save = new QPushButton("Save album", this);
    add = new QPushButton("Add", this);
    dlt = new QPushButton("Delete", this);
    left = new QPushButton("<<", this);
    right = new QPushButton(">>", this);
    curr_photo = new QPixmap();
    phNum = new QLabel(this);
    photo = new QLabel(this);
    photo->setText("There are no photos!\n Add some by pressing \"add\"");
    photo->setFont(QFont("TimesNewRoman", 8));
    QHBoxLayout *hbox = new QHBoxLayout(this);
    QVBoxLayout *vbox = new QVBoxLayout(this);
    photo->setScaledContents(true);
    photo->setBaseSize(800, 600);
    photo->setMaximumSize(800, 600);
    photo->setAlignment(Qt::AlignCenter);
    Qt::Alignment align;
    align.operator|(Qt::AlignHCenter);
    vbox->addWidget(phNum,  Qt::AlignRight, Qt::AlignBottom);
    phNum->setAlignment(Qt::AlignHCenter);
    vbox->addWidget(left, Qt::AlignRight, Qt::AlignBottom);
    vbox->addWidget(right, Qt::AlignRight, Qt::AlignBottom);
    vbox->addWidget(add, Qt::AlignRight, Qt::AlignBottom);
    vbox->addWidget(dlt, Qt::AlignRight, Qt::AlignBottom);
    vbox->addWidget(save, Qt::AlignRight, Qt::AlignBottom);
    hbox->addWidget(photo, Qt::AlignVCenter, align);
    hbox->addLayout(vbox);
    connect(add, &QPushButton::clicked, this, &PhotoForm::addPhotos);
    connect(save, &QPushButton::clicked, this, &PhotoForm::saveAlbum);
    setLayout(hbox);
}

void PhotoForm::setCurrentDirectory(const QString& directory)
{
    currentDirectory = directory;
}

void PhotoForm::addPhotos()
{
    QTextStream out(stdout);
    QFileDialog file_dialog;
    QStringList photo_list = file_dialog.getOpenFileNames();
    for (int i = 0; i < photo_list.count() ; ++i ) {
        QString lin_text = photo_list.at(i);
        lin_text.replace("/", "\\");
        photo_list.replace(i, lin_text);
        QStringList photo_names = lin_text.split("\\");
        QString photo_name = photo_names.at(photo_names.count() - 1);
        QFile::copy(photo_list.at(i), currentDirectory + "\\" + photo_name);
        paths_to_photos.push_back(currentDirectory + "\\" + photo_name);
    }
    if(!paths_to_photos.isEmpty())
    {
    photo->setPixmap(QPixmap(paths_to_photos.at(num)));
    phNum->setText(QString::number(num+1) + "/" + QString::number(paths_to_photos.size()));
    left->disconnect();
    right->disconnect();
    connect(left, &QPushButton::clicked, this, &PhotoForm::prev);
    connect(right, &QPushButton::clicked, this, &PhotoForm::next);
    }
}

void PhotoForm::next()
{
    num = num + 1;
    if(num > paths_to_photos.size() - 1)
    {
        num = num - 1;
    }
    photo->setPixmap(QPixmap(paths_to_photos.at(num)));
    phNum->setText(QString::number(num+1) + "/" + QString::number(paths_to_photos.size()));
    QTextStream out(stdout);
    out << num << Qt::endl;
}

void PhotoForm::prev()
{
    num = num - 1;
    if(num == -1)
    {
        num = num + 1;
    }
    photo->setPixmap(QPixmap(paths_to_photos.at(num)));
    phNum->setText(QString::number(num+1) + "/" + QString::number(paths_to_photos.size()));
    QTextStream out(stdout);
    out << num << Qt::endl;

}

void PhotoForm::saveAlbum()
{
    PhotoForm::WriteSettings();

}

void PhotoForm::WriteSettings()
{
        QString filename = currentDirectory + ".txt";
         QFile file(filename);
         if(file.open(QIODevice::WriteOnly))
         {
         QTextStream out(&file);
         auto cnt = paths_to_photos.size();
         for(int i = 0; i < cnt; ++i)
         {
             out << paths_to_photos.at(i) << Qt::endl;
         }
     }
}

void PhotoForm::prevNnext_buttonConnector()
{
    connect(left, &QPushButton::clicked, this, &PhotoForm::prev);
    connect(right, &QPushButton::clicked, this, &PhotoForm::next);
}

