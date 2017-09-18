#ifndef MODDATA_H 
#define MODDATA_H 
 
#include <QString>
#include <QMap>
#include <iostream>
#include <QModelIndex>

#define ORG_NAME "GEOSEIS"
#define APP_NAME "modPad"
#define APP_VERSION "1.00"
#define APP_DATE "2015.07"

//#define qDebug() cout

#define MOD "mod"
#define PARAM "param"
#define PVALUE "pvalue"
#define  MODEXT ".mdef";
 
#define MOD_SINGLE_FILE "modsingle.model"
//================================
class valueInfo
{
public:
    valueInfo(){};
    QString type,value,spec,doc;
    QString pname;
    void set(QString,QString,QString,QString);
};       

class paramInfo
{
public:
    paramInfo(){};
    QString name,type,spec,doc;
    void set(QString,QString,QString,QString);
    QMap <QString,valueInfo> m_mapValues;
};
class modInfo
{
public:
    modInfo(){};
    QString name,type,spec;
    void set(QString,QString,QString);
    QMap <QString,paramInfo> m_mapParams;
};
//===============================================

     
 
class modData  
{
public:
    modData();
    ~modData();
    void init();

    QString m_modName;


    modInfo m_mod;
    paramInfo m_param;
    valueInfo m_value;

    QModelIndex m_modIndex;
    //QModelIndex m_paramIndex;
   // QModelIndex m_valueIndex;


};

#endif

