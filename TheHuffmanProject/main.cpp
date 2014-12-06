#include "Decoding.h"
#include "Encoding.h"
#include "HuffmanInfo.h"

int main(int argc, char *argv[])
{
    QString filePath, extenCheck; // file path /extension check variable
    QString ioFileName[2]; // input/output file name
    QString mode[2]; //compress or decompress mode -c/-d

    if(argc == 5 || argc == 3) //compress
    {
        ioFileName[0] = argv[2]; //input file name
        mode[0] = argv[1]; //-c
        mode[1] = argv[3]; //-o
        if(argc == 5 && mode[0] == "-c" && mode[1] == "-o")
        {
            ioFileName[1] = argv[4]; //output file name
            extenCheck = ioFileName[1].right(5);
            if(extenCheck == ".huff")
            {
                encoding(ioFileName);//encoding function
            }
            else
            {
                showInfo(); //informations about compressing and decompressing
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
                filePath = argv[3];
                mode[0] = argv[2];
                if(mode[0] == "-d")
                {
                    //Unfinished
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
            qDebug() << "\nExtensao nao .huff";
            showInfo();
        }
    }
    else
    {
        showInfo();
    }
    return 0;
}
