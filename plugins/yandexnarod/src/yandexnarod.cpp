/****************************************************************************
 *  yandexnarod.cpp
 *
 *  Copyright (c) 2008-2009 by Alexander Kazarin <boiler@co.ru>
 *                     2010 by Nigmatullin Ruslan <euroelessar@ya.ru>
 *                     2011 by Prokhin Alexey <alexey.prokhin@yandex.ru>
 *
 ***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************
*****************************************************************************/

#include "yandexnarod.h"
#include "requestauthdialog.h"
#include "yandexnarodauthorizator.h"
#include "yandexnaroduploadjob.h"
#include <qutim/actiongenerator.h>
#include <qutim/contact.h>
#include <qutim/message.h>
#include <qutim/account.h>
#include <qutim/protocol.h>
#include <qutim/settingslayer.h>
#include <qutim/configbase.h>
#include <qutim/debug.h>

struct YandexNarodScope
{
	QNetworkAccessManager *networkManager;
	YandexNarodAuthorizator *authorizator;
};

static inline YandexNarodScope *scope()
{
	static YandexNarodScope scope;
	return &scope;
}

void YandexNarodPlugin::init()
{
	setInfo(QT_TRANSLATE_NOOP("Plugin", "YandexNarod"),
			QT_TRANSLATE_NOOP("Plugin", "Send files via Yandex.Narod filehosting service"),
			PLUGIN_VERSION(0, 2, 1, 0));
	setCapabilities(Loadable);
	addAuthor(QT_TRANSLATE_NOOP("Author","Sidorov Aleksey"),
			  QT_TRANSLATE_NOOP("Task","Developer"),
			  QLatin1String("sauron@citadelspb.com"),
			  QLatin1String("sauron.me"));
	addAuthor(QT_TRANSLATE_NOOP("Author", "Ruslan Nigmatullin"),
			  QT_TRANSLATE_NOOP("Task", "Developer"),
			  QLatin1String("euroelessar@gmail.com"));
	addAuthor(QT_TRANSLATE_NOOP("Author", "Alexey Prokhin"),
			  QT_TRANSLATE_NOOP("Task", "Author"),
			  QLatin1String("alexey.prokhin@yandex.ru"));
	addAuthor(QT_TRANSLATE_NOOP("Author","Alexander Kazarin"),
			  QT_TRANSLATE_NOOP("Task","Author"),
			  QLatin1String("boiler@co.ru"));
	addExtension(QT_TRANSLATE_NOOP("Plugin", "Yandex.Narod"),
				 QT_TRANSLATE_NOOP("Plugin", "Send files via Yandex.Narod filehosting service"),
				 new SingletonGenerator<YandexNarodFactory>(),
				 ExtensionIcon(""));
}

bool YandexNarodPlugin::load()
{
	SettingsItem *settings = new GeneralSettingsItem<YandexNarodSettings>(
			Settings::Plugin,
			QIcon(),
			QT_TRANSLATE_NOOP("Yandex", "Yandex Narod"));
	settings->connect(SIGNAL(testclick()), this,  SLOT(on_btnTest_clicked()));
	Settings::registerItem(settings);
	scope()->networkManager = new QNetworkAccessManager(this);
	loadCookies();
	scope()->authorizator = new YandexNarodAuthorizator(scope()->networkManager);
	connect(scope()->authorizator, SIGNAL(needSaveCookies()), SLOT(saveCookies()));
	connect(scope()->networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(saveCookies()));

	return true;
}

bool YandexNarodPlugin::unload()
{
	return false;
}

void YandexNarodPlugin::loadCookies()
{
	Config cookies = Config().group("yandex");
	QNetworkCookieJar *cookieJar = scope()->networkManager->cookieJar();
	QList<QNetworkCookie> cookieList;
	int count = cookies.beginArray("cookies");
	for (int i = 0; i < count; i++) {
		QNetworkCookie netcook;
		const Config cookie = cookies.arrayElement(i);
		netcook.setDomain(cookie.value("domain", QString()));
		QString date = cookie.value("expirationDate", QString());
		if (!date.isEmpty())
			netcook.setExpirationDate(QDateTime::fromString(date, Qt::ISODate));
		if (!netcook.expirationDate().isValid() || netcook.expirationDate() < QDateTime::currentDateTime())
			continue;
		netcook.setHttpOnly(cookie.value("httpOnly", false));
		netcook.setSecure(cookie.value("secure", false));
		netcook.setName(cookie.value("name", QString()).toLatin1());
		netcook.setPath(cookie.value("path", QString()));
		netcook.setValue(cookie.value("value", QByteArray(), Config::Crypted));
		cookieList.append(netcook);
		debug() << netcook;
	}
	cookieJar->setCookiesFromUrl(cookieList, QUrl("http://yandex.ru"));
}

void YandexNarodPlugin::saveCookies()
{
#if 0
	Config cookies = Config().group("yandex");
	cookies.remove("cookies");
	cookies.beginArray("cookies");

	QNetworkCookieJar *cookieJar = scope()->networkManager->cookieJar();
	int i = 0;
	foreach (QNetworkCookie netcook, cookieJar->cookiesForUrl(QUrl("http://narod.yandex.ru"))) {
		if (netcook.isSessionCookie())
			continue;
		ConfigGroup cookie = cookies.arrayElement(i++);
		cookie.setValue("domain", netcook.domain());
		cookie.setValue("expirationDate", netcook.expirationDate().toString(Qt::ISODate));
		cookie.setValue("httpOnly", netcook.isHttpOnly());
		cookie.setValue("secure", netcook.isSecure());
		cookie.setValue("name", QString::fromLatin1(netcook.name()));
		cookie.setValue("path", netcook.path());
		cookie.setValue("value", netcook.value(), Config::Crypted);
	}
	cookies.sync();
#else
	Config config;
	config.beginGroup(QLatin1String("yandex"));
	config.setValue(QLatin1String("token"), scope()->authorizator->token(), Config::Crypted);
#endif
}

void YandexNarodPlugin::onActionClicked(QObject *obj)
{
	Q_UNUSED(obj);
//	m_uploadWidget = new YandexNarodUploadDialog();
//	connect(m_uploadWidget, SIGNAL(canceled()), this, SLOT(removeUploadWidget()));
//
//	m_uploadWidget->show();
//
//		fi.setFile(filepath);
//		group.setValue("lastdir", fi.dir().path());
//		group.sync();
//
//		m_netMan = new YandexNarodNetMan(m_uploadWidget);
//		m_uploadWidget->setContact(contact);
//		connect(m_netMan, SIGNAL(statusText(QString)), m_uploadWidget, SLOT(setStatus(QString)));
//		connect(m_netMan, SIGNAL(statusFileName(QString)), m_uploadWidget, SLOT(setFilename(QString)));
//		connect(m_netMan, SIGNAL(transferProgress(qint64,qint64)), m_uploadWidget, SLOT(progress(qint64,qint64)));
//		connect(m_netMan, SIGNAL(uploadFileURL(QString)), this, SLOT(onFileURL(QString)));
//		connect(m_netMan, SIGNAL(uploadFinished()), m_uploadWidget, SLOT(setDone()));
//		m_netMan->startUploadFile(filepath);
//	}
//	else {
//		delete m_uploadWidget; m_uploadWidget=0;
//	}
//
//	authtest=false;
}

void YandexNarodPlugin::onManageClicked()
{
//	if (m_manageDialog.isNull()) {
//		m_manageDialog = new YandexNarodManager();
//		m_manageDialog->show();
//	}
}

void YandexNarodPlugin::on_btnTest_clicked()
{
	YandexNarodSettings *settingsWidget = qobject_cast<YandexNarodSettings *>(sender());
//	testnetman = new YandexNarodNetMan(settingsWidget);
//	connect(testnetman, SIGNAL(statusText(QString)), settingsWidget, SLOT(setStatus(QString)));
//	connect(testnetman, SIGNAL(finished()), this , SLOT(on_TestFinished()));
//	debug() << settingsWidget->getLogin() << settingsWidget->getPasswd();
//	testnetman->startAuthTest(settingsWidget->getLogin(), settingsWidget->getPasswd());
	YandexNarodAuthorizator *auth = new YandexNarodAuthorizator(settingsWidget);
	auth->requestAuthorization(settingsWidget->getLogin(), settingsWidget->getPasswd());
}

void YandexNarodPlugin::on_TestFinished()
{
//	delete testnetman;
}

void YandexNarodPlugin::actionStart()
{
}

void YandexNarodPlugin::onFileURL(const QString &)
{
//	YandexNarodNetMan *netMan = qobject_cast<YandexNarodNetMan *>(sender());
//	Q_ASSERT(netMan);
//
//	if (Contact *contact = netMan->contact()) {
//		QString sendmsg = Config().group("yandexnarod").value("template", QString("File sent: %N (%S bytes)\n%U"));
//		sendmsg.replace("%N", fi.fileName());
//		sendmsg.replace("%U", url);
//		sendmsg.replace("%S", QString::number(fi.size()));
//		m_uploadWidget->setStatus(tr("File sent"));
//		m_uploadWidget->close();
//		Message message;
//		message.setText(sendmsg);
//		contact->account()->getUnitForSession(contact)->sendMessage(message);
//	}
}

YandexNarodFactory::YandexNarodFactory() :
	FileTransferFactory(tr("Yandex.Narod"), 0)
{
	setIcon(QIcon(":/icons/yandexnarodplugin.png"));
	foreach (Protocol *protocol, Protocol::all()) {
		foreach (Account *account, protocol->accounts())
			onAccountAdded(account);
		connect(protocol, SIGNAL(accountCreated(qutim_sdk_0_3::Account*)),
				SLOT(onAccountAdded(qutim_sdk_0_3::Account*)));
	}
}

bool YandexNarodFactory::checkAbility(ChatUnit *unit)
{
	Q_ASSERT(unit);
	Status status = unit->account()->status();
	return status != Status::Offline && status != Status::Connecting;
}

bool YandexNarodFactory::startObserve(ChatUnit *unit)
{
	Q_ASSERT(unit);
	m_observedUnits.insert(unit->account(), unit);
	return true;
}

bool YandexNarodFactory::stopObserve(ChatUnit *unit)
{
	Q_ASSERT(unit);
	Observers::iterator itr = m_observedUnits.begin();
	while (itr != m_observedUnits.end()) {
		if (*itr == unit)
			itr = m_observedUnits.erase(itr);
		else
			++itr;
	}
	return true;
}

FileTransferJob *YandexNarodFactory::create(ChatUnit *unit)
{
	return new YandexNarodUploadJob(unit, this);
}

QNetworkAccessManager *YandexNarodFactory::networkManager()
{
	return scope()->networkManager;
}

YandexNarodAuthorizator *YandexNarodFactory::authorizator()
{
	return scope()->authorizator;
}

void YandexNarodFactory::onAccountAdded(qutim_sdk_0_3::Account *account)
{
	connect(account, SIGNAL(statusChanged(qutim_sdk_0_3::Status,qutim_sdk_0_3::Status)),
			SLOT(onAccountStatusChanged(qutim_sdk_0_3::Status)));
}

void YandexNarodFactory::onAccountStatusChanged(const qutim_sdk_0_3::Status &status)
{
	bool isOnline = status != Status::Offline && status != Status::Connecting;
	foreach (ChatUnit *unit, m_observedUnits.values(sender()))
		changeAvailability(unit, isOnline);
}

YandexRequest::YandexRequest(const QUrl &url)
{
	QUrl tmp = url;
	tmp.addQueryItem(QLatin1String("oauth_token"), scope()->authorizator->token());
	setUrl(tmp);
	debug() << tmp;
//	QByteArray token = scope()->authorizator->token().toLatin1();
//	setRawHeader("Authorization", "OAuth " + token);
//	debug() << token;
//	setRawHeader("Authorization", token);
}

QUTIM_EXPORT_PLUGIN(YandexNarodPlugin)