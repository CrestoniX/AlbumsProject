#ifndef SETTINGSLOADER_H
#define SETTINGSLOADER_H

#include <QObject>
#include <QList>
#include <QString>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QApplication>

class SettingsLoader : public QObject
{
    Q_OBJECT
public:
    explicit SettingsLoader(QObject *parent = nullptr);
    QList<QString> parse_albums_names();
    void save_albums_names(const QList<QString>&);

signals:

private:
    QString dir_with_settings = "Settings";
    QDir settings_directory{};
    QList<QString> list_of_settings_files{};
};

#endif // SETTINGSLOADER_H
