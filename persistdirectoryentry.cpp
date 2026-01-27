#include "persistdirectoryentry.h"

PersistDirectoryEntry::PersistDirectoryEntry(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var), persistId(0),cPersist(0) {}
