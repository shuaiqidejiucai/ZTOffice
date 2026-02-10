#ifndef PST_MAINMASTER_H
#define PST_MAINMASTER_H
#include "pst_base.h"

class PST_SlideAtom;
class PST_ColorSchemeAtom;
class PST_TxMasterStyleAtom;
class PST_RoundTripOArtTextStyles12Atom;
class PST_PPDrawing;
class PST_ProgTags;
class PST_RoundTripTheme12Atom;
class PST_RoundTripColorMapping12Atom;
class PST_RoundTripContentMasterInfo12Atom;
class PST_RoundTripOriginalMainMasterId12Atom;
class PST_CString;
class PSTParser_EXPORT PST_MainMaster : public PST_Base
{
public:
    PST_MainMaster(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch * pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QSharedPointer<PST_SlideAtom> slideAtomPtr;
    QList<QSharedPointer<PST_ColorSchemeAtom> > colorSchemeAtomPtrList;
    QList<QSharedPointer<PST_TxMasterStyleAtom> > txMasterStyleAtomPtrList;
    QSharedPointer<PST_RoundTripOArtTextStyles12Atom> roundTripOArtTxtStyles12Atom;
    QSharedPointer<PST_PPDrawing> ppdDwingPtr;
    QSharedPointer<PST_ProgTags> progTagsPtr;
    QList<QSharedPointer<PST_RoundTripTheme12Atom> > roundTripTheme12AtomPtrList;
    QList<QSharedPointer<PST_RoundTripColorMapping12Atom> > roundTripColorMapping12AtomPtrList;
    QList<QSharedPointer<PST_RoundTripContentMasterInfo12Atom> > roundTripContentMasterInfo12AtomPtrList;
    QList<QSharedPointer<PST_RoundTripOriginalMainMasterId12Atom> > roundTripContentMasterId12AtomPtrList;
    QList<QSharedPointer<PST_CString> > cstringPtrList;

};

#endif // PST_MAINMASTER_H
