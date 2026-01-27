#include "pst_binarytagdata.h"

PST_BinaryTagData::PST_BinaryTagData(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_BinaryTagData::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return -1;
		}
		switch (ST_TP(stVar))
		{
		case RT_RoundTripDocFlags12Atom:
		{
			QSharedPointer<PST_RoundTripDocFlags12Atom> roundTripDocFlags12Atom (new PST_RoundTripDocFlags12Atom(m_srcData, stVar));
			roundTripDocFlags12AtomList.append(roundTripDocFlags12Atom);
		}
		break;
		case RT_GridSpacing10Atom:
		{
			QSharedPointer<PST_GridSpacing10Atom> gridSpacing10Atom (new PST_GridSpacing10Atom(m_srcData, stVar));
			gridSpacing10AtomList.append(gridSpacing10Atom);
		}
		break;
		case RT_SlideTime10Atom:
		{
			QSharedPointer<PST_SlideTime10Atom> slideTime10Atom (new PST_SlideTime10Atom(m_srcData, stVar));
			slideTime10AtomList.append(slideTime10Atom);
		}
		break;
		case RT_RoundTripHeaderFooterDefaults12Atom:
		{
			QSharedPointer<PST_RoundTripHeaderFooterDefaults12Atom> roundTripHFDefaults12Atom (new PST_RoundTripHeaderFooterDefaults12Atom(m_srcData, stVar));
			RTHFD12AtomList.append(roundTripHFDefaults12Atom);
		}
		break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}

