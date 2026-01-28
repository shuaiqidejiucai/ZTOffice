#include "pst_persistdirectoryatom.h"

PST_PersistDirectoryAtom::PST_PersistDirectoryAtom(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PST_PersistDirectoryAtom::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);

	do
	{
		QSharedPointer<PersistDirectoryEntry> persistDirEntry(new PersistDirectoryEntry());
		quint32 PersistBits =  GetFlagData<quint32>(m_srcData, pos);
		persistDirEntry->cPersist = PersistBits >> 20;
		persistDirEntry->persistId = PersistBits & 0xFFFFF;

		for (quint16 i = 1; i <= persistDirEntry->cPersist; ++i)
		{
			persistDirEntry->rgPersistOffsetPtr_Array.append(GetFlagData<quint32>(m_srcData, pos));
		}
		rgPersistDirEntryArray.append(persistDirEntry);
	} while (pos < ST_EP(m_STVar));

	return 0;
}
