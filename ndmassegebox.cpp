#include "ndmassegebox.h"

ndmassegebox::ndmassegebox(QWidget *parent) : QWidget(parent)
{


    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::ApplicationModal);
    this->setStyleSheet("background-color:#22293c;");

    int fontId = QFontDatabase::addApplicationFont(QCoreApplication::applicationDirPath() + "/PingFangSCRegular.ttf");
    m_Itype = 0;

    Init();

}

ndmassegebox::~ndmassegebox()
{

}

void ndmassegebox::Init()
{
    QVBoxLayout *pLayout_main = new QVBoxLayout(this);

    QWidget* widtitle = new QWidget(this);
    widtitle->setStyleSheet("background-color:#2B3046;");
    widtitle->setFixedHeight(50);
    QHBoxLayout *pLayout_title = new QHBoxLayout(widtitle);
    m_titleLabel = new QLabel(this);
    m_titleLabel->setStyleSheet("QLabel{color:white;font:18px;}");
    m_btn_closeBtn = new PushButton();
    m_btn_closeBtn->loadPixmap("./Config/Res/close_button");
    pLayout_title->addWidget(m_titleLabel);
    pLayout_title->addWidget(m_btn_closeBtn,0,Qt::AlignRight);
    pLayout_title->setContentsMargins(8,0,8,0);

    m_lbText = new QLabel(this);
    m_lbText->setAlignment(Qt::AlignCenter);
    m_lbText->setStyleSheet("QLabel{color:white;font:18px}");

    QHBoxLayout *pLayout_btn = new QHBoxLayout();
    QString strStyle = "QPushButton{color:white;background-color:#383e4f;border-radius:0px;font:15px}"
                       "QPushButton:checked{color:white;background-color:#1673DB}";
    m_btn_okBtn = new QPushButton(this);
    m_btn_cancleBtn = new QPushButton(this);
    m_btn_okBtn->setText(QStringLiteral("确定"));
    m_btn_cancleBtn->setText(QStringLiteral("取消"));
    m_btn_okBtn->setFixedSize(86,38);
    m_btn_cancleBtn->setFixedSize(86,38);
    m_btn_okBtn->setStyleSheet(strStyle);
    m_btn_cancleBtn->setStyleSheet(strStyle);
    m_btn_okBtn->setFocusPolicy(Qt::NoFocus);
    m_btn_cancleBtn->setFocusPolicy(Qt::NoFocus);
    m_btn_okBtn->setCheckable(true);
    m_btn_cancleBtn->setCheckable(true);
    m_btn_okBtn->setChecked(true);
    connect(m_btn_okBtn, SIGNAL(clicked()), this, SLOT(okBtn_press()));
    connect(m_btn_closeBtn, SIGNAL(clicked()), this, SLOT(closeBtn_press()));
    connect(m_btn_cancleBtn, SIGNAL(clicked()), this, SLOT(cancleBtn_press()));
    pLayout_btn->addStretch();
    pLayout_btn->addWidget(m_btn_okBtn);
    pLayout_btn->addWidget(m_btn_cancleBtn);
    pLayout_btn->addStretch();
    pLayout_btn->setSpacing(60);
    pLayout_btn->setContentsMargins(0,0,0,10);

    pLayout_main->addWidget(widtitle);
    pLayout_main->addWidget(m_lbText);
    pLayout_main->addLayout(pLayout_btn);
    pLayout_main->setSpacing(0);
    pLayout_main->setContentsMargins(0,0,0,0);
}

void ndmassegebox::setType(int Itype)
{
    m_Itype = Itype;
}

void ndmassegebox::setLabelText(QString text1, QString text2)
{
    m_titleLabel->setText(text1);
    m_lbText->setText(text2);
}

void ndmassegebox::okBtn_press()
{
    emit Clicked_btn_OK(m_Itype);
    m_btn_okBtn->setChecked(true);
    m_btn_cancleBtn->setChecked(false);
    close();
}
void ndmassegebox::cancleBtn_press()
{
    emit Clicked_btn_Cancel();
    m_btn_okBtn->setChecked(true);
    m_btn_cancleBtn->setChecked(false);
    close();
}
void ndmassegebox::closeBtn_press()
{
    emit Clicked_btn_Cancel();
    m_btn_okBtn->setChecked(true);
    m_btn_cancleBtn->setChecked(false);
    close();
}



//按钮添加背景图
void ndmassegebox::SetButtonText(QString imgsrc,QPushButton* button)
{
    int img_w = QPixmap(imgsrc).width();
    int img_h = QPixmap(imgsrc).height();
    int PicWidth = img_w / 4;
    button->setFixedSize(PicWidth, img_h);
    button->setStyleSheet(QString("QLabel{border-width: 41px; border-image: url(%1)  0 0 0 %2 repeat  repeat;border-width: 0px; border-radius: 0px;}")
        .append("QLabel::hover{border-image: url(%1) 0 0 0 %3  repeat  repeat;}")
        .append("QLabel::pressed{border-image: url(%1) 0  0 0 %4 repeat  repeat;}")
        .append("QLabel::checked{border-image: url(%1) 0  0 0 %4 repeat  repeat;}")
        .append("QLabel::disabled{border-image: url(%1) 0  0 0 %5 repeat  repeat;}")
        .arg(imgsrc).arg(0).arg(PicWidth * 1).arg(PicWidth * 2).arg(PicWidth * 3));
}
