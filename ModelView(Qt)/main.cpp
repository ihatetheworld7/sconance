#include "modelview.h"
#include <QApplication>
#include <QDirModel>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QSplitter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    ModelView w;
//    w.show();
    QDirModel model;
    QTreeView tree;
    QListView list;
    QTableView table;
    tree.setModel(&model);
    list.setModel(&model);
    table.setModel(&model);
//    tree.setSelectionModel(QAbstractItemView::MultiSelection);
//    list.setSelectionModel(tree.selectionModel());
//    table.setSelectionModel(tree.selectionModel());
    QObject::connect(&tree,SIGNAL(doubleClicked(QModelIndex)),&list,SLOT(setRootIndex(QModelIndex)));
    QObject::connect(&tree,SIGNAL(doubleClicked(QModelIndex)),&table,SLOT(setRootIndex(QModelIndex)));
    QSplitter *splitter=new QSplitter;
    splitter->addWidget(&tree);
    splitter->addWidget(&list);
    splitter->addWidget(&table);
    splitter->setWindowTitle(QObject::tr("Model/View"));
    splitter->resize(800,600);
    splitter->show();

    return a.exec();
}
