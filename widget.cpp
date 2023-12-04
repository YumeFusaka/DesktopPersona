#include "widget.h"
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QFileDialog.h>
Widget::Widget(QWidget* parent)
	: QWidget(parent)
	, roleLabel(new QLabel(this))
	, curFrame(0)
	, desktopWidget(new DesktopWidget)
{
	initBtn();
	//去掉窗口的边框，和让背景透明
	setWindowFlags(Qt::WindowType::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	/*//使用定时器更新动画
	qtimer* updatetimer = new qtimer(this);
	updatetimer->callontimeout(this, &widget::updateroleanimation);
	updatetimer->start(500);*/

	updateRoleAnimation();

	//给窗口设置阴影
	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
	effect->setColor(QColor(230, 231, 232, 220));
	effect->setBlurRadius(10);
	this->setGraphicsEffect(effect);

	this->installEventFilter(this);
	roleLabel->resize(300, 500);

	desktopWidget->show();
}

Widget::~Widget()
{}

void Widget::updateRoleAnimation() {
	QString qss("background-repeat:no-repeat;");
	roleLabel->setStyleSheet(qss
		+ QString("background-image:url(:/C:/Users/j/Pictures/pt/%1.png)").arg(curFrame));
	curFrame = (curFrame + 1) % 5;
}

bool Widget::eventFilter(QObject* watched, QEvent* ev) {
	QMouseEvent* mouseev = static_cast<QMouseEvent*>(ev);
	//判断鼠标左键按下
	static QPoint begpos;
	if (ev->type() == QEvent::MouseButtonPress) {
		begpos = mouseev->globalPos() - this->pos();
	}
	//判断鼠标移动
	else if (ev->type() == QEvent::MouseMove &&
		mouseev->buttons() & Qt::MouseButton::LeftButton) {
		this->move(mouseev->globalPos() - begpos);
	}

	return false;
}

void Widget::initBtn() {
	closeBtn = new QPushButton(this);
	cutBtn = new QPushButton(this);
	openBtn = new QPushButton(this);
	closeBtn->setGeometry(250, 200, 32, 32);
	cutBtn->setGeometry(250, 240, 32, 32);
	openBtn->setGeometry(250, 280, 32, 32);

	closeBtn->setStyleSheet("background-image:url(:/C:/Users/j/Pictures/pt/qidong.png)");
	cutBtn->setStyleSheet("background-image:url(:/C:/Users/j/Pictures/pt/you.png)");
	openBtn->setStyleSheet("background-image:url(:/C:/Users/j/Pictures/pt/shengji.png)");

	this->setStyleSheet("QPushButton{background-color:rgb(255,204,229);\
						border:none;border-radius:5px;background-repeat:no-repeat;background-position: center center;}\
						QPushButton:hover{background-color:rgb(204,204,255)}");
	connect(closeBtn, &QPushButton::pressed, this, &Widget::closeApplication);
	connect(cutBtn, &QPushButton::pressed, this, &Widget::updateRoleAnimation);
	connect(openBtn, &QPushButton::pressed, this, [=]() {
		QString filename = QFileDialog::getOpenFileName(nullptr, "选择壁纸", "./", "Image (*.jpg *.png)");
		if (filename.isEmpty()) {
			return;
		}
		desktopWidget->setPixmap(filename);
		});
}
