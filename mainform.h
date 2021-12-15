#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QListWidget>
#include <QToolBar>
#include <QList>
#include <QDir>
#include "photoform.h"

class MainForm : public QWidget
{
    Q_OBJECT

public:
    MainForm(QWidget *parent = nullptr);
    ~MainForm();



private slots:
    void addAlbum();
    void deleteAlbum();
    //void renameAlbum();
    void openAlbum();
private:
    QPushButton *add;
    QPushButton *rename;
    QPushButton *dlt;
    QPushButton *open;
    QListWidget *albums;
    PhotoForm *photoform;

private:
    void writeSetting();
    void readSetting();
    void ReadPhotoSettings();

};
#endif // MAINFORM_H
