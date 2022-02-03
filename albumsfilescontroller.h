#ifndef ALBUMSFILESCONTROLLER_H
#define ALBUMSFILESCONTROLLER_H

#include <QObject>
#include <QDir>
#include <QApplication>

class AlbumsFilesController : public QObject
{
    Q_OBJECT
public:
    explicit AlbumsFilesController(QObject *parent = nullptr);
    void add_album_directory(const QString&);
    void remove_album_directory(const QString&);
    void rename_album_directory();
    void mv_photo_to_its_album();
    void delete_photo_from_album();
signals:

private:
    const QString dir_with_albums = "Albums";
    QDir albums_dirs_creator{};

};

#endif // ALBUMSFILESCONTROLLER_H
