#ifndef ARCH_H
#define ARCH_H

#include <QtCore>
#include "Globals.h"

/*!
  This struct defines the structure of the archive
  */
typedef struct
{
    int* fnlength; // Array of lenghts of the filenames
    int* fclength;  // Array of lenghts of the file contents
    QString* fname; // Array of filenames
    QByteArray* fcontent; // Array of file contents
} levelArch;

/*!
  Extracts an archive given its path, relative to the application or absolute.
  The extracted files are extracted in the directory ./level relative to the application.
  */
void extract(QString fileName)
{
    // Read data
    QFile f(fileName);

    if (!f.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open file: " << fileName;
        return;
    }

    QByteArray file = f.readAll();
    f.close();
    // End read data

    // Parse data
    if(file.at(0) != ARCH_ID1 && file.at(1) != ARCH_ID2)
    {
        qDebug() << "Corrupt file1: " << fileName;
        return;
    }
    int noFiles = (int) file.at(2);

    // Create struct
    levelArch *level = new levelArch;
    level->fnlength = new int[noFiles];
    level->fclength = new int[noFiles];
    level->fname = new QString[noFiles];
    level->fcontent = new QByteArray[noFiles];

    int ftell = 3;

    for(int i = 0; i < noFiles; i++)
    {
        if(ftell > file.size())
        {
            qDebug() << "Corrupt file2: " << fileName;
            return;
        }

        level->fnlength[i] = (int) file.at(ftell);

        ftell++;
    }

    for(int i = 0; i < noFiles; i++)
    {
        if(ftell + 3 > file.size())
        {
            qDebug() << "Corrupt file3: " << fileName;
            return;
        }

        level->fclength[i] = (unsigned char) file.at(ftell) * 256 * 256 * 256 + (unsigned char) file.at(ftell + 1) * 256 * 256 + (unsigned char) file.at(ftell + 2) * 256 + (unsigned char) file.at(ftell + 3);
        ftell += 4;
    }

    for(int i = 0; i < noFiles; i++)
    {
        if(ftell + level->fnlength[i] > file.size())
        {
            qDebug() << "Corrupt file4: " << fileName;
            return;
        }

        for(int j = 0; j < level->fnlength[i]; j++ )
        {
            level->fname[i].append( file.at(ftell) );
            ftell++;
        }

    }

    for(int i = 0; i < noFiles; i++)
    {
        if(ftell + level->fclength[i] > file.size())
        {
            qDebug() << "Corrupt file5: " << fileName;
            return;
        }

        for(int j = 0; j < level->fclength[i]; j++ )
        {
            level->fcontent[i].append( file.at(ftell) );
            ftell++;
        }
    }
    // End parsing

    // Write files
    QDir().mkdir(LEVEL_DIR);

    for(int i = 0; i < noFiles; i++)
    {
        QString fileName("");
        fileName.append(LEVEL_DIR);
        fileName.append("/");
        fileName.append(level->fname[i]);

        QFile out(fileName);
        if (!out.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qDebug() << "Could not write file: " << fileName;
            return;
        }

        out.write(level->fcontent[i]);

        out.close();
    }

    // End write files

    return;
}

#endif
