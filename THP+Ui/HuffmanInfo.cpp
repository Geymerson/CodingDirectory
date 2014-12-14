#include "HuffmanInfo.h"

void showInfo()
{
    qDebug() << "Comando invalido! Use:";
    qDebug() << "\t <huffman -c arquivo_origem.x -o arquivo_de_saida.huff> para comprimir e gerar"
             << "um arquivo de saida arquivo_de_saida.huff";
    qDebug() << "\t <huffman -c arquivo.x> para comprimir o arquivo.x e gerar um arquivo de saida 'arquivo.huff'";
    qDebug() << "\t <huffman arquivo.huff> para descomprimir o arquivo arquivo.huff na pasta local";
    qDebug() << "\t <huffman arquivo.huff -d /home/user/destino> para descomprimir no diretorio desejado\n";
}

void codError(bool value)
{
    if(!value)
    {
        qDebug() << "Error! corrupted file.";
    }
}
