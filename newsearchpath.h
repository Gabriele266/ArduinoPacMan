#ifndef NEWSEARCHPATH_H
#define NEWSEARCHPATH_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>

namespace Ui {
class NewSearchPath;
}

class NewSearchPath : public QDialog
{
    Q_OBJECT

public:
    explicit NewSearchPath(QWidget *parent = nullptr);
    ~NewSearchPath();

signals:
    /// Emesso quando si accetta e si ha un percorso immesso
    void pathAccepted(QString path);

private slots:
    void on_buttonBox_accepted();

    void on_pathEditor_textChanged(const QString &arg1);

    void on_editButton_clicked();

private:
    Ui::NewSearchPath *ui;
};

#endif // NEWSEARCHPATH_H
