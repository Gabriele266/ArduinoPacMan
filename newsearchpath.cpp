#include "newsearchpath.h"
#include "ui_newsearchpath.h"

NewSearchPath::NewSearchPath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSearchPath)
{
    ui->setupUi(this);
}

NewSearchPath::~NewSearchPath()
{
    delete ui;
}

void NewSearchPath::on_buttonBox_accepted()
{
    // Emetto il sengale
    emit pathAccepted(ui->pathEditor->text());
}

void NewSearchPath::on_pathEditor_textChanged(const QString &arg1)
{
    // Controllo che non sia vuoto
    if(arg1 != ""){
        if(QDir(arg1).exists()){
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        }
        else{
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        }
    }
}
