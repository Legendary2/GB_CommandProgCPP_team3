#include "helpbrowser.h"
#include "ui_helpbrowser.h"

helpbrowser::helpbrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helpbrowser)
{
    ui->setupUi(this);

    helpbrowser hb("/helpfiles", "index.htm");
    hb.resize(300, 250);
    hb.show();

}

helpbrowser::~helpbrowser()
{
    delete ui;
}
