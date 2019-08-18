#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
#include "showwidget.h"
#include <QColorDialog>


class ImageProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = 0);
    ~ImageProcessor();
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);
    void mergeFormat(QTextCharFormat);
private:
    QMenu *fileMenu;
    QMenu *zoomMenu;
    QMenu *rotateMenu;
    QMenu *mirrorMenu;
    QImage img;
    QString fileName;
    ShowWidget *showWidget;
    QAction *openFileAction;
    QAction *newFileAction;
    QAction *printTextAction;
    QAction *printImageAction;
    QAction *exitAction;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *aboutAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *rotate90Action;
    QAction *rotate180Action;
    QAction *rotate270Action;
    QAction *mirroVertiacalAction;
    QAction *mirroHorizontalAction;
    QAction *undoAction;
    QAction *redoAction;
    QToolBar *fileTool;
    QToolBar *zoomTool;
    QToolBar *rotateTool;
    QToolBar *mirrorTool;
    QToolBar *doToolBar;

    QLabel *fontLabel1;
    QFontComboBox *fontComboBox;
    QLabel *listLabel;
    QComboBox *listComboBox;
    QActionGroup *actGrp;
    QAction *leftAction;
    QAction *rightAction;
    QAction *centerAction;
    QAction *justifyAction;
    QToolBar *listToolBar;
    QLabel *fontLabel2;
    QComboBox *sizeComboBox;
    QToolButton *boldBtn;
    QToolButton *italicBtn;
    QToolButton *underlineBtn;
    QToolButton *colorBtn;
    QToolBar *fontToolBar;

protected slots:
    void ShowFontComboBox(QString comboStr);
    void ShowSizeSpinBox(QString spinValue);
    void ShowBoldBtn();
    void ShowItalicBtn();
    void ShowUnderlineBtn();
    void ShowColorBtn();
    void showList(int);
    void showAlignment(QAction *act);
    void showCursorPositionChanged();
    void ShowCurrentFormatChanged(const QTextCharFormat &fmt);
};

#endif // IMAGEPROCESSOR_H
