#ifndef PST_NOTESTEXTVIEWINFO_H
#define PST_NOTESTEXTVIEWINFO_H

#include "pst_base.h"

class PST_ViewInfoAtom;
class PSTParser_EXPORT PST_NotesTextViewInfo : public PST_Base
{
public:
    PST_NotesTextViewInfo(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QList<QSharedPointer<PST_ViewInfoAtom> > viewInfoAtomList;
};

#endif // PST_NOTESTEXTVIEWINFO_H
