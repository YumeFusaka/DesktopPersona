#pragma once

#include <QWidget>
#include <QLabel>
#include <QPixmap>

class DesktopWidget : public QWidget
{
	Q_OBJECT

public:
	DesktopWidget(QWidget* parent = nullptr);
	~DesktopWidget();
	void setAllWallpaper();
	void setPixmap(const QString& fileName);
private:
	QLabel* bkLabel; //放壁纸
	QPixmap bkPixmap;

};
