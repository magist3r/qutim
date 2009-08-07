#ifndef DEPRECATEDPLUGIN_P_H
#define DEPRECATEDPLUGIN_P_H

#include "plugin.h"

namespace qutim_sdk_0_3
{
	Plugin *createDeprecatedPlugin(QObject *object);

	class LIBQUTIM_EXPORT DeprecatedPlugin : public Plugin
	{
		Q_OBJECT
	public:
		DeprecatedPlugin(QObject *object);
		virtual void init();
		virtual bool load();
		virtual bool unload();
	private:
		QByteArray m_name;
		QByteArray m_description;
		QObject *m_object;
		bool m_inited;
	};
}

#endif // DEPRECATEDPLUGIN_P_H
