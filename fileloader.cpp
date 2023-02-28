#include "fileloader.h"
#include <QFile>
#include <QTextStream>

FileLoader::FileLoader(QObject *parent) : QObject(parent)
{
}

QString FileLoader::loadFile(const QString& filePath) const
{
    QString contents;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return contents;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
    contents = in.readAll();

    file.close();

    return contents;
}

QString FileLoader::getFilePath() const {
    return filePath;
}
