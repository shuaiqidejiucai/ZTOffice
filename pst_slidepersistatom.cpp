#include "pst_slidepersistatom.h"

PST_SlidePersistAtom::PST_SlidePersistAtom(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_SlidePersistAtom::parser()
{
	m_isParser = true;
	quint32 pos = ST_SP(m_STVar);
	PSRReference = GetFlagData<quint32>(m_srcData, pos);
	Flags = GetFlagData<quint32>(m_srcData, pos);
	NumberTexts = GetFlagData<qint32>(m_srcData, pos);
	SlideID = GetFlagData<qint32>(m_srcData, pos);
	Unused = GetFlagData<qint32>(m_srcData, pos);
    return 0;
}
