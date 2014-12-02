#include "Decoding.h"

void treeCreat(Node<char> *tree, QByteArray *treeRep)
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
    treeCreat(tree->left, treeRep);
    treeCreat(tree->right, treeRep);
}

int decoding(QString fileName)
{

//############################## Openning the File ##################################

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "The file could not be read";
        return 1;
    }

//############################## Read Process #######################################

    QByteArray line = file.read(3);
    QByteArray sample(QByteArray::number(line.at(0), 2).rightJustified(8, '0'));
    bool ok;

    QByteArray sample2(sample.right(5));
    sample2.append(QByteArray::number(line.at(1), 2).rightJustified(8, '0'));
    //qDebug() << sample2;
    sample.truncate(3);

    int trash = sample.toInt(&ok, 2);
    int treeSize = sample2.toInt(&ok, 2);
    int nameSize = line.at(2);

    QString name = file.read(nameSize);
    QByteArray treeRep = file.read(treeSize);
//    qDebug() << treeRep;

    Node<char> *tree = new Node<char>;
    Node<char> *tempCursor = tree;
    treeCreat(tree, &treeRep);

    //tree->show(tree);

    QFile testFile("sampleFile.huff");
    testFile.open(QIODevice::WriteOnly);
    QByteArray codArray;

    while(!file.atEnd())
    {
        line = file.read(8000);
        //qDebug() << line;
        if(!file.atEnd())
        {
            //qDebug() << line.length();
            for(int i = 0; i < line.length(); i++)
            {
                QByteArray temp = QByteArray::number(line.at(i), 2).right(8).rightJustified(8,'0');
                //qDebug() << temp;

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
                        qDebug() << tempCursor->content;
                        tempCursor = tree;
                    }
                }
            }
            if(codArray.length() >= 8000)
            {
                testFile.write(codArray);
                codArray.clear();
            }
        }
        else
        {
            for(int i = 0; i < line.length(); i++)
            {
                QByteArray temp = QByteArray::number(line.at(i), 2).right(8).rightJustified(8,'0');
                qDebug() << temp;
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
                            qDebug() << tempCursor->content;
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
                            qDebug() << tempCursor->content;
                            tempCursor = tree;
                        }
                    }
                }
            }
        }
    }

    testFile.write(codArray);

    tree->clear(tree);
    file.close();
    testFile.close();
    return 0;
}
