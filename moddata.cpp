#include <moddata.h>

modData::modData()
{
    init(); 

}
//-----------------
modData::~modData()
{

}
//----------------------------------
void modData::init()
{
    m_modIndex = QModelIndex() ;
    //m_paramIndex = QModelIndex();
   // m_valueIndex = QModelIndex();

}
//=====================================================
void modInfo::set(QString n,QString t,QString s)
{
    name = n;
    type= t;
    spec = s;
}
void paramInfo::set(QString n,QString t,QString s,QString d)
{
    name = n;
    type= t;
    spec = s;
    doc = d;

}
void valueInfo::set(QString n,QString t,QString s,QString d)
{
    value = n;
    type= t;
    spec = s;
    doc = d;

}

