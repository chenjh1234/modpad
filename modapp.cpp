#include "modapp.h"
modApp *theApp;

modApp::modApp( int & argc, char ** argv ):QApplication(argc,argv)
{
    theApp = this;
}
modApp::~modApp()
{
}

