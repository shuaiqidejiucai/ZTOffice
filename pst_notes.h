#ifndef PST_NOTES_H
#define PST_NOTES_H

#include "pst_base.h"

class PST_NotesAtom;
class PST_PPDrawing;
class PST_ColorSchemeAtom;
class PST_ProgTags;
class PST_RoundTripTheme12Atom;
class PST_RoundTripColorMapping12Atom;
class PST_RoundTripNotesMasterTextStyles12Atom;
class PST_Notes : public PST_Base
{
public:
    PST_Notes(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch * pSearchPtr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QSharedPointer<PST_NotesAtom> notesAtomPtr;
    QSharedPointer<PST_PPDrawing> ppdrwingPtr;
    QSharedPointer<PST_ColorSchemeAtom> colorSchemeAtomPtr;
    QSharedPointer<PST_ProgTags> protagesPtr;
    QSharedPointer<PST_RoundTripTheme12Atom> roundTripTheme12AtomPtr;
    QSharedPointer<PST_RoundTripColorMapping12Atom> roundTripMapping12AtomPtr;
    QSharedPointer<PST_RoundTripNotesMasterTextStyles12Atom> roundTripNotesMasterTextStyles12Atom;
};

#endif // PST_NOTES_H
