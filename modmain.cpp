#include "modapp.h"
#include "modmain.h"
#include <QSettings>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QModelIndex>
 
modMain::modMain():QMainWindow()
{
    modDockWidget = new QDockWidget(this);
    modDockWidget->setObjectName("modWidget");

  
    addDockWidget(Qt::LeftDockWidgetArea, modDockWidget);
     
    //textView = new QTextBrowser(this);
    modview = new modView(this);
    DOC = theApp->m_doc ;

    setCentralWidget(modview);

    //tabWidget = new QTabWidget();
    modWidget = new QWidget(this);
    modDockWidget->setWidget(modWidget);

    
    vLayout = new QVBoxLayout(modWidget);

    topw = new QWidget(modWidget);
    midw = new QWidget(modWidget);
    btw = new QWidget(modWidget);

    formMod.setupUi(topw);
    formParam.setupUi(midw);
    formValue.setupUi(btw);

    vLayout->addWidget(topw);
    vLayout->addWidget(midw);
    vLayout->addWidget(btw);
 
     //buttons:
    connect(formMod.pushButtonUpdate, SIGNAL(clicked()), this, SLOT(slotModUpdate()));

    connect(formParam.pushButtonAdd, SIGNAL(clicked()), this, SLOT(slotParamAdd()));
    connect(formParam.pushButtonClear, SIGNAL(clicked()), this, SLOT(slotParamClear()));

    connect(formValue.pushButtonAdd, SIGNAL(clicked()), this, SLOT(slotValueAdd()));
    connect(formValue.pushButtonClear, SIGNAL(clicked()), this, SLOT(slotValueClear()));
    connect(formValue.pushButtonAddHeader, SIGNAL(clicked()), this, SLOT(slotValueHeader()));
    // modview 
    connect(this, SIGNAL(sigModUpdate()), modview, SLOT(slotModUpdate()));
    connect(this, SIGNAL(sigParamAdd()), modview, SLOT(slotParamAdd()));
    connect(this, SIGNAL(sigValueAdd()), modview, SLOT(slotValueAdd()));
    //main:
    connect(modview, SIGNAL(selectOK()), this, SLOT(slotSelectSet()));
  
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

     
    setTitle();
    setHeader();

    setMod("modname","SINGLETRACE","this is a test");
    slotModUpdate();
    setParam("parm1","SINGLETRACE","this is a test","test yes");
    slotParamAdd();

//cout << "!1111222\n";
    
    //createMenus();
    //createToolBars();
    //createStatusBar();
    //readSettings();
    //modhead = "";
return;  
   
 
};
void modMain::getValue()
{
    DOC->m_value.value =  formValue.textEditValue->toPlainText();
    DOC->m_value.type =  formValue.comboBoxType->currentText();
    DOC->m_value.spec =  formValue.textEditSpec->toPlainText();
    DOC->m_value.doc =  formValue.textEditDoc->toPlainText();
    //qDebug() << "get valude:";
   // qDebug() << DOC->m_value.value;
   // qDebug() << DOC->m_value.type;
    //qDebug() << DOC->m_value.spec;
   // qDebug() << DOC->m_value.doc;

}
void modMain::setValue(QString v,QString t,QString s,QString d)
{
    int idx;
    DOC->m_value.set(v,t,s,d);
    idx = formValue.comboBoxType->findText(t);
    formValue.textEditValue->setText(v);
    if (idx !=-1)
        formValue.comboBoxType->setCurrentIndex(idx);
    formValue.textEditSpec->setText(s);
    formValue.textEditDoc->setText(d);

}
void modMain::setParam(QString n,QString t,QString s,QString d)
{
    //qDebug("11111111\n");
    int idx;
    formParam.lineEditName->setText(n);
    idx = formParam.comboBoxType->findText(t);
    if (idx !=-1)
        formParam.comboBoxType->setCurrentIndex(idx);
    formParam.lineEditSpec->setText(s);
    formParam.textEditDoc->setText(d);

}
void modMain::getParam()
{
    DOC->m_param.name =  formParam.lineEditName->text();
    DOC->m_param.type =  formParam.comboBoxType->currentText();
    DOC->m_param.spec =  formParam.lineEditSpec->text();
    DOC->m_param.doc =  formParam.textEditDoc->toPlainText();
     
   // qDebug() <<"get Paraminfo";
   // qDebug() <<  DOC->m_param.name;
   // qDebug() <<  DOC->m_param.type;
   // qDebug() <<  DOC->m_param.spec;
   // qDebug() <<  DOC->m_param.doc;
}
void modMain::setMod(QString n,QString t,QString s)
{
    int idx;
    formMod.lineEditName->setText(n);
    idx = formMod.comboBoxType->findText(t);
    formMod.comboBoxType->setCurrentIndex(idx);
    formMod.textEditSpec->setText(s);
}
void modMain::getMod()
{
    QString str;
   // qDebug("get Modinfo\n");
    DOC->m_mod.name =  formMod.lineEditName->text();
    DOC->m_mod.type =  formMod.comboBoxType->currentText();
    DOC->m_mod.spec =  formMod.textEditSpec->toPlainText();
     
   // qDebug() <<  DOC->m_mod.name;
    //qDebug() <<   DOC->m_mod.type;
   // qDebug() <<   DOC->m_mod.spec;
}
void modMain::slotModUpdate()
{

    getMod();
    emit sigModUpdate();
    setTitle();
     
}
void modMain::slotParamAdd()
{
     //qDebug() << "Param Add\n";
     getParam();
   // qDebug("after value add\n");
     emit sigParamAdd();
}
void modMain::slotParamClear()
{
   // qDebug("Param clear\n");
    QString s;
    s = "";
    setParam(s,s,s,s);
    //qDebug("after Param clear\n");
}
void modMain::slotValueAdd()
{
   // qDebug("value add\n");
    getValue();
    //qDebug("after value add\n");
    emit sigValueAdd();
}
void modMain::slotValueClear()
{ 
   // qDebug("value clear\n");
    QString s;
    s = "";
    setValue(s,s,s,s);
   // qDebug("after value clear\n");
}
void modMain::slotSelectSet()
{ 
    QModelIndex idx;
    QString n,t,s,d;
    QString ty;
    int row;
    idx = modview->m_index;
    ty = idx.data(Qt::StatusTipRole).toString();
    row = idx.row();
    if (ty == MOD)
    {
        n = idx.data().toString();
        t = idx.sibling(row,1).data().toString();
        s = idx.sibling(row,2).data().toString();
        setMod(n,t,s);
    }
    else if (ty == PARAM)
    {
        n = idx.data().toString();
        t = idx.sibling(row,1).data().toString();
        s = idx.sibling(row,2).data().toString();
        d = idx.sibling(row,3).data().toString();
        setParam(n,t,s,d);
        // parent:Mod
        idx = idx.parent();
        row = idx.row();
        n = idx.data().toString();
        t = idx.sibling(row,1).data().toString();
        s = idx.sibling(row,2).data().toString();
        setMod(n,t,s);

    }
    else if(ty == PVALUE)
    {
        n = idx.data().toString();
        t = idx.sibling(row,1).data().toString();
        s = idx.sibling(row,2).data().toString();
        d = idx.sibling(row,3).data().toString();
        setValue(n,t,s,d);
        // parent:param
        idx = idx.parent();
        row = idx.row();
        n = idx.data().toString();
        t = idx.sibling(row,1).data().toString();
        s = idx.sibling(row,2).data().toString();
        d = idx.sibling(row,3).data().toString();
        setParam(n,t,s,d);
                // parent:Mod
        idx = idx.parent();
        row = idx.row();
        n = idx.data().toString();
        t = idx.sibling(row,1).data().toString();
        s = idx.sibling(row,2).data().toString();
        setMod(n,t,s);

    }
}
void modMain::readSettings()
{
    QSettings settings(ORG_NAME, APP_NAME);
    QString str = settings.value("modname").toString();
    theApp->m_doc->m_modName =str; 
 
}
void modMain::writeSettings()
{
    QSettings settings(ORG_NAME,APP_NAME);
    settings.setValue("modname", theApp->m_doc->m_modName);
}   
void modMain::createActions()
{
    qDebug() <<  "yes create actions";
    cout << "ssssss\n";

    openFileAct = new QAction(QIcon(":/images/openfile.png"), tr("OpenFile"), this);
    //newAct->setShortcuts(QKeySequence::New);
    openFileAct->setStatusTip(tr("open file"));
    connect(openFileAct, SIGNAL(triggered()), this, SLOT(slotOpenFile()));

    createCPPAct = new QAction(QIcon(":/images/createcpp.png"), tr("Create CPP"), this);
    //newAct->setShortcuts(QKeySequence::New);
    createCPPAct->setStatusTip(tr("create CPP"));
    connect(createCPPAct, SIGNAL(triggered()), this, SLOT(slotCreateCPP()));

    saveFileAct = new QAction(QIcon(":/images/savefile.png"), tr("SaveFile"), this);
    //newAct->setShortcuts(QKeySequence::New);
    saveFileAct->setStatusTip(tr("saveFile"));
    connect(saveFileAct, SIGNAL(triggered()), this, SLOT(slotSaveFile()));

    saveFileAsAct = new QAction(QIcon(":/images/savefileas.png"), tr("SaveFileAs"), this);
    //newAct->setShortcuts(QKeySequence::New);
    saveFileAct->setStatusTip(tr("saveFile"));
    connect(saveFileAsAct, SIGNAL(triggered()), this, SLOT(slotSaveFileAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    moveUpAct = new QAction(QIcon(":/images/moveup.png"),tr("MoveUp"), this);
    moveUpAct->setStatusTip(tr("move Up"));
    connect(moveUpAct, SIGNAL(triggered()), this, SLOT(slotMoveUp()));

    moveDownAct = new QAction(QIcon(":/images/movedown.png"),tr("MoveDown"), this);
    moveDownAct->setStatusTip(tr("move Down"));
    connect(moveDownAct, SIGNAL(triggered()), this, SLOT(slotMoveDown()));

    removeAct = new QAction(QIcon(":/images/remove.png"),tr("Remove"), this);
    removeAct->setStatusTip(tr("Remove"));
    connect(removeAct, SIGNAL(triggered()), this, SLOT(slotRemove()));

    aboutAct = new QAction(QIcon(":/images/about.png"),tr("&About"), this);
    aboutAct->setStatusTip(tr("show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(slotAbout()));

    helpAct = new QAction(QIcon(":/images/help.png"),tr("&Help"), this);
    helpAct->setStatusTip(tr("Help"));
    connect(helpAct, SIGNAL(triggered()), this, SLOT(slotHelp()));

    qDebug() << "create actions ok";

}
void modMain::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openFileAct);       
    fileMenu->addSeparator(); 
    fileMenu->addAction(createCPPAct);  
    fileMenu->addSeparator(); 
    fileMenu->addAction(saveFileAct); 
    fileMenu->addAction(saveFileAsAct); 
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    modifyMenu = menuBar()->addMenu(tr("&Modify"));
    modifyMenu->addAction(moveUpAct);
    modifyMenu->addAction(moveDownAct);
    modifyMenu->addAction(removeAct);
 
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAct);
    helpMenu->addAction(aboutAct);
    qDebug() << "create menu";
    
}
void modMain::createToolBars()
{
    fileToolBar = addToolBar(tr("ToolBar"));
    fileToolBar->addAction(openFileAct); 
    fileToolBar->addAction(saveFileAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(createCPPAct);
    fileToolBar->addSeparator();

    fileToolBar->addAction(moveUpAct);
    fileToolBar->addAction(moveDownAct);
    fileToolBar->addSeparator();

    fileToolBar->addAction(removeAct);
    fileToolBar->addSeparator();

    fileToolBar->addAction(aboutAct);
     qDebug() << "create toolBar";
}
void modMain::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
     qDebug() << "create StatusBar";
}
void modMain::slotMoveUp()
{
    QModelIndex idx;
    QString n,t,s,d,ty;
    QString nn,tn,sn,dn;
    int row;
    idx = modview->m_index;
    row = idx.row();
    if (row == 0)
        return;// already moved to row =0;
    ty = idx.data(Qt::StatusTipRole).toString();
    if (ty == MOD)
    {
        return;
    }

    n = idx.data().toString();
    t = idx.sibling(row,1).data().toString();
    s = idx.sibling(row,2).data().toString();
    d = idx.sibling(row,3).data().toString();
// get row -1:
     
    nn = idx.sibling(row-1,0).data().toString();
    tn = idx.sibling(row-1,1).data().toString();
    sn = idx.sibling(row-1,2).data().toString();
    dn = idx.sibling(row-1,3).data().toString();
// set data for row :
    modview->model->setData(idx,nn);
    modview->model->setData(idx.sibling(row,1),tn);
    modview->model->setData(idx.sibling(row,2),sn);
    modview->model->setData(idx.sibling(row,3),dn);
// set data for row -1:                                                  // set data for row :
    modview->model->setData(idx.sibling(row-1,0),n);
    modview->model->setData(idx.sibling(row-1,1),t);
    modview->model->setData(idx.sibling(row-1,2),s);
    modview->model->setData(idx.sibling(row-1,3),d);
    idx = idx.sibling(row-1,0);
    modview->selectionModel->clear(); 
    modview->selectionModel->select(idx,QItemSelectionModel::Select);   
}
void modMain::slotMoveDown()
{
    QStandardItem *item;
    QModelIndex idx;
    QString n,t,s,d;
    QString nn,tn,sn,dn;
    QString ty;
    int row,rows;
    idx = modview->m_index;
    ty = idx.data(Qt::StatusTipRole).toString();
    if (ty == MOD)
    {
        return;
    }

    row = idx.row();
    item = modview->model->itemFromIndex(idx.parent());
    rows = item->rowCount();

    if (row >= rows-1)
        return;// already moved to rowCounter ;
//-------------------
    n = idx.data().toString();
    t = idx.sibling(row,1).data().toString();
    s = idx.sibling(row,2).data().toString();
    d = idx.sibling(row,3).data().toString();
// get row +1:
     
    nn = idx.sibling(row+1,0).data().toString();
    tn = idx.sibling(row+1,1).data().toString();
    sn = idx.sibling(row+1,2).data().toString();
    dn = idx.sibling(row+1,3).data().toString();
// set data for row :
    modview->model->setData(idx,nn);
    modview->model->setData(idx.sibling(row,1),tn);
    modview->model->setData(idx.sibling(row,2),sn);
    modview->model->setData(idx.sibling(row,3),dn);
// set data for row +1:                                                  // set data for row :
    modview->model->setData(idx.sibling(row+1,0),n);
    modview->model->setData(idx.sibling(row+1,1),t);
    modview->model->setData(idx.sibling(row+1,2),s);
    modview->model->setData(idx.sibling(row+1,3),d);
    idx = idx.sibling(row+1,0);
    modview->selectionModel->clear(); 
    modview->selectionModel->select(idx,QItemSelectionModel::Select);
}
void modMain::slotRemove()
{
    QStandardItem *item;
    QModelIndex idx;
    QString str,name;
    QString ty;
    int row,rows,id;
    idx = modview->m_index;

    ty = idx.data(Qt::StatusTipRole).toString();
    name = idx.data().toString();
    row = idx.row();
    if (ty != MOD)
    {
        item = modview->model->itemFromIndex(idx.parent());
        rows = item->rowCount();
    }
    else
    {
        rows = modview->model->itemFromIndex(idx)->rowCount();
    }
        
    if (ty == MOD)// remove all the aprameters not include itslef.
    {
        str = "do you really Remove All the prameters?";
        
        id = QMessageBox::question(this,"Remove Module?",str);
        if (id !=QMessageBox::Yes) return;
        qDebug() << "remove parameter = " ;
        modview->model->removeRows(0,rows,idx);
        return;          
    }
    //
    if (ty == PARAM)// remove all the values  include itslef.
    {
        str = "do you really Remove the prameter:" + name + ", and all its values?";
        
        id = QMessageBox::question(this,"Remove Parameter?",str);
        if (id !=QMessageBox::Yes) return;
        //qDebug() << "remove rows = " << rows;
        modview->model->removeRow(row,idx.parent());
        return;          
    }
        //
    if (ty == PVALUE)// remove itslef.
    {
        str = "do you really Remove the value:" + name  ;
        
        id = QMessageBox::question(this,"Remove Value?",str);
        if (id !=QMessageBox::Yes) return;
        //qDebug() << "remove rows = " << rows;
        modview->model->removeRow(row,idx.parent());
        return;          
    }
}
void modMain::slotOpenFile()
{
    QString n,t,s,d;
    QStandardItemModel *model; 
    QModelIndex idx,pidx,vidx; 
//    int nump,numv,i,j; 

    model = modview->model;
    model->removeRow(0);

    QString str;
    str = DOC->m_modName+MODEXT;
    QFile file(str);
   

    if (!file.open(QIODevice::ReadOnly |QIODevice::Text))
        return ;
     qDebug() << "open fle ok = " << str;
     QString errorStr;
     int errorLine;
     int errorColumn;

     QDomDocument doc;
     if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
     {
         qDebug() << "doc error";
         return ;
     }
     file.close();
   
     QDomElement root = doc.documentElement() ;
     n = root.attribute("name");
     t = root.attribute("type");
     s = root.attribute("spec");
     d = root.attribute("doc");
     qDebug() <<n<<t<<s<<d;
     setMod(n,t,s);
     slotModUpdate();

     QDomNode node = root.firstChild();

    // qDebug() << "begin =" << node.toElement().tagName();;

     while (!node.isNull()) 
     {
             // qDebug() << "in loop " << node.toElement().tagName();
         if (node.toElement().tagName() == "param") 
         { 
             n = node.toElement().attribute("name");
             t = node.toElement().attribute("type");
             s = node.toElement().attribute("spec");
             d = node.toElement().attribute("doc");
             qDebug() <<n<<t<<s<<d;
             setParam(n,t,s,d);
             slotParamAdd();
              
             QDomNode v = node.firstChild();
             while (!v.isNull())
             {  
                 if (v.toElement().tagName() == "value")
                 {
                      n = v.toElement().attribute("name");
                      t = v.toElement().attribute("type");
                      s = v.toElement().attribute("spec");
                      d = v.toElement().attribute("doc");
                      qDebug() <<n<<t<<s<<d;
                      setParam(n,t,s,d);
                      slotValueAdd();    
                 } 
                 v = v.nextSibling();  
             }// endof while
               
         }//end of if
         node = node.nextSibling();//¶ÁÈ¡ÐÖµÜ½Úµã
     }//end of while


}


void modMain::slotSaveFile()
{
    QString n,t,s,d;
    QStandardItemModel *model;
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\", encoding=\"UTF-8\"");
    QDomElement module = doc.createElement("module");
    QDomElement param;// = doc.createElement("param");
    QDomElement value;// = doc.createElement("value");

    model = modview->model;
    QModelIndex idx,pidx,vidx;
    int nump,numv,i,j;
    idx = model->index(0,0);
    n = model->data(model->index(0,0,QModelIndex())).toString();
    t = model->data(model->index(0,1,QModelIndex())).toString();
    s = model->data(model->index(0,2,QModelIndex())).toString();
    d = model->data(model->index(0,3,QModelIndex())).toString();
    qDebug() <<n<<t<<s<<d;
    nump = model->rowCount(idx);
    qDebug() << "nump= " <<nump;
    module.setAttribute("name",n);
    module.setAttribute("type",t);
    module.setAttribute("spec",s);
    doc.appendChild(module);
    //module.setAttribute("doc",d);
    for (i = 0; i <nump ;i++)
    {
        pidx = model->index(i,0,idx);
        n = model->data(model->index(i,0,idx)).toString();
        t = model->data(model->index(i,1,idx)).toString();
        s = model->data(model->index(i,2,idx)).toString();
        d = model->data(model->index(i,3,idx)).toString();
        qDebug() <<n<<t<<s<<d;
        numv = model->rowCount(pidx);
        qDebug() << "numv= " <<numv;
        param  = doc.createElement("param");
        param.setAttribute("name",n);
        param.setAttribute("type",t);
        param.setAttribute("spec",s);
        param.setAttribute("doc",d);

        module.appendChild(param);
        for (j = 0; j < numv; j++)
        {
             vidx = model->index(i,0,pidx);
             n = model->data(model->index(j,0,pidx)).toString();
             t = model->data(model->index(j,1,pidx)).toString();
             s = model->data(model->index(j,2,pidx)).toString();
             d = model->data(model->index(j,3,pidx)).toString();
             qDebug() <<n<<t<<s<<d;
             value  = doc.createElement("value");
             value.setAttribute("name",n);
             value.setAttribute("type",t);
             value.setAttribute("spec",s);
             value.setAttribute("doc",d);

             param.appendChild(value);
        }
    }
    QString str;
    str = DOC->m_modName + MODEXT;//".mdef";
    QFile file(str);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate |QIODevice::Text))
        return ;
    QTextStream out(&file);
    out.setCodec("UTF-8");
    doc.save(out,4,QDomNode::EncodingFromTextStream);
    file.close();
    
}
int modMain::createSubCPP()
{
    QString n,t,s,d;
    QStandardItemModel *model;
    QString var,dft,getp,setp,modname,pname,vname;
    QString str,ty,strd,strp;
    QStringList strlist,strslist,strdlist;
    var = dft = getp =setp ="";

    model = modview->model;
    QModelIndex idx,pidx,vidx;
    int nump,numv,i,j,numop;
    idx = model->index(0,0);
    n = model->data(model->index(0,0,QModelIndex())).toString();
    t = model->data(model->index(0,1,QModelIndex())).toString();
    s = model->data(model->index(0,2,QModelIndex())).toString();
    d = model->data(model->index(0,3,QModelIndex())).toString();

    if (t == "SINGLETRACE") 
        m_modType = "EXEC_TYPE_SINGLETRACE";
    else if(t == "MULTITRACE") 
        m_modType = "EXEC_TYPE_MULTITRACE";
    else if(t == "INPUT") 
        m_modType = "EXEC_TYPE_INPUT";
    else  
        m_modType = "EXEC_TYPE_UNKOWN";
    //setModule:
    str =  IDENT + "pdef->setModule(" + QMARK +n + QMARK +"," +QMARK + s +QMARK + ");\n";
    setp += str;  
    //setVersion:
    str = IDENT +"pdef->setVersion("+ "1.0" +  ");\n";
    setp += str;
    //addDoc:
    str = IDENT +"pdef->addDoc("+ QMARK + s + QMARK +  ");\n";
    setp += str;  

 
    qDebug() << str;
    nump = model->rowCount(idx);
    qDebug() << "nump= " <<nump;
  
    //begin parameters:

    for (i = 0; i <nump ;i++)
    {
        pidx = model->index(i,0,idx);
        n = model->data(model->index(i,0,idx)).toString();
        t = model->data(model->index(i,1,idx)).toString();
        s = model->data(model->index(i,2,idx)).toString();
        d = model->data(model->index(i,3,idx)).toString();
        pname = n;
        qDebug() <<n<<t<<s<<d;
        numv = model->rowCount(pidx);
        if (numv ==0)
        {
            str = "No Value set in parameter: " + pname;
            QMessageBox::question(this,"Error Parameter?",str);
            return -1;
        }
        qDebug() << "numv= " << numv;
        if (t == "FIXED" )
            ty = "NUM_VALUES_FIXED";
        else if (t == "VARIABLE" )
            ty  = "NUM_VALUES_VARIABLE";
        // setp:
        // addParam:
        str = "\n"; // add a NULL line befor add Param
        setp += str; 
        str = IDENT +"pdef->addParam("+ QMARK + n + QMARK +"," +QMARK + s +QMARK;
        str +=  ","  + ty  + "," + QMARK + d +QMARK + ");\n";
        setp += str;  

        // getp:
        str = IDENT + "if(param->exists(" + QMARK + pname + QMARK +"))\n";
        getp += str;
        str = IDENT + "{\n";
        getp += str;
 
        for (j = 0; j < numv; j++)
        {
             vidx = model->index(i,0,pidx);
             n = model->data(model->index(j,0,pidx)).toString();
             t = model->data(model->index(j,1,pidx)).toString();
             s = model->data(model->index(j,2,pidx)).toString();
             d = model->data(model->index(j,3,pidx)).toString();
             if (j == 0) vname = pname;
             else vname = pname +str.setNum(j);

             qDebug() << n << t << s << d;
             if (t == "INT")
             {
                 ty = "VALTYPE_NUMBER";
                 str = IDENT2+"int " + vname + ";" + "  //" + s +"\n";
                 strd = IDENT + "vars->" + vname + " = "+ DEFAULT_NUMBER + ";\n" ;
                 strp = IDENT2 + "param->getInt(" + QMARK + pname + QMARK + ","+ "&var->" + vname +";\n" ;
             }
             else if(t == "FLOAT")
             {
                 ty = "VALTYPE_NUMBER";
                 str = IDENT2+"float " + vname + ";" + " //" + s +"\n";
                 strd = IDENT +"vars->" + vname + " = " + DEFAULT_NUMBER + ";\n" ;
                 strp = IDENT2 + "param->getFloat(" + QMARK + pname + QMARK + ","+ "&var->" + vname +";\n" ;
             }
             if(t == "DOUBLE")
             {
                 ty = "VALTYPE_NUMBER";
                 str = IDENT2+"double " + vname + ";" + " //" + s +"\n";
                 strd = IDENT +"vars->" + vname + " = " + DEFAULT_NUMBER + ";\n" ;
                 strp = IDENT2 + "param->getDouble(" + QMARK + pname + QMARK + ","+ "&var->" + vname +";\n" ;
             }
             else if (t == "STRING" )
             {
                 ty  = "VALTYPE_STRING";
                 str = IDENT2+"string " + vname + ";" + " //" + s +"\n";
                 strd = IDENT +"vars->" + vname + " = " + DEFAULT_STRING + ";\n" ;
                 strp = IDENT2 + "param->getString(" + QMARK + pname + QMARK + ","+ "&var->" + vname +";\n" ;
             }
             else if (t == "OPTION" )
             {
                 ty  = "VALTYPE_OPTION";
                 str = IDENT2+"string " + vname + ";" + " //" + s +"\n";
                 strd = IDENT + "vars->" + vname + " = " + DEFAULT_STRING + ";\n" ;
                 strp = IDENT2 + "param->getString(" + QMARK + pname + QMARK + ","+ "&var->" + vname +";\n" ;
             }
             else if (t == "HEADER" )
             {
                 ty  = "VALTYPE_HEADER_NUMBER";
                 str = IDENT2+"string " + vname + ";" + " //" + s +"\n";
                 strd = IDENT + "vars->" + vname + " = " + DEFAULT_STRING + ";" ;
                 strp = IDENT2 + "param->getString(" + QMARK + pname + QMARK + ","+ "&var->" + vname +";\n" ;
             }
           //var:
             var += str;
           //dft:
             dft += strd;
           //getp:
             getp += strp; 


           // setp:
             if(t != "OPTION")//option:
             {
                 str = IDENT +"pdef->addValue("+ QMARK + n + QMARK +"," +ty + "," +QMARK + s +QMARK; 
                 str +=  QString(",")+ QMARK + d +QMARK + ");\n";
                 setp += str; 
             }
              
             else  //option:
             {

                 strlist = n.split("\n");
                 strslist = s.split("\n");
                 strdlist = d.split("\n");

                 numop = strlist.size();

                 n = strlist[0];
                 s = strslist[0];
                 d = strdlist[0];

                 str = IDENT +"pdef->addValue(" + QMARK + n + QMARK + "," + ty + "," + QMARK + s + QMARK;
                 str +=  QString(",")   + QMARK + d +QMARK + ");\n";
                 setp += str;

                 for (int jj = 0; jj < numop; jj++)
                 {
                     n = strlist.at(jj);
                     if (strslist.size()>jj)// mybe no spec
                         s = strslist.at(jj);
                     else
                         s ="";

                     if (strdlist.size()>jj)// mybe no extra spec
                         d = strdlist.at(jj);
                     else
                         d ="";
                      
                     str = IDENT +"pdef->addOption(" + QMARK + n + QMARK + ","  + QMARK + s + QMARK;
                     str +=  QString(",")   + QMARK + d +QMARK + ");\n";
                     setp += str;  
                 }
             }//option
        }//values
        //for getP
        str = IDENT + "}\n";
        getp += str;
    }//params

    //qDebug() << setp;
    //qDebug() << var;
    //qDebug() << dft;
    //qDebug() << getp;
    m_subSetParam = setp;
    m_subDefault = dft;
    m_subVar = var;
    m_subGetParam = getp;
    //m_modType;
    return 0;
}
void modMain::slotCreateCPP()
{
    QString str,filein,fileon,modname,line;
    int i;
    i = createSubCPP();
    if (i !=0) return;


    modname = DOC->m_modName;
    filein = MOD_SINGLE_FILE;
    fileon = "mod_" + modname + ".cpp";
    QFile filei(filein);
    QFile fileo(fileon);
    if (!filei.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        qDebug()<< "open model error =" << filein;
        return ;
    }

    if (!fileo.open(QIODevice::WriteOnly | QIODevice::Truncate |QIODevice::Text))
    {
        qDebug()<< "create cpp error =" << fileon;
        return ;
    }
    QTextStream tin(&filei);
    QTextStream tout(&fileo);
    /*
#define ADD_VAR "ADD_VAR:"
#define ADD_INITD "ADD_INIT_DEFAULT:"
#define ADD_INITP "ADD_INIT_PARAMETERS:"
#define ADD_SETP "ADD_PARAMETERS:"
#define MOD_SINGLE "EXEC_TYPE_SINGLETRACE"*/
    while (!tin.atEnd())
    {
        line = tin.readLine();
        if (line.contains(ADD_VAR))
        {
            tout << m_subVar ; 
            continue;
        }
        if (line.contains(ADD_INITD))
        {
            tout << m_subDefault ; 
            continue;
        }
        if (line.contains(ADD_INITP))
        {
            tout << m_subGetParam; 
            continue;
        }
        if (line.contains(ADD_SETP))
        {
            tout << m_subSetParam ; 
            continue;
        }
        if (line.contains(MOD_SINGLE_STR))
        {
            line.replace(QString(MOD_SINGLE_STR),m_modType); 
        }
        if (line.contains(MOD_NAME))
        {
            line.replace(QString(MOD_NAME),DOC->m_modName); 
        }
  
        tout << line << endl;
        //cout << line.toUtf8().data() <<endl;
    }
    qDebug() << "end of read";

}
void modMain::slotSaveAsFile()
{
}
void modMain::slotHelp()
{
}
void modMain::slotAbout()
{
    QString title,str,str1;
    title = ORG_NAME;
    str1 = __DATE__;
    str = QString("   App name : ") +QString(APP_NAME) + "\n" +
          QString("App version : ") +QString(APP_VERSION) + "\n" +
          QString("       Date : ") +str1;
   QMessageBox::about(this, title,str);

}
void modMain::setTitle()
{
    QString str;
    str = "";
    str = str + APP_NAME + "-"+APP_VERSION +"-"+ __DATE__ +"-";
    str = str + theApp->m_doc->m_modName;

    setWindowTitle(str);
    qDebug() << "title = " << str;

}
void modMain::closeEvent(QCloseEvent *event)

{
 
    //if (maybeSave()) {
        writeSettings();
        //event->accept();
    //} else {
    //    event->ignore();
    //}
}
QStringList modMain::getHeader()
{
    QStringList strlist;

    csVector<csHeaderInfo const *> hdrList(40);
    //qDebug() << "11111";
    csStandardHeaders::getAll( &hdrList );
    //qDebug() << "is in the getHeader = " << hdrList.size();
    for( int ihdr = 0; ihdr < hdrList.size(); ihdr++ ) 
    {
        csHeaderInfo const* info = hdrList.at(ihdr);
        //qDebug() << ihdr << info->name.c_str();
        strlist << info->name.c_str();

    //fprintf(myStream,"Trace header #%3d: %-20s %-10s %s\n", ihdr+1, info->name.c_str(), cseis_geolib::csGeolibUtils::typeText(info->type), info->description.c_str() );
    } 
    return strlist; 
}
void  modMain::setHeader()
{

    QStringList slist ;
    //qDebug() << "setHeader";
    slist = getHeader();
    formValue.comboBoxHeader->insertItems(0,slist);
}
void  modMain::slotValueHeader()
{
    QString v;
    v = formValue.comboBoxHeader->currentText();
    formValue.textEditValue->append(v);
}
