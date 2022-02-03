#include "albumsfilescontroller.h"

AlbumsFilesController::AlbumsFilesController(QObject *parent) : QObject(parent)
{
    if(!albums_dirs_creator.exists(dir_with_albums))
        albums_dirs_creator.mkdir(dir_with_albums);
    albums_dirs_creator.setPath(QApplication::applicationDirPath() + "/" + dir_with_albums);
}

void AlbumsFilesController::add_album_directory(const QString& album_name)
{
    albums_dirs_creator.mkdir(album_name);
}

void AlbumsFilesController::remove_album_directory(const QString &album_name)
{
    if(albums_dirs_creator.exists(album_name)) albums_dirs_creator.rmdir(album_name);
}
