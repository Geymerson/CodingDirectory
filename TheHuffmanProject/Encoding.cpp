#include "Encoding.h"

//Creates the codification of the characters
void charCodification(Node<int> *tree, Node<int> *left,
                      Node<int> *right, QString aux[], QString sample)
{
    if(tree != 0)
    {
        Node<int> *temp = tree;

        if(temp == left)
        {
            sample.append(QString::number(0, 10));
        }
        else if(temp == right)
        {
            sample.append(QString::number(1, 10));
        }
        if(tree->isLeaf(tree))
        {
           aux[tree->content] = sample;
           //qDebug() << tree->content << ":"<< aux[tree->content];
           sample.remove(sample.size() - 1, 1);
           return;
        }
        charCodification(tree->left, tree->left, tree->right, aux, sample);
        charCodification(tree->right, tree->left, tree->right, aux, sample);
        sample.remove(sample.size() - 1, 1);
        return;
    }
    return;
}

//Creates the representation of the tree
void treeRepresentation(Node<int> *tree, QByteArray *k)
{
    if(tree->isLeaf(tree))
    {
        if(tree->content == 40 || tree->content == 42)
        {
            k->append('*').append(tree->content);
        }
        else
        {
            k->append(tree->content);
        }
        return;
    }
    k->append('(');
    treeRepresentation(tree->left, k);
    treeRepresentation(tree->right, k);
    return;
}

//Creates the file codification
int encoding(QString ioFileName[])
{
    if(ioFileName[1] == "oName") //if original name used for the output file
    {
        int i = ioFileName[0].length();
        int j = 1;
        while(ioFileName[0].at(i - 1) != '.')
        {
            i--;
            j++;
        }
        ioFileName[1] = ioFileName[0].left(ioFileName[0].length() - j); //Removing the .ext from the fileName
    }
    ioFileName[1].append(".huff"); //output file: fileName.huff

    QFile file(ioFileName[0]); //input file
    QFile codFile(ioFileName[1]); //output file
    codFile.open(QIODevice::WriteOnly);

    QString aux1;
    QByteArray aux2, aux3;
    LinkedList<int> list; //list to create the tree
    int count[256] = {0};

    aux2.append("00"); //First two bytes for trash and tree size
    unsigned char fileNameSize = ioFileName[0].length();
    qDebug() << fileNameSize;
    aux2.append(fileNameSize); //inserts the file size
    aux2.append(ioFileName[0]); //inserts the file name
    codFile.write(aux2);
    aux2.clear();

//############################## Openning the File ##################################

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "The file could not be read";
        return 1;
    }

//################## Character count and making the the linked list #################

    while (!file.atEnd())
    {
        QByteArray line = file.read(8000);
        for(int i = 0; i < line.size(); ++i)
        {
            ++count[(unsigned char) line.at(i)];
        }
    }
    for(int j = 0; j < 256; ++j) // "j"represents the character
    {
        if(count[j])
        {
            list.insert(j, count[j]); //inserting character, character quantity in a linked list
        }
    }

//############################### building the tree ##############################

    Node<int> *tree;
    int sum;

    if(list.length() == 1)
    {
        tree = new Node<int>(list.getValue(), list.getQuantity());
    }
    else
    {
        while(list.length() != 1)
        {
            list.bubbleSort();//Ordenate the list
            sum = list.getQuantity();
            list.next();
            sum += list.getQuantity(); //Holds the sum of the two first nodes quantity
            list.moveToStart(); //moves to the start of the list
            tree = new Node<int>(0, sum);
            if(list.getPointer())
            {
                tree->left = list.getPointer();
            }
            else
            {
                tree->left = new Node<int>(list.getValue(), list.getQuantity());
            }
            list.remove();
            if(list.getPointer())
            {
                tree->right = list.getPointer();
            }
            else
            {
                tree->right = new Node<int>(list.getValue(), list.getQuantity());
            }
            list.remove();
            list.pInsert(tree->content, tree->quantity, tree);
        }
    }
    //tree->show(tree);

//############################ Tree representation ##################################

    QByteArray treeRep;
    treeRepresentation(tree, &treeRep); //treeRep holds the representation of the tree
    codFile.write(treeRep);
//    qDebug() << treeRep;
//    qDebug() << treeRep.length();

//############################ Generating the Codification ##########################

    QString codVector[256];
    if(tree->isLeaf(tree))
    {
        //qDebug() << "Here 1";
        QString temp('0');
        codVector[(unsigned char)tree->content] = temp;
    }
    else
    {
        //qDebug() << "Here 2";
        charCodification(tree, 0, 0, codVector, aux1);//Now CodVector has char's codification
    }
    int trash = 0;

    QByteArray codArray;
    bool ok;
    file.seek(0); //Move the cursor to the start of the file

    while (!file.atEnd())
    {
        QByteArray line = file.read(8000);
        for(int i = 0; i < line.size(); ++i)
        {
            codArray.append(codVector[(unsigned char) line.at(i)]);
            //qDebug() << codArray;
            if(codArray.length() >= 8)
            {
                aux3 = codArray.left(8);
                char ch = (unsigned char) aux3.toInt(&ok,2);
                aux2.append(ch);
                aux3.clear();
                codArray.remove(0, 8);
                if(aux2.length() >= 1000)
                {
                    codFile.write(aux2);
                    aux2.clear();
                }
            }
        }
        if(file.atEnd())
        {
            if(codArray.length() % 8)
            {
                trash = 8 - (codArray.length() % 8);

                for(int i = 0; i < trash; i++)
                {
                    codArray.append('0');
                }
                char ch = (unsigned char)codArray.toInt(&ok, 2);
                aux2.append(ch);
                codArray.clear();
            }
        }
    }
    codFile.write(aux2);
    codArray.clear();
    aux2.clear();

//############################ Formating trash and treeSize #########################

    aux2.append(QByteArray::number(trash, 2).rightJustified(3, '0'));
    //qDebug() << aux2;
    aux2.append(QByteArray::number(treeRep.length(), 2).rightJustified(13,'0'));
    //qDebug() << aux2;

    codFile.seek(0);
    for(int i = 0; i < 16; i++) //inserting the first and the second byte for trash and tree size
    {
        aux3.append(aux2.at(i));
        if(aux3.length() == 8)
        {
            char ch = (unsigned char)aux3.toInt(&ok, 2);
            codArray.append(ch);
            codFile.write(codArray);
            aux3.clear();
            codArray.clear();
        }
    }

    codFile.close();
    file.close();
    tree->clear(tree);
    return 0;
}
