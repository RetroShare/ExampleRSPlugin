#include "NetExampleMainpage.h"
#include "ui_NetExampleMainpage.h"
//#include "services/p3NetExample.h"
#include "interface/rsNetExample.h"
#include<qjsondocument.h>


NetExampleMainpage::NetExampleMainpage(QWidget *parent, NetExampleNotify *notify) :
	MainPage(parent),
	mNotify(notify),
	ui(new Ui::NetExampleMainpage)
{
	ui->setupUi(this);

	connect(mNotify, SIGNAL(NeMsgArrived(RsPeerId,QString)), this , SLOT(NeMsgArrived(RsPeerId,QString)));
	connect(mNotify, SIGNAL(NePaintArrived(RsPeerId,int,int)), this , SLOT(NePaintArrived(RsPeerId,int,int)));
	//ui->listWidget->addItem("str");
	connect(ui->paintWidget, SIGNAL(mmEvent(int,int)), this, SLOT(mmEvent(int,int)));

}

NetExampleMainpage::~NetExampleMainpage()
{
	delete ui;
}

void NetExampleMainpage::mmEvent(int x, int y)
{
	rsNetExample->broadcast_paint(x,y);
}

void NetExampleMainpage::on_pingAllButton_clicked()
{
	rsNetExample->ping_all();
	NeMsgArrived(rsPeers->getOwnId(),"ping");
}


void NetExampleMainpage::NeMsgArrived(const RsPeerId &peer_id, QString str)
{
	QJsonDocument jdoc = QJsonDocument::fromJson(str.toUtf8());
	QVariantMap vmap = jdoc.toVariant().toMap();
	std::cout << "GUI got Packet from: " << peer_id;
	std::cout << " saying " << str.toStdString();
	std::cout << std::endl;
	QString type = vmap.value("type").toString();
	if (type == "chat"){
		QString output = QString::fromStdString(rsPeers->getPeerName(peer_id));
		output+=": ";
		output+=vmap.value("message").toString();
		ui->listWidget->addItem(output);
	}else if (type == "paint"){
		int x =vmap.value("x").toInt();
		int y =vmap.value("y").toInt();
		NePaintArrived(peer_id,x,y);
	}else{
		QString output = QString::fromStdString(rsPeers->getPeerName(peer_id));
		output+=": ";
		output+=str;
		ui->listWidget->addItem(output);
	}

	{
		QString output = QString::fromStdString(rsPeers->getPeerName(peer_id));
		output+=": ";
		output+=str;
		ui->netLogWidget->addItem(output);
	}
}
void NetExampleMainpage::NePaintArrived(const RsPeerId &peer_id, int x, int y)
{

	std::cout << "GUI got Paint from: " << peer_id;
	std::cout << std::endl;

	ui->paintWidget->paintAt(x,y);
}

void NetExampleMainpage::on_broadcastButton_clicked()
{
	rsNetExample->msg_all(ui->msgInput->text().toStdString());
	NeMsgArrived(rsPeers->getOwnId(),ui->msgInput->text());
	ui->msgInput->clear();
}
