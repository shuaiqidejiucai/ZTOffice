#ifndef PST_NOTESTEXTVIEWINFO_H
#define PST_NOTESTEXTVIEWINFO_H

#include "pst_base.h"
#include "pst_viewinfoatom.h"

class PST_NotesTextViewInfo : public PST_Base
{
public:
    PST_NotesTextViewInfo(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;

    QList<QSharedPointer<PST_ViewInfoAtom> > viewInfoAtomList;
};

#endif // PST_NOTESTEXTVIEWINFO_H
