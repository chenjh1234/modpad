#include <iostream>
#include <QDebug>
#include <QtGlobal>
#include <Qt>
#include <QApplication>// if we add it qDebug() cannot work
#include <QDebug>
#include "modapp.h"
#include "moddata.h"
#include "modmain.h"
using namespace std;
 
 
int main(int argc, char *argv[])
{
    
    //qInstallMessageHandler((QtMessageHandler)myMessageOutput);
    modApp app(argc, argv);
    app.setOrganizationName(ORG_NAME);
    app.setApplicationName(APP_NAME);

    modData doc;
    app.m_doc = &doc;
 
    modMain mainWin;
    app.m_win = &mainWin;

    mainWin.show();
    return app.exec();
 
} 

