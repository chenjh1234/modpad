#ifndef MODMAIN_H
#define MODMAIN_H
#include <QDebug>
#include <QMainWindow>
#include <QSplitter>
#include <QString>
#include <QTabWidget>
#include <QDockWidget>
#include <QTextBrowser>
#include <QProcess>
#include <iostream>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>

#include "csException.h"
#include "csStandardHeaders.h"
#include "csHeaderInfo.h"
#include "csVector.h"
#include "csException.h"

//#include "moddata.h"
#include "modview.h"
#include "ui_module.h"
#include "ui_parmvalue.h"
#include "ui_modparameter.h"
// mark in the module
#define ADD_VAR "ADD_VAR:"
#define ADD_INITD "ADD_INIT_DEFAULT:"
#define ADD_INITP "ADD_INIT_PARAMETERS:"
#define ADD_SETP "ADD_PARAMETERS:"
#define MOD_SINGLE_STR "EXEC_TYPE_SINGLETRACE"
#define MOD_NAME "MODNAME"

// mark for spell
#define QMARK "\""
#define IDENT QString("    ")
#define IDENT2 QString("    ")+QString("    ")
#define DEFAULT_NUMBER "-999"
#define DEFAULT_STRING "\"\""

using namespace std;
using namespace cseis_geolib;
 
class modMain : public QMainWindow
{
    Q_OBJECT

public:
    modMain();


/**
     * get parameters from widget to m_data
     */
    void getValue();
    void getParam();
    void getMod();
/**
     * set parameters   to widget(m_data ? x)
     */
    void setValue(QString v,QString t,QString s,QString d);
    void setParam(QString n,QString t,QString s,QString d);
    void setMod(QString n,QString t,QString s);

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    void setTitle();
    int createSubCPP();
    QStringList getHeader();
    void  setHeader();

    QString m_subSetParam,m_subDefault,m_subVar,m_subGetParam;
    QString m_modType;

    QMenu *fileMenu;
    QMenu *modifyMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    QAction *openFileAct;
    QAction *createCPPAct;
    QAction *saveFileAct;
    QAction *saveFileAsAct;
    QAction *exitAct;

    QAction *moveUpAct;
    QAction *moveDownAct;
    QAction *removeAct;

    QAction *aboutAct;
    QAction *helpAct;

 
protected:
    void closeEvent(QCloseEvent *event);
     

   // QPlainTextEdit *textEdit;
    //QTextBrowser *textView;
    //QSplitter *split;
    modView *modview;
    QTabWidget *tabWidget;
    QDockWidget *modDockWidget;
    QWidget *modWidget;

    //treeView *treeProject;
    //listView *listFlow,*listJob,*listData,*listLog,*listTable;
    //createpDlg *dlgCreate;
    //modData *m_data;

    QString curFile;

    QProcess run;

    QString modhead;
    

private slots:
    //ui push buttons:
    void slotModUpdate();
    void slotParamAdd(); 
    void slotParamClear();
    void slotValueAdd();
    void slotValueClear();
    void slotSelectSet();//when select item in tree,set data for ui components
    

    // for treevie items
    void slotMoveUp();
    void slotMoveDown();
    void slotRemove();
    // foor toolbar:
    void slotOpenFile();
    void slotCreateCPP();//create module.cpp and makefile
    void slotSaveFile();
    void slotSaveAsFile();
    void slotHelp();
    void slotAbout();
    void slotValueHeader(); // set the selected header to defalt

signals:
    void sigModUpdate();
    void sigParamAdd();
    void sigValueAdd();

private:
        QWidget *topw,*btw,*midw;
        QVBoxLayout *vLayout;
    Ui::FormParam formParam;
    Ui::FormMod formMod;
    Ui::FormValue formValue;
 
};
  
#endif

