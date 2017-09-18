#ifndef MODAPP_H
#define MODAPP_H

#include <QApplication>
#include "modmain.h"
#include "moddata.h"
#include <iostream>
class modApp;
//class modMain;

#define DOC theApp->m_doc

using namespace std;
extern modApp *theApp;
 
class modApp :public QApplication  
{
public:
    modApp( int & argc, char ** argv );
    ~modApp();
    modData *m_doc;
    modMain *m_win;

private:

};
#endif
