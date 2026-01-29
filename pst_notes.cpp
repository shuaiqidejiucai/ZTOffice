#include "pst_notes.h"

PST_Notes::PST_Notes(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData, var)
{

}

int PST_Notes::parser()
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
		case RT_NotesAtom:
		{
			notesAtomPtr = QSharedPointer<PST_NotesAtom>::create(m_srcData, stVar);
		}
		break;
		case RT_Drawing:
		{
			ppdrwingPtr = QSharedPointer<PST_PPDrawing>::create(m_srcData, stVar);
		}
		break;
		case RT_ColorSchemeAtom:
		{
			colorSchemeAtomPtr = QSharedPointer<PST_ColorSchemeAtom>::create(m_srcData, stVar);
		}
			break;
		case RT_ProgTags:
		{
			protagesPtr = QSharedPointer<PST_ProgTags>::create(m_srcData, stVar);
		}
			break;
		case RT_RoundTripTheme12Atom:
		{
			roundTripTheme12AtomPtr = QSharedPointer<PST_RoundTripTheme12Atom>::create(m_srcData, stVar);
		}
			break;
		case RT_RoundTripColorMapping12Atom:
		{
			roundTripMapping12AtomPtr = QSharedPointer<PST_RoundTripColorMapping12Atom>::create(m_srcData, stVar);
		}
			break;
		case RT_RoundTripNotesMasterTextStyles12Atom:
		{
			roundTripNotesMasterTextStyles12Atom = QSharedPointer<PST_RoundTripNotesMasterTextStyles12Atom>::create(m_srcData, stVar);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}
