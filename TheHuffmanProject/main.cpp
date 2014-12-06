#include "Decoding.h"
#include "Encoding.h"
#include "HuffmanInfo.h"
#include <QDir>

int main(int argc, char *argv[])
{
    QString filePath, extenCheck; // file path /extension check variable
    QString ioFileName[2]; // input/output file name
    QString mode[2]; //compress or decompress mode -c/-d

    if(argc == 5 || argc == 3) //compress
    {
        ioFileName[0] = argv[2]; //input file name
        //qDebug() << ioFileName[0];
        mode[0] = argv[1]; //-c
        if(argc == 5 && mode[0] == "-c")
        {
            mode[1] = argv[3]; //-o
            if(mode[1] == "-o")
            {
                ioFileName[1] = argv[4]; //output file name
                extenCheck = ioFileName[1].right(5);
                if(extenCheck == ".huff")
                {
                    encoding(ioFileName);//encoding function
                }
                else
                {
                    qDebug() << "\nExtensao nao .huff\n";
                    showInfo(); //informations about compressing and decompressing
                }
            }
        }
        else if(argc == 3 && mode[0] == "-c")
        {
            ioFileName[1] = "oName";
            encoding(ioFileName); //decoding function
        }
        else
        {
            showInfo();
        }
    }
    else if(argc == 4 || argc == 2) //decompress
    {
        ioFileName[0] = argv[1];
        extenCheck = ioFileName[0].right(5);
        if(extenCheck == ".huff")
        {
            if(argc == 4)
            {
                mode[0] = argv[2]; //-d
                if(mode[0] == "-d")
                {
                    filePath = argv[3];//home/user/path
                    QDir savingPath(filePath);
                    if(savingPath.exists())
                    {
                        ioFileName[1] = filePath;
                        decoding(ioFileName);
                    }
                    else
                    {
                        qDebug() << "\nDiretorio inexistente\n";
                    }
                }
                else
                {
                    showInfo();
                }
            }
            else
            {
                ioFileName[1] = "oName";
                decoding(ioFileName);
            }
        }
        else
        {
            qDebug() << "\nExtensao nao .huff\n";
            showInfo();
        }
    }
    else
    {
        showInfo();
    }
    return 0;
}
