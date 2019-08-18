#include "imageprocessor.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QMatrix>
#include <QTextList>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Textwang");
    resize(800,600);
    showWidget=new ShowWidget(this);
    setCentralWidget(showWidget);
    listLabel=new QLabel("排序");
    listComboBox=new QComboBox;
    listComboBox->addItem("Standard");
    listComboBox->addItem("QTextListFormat::ListDisc");
    listComboBox->addItem("QTextListFormat::ListCircle");
    listComboBox->addItem("QTextListFormat::ListSquare");
    listComboBox->addItem("QTextListFormat::ListDecimal");
    listComboBox->addItem("QTextListFormat::ListLowerAlpha");
    listComboBox->addItem("QTextListFormat::ListUpperAlpha");
    listComboBox->addItem("QTextListFormat::ListLowerRoman");
    listComboBox->addItem("QTextListFormat::ListUpperRoman");
    fontLabel1=new QLabel("字体：");
    fontComboBox=new QFontComboBox;
    fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);
    fontLabel2=new QLabel("字号：");
    sizeComboBox=new QComboBox;
    QFontDatabase db;
    foreach (int size, db.standardSizes()) {
        sizeComboBox->addItem(QString::number(size));
    }
    boldBtn=new QToolButton;
    boldBtn->setIcon(QIcon("D:\\Image\\粗体.png"));
    boldBtn->setCheckable(true);
    italicBtn=new QToolButton;
    italicBtn->setIcon(QIcon("D:\\Image\\斜体.png"));
    italicBtn->setCheckable(true);
    underlineBtn=new QToolButton;
    underlineBtn->setIcon(QIcon("D:\\Image\\下划线.png"));
    underlineBtn->setCheckable(true);
    colorBtn=new QToolButton;
    colorBtn->setIcon(QIcon("D:\\Image\\颜色.png"));
    colorBtn->setCheckable(true);

    createActions();
    createMenus();
    createToolBars();
    if(img.load("D:\\Image\\2.jpg"))
    {
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
    }
    connect(fontComboBox,SIGNAL(activated(QString)),this,SLOT(ShowFontComboBox(QString)));
    connect(sizeComboBox,SIGNAL(activated(QString)),this,SLOT(ShowSizeSpinBox(QString)));
    connect(boldBtn,SIGNAL(clicked(bool)),this,SLOT(ShowBoldBtn()));
    connect(italicBtn,SIGNAL(clicked(bool)),this,SLOT(ShowItalicBtn()));
    connect(underlineBtn,SIGNAL(clicked(bool)),this,SLOT(ShowUnderlineBtn()));
    connect(colorBtn,SIGNAL(clicked(bool)),this,SLOT(ShowColorBtn()));
    connect(showWidget->text,SIGNAL(currentCharFormatChanged(QTextCharFormat&)),this,SLOT(ShowCurrentFormatChanged(QTextCharFormat)));
    connect(listComboBox,SIGNAL(activated(int)),this,SLOT(showList(int)));
    connect(showWidget->text->document(),SIGNAL(undoAvailable(bool)),redoAction,SLOT(setEnabled(bool)));
    connect(showWidget->text->document(),SIGNAL(redoAvailable(bool)),redoAction,SLOT(setEnabled(bool)));
    connect(showWidget->text,SIGNAL(cursorPositionChanged()),this,SLOT(showCursorPositionChanged()));
}

ImageProcessor::~ImageProcessor()
{
    
}
void ImageProcessor::createActions()
{
    openFileAction = new QAction(QIcon("D:\\Image\\打开文件.png"),("打开"),this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip("打开一个文件");
    newFileAction=new QAction(QIcon("D:\\Image\\新建文件.png"),("新建"),this);
    newFileAction->setShortcut(tr("Ctrl+N"));
    newFileAction->setStatusTip("新建一个文件");
    exitAction=new QAction(("退出"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip("退出程序");
    connect(exitAction,&QAction::triggered,this,&ImageProcessor::close);
    copyAction=new QAction(QIcon("D:\\Image\\复制文件.png"),("复制"),this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip("复制文件");
    connect(copyAction,&QAction::triggered, showWidget->text,&QTextEdit::close);
    cutAction=new QAction(QIcon("D:\\Image\\剪切文件.png"),("剪切"),this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip("剪切文件");
    connect(cutAction,&QAction::triggered,showWidget->text,&QTextEdit::cut);
    pasteAction=new QAction(QIcon("D:\\Image\\粘贴.png"),("粘贴"),this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip("粘贴文件");
    connect(pasteAction,&QAction::triggered,showWidget->text,&QTextEdit::paste);
    aboutAction=new QAction(("关于"),this);
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(QAppliction::aboutQt()));
    printTextAction=new QAction(QIcon("D:\\Image\\打印.png"),("打印文本"),this);
    printTextAction->setStatusTip("打印一个文本");
    printImageAction=new QAction(QIcon("D:\\Image\\打印1.png"),("打印图片"),this);
    printImageAction->setStatusTip("打印一幅图片");
    zoomInAction=new QAction(QIcon("D:\\Image\\放大镜.png"),("放大"),this);
    zoomInAction->setStatusTip("放大一幅图片");
    zoomOutAction=new QAction(QIcon("D:\\Image\\缩小.png"),("缩小"));
    zoomOutAction->setStatusTip("缩小一幅图片");
    rotate90Action=new QAction(QIcon("D:\\Image\\顺时针旋转.png"),("旋转90"),this);
    rotate90Action->setStatusTip("将一幅图旋转90");
    rotate180Action=new QAction(QIcon("D:\\Image\\旋转.png"),("旋转180"),this);
    rotate180Action->setStatusTip("将一幅图旋转180");
    rotate270Action=new QAction(QIcon("D:\\Image\\向右旋转.png"),("旋转270"),this);
    rotate270Action->setStatusTip("将一幅图旋转270");
    mirroVertiacalAction=new QAction(QIcon("D:\\Image\\镜像1.png"),("纵向镜像"),this);
    mirroVertiacalAction->setStatusTip("图片纵向镜像");
    mirroHorizontalAction=new QAction(QIcon("D:\\Image\\镜像.png"),("横向镜像"),this);
    mirroHorizontalAction->setStatusTip("图像横向镜像");
    undoAction=new QAction(QIcon("D:\\Image\\撤销.png"),("撤销"),this);
    connect(undoAction,&QAction::triggered,showWidget->text,&QTextEdit::undo);
    redoAction=new QAction(QIcon("D:\\Image\\重做.png"),("重做"),this);
    actGrp=new QActionGroup(this);
    leftAction=new QAction(QIcon("D:\\Image\\左对齐.png"),"左对齐",actGrp);
    leftAction->setCheckable(true);
    rightAction=new QAction(QIcon("D:\\Image\\右对齐.png"),"右对齐",actGrp);
    rightAction->setCheckable(true);
    centerAction=new QAction(QIcon("D:\\Image\\居中对齐.png"),"居中",actGrp);

    centerAction->setCheckable(true);
    justifyAction=new QAction(QIcon("D:\\Image\\两端对齐.png"),"两端对齐",actGrp);
    justifyAction->setCheckable(true);
    connect(actGrp,SIGNAL(triggered(QAction*)),this,SLOT(showAlignment(QAction*)));

    connect(redoAction,&QAction::triggered,showWidget->text,&QTextEdit::redo);

    connect(newFileAction,&QAction::triggered,[=]()
    {
        ImageProcessor *newImagProcessor=new ImageProcessor;
        newImagProcessor->show();
    });
    connect(openFileAction,&QAction::triggered,[=](){
        fileName=QFileDialog::getOpenFileName(this);
        if(!fileName.isEmpty())
        {
            if(showWidget->text->document()->isEmpty())
            {
                loadFile(fileName);
            }
            else
            {
                ImageProcessor *newImgProcesser=new ImageProcessor;
                newImgProcesser->show();
                newImgProcesser->loadFile(fileName);
            }
        }
    });
    connect(printTextAction,&QAction::triggered,[=](){
        QPrinter painter;
        QPrintDialog printDialog(&painter,this);
        if(printDialog.exec())
        {
            QTextDocument *doc=showWidget->text->document();
            doc->print(&painter);
        }
    });
    connect(printImageAction,&QAction::triggered,[=](){
        QPrinter printer;
        QPrintDialog printDialog(&printer,this);
        if(printDialog.exec())
        {
            QPainter painter(&printer);
            QRect rect=painter.viewport();
            QSize size=img.size();
            painter.setViewport(rect.x(),rect.y(),size.width(),size.height());
            painter.setWindow(img.rect());
            painter.drawImage(0,0,img);
        }
    });
    connect(zoomInAction,&QAction::triggered,[=]()
    {
        if(img.isNull())
            return;
        QMatrix matrix;
        matrix.scale(2,2);
        img=img.transformed(matrix);
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
    });
    connect(zoomOutAction,&QAction::triggered,[=](){
        if(img.isNull())
            return;
        QMatrix matrix;
        matrix.scale(0.5,0.5);
        img=img.transformed(matrix);
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
    });
    connect(rotate90Action,&QAction::triggered,[=](){
        if(img.isNull())
            return;
        QMatrix matrix;
        matrix.rotate(90);
        img=img.transformed(matrix);
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
    });
    connect(rotate180Action,&QAction::triggered,[=](){
        if(img.isNull())
            return;
        QMatrix matrix;
        matrix.rotate(180);
        img=img.transformed(matrix);
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
        
    });
    connect(rotate270Action,&QAction::triggered,[=](){
        if(img.isNull())
            return;
        QMatrix matrix;
        matrix.rotate(270);
        img=img.transformed(matrix);
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
    });
    connect(mirroVertiacalAction,&QAction::triggered,[=](){
        if(img.isNull())
            return;
        img=img.mirrored(false,true);
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
    });
    connect(mirroHorizontalAction,&QAction::triggered,[=](){
        if(img.isNull())
            return;
        img=img.mirrored(true,false);
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
    });
}
void ImageProcessor::createMenus()
{
    fileMenu=menuBar()->addMenu("文件");
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(printTextAction);
    fileMenu->addAction(printImageAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    zoomMenu=menuBar()->addMenu("编辑");
    zoomMenu->addAction(copyAction);
    zoomMenu->addAction(cutAction);
    zoomMenu->addAction(pasteAction);
    zoomMenu->addAction(aboutAction);
    zoomMenu->addSeparator();
    zoomMenu->addAction(zoomInAction);
    zoomMenu->addAction(zoomOutAction);
    rotateMenu=menuBar()->addMenu("旋转");
    rotateMenu->addAction(rotate90Action);
    rotateMenu->addAction(rotate180Action);
    rotateMenu->addAction(rotate270Action);
    mirrorMenu=menuBar()->addMenu("镜像");
    mirrorMenu->addAction(mirroVertiacalAction);
    mirrorMenu->addAction(mirroHorizontalAction);
}
void ImageProcessor::createToolBars()
{
    fileTool=addToolBar("File");
    fileTool->addAction(openFileAction);
    fileTool->addAction(newFileAction);
    fileTool->addAction(printTextAction);
    fileTool->addAction(printImageAction);

    zoomTool=addToolBar("Edit");
    zoomTool->addAction(copyAction);
    zoomTool->addAction(cutAction);
    zoomTool->addAction(pasteAction);
    zoomTool->addSeparator();
    zoomTool->addAction(zoomInAction);
    zoomTool->addAction(zoomOutAction);

    rotateTool=addToolBar("rotate");
    rotateTool->addAction(rotate90Action);
    rotateTool->addAction(rotate180Action);
    rotateTool->addAction(rotate270Action);

    doToolBar=addToolBar("doEdit");
    doToolBar->addAction(undoAction);
    doToolBar->addAction(redoAction);
    fontToolBar=addToolBar("Font");
    fontToolBar->addWidget(fontLabel1);
    fontToolBar->addWidget(fontComboBox);
    fontToolBar->addWidget(fontLabel2);
    fontToolBar->addWidget(sizeComboBox);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(boldBtn);
    fontToolBar->addWidget(italicBtn);
    fontToolBar->addWidget(underlineBtn);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(colorBtn);
    listToolBar=addToolBar("list");
    listToolBar->addWidget(listLabel);
    listToolBar->addWidget(listComboBox);
    listToolBar->addSeparator();
    listToolBar->addActions(actGrp->actions());
}

void ImageProcessor::loadFile(QString filename)
{
    printf("file name:%s\n",filename.data());
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);
        while(!textStream.atEnd())
        {
            showWidget->text->append(textStream.readLine());
            printf("read line\n");
        }
        printf("end\n");
    }
}
void ImageProcessor::ShowFontComboBox(QString comboStr)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(comboStr);
    mergeFormat(fmt);
}
void ImageProcessor::mergeFormat(QTextCharFormat format)
{
    QTextCursor cursor=showWidget->text->textCursor();
    if(!cursor.hasSelection())
    {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
    showWidget->text->mergeCurrentCharFormat(format);
}
void ImageProcessor::ShowSizeSpinBox(QString spinValue)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(spinValue.toFloat());
    showWidget->text->mergeCurrentCharFormat(fmt);
}
void ImageProcessor::ShowBoldBtn()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(boldBtn->isChecked()?QFont::Bold:QFont::Normal);
    showWidget->text->mergeCurrentCharFormat(fmt);
}
void ImageProcessor::ShowItalicBtn()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(italicBtn->isChecked());
    showWidget->text->mergeCurrentCharFormat(fmt);
}
void ImageProcessor::ShowUnderlineBtn()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(underlineBtn->isChecked());
    showWidget->text->mergeCurrentCharFormat(fmt);
}
void ImageProcessor::ShowColorBtn()
{
    QColor color=QColorDialog::getColor(Qt::red,this);
    if(color.isValid())
    {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        showWidget->text->mergeCurrentCharFormat(fmt);
    }
}
void ImageProcessor::ShowCurrentFormatChanged(const QTextCharFormat &fmt)
{
    fontComboBox->setCurrentIndex(fontComboBox->findText(fmt.fontFamily()));
    sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(fmt.fontPointSize())));
    boldBtn->setChecked(fmt.font().bold());
    italicBtn->setChecked(fmt.fontItalic());
    underlineBtn->setChecked(fmt.fontUnderline());
}
void ImageProcessor::showAlignment(QAction *act)
{
    if(act==leftAction)
    {
        showWidget->text->setAlignment(Qt::AlignLeft);
    }
    if(act==rightAction)
    {
        showWidget->text->setAlignment(Qt::AlignRight);
    }
    if(act==centerAction)
    {
        showWidget->text->setAlignment(Qt::AlignCenter);
    }
    if(act==justifyAction)
    {
        showWidget->text->setAlignment(Qt::AlignJustify);
    }
}
void ImageProcessor::showCursorPositionChanged()
{
    if(showWidget->text->alignment()==Qt::AlignLeft)
    {
        leftAction->setChecked(true);
    }
    if(showWidget->text->alignment()==Qt::AlignRight)
    {
        rightAction->setChecked(true);
    }
    if(showWidget->text->alignment()==Qt::AlignCenter)
    {
        centerAction->setChecked(true);
    }
    if(showWidget->text->alignment()==Qt::AlignJustify)
    {
        justifyAction->setChecked(true);
    }
}
void ImageProcessor::showList(int index)
{
    QTextCursor cursor=showWidget->text->textCursor();
    if(index!=0)
    {
        QTextListFormat::Style style=QTextListFormat::ListDisc;
        switch(index)
        {
        default:
case 1:
            style=QTextListFormat::ListDisc;break;
        case 2:
            style=QTextListFormat::ListCircle;break;
        case 3:
            style=QTextListFormat::ListSquare;break;
        case 4:
            style=QTextListFormat::ListDecimal;break;
        case 5:
            style=QTextListFormat::ListLowerAlpha;break;
        case 6:
            style=QTextListFormat::ListUpperAlpha;break;
        case 7:
            style=QTextListFormat::ListLowerRoman;break;
        case 8:
            style=QTextListFormat::ListUpperRoman;break;
        }
        cursor.beginEditBlock();
        QTextBlockFormat blockFmt=cursor.blockFormat();
        QTextListFormat listFmt;
        if(cursor.currentList())
        {
            listFmt=cursor.currentList()->format();
        }
        else
        {
            listFmt.setIndent(blockFmt.indent()+1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
        cursor.endEditBlock();
    }
    else{
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}

