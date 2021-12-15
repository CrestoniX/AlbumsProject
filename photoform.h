#ifndef PHOTOFORM_H
#define PHOTOFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>

class PhotoForm : public QWidget
{
    Q_OBJECT
public:
    explicit PhotoForm(QWidget *parent = nullptr);
private:
    QPushButton *save;
    QPushButton *add;
    QPushButton *dlt;
    QPixmap *curr_photo;
private slots:
    void addPhotos();
//    void deletePhoto();
    void WriteSettings();
public:
    int num = 0;
    QLabel *phNum;
    QPushButton *left;
    QPushButton *right;
    QString currentDirectory;
    QLabel *photo;
    QList<QString> paths_to_photos;
    void setCurrentDirectory(const QString& directory);
    void saveAlbum();
    void prevNnext_buttonConnector();
public slots:
    void next();
    void prev();

};

#endif // PHOTOFORM_H
