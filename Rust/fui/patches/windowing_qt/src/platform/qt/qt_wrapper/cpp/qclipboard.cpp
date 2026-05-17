#include <QClipboard>
#include "qclipboard.h"

void QClipboard_setText(void *self, void *text, int mode)
{
    QClipboard *clipboard = static_cast<QClipboard *>(self);
	const QString *qtext = static_cast<const QString *>(text);
	clipboard->setText(*qtext, (QClipboard::Mode)mode);
}

void* QClipboard_text(void *self, int mode)
{
    QClipboard *clipboard = static_cast<QClipboard *>(self);
	QString result = clipboard->text((QClipboard::Mode)mode);
	if (result.isNull()) {
        return nullptr;
    }
    return static_cast<void *>(new QString(std::move(result)));
}
