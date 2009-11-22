/****************************************************************************
 *  roster.h
 *
 *  Copyright (c) 2009 by Nigmatullin Ruslan <euroelessar@gmail.com>
 *                        Prokhin Alexey <alexey.prokhin@yandex.ru>
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

#ifndef ROSTER_H
#define ROSTER_H

#include <QQueue>
#include "snachandler.h"
#include "messageplugin.h"
#include "icqcontact.h"

namespace Icq {

class OscarConnection;

class Roster : public SNACHandler
{
	Q_OBJECT
public:
	Roster(IcqAccount *account);
	virtual void handleSNAC(AbstractConnection *conn, const SNAC &snac);
	QString groupId2Name(quint16 id) { return m_groups.value(id); }
	IcqContact *contact(const QString &uin) { return m_contacts.value(uin); }
	void sendMessage(const QString &id, const QString &message);
	void sendAuthResponse(const QString &id, const QString &message, bool auth = true);
	quint16 sendAddGroupRequest(const QString &name, quint16 group_id = 0);
	void sendRemoveGroupRequest(quint16 id);
	IcqContact *sendAddContactRequest(const QString &contact_id, const QString &contact_name, quint16 group_id);
	void sendRemoveContactRequst(const QString &contact_id);
	void sendRenameContactRequest(const QString &contact_id, const QString &name);
	void sendRenameGroupRequest(quint16 group_id, const QString &name);
private:
	enum ModifingType {
		mt_add = ListsAddToList,
		mt_add_modify = ListsList,
		mt_modify = ListsUpdateGroup,
		mt_remove =  ListsRemoveFromList
	};
	enum SsiBuddyTlvs
	{
		SsiBuddyNick = 0x0131,
		SsiBuddyComment = 0x013c,
		SsiBuddyReqAuth = 0x0066
	};
	struct SSIItem
	{
		SSIItem():
			group_id(0), item_id(0)
		{}
		SSIItem(const SNAC &snac);
		~SSIItem(){}
		QString toString() const;
		QString record_name;
		quint16 group_id;
		quint16 item_id;
		quint16 item_type;
		TLVMap tlvs;
	};
	struct SSIHistoryItem
	{
		SSIHistoryItem(const SSIItem &item_, ModifingType type_):
			item(item_), type(type_)
		{
		}
		SSIItem item;
		ModifingType type;
	};
	enum State { ReceivingRoster, RosterReceived } m_state;
	void handleServerCListReply(const SNAC &snac);
	void handleSSIItem(const SSIItem &item, ModifingType type);
	void handleAddModifyCLItem(const SSIItem &item, ModifingType type);
	void handleRemoveCLItem(const SSIItem &item);
	void removeContact(IcqContact *contact);
	void handleSSIServerAck(const SNAC &sn);
	void handleUserOnline(const SNAC &snac);
	void handleUserOffline(const SNAC &snac);
	void handleMessage(const SNAC &snac);
	void handleError(const SNAC &snac);
	void handleMetaInfo(const SNAC &snac);
	void sendRosterAck();
	void sendOfflineMessagesRequest() { sendMetaInfoRequest(0x003C); }
	void sendMetaInfoRequest(quint16 type);
	void sendCLModifyStart();
	void sendCLModifyEnd();
	void sendCLOperator(const SSIItem &item, quint16 operation);
	IcqAccount *m_account;
	OscarConnection *m_conn;
	QMap<quint16, QString> m_groups;
	QMultiHash<Capability, MessagePlugin *> m_msg_plugins;
	QHash<QString, IcqContact *> m_contacts;
	QHash<QString, IcqContact *> m_not_in_list;
	QQueue<SSIHistoryItem> m_ssi_history;
};

} // namespace Icq

#endif // ROSTER_H
