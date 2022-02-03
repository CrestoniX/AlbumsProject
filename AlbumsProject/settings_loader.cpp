#include "settings_loader.h"

SettingsLoader::SettingsLoader(QObject *parent) : QObject(parent)
{
    if(!settings_directory.exists(dir_with_settings))
        settings_directory.mkdir(dir_with_settings);
    settings_directory.setPath(QApplication::applicationDirPath() + "/" + dir_with_settings);
}

QList<QString> SettingsLoader::parse_albums_names()
{
    QFile file(dir_with_settings + "/" + "albums.json");
}

void SettingsLoader::save_albums_names(const QList<QString> &albums)
{
    int i = 0;
    QFile file(dir_with_settings + "/" + "albums.json");
    QJsonObject obj;
    for(const auto& album : albums)
    {
        obj[QString::number(i)] = album;
    }
    QJsonObject main_obj;
    main_obj["Albums"] = obj;
    if(file.open(QIODevice::ReadWrite))
    {
        file.write(QJsonDocument(main_obj).toJson(QJsonDocument::Indented));
    }
    else
    {
        qDebug() << "Cannot open file";
    }
}
