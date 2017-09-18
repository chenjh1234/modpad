#include<QMessageBox>
#include<QStandardItem>
#include "modapp.h"
#include "modview.h"
modView::modView(QWidget *p):QTreeView(p)
{
    init();
}
//=======================
modView::~modView()
{

}

//=======================
void modView::init()
{    
    setSortingEnabled(false);
    setEditTriggers(0);
    setSelectionMode(QAbstractItemView::SingleSelection);

    model=NULL;
    QStringList listh;
    listh << "name" <<"type" << "specification" << "document";
    //qDebug() << listh;
    setHeader(listh);
    //if(selectionModel!= NULL)  delete selectionModel; 
    selectionModel = new QItemSelectionModel(model);
    setSelectionModel(selectionModel);
 
}
 
int modView::setHeader(QStringList head)
{

    int num,i;
    num = head.size(); 
    if (model == NULL) 
    {
         model = new QStandardItemModel(1,num);
         setModel(model);      
    }
    model->setHorizontalHeaderLabels (head);
    
    for (i = 0; i <num ; i++)
    {     
        model->setHeaderData(i, Qt::Horizontal,tr( head[i].toUtf8().data()) );         
    }
    return 0;
}
 
int modView::addRow(QString str)
{
    QStringList  list;
    list.append(str);
    return addRow(list);

}
 
int modView::addRow(QStringList item)
{


    int num,idx,i;  
    idx = 0;  
    num =item.size(); 
    if (model ==NULL) 
    {
         model = new QStandardItemModel(1,num);       
    }
    model->insertRow(idx,QModelIndex());//insert from index 0;
    for (i = 0; i <num ; i++)
    {
        model->setData(model->index(idx,i,QModelIndex()),item[i]);
    }
    return 0; 
}
int modView::getParamRow()
{
    QModelIndex index;
    QString str;
    QList<QStandardItem *> items;
    int row;
    QStandardItem *item;
    QModelIndex idx;

    index = DOC->m_modIndex;
 
    item = model->itemFromIndex(index);
        
    // last selected:
    idx= m_index;//selected
    str = idx.data(Qt::StatusTipRole).toString();// type of the selected "mod.,param,value"
 
    qDebug() << "add param selected idx = " << idx.isValid() << str <<idx.row();

    if (idx.isValid())
    {
        if (str == MOD) //select module lever        
            if (item->rowCount() == 0) row = 0;// no parameters
            else row = item->rowCount();       // append
        else if(str == PARAM)//select param lever:
            //if (item->rowCount() == 0) row = 0; //no parameters no use
            //else row = idx.row() + 1;           // insert next to selected
            row = idx.row() + 1;                 // insert next to selected
        else if(str == PVALUE)//selected value:
            row =  idx.parent().row() + 1;
    }
    else 
        row =-1;
    return row;
}

int modView::getValueRow(QModelIndex &parent)
{
    QModelIndex index;
    QString str;
    QList<QStandardItem *> items;
    int row,i;
    QStandardItem *item;
    QModelIndex idx;

    index = DOC->m_modIndex;
 
    item = model->itemFromIndex(index);
        
    // last selected:
    idx= m_index;//selected
    str = idx.data(Qt::StatusTipRole).toString();// type of the selected "mod.,param,value"
 
    qDebug() << " add value selected idx = " << idx.isValid() << str  << idx.row();

    if (idx.isValid())
    {
        if (str == MOD) //select module lever        
            row = -1;
        else if(str == PARAM)//select param lever:
        {
            i = model->itemFromIndex(idx)->rowCount();
            qDebug() << " child num = " << i;
            if (i == 0) row = 0; //no values create one;
            else row = idx.row() + 1;           //append          
            parent = idx;  
        }
        else if(str == PVALUE)//selected value:
        {
            row =  idx.row() + 1;
            parent = idx.parent();
        }
    }
    else 
        row =-1;
    qDebug() << " add value get row return = " << parent.data().toString() <<row;
    return row;
}
 
QModelIndex modView::addChild(QStringList strlist,QModelIndex index,int row)
{
     
    QString str;
    QList<QStandardItem *> items;
    int i,num;
    QStandardItem *item,*itemc;
    QModelIndex idx;
    num = strlist.size(); 
  
    item = model->itemFromIndex(index);
    setExpanded(index,true);
 
    for (i = 0; i <num ; i++)
    {
        itemc = new QStandardItem();
        itemc->setData(strlist[i],Qt::DisplayRole);
        items << itemc;
    }
    item->insertRow(row,items);
    idx = model->index(row,0,index);
    //idx = model->index(row,0,DOC->m_modIndex);
   // qDebug() << "child1 = " <<idx.data().toString();
 
   //idx = item->takeChild(row)->index();
    // qDebug() << "child2 = " <<idx.data().toString();
    return idx;
}
void modView::modView::modView::slotModUpdate()
{
    QStringList strlist;
    QString str;
    QModelIndex idx;
    str = MOD;
    int i,num;
    qDebug("modupdate  in modtree\n");
    strlist << DOC->m_mod.name << DOC->m_mod.type <<DOC->m_mod.spec;
    num = strlist.size();

    if (model->rowCount() ==0 )
    {
        addRow(strlist);
    }
    //else
    {
        for (i = 0; i <num ; i++)
        {
            model->setData(model->index(0,i,QModelIndex()),strlist[i]);
            model->setData(model->index(0,i,QModelIndex()),strlist[i],Qt::ToolTipRole);
            
        }
        qDebug() << "MOD="<<str;
        model->setData(model->index(0,0,QModelIndex()),str,Qt::StatusTipRole);
        model->setData(model->index(0,0,QModelIndex()),QIcon(":/images/model.png"),Qt::DecorationRole);
    }
    idx = model->index(0,0,QModelIndex());
    selectionModel->select(idx,QItemSelectionModel::Select);
    DOC->m_modName = DOC->m_mod.name;
    DOC->m_modIndex = idx;
}
void modView::modView::slotParamAdd()
{
    QStringList strlist;
    QString str;
    QModelIndex idx;
    int row;

    qDebug() << "ParamAdd  in modtree\n =" <<DOC->m_param.name ;

    strlist << DOC->m_param.name << DOC->m_param.type <<DOC->m_param.spec <<DOC->m_param.doc;
    if(DOC->m_param.name.isEmpty())// name is empty is not allowed;
    {
        QMessageBox::warning(this,"Error"," The parameter Name cannot be NULL");
        return;
    }
    if(!DOC->m_param.name.at(0).isLetter())// first char is noe a letter is empty is not allowed;
    {
        QMessageBox::warning(this,"Error"," The initial of the parameter Name must  be a letter");
        return;
    }
    if (!DOC->m_modIndex.isValid())
    {
        QMessageBox::warning(this,"Error"," Plaese create module first");
        return;
    }
    row = getParamRow();
    if (row <0)
    {
        QMessageBox::warning(this,"Error"," No selected Parameter in Modtree");
        return;
    }
    //if the name exist:
    if(findParams(DOC->m_param.name))
    {
        QMessageBox::warning(this,"Error"," The Parameter name already exist");
        return;
    }

    
    idx  = addChild(strlist,DOC->m_modIndex,row);
    str = PARAM;
    model->setData(idx,str,Qt::StatusTipRole);
    model->setData(idx,QIcon(":/images/parameter.png"),Qt::DecorationRole);
    selectionModel->clear();
    selectionModel->select(idx,QItemSelectionModel::Select);
    //DOC->m_paramIndex = idx;
}
bool modView::findParams(QString name)
{
    QString str;
    QList<QStandardItem *> items;
    int i,num;
    QStandardItem *item;
    QModelIndex idx,index;

    index = model->index(0,0,QModelIndex());// index of the module;
    item = model->itemFromIndex(index);
    num = item->rowCount(); 
     
    for (i = 0; i <num ; i++)
    {
        idx = model->index(i,0,index);
        str = model->data(idx,Qt::DisplayRole).toString();
        if(str == name) 
            return true;
    }
    return false;

}
void modView::slotValueAdd()
{
    QStringList strlist;
    QString str;
    QModelIndex idx,parent;
    int row;

    qDebug("ValueAdd in modtree\n");
    strlist << DOC->m_value.value << DOC->m_value.type <<DOC->m_value.spec <<DOC->m_value.doc;
 
    if (!DOC->m_modIndex.isValid())
    {
        QMessageBox::warning(this,"Error"," Plaese create module first");
        return;
    }
    row = getValueRow(parent);
    if (row <0 || !parent.isValid() )
    {
        QMessageBox::warning(this,"Error"," No selected Parameter in Modtree");
        return;
    }
    idx  = addChild(strlist,parent,row);
    str = PVALUE;
    model->setData(idx,str,Qt::StatusTipRole);
    model->setData(idx,QIcon(":/images/value.png"),Qt::DecorationRole);
    selectionModel->clear();
    qDebug() << "add value idx v= " << idx.data().toString();
    selectionModel->select(idx,QItemSelectionModel::Select);
    //DOC->m_valueIndex = idx;
}
void modView::selectionChanged(const QItemSelection & selected, const QItemSelection & deselected)
{
    QTreeView::selectionChanged(selected, deselected);
    QModelIndex index,pindex;
    QString project,line;

    if (selected.indexes().size() == 0 ) return;
    index = selected.indexes().at(0);  
    m_index = index;
    //qDebug()<< "select changed = " << index.isValid() << index.row();
    emit selectOK();
}
  
 
