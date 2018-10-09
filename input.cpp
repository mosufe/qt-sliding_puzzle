#include "resources.h"
#include <QInputDialog>
#include <QDir>

Input::Input(){
    bool ok;
        text = QInputDialog::getText(0, "Parabéns! Voce Completou o jogo!","Seu Nome:", QLineEdit::Normal,QDir::home().dirName(), &ok);
        if (ok && !text.isEmpty()){
            printf("%s",text.toUtf8().constData());
        }
}
