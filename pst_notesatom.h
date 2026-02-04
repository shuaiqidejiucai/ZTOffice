#ifndef PST_NOTESATOM_H
#define PST_NOTESATOM_H

#include "pst_base.h"

class PST_NotesAtom : public PST_Base
{
public:
    PST_NotesAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_NOTESATOM_H
