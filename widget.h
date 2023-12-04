#pragma once

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include "desktopwidget.h"
class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget* parent = nullptr);
	~Widget();
	void updateRoleAnimation();
	bool eventFilter(QObject* watched, QEvent* ev) override;
	void initBtn();
private:
	QLabel* roleLabel;
	qint8 curFrame;  //当前帧
	QPushButton* closeBtn;
	QPushButton* cutBtn;
	QPushButton* openBtn;

	DesktopWidget* desktopWidget;
private slots:
	// 关闭槽函数
	void closeApplication() {
		QCoreApplication::quit();
	}
};
