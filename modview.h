#ifndef MODVIEW_H 
#define MODVIEW_H 

#include <QWidget>
#include <QListView>
#include <QTreeView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QModelIndex>
class modView :public QTreeView
{
    Q_OBJECT

public:
    modView(QWidget *p);
    ~modView();
    void init();
    int setHeader(QStringList h);
    int addRow(QStringList item);
    int addRow(QString item);

    QModelIndex addChild(QStringList strlist,QModelIndex index,int row);
/** which row to insert param ,in modview, -1 nothing selected;
 *  used in slotParamAdd
*/
    int  getParamRow();
/** which row to insert value ,in modview, -1 nothing selected;
 *  and get the parent(Param selected); -1 or parent = invalid;
 *   warning;
 *   used in slotValueAdd
*/
    int getValueRow(QModelIndex &parent);
/**
     * find if have the paramter name in the module 

    * 
     * @param name 
     * 
     * @return bool 
     */
    bool findParams(QString name);

    QStandardItemModel  *model;
    QSortFilterProxyModel *pmodel;
    QItemSelectionModel *selectionModel;

    QModelIndex m_index;//selected QModelindex;


public slots:
    void slotModUpdate();
    void slotParamAdd();
    void slotValueAdd();

signals:
    void selectOK();

protected:

    void selectionChanged(const QItemSelection & selected, const QItemSelection & deselected);
};



#endif

