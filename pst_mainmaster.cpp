#include "pst_mainmaster.h"

PST_MainMaster::PST_MainMaster(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData, var)
{

}

int PST_MainMaster::parser()
{
	ST_Variable stVar;
	quint32 pos = ST_SP(stVar);
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return Error_FailedType;
		}
		switch (ST_TP(stVar))
		{
		case RT_SlideAtom:
		{
			slideAtomPtr = QSharedPointer<PST_SlideAtom>::create(m_srcData, stVar);
			addChildNodePtr(slideAtomPtr);
		}
		break;
		case RT_ColorSchemeAtom:
		{
			QSharedPointer<PST_ColorSchemeAtom> colorSchemeAtom(new PST_ColorSchemeAtom(m_srcData, stVar));
			colorSchemeAtomPtrList.append(colorSchemeAtom);
			addChildNodePtr(colorSchemeAtom);
		}
		break;
		case RT_TextMasterStyleAtom:
		{
			QSharedPointer<PST_TxMasterStyleAtom> txMasterStyleAtomPtr(new PST_TxMasterStyleAtom(m_srcData, stVar));
			txMasterStyleAtomPtrList.append(txMasterStyleAtomPtr);
			addChildNodePtr(txMasterStyleAtomPtr);
		}
			break;
		case RT_RoundTripOArtTextStyles12Atom:
		{
			roundTripOArtTxtStyles12Atom = QSharedPointer<PST_RoundTripOArtTextStyles12Atom>::create(m_srcData, stVar);
			addChildNodePtr(roundTripOArtTxtStyles12Atom);
		}
		break;
		case RT_Drawing:
		{
			ppdDwingPtr = QSharedPointer<PST_PPDrawing>::create(m_srcData, stVar);
			addChildNodePtr(ppdDwingPtr);
		}
			break;
		case RT_ProgTags:
		{
			progTagsPtr = QSharedPointer<PST_ProgTags>::create(m_srcData, stVar);
			addChildNodePtr(progTagsPtr);
		}
			break;
		case RT_RoundTripTheme12Atom:
		{
			QSharedPointer<PST_RoundTripTheme12Atom> roundTripTheme12AtomPtr(new PST_RoundTripTheme12Atom(m_srcData, stVar));
			roundTripTheme12AtomPtrList.append(roundTripTheme12AtomPtr);
			addChildNodePtr(roundTripTheme12AtomPtr);
		}
			break;
		case RT_RoundTripColorMapping12Atom:
		{
			QSharedPointer<PST_RoundTripColorMapping12Atom> roundTripColoeMapping12AtomPtr (new PST_RoundTripColorMapping12Atom(m_srcData, stVar));
			roundTripColorMapping12AtomPtrList.append(roundTripColoeMapping12AtomPtr);
			addChildNodePtr(roundTripColoeMapping12AtomPtr);
		}
			break;
		case RT_RoundTripContentMasterInfo12Atom:
		{
			QSharedPointer<PST_RoundTripContentMasterInfo12Atom> roundTripContentMaster12AtomPtr(new PST_RoundTripContentMasterInfo12Atom(m_srcData, stVar));
			roundTripContentMasterInfo12AtomPtrList.append(roundTripContentMaster12AtomPtr);
			addChildNodePtr(roundTripContentMaster12AtomPtr);
		}
			break;
		case RT_RoundTripOriginalMainMasterId12Atom:
		{
			QSharedPointer<PST_RoundTripOriginalMainMasterId12Atom>roundTripOriginalMainMasterId12AtomPtr(new PST_RoundTripOriginalMainMasterId12Atom(m_srcData, stVar));
			roundTripContentMasterId12AtomPtrList.append(roundTripOriginalMainMasterId12AtomPtr);
			addChildNodePtr(roundTripOriginalMainMasterId12AtomPtr);
		}
			break;
		case RT_CString:
		{
			QSharedPointer<PST_CString> cstring(new PST_CString(m_srcData, stVar));
			cstringPtrList.append(cstring);
			addChildNodePtr(cstring);
		}
			break;
		default:
			break;
			
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(stVar));
	return Error_SuccessType;
}

void PST_MainMaster::clearParserData()
{
	slideAtomPtr.clear();
	colorSchemeAtomPtrList.clear();
	txMasterStyleAtomPtrList.clear();
	roundTripOArtTxtStyles12Atom.clear();
	ppdDwingPtr.clear();
	progTagsPtr.clear();
	roundTripTheme12AtomPtrList.clear();
	roundTripColorMapping12AtomPtrList.clear();
	roundTripContentMasterInfo12AtomPtrList.clear();
	roundTripContentMasterId12AtomPtrList.clear();
	cstringPtrList.clear();
}

int PST_MainMaster::priority()
{
	return 0;
}
