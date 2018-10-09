#include "resources.h"
#include <QApplication>
#include <QFile>
#include <QDataStream>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>

    struct score{
        QString name;
        float time;
        int moves;
    };

    score scoreList [20];


    void RecordWindow::resetList (){
        for (int i=0; i < sizeof(scoreList) / sizeof(*scoreList); i++){
            scoreList[i].name = "...";
            scoreList[i].time = float(0);
            scoreList[i].moves = int(0);
        }
    }

    void RecordWindow::writeFile (){
        QFile f("Hall_of_fame.txt");

        if (!f.open(QIODevice::WriteOnly))
            qFatal("Could not open file");

        QDataStream out(&f);
        out.setVersion(QDataStream::Qt_4_6);

        for (int i=0; i < sizeof(scoreList)/sizeof(*scoreList); i++){
            out << scoreList[i].name;
            out << scoreList[i].time;
            out << scoreList[i].moves;
        }
        f.close();
    }

    void RecordWindow::readFile (){
        QFile f("Hall_of_fame.txt");

        if (!f.open(QIODevice::ReadOnly))
            qFatal("Could not open file");

        QDataStream in(&f);
        in.setVersion(QDataStream::Qt_4_6);

        for (int i=0; (!f.atEnd()) and (i < sizeof(scoreList)); i++){
            in >> scoreList[i].name;
            in >> scoreList[i].time;
            in >> scoreList[i].moves;
        }
        f.close();
    }

    void RecordWindow::createWindow(int jogadas){
        recordWindow.setWindowTitle("Score Board");
        recordWindow.resize(700,700);

        QGridLayout gridLayout;
        QLabel *name = new QLabel("Nome");
        name->setAlignment(Qt::AlignCenter);
        QLabel *movements = new QLabel("Movimentos");
        movements->setAlignment(Qt::AlignCenter);
        QLabel *time = new QLabel("Tempo");
        time->setAlignment(Qt::AlignCenter);

        gridLayout.addWidget(name,0,0,1,1);
        gridLayout.addWidget(movements,0,1,1,1);
        gridLayout.addWidget(time,0,2,1,1);

        QLabel *labels [20][3];

        for (int i=1;i<10;i++){
            labels[i][0] = new QLabel();
            labels[i][1] = new QLabel();
            labels[i][2] = new QLabel();

            labels[i][0]->setAlignment(Qt::AlignCenter);
            labels[i][1]->setAlignment(Qt::AlignCenter);
            labels[i][2]->setAlignment(Qt::AlignCenter);

            labels[i][0]->setText(scoreList[i].name);
            labels[i][1]->setText(QString::number(scoreList[i].time));
            labels[i][2]->setText(QString::number(scoreList[i].moves));
            gridLayout.addWidget(labels[i][0], i, 0, 1, 1);
            gridLayout.addWidget(labels[i][1], i, 1, 1, 1);
            gridLayout.addWidget(labels[i][2], i, 2, 1, 1);
        }

        recordWindow.setLayout(&gridLayout);
        recordWindow.show();
    }
