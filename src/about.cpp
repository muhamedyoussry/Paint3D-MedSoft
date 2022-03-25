#include "about.h"
#include "ui_about.h"
#include <QDesktopServices>
#include <QUrl>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

}

About::~About()
{
    delete ui;
}

void About::on_closeDialog_clicked()
{
    this->close();
}


void About::on_moreInfoDialog_clicked()
{
    QDesktopServices::openUrl(QUrl("https://medsft.com/", QUrl::TolerantMode));
}

