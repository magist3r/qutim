#include "quetzalgui.h"
#include <QLibrary>
#include <QFileInfo>

namespace Quetzal
{
static _purple_request_get_ui_ops purple_request_get_ui_ops = NULL;
static _purple_request_close purple_request_close = NULL;

static void kde_request_close(FileDialog *dialog)
{
	PurpleRequestType type;
	if (dialog->mode() & KFile::File )
		type = PURPLE_REQUEST_FILE;
	else
		type = PURPLE_REQUEST_FOLDER;
	purple_request_close(type, dialog);
}

FileDialog::FileDialog(const KUrl &startDir, const QString &title,
					   GCallback ok_cb, GCallback cancel_cb, void *user_data)
	: KFileDialog(startDir, QString(), 0)
{
	setWindowTitle(title);
	m_ok_cb = (PurpleRequestFileCb)ok_cb;
	m_cancel_cb = (PurpleRequestFileCb)cancel_cb;
	m_user_data = user_data;
	connect(this, SIGNAL(closeClicked()), this, SLOT(slotCancel()));
	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_QuitOnClose, false);
}

void FileDialog::slotOk()
{
	if (m_ok_cb)
		m_ok_cb(m_user_data, selectedFile().toUtf8().constData());
	m_ok_cb = NULL;
	kde_request_close(this);
}

void FileDialog::slotCancel()
{
	if (m_cancel_cb)
		m_cancel_cb(m_user_data, selectedFile().toUtf8().constData());
	m_cancel_cb = NULL;
	kde_request_close(this);
}

void FileDialog::closeEvent(QCloseEvent *e)
{
	slotCancel();
	KFileDialog::closeEvent(e);
}

static void *kde_request_file(const char *title, const char *filename,
							  gboolean savedialog, GCallback ok_cb,
							  GCallback cancel_cb, PurpleAccount *account,
							  const char *who, PurpleConversation *conv,
							  void *user_data)
{
	Q_UNUSED(account);
	Q_UNUSED(who);
	Q_UNUSED(conv);
	QFileInfo info = QString(filename);
	KFileDialog *dialog = new FileDialog(info.absolutePath(), title, ok_cb, cancel_cb, user_data);
	dialog->setOperationMode(savedialog ? KFileDialog::Saving : KFileDialog::Opening);
	dialog->setMode(KFile::File);
	dialog->show();
	return dialog;
}

static void *kde_request_folder(const char *title, const char *dirname,
								GCallback ok_cb, GCallback cancel_cb,
								PurpleAccount *account, const char *who,
								PurpleConversation *conv, void *user_data)
{
	Q_UNUSED(account);
	Q_UNUSED(who);
	Q_UNUSED(conv);
	FileDialog *dialog = new FileDialog(KUrl(dirname), title, ok_cb, cancel_cb, user_data);
	dialog->setMode(KFile::Directory | KFile::ExistingOnly);
	dialog->show();
	return dialog;
}

void initGui()
{
	QLibrary lib("purple");
	purple_request_get_ui_ops = (_purple_request_get_ui_ops)lib.resolve("purple_request_get_ui_ops");
	purple_request_close = (_purple_request_close)lib.resolve("purple_request_close");

	PurpleRequestUiOps *ui_ops = purple_request_get_ui_ops();
	ui_ops->request_file = kde_request_file;
	ui_ops->request_folder = kde_request_folder;
}
}