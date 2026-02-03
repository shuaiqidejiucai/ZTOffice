#include "pst_handout.h"

PST_Handout::PST_Handout(const QByteArray& srcData, const ST_Variable& var):PST_Base(srcData,var)
{

}

int PST_Handout::parser()
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
        case RT_Drawing:
        {
            ppDwingPtr = QSharedPointer<PST_PPDrawing>::create(m_srcData, stVar);
            addChildNodePtr(ppDwingPtr);
        }
        break;
        case RT_ColorSchemeAtom:
        {
            colorSchemeAtomPtr = QSharedPointer<PST_ColorSchemeAtom>::create(m_srcData, stVar);
            addChildNodePtr(colorSchemeAtomPtr);
        }
            break;
        case RT_ProgTags:
        {
            proTagesPtr = QSharedPointer<PST_ProgTags>::create(m_srcData, stVar);
            addChildNodePtr(proTagesPtr);
        }
        break;
        case RT_RoundTripTheme12Atom:
        {
            RTT12AtomPtr = QSharedPointer<PST_RoundTripTheme12Atom>::create(m_srcData, stVar);
            addChildNodePtr(RTT12AtomPtr);
        }
        break;
        case RT_RoundTripColorMapping12Atom:
        {
            RTCMappingAtomPtr = QSharedPointer<PST_RoundTripColorMapping12Atom>::create(m_srcData, stVar);
            addChildNodePtr(RTCMappingAtomPtr);
        }
        break;
        default:
            break;
        }
        pos = ST_EP(stVar);
    } while (pos < ST_EP(stVar));
    return Error_SuccessType;
}

void PST_Handout::clearParserData()
{
    ppDwingPtr.clear();
    colorSchemeAtomPtr.clear();
    proTagesPtr.clear();
    RTT12AtomPtr.clear();
    RTCMappingAtomPtr.clear();
}

int PST_Handout::priority()
{
    return 0;
}
