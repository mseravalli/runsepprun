#include <QtCore>

int main()
{
    QList<QString> files;

    QString xmlName = "level3";

    files.append(xmlName + ".xml");
    files.append(QString("snow.svg"));
    files.append(QString("background1.svg"));
    files.append(QString("cloud.svg"));
    files.append(QString("coin.svg"));
    files.append(QString("cloud.svg"));
    files.append(QString("collectEgg.svg"));
    files.append(QString("egg.svg"));
    files.append(QString("flag.svg"));
    files.append(QString("grave.svg"));
    files.append(QString("ice.svg"));
    files.append(QString("ice2.svg"));
    files.append(QString("igloo.svg"));
    files.append(QString("pins.svg"));
    files.append(QString("snowman.svg"));
    files.append(QString("snowtree.svg"));
    files.append(QString("transparent.svg"));

    // DO NOT EDIT

    QByteArray fileContents[files.size()];
    
    for(int i = 0; i < files.size(); i++)
    {
        QFile f(files[i]);
        f.open(QIODevice::ReadOnly);
        fileContents[i] = f.readAll();
        f.close();
    }


    QFile out(xmlName + ".level");
    out.open(QIODevice::WriteOnly | QIODevice::Truncate);

    out.write("\x12");
    out.write("\x24");

    QByteArray tmp;

    tmp.clear();
    tmp.append((char) files.size());
    out.write(tmp);

    for(int i = 0; i < files.size(); i++)
    {
        tmp.clear();
        tmp.append((char) files.at(i).length());
        out.write(tmp);
    }

    for(int i = 0; i < files.size(); i++)
    {
        int t1 = fileContents[i].size() / (256*256*256);
        int t2 = (fileContents[i].size() % (256*256*256)) / (256*256);
        int t3 = ((fileContents[i].size() % (256*256*256)) % (256*256))  / 256;
        int t4 = ((fileContents[i].size() % (256*256*256)) % (256*256))  % 256;

        qDebug() << t1 << t2 << t3 << t4;
        tmp.clear();
        tmp.append((char) t1 );
        tmp.append((char) t2 );
        tmp.append((char) t3 );
        tmp.append((char) t4 );
        out.write(tmp);
    }

    for(int i = 0; i < files.size(); i++)
    {
        tmp.clear();
        tmp.append(files.at(i));
        out.write(tmp);
    }

    for(int i = 0; i < files.size(); i++)
    {
        out.write(fileContents[i]);
    }

    out.close();

    return 0;
} 
