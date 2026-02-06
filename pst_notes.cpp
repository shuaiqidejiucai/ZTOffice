#include "pst_notes.h"
#include "pstsearch.h"
#include "pst_notesatom.h"
#include "pst_ppdrawing.h"
#include "pst_colorschemeatom.h"
#include "pst_progtags.h"
#include "pst_roundtriptheme12atom.h"
#include "pst_roundtripcolormapping12atom.h"
#include "pst_roundtripnotesmastertextstyles12atom.h"
PST_Notes::PST_Notes(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData, var)
{

}

int PST_Notes::parser(PSTSearch* pSearchPtr)
{
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return Error_FailedType;
		}
		switch (ST_TP(stVar))
		{
		case RT_NotesAtom:
		{
			notesAtomPtr = QSharedPointer<PST_NotesAtom>::create(m_srcData, stVar);
			addChildNodePtr(notesAtomPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, notesAtomPtr);
		}
		break;
		case RT_Drawing:
		{
			ppdrwingPtr = QSharedPointer<PST_PPDrawing>::create(m_srcData, stVar);
			addChildNodePtr(ppdrwingPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, ppdrwingPtr);
		}
		break;
		case RT_ColorSchemeAtom:
		{
			colorSchemeAtomPtr = QSharedPointer<PST_ColorSchemeAtom>::create(m_srcData, stVar);
			addChildNodePtr(colorSchemeAtomPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, colorSchemeAtomPtr);
		}
			break;
		case RT_ProgTags:
		{
			protagesPtr = QSharedPointer<PST_ProgTags>::create(m_srcData, stVar);
			addChildNodePtr(protagesPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, protagesPtr);
		}
			break;
		case RT_RoundTripTheme12Atom:
		{
			roundTripTheme12AtomPtr = QSharedPointer<PST_RoundTripTheme12Atom>::create(m_srcData, stVar);
			addChildNodePtr(roundTripTheme12AtomPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, roundTripTheme12AtomPtr);
		}
			break;
		case RT_RoundTripColorMapping12Atom:
		{
			roundTripMapping12AtomPtr = QSharedPointer<PST_RoundTripColorMapping12Atom>::create(m_srcData, stVar);
			addChildNodePtr(roundTripMapping12AtomPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, roundTripMapping12AtomPtr);
		}
			break;
		case RT_RoundTripNotesMasterTextStyles12Atom:
		{
			roundTripNotesMasterTextStyles12Atom = QSharedPointer<PST_RoundTripNotesMasterTextStyles12Atom>::create(m_srcData, stVar);
			addChildNodePtr(roundTripNotesMasterTextStyles12Atom);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, roundTripNotesMasterTextStyles12Atom);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_Notes::clearParserData()
{
	notesAtomPtr.clear();
	ppdrwingPtr.clear();
	colorSchemeAtomPtr.clear();
	protagesPtr.clear();
	roundTripTheme12AtomPtr.clear();
	roundTripMapping12AtomPtr.clear();
	roundTripNotesMasterTextStyles12Atom.clear();
}

int PST_Notes::priority()
{
	return 0;
}
