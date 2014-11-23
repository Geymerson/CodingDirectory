    #include "Encoding.h"

int main()
{

    encoding("test.txt");

//    int count[256] = {0};
//    QFile file("test.txt");

//    if(!file.open(QIODevice::ReadOnly))
//    {
//        qDebug() << "The file could not be read";
//        return 1;
//    }

//    while (!file.atEnd())
//    {
//        QByteArray line = file.readLine(1024);
//        for(int i = 0; i < line.size(); ++i)
//        {
//            ++count[(unsigned char) line.at(i)];
//        }
//    }

//    for(int j = 0; j < 256; ++j)
//    {
//        if(count[j])
//            qDebug() << j <<count[j];
//            //qDebug() << qPrintable(QString::number(j, 16)) << count[j];
//    }
//    return 0;
    return 0;
}
