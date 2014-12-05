#include "Decoding.h"

void treeCreate(Node<char> *tree, QByteArray *treeRep)
{
    if(treeRep->length() == 0 || tree == 0)
    {
        return;
    }

    if(treeRep->at(0) == '(')
    {
        tree->left = new Node<char>;
        tree->right = new Node<char>;
        treeRep->remove(0, 1);
    }
    else if(treeRep->at(0) == '*')
    {
        if(treeRep->length() > 1)
        {
            if(treeRep->at(1) == '(' || treeRep->at(1) == '*')
            {
                tree->content = treeRep->at(1);
                treeRep->remove(0, 2);
            }
            else
            {
                tree->content = treeRep->at(0);
                treeRep->remove(0, 1);
            }
        }
        else
        {
            tree->content = treeRep->at(0);
            treeRep->remove(0, 1);
        }
        return;
    }
    else
    {
        tree->content = treeRep->at(0);
        treeRep->remove(0, 1);
        return;
    }
    treeCreate(tree->left, treeRep);
    treeCreate(tree->right, treeRep);
}



int decoding(QString ioFileName[])
{

//############################## Openning the File ##################################

    QFile file(ioFileName[0]);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "The file could not be read";
        return 1;
    }

//############################## Read Process #######################################

    QByteArray line = file.read(3);
    QByteArray codArray, treeRep, aux1, aux2, aux3;
    QString name;
    int trash, treeSize, nameSize;
    bool ok;

    aux1.append(QByteArray::number(line.at(0), 2).rightJustified(8, '0').right(8));
    aux2.append(aux1.right(5));
    aux2.append(QByteArray::number(line.at(1), 2).rightJustified(8, '0').right(8));
    aux1.truncate(3);
    aux3.append(line.at(2));
    //qDebug() << aux3;

    trash = aux1.toInt(&ok, 2);
    treeSize = aux2.toInt(&ok, 2);
    nameSize = aux3.toInt(&ok, 16);
    name = file.read(nameSize); //Original name
    treeRep = file.read(treeSize);

    if(ioFileName[1] != "oName") //If not the original name, use the name informed by the user
    {
        name = ioFileName[1];
    }

    QFile outFile(name);
    outFile.open(QIODevice::WriteOnly);

//############################## Creating the tree #######################################

    Node<char> *tree = new Node<char>;
    treeCreate(tree, &treeRep);
    Node<char> *tempCursor = tree;
    //tree->show(tree);

//############################## Decodification process ####################################

    while(!file.atEnd())
    {
        line = file.read(8000);
        if(!file.atEnd())
        {
            for(int i = 0; i < line.length(); i++)
            {
                QByteArray temp = QByteArray::number(line.at(i), 2).right(8).rightJustified(8,'0');
                for(int j = 0; j < temp.length(); j++)
                {
                    if(temp.at(j) == '0')
                    {
                        tempCursor = tempCursor->left;
                    }
                    else if(temp.at(j) == '1')
                    {
                        tempCursor = tempCursor->right;
                    }
                    if(tempCursor->isLeaf(tempCursor))
                    {
                        codArray.append((char) tempCursor->content);
                        tempCursor = tree;
                    }
                }
            }
            if(codArray.length() >= 8000)
            {
                outFile.write(codArray);
                codArray.clear();
            }
        }
        else
        {
            for(int i = 0; i < line.length(); i++)
            {
                QByteArray temp = QByteArray::number(line.at(i), 2).right(8).rightJustified(8,'0');
                if(i == (line.length() - 1)) //last byte
                {
                    for(int j = 0; j < temp.length() - trash; j++)
                    {
                        if(temp.at(j) == '0')
                        {
                            tempCursor = tempCursor->left;
                        }
                        else if(temp.at(j) == '1')
                        {
                            tempCursor = tempCursor->right;
                        }
                        if(tempCursor->isLeaf(tempCursor))
                        {
                            codArray.append((char) tempCursor->content);
                            tempCursor = tree;
                        }
                    }
                }
                else
                {
                    for(int j = 0; j < temp.length(); j++)
                    {
                        if(temp.at(j) == '0')
                        {
                            tempCursor = tempCursor->left;
                        }
                        else if(temp.at(j) == '1')
                        {
                            tempCursor = tempCursor->right;
                        }
                        if(tempCursor->isLeaf(tempCursor))
                        {
                            codArray.append((char) tempCursor->content);
                            tempCursor = tree;
                        }
                    }
                }
            }
        }
    }

    outFile.write(codArray);
    tree->clear(tree);
    file.close();
    outFile.close();
    return 0;
}
