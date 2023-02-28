#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
#include <QString>

class FileLoader : public QObject
{
    Q_OBJECT
public:
    explicit FileLoader(QObject *parent = nullptr);
    QString getFilePath() const;

public slots:
    QString loadFile(const QString& filePath) const;

private:
    QString filePath;

};

#endif // FILELOADER_H
