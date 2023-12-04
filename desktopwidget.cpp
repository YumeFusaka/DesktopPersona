#include "desktopwidget.h"
#include <QHBoxLayout>
#include <QApplication>
#include <qt_windows.h>
#include <QDebug>
#include <QScreen>
DesktopWidget::DesktopWidget(QWidget* parent)
	: QWidget(parent)
	, bkLabel(new QLabel)
{
	this->resize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(bkLabel);


	setPixmap(":/C:/Users/j/Pictures/pt/b.png");
	setAllWallpaper();
}

DesktopWidget::~DesktopWidget()
{}

void DesktopWidget::setAllWallpaper() {

	HWND desktopHwd = FindWindow(L"Progman", L"Program Manager");
	if (!desktopHwd) {
		qDebug() << "查找失败";
		return;
	}
	//把this设置给找到的窗口
	qDebug() << "设置成功";
	//SetParent((HWND)this->winId(), desktopHwd);
}

void DesktopWidget::setPixmap(const QString& fileName) {
	if (QPixmap(fileName).isNull()) {
		return;
	}
	int nWidth = GetSystemMetrics(SM_CXSCREEN);
	int nHeight = GetSystemMetrics(SM_CYSCREEN);
	QSize size(nWidth, nHeight);
	bkPixmap = bkPixmap.scaled(size);
	bkPixmap.load(fileName);
	bkLabel->setPixmap(bkPixmap);
	bkLabel->setGeometry(0, 0, nWidth, nHeight);

	this->hide();
	this->showFullScreen();  //全屏显示
}

