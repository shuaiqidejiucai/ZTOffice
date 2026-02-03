#ifndef PST_GENERICDATEMETACHARATOM_H
#define PST_GENERICDATEMETACHARATOM_H

#include "pst_base.h"

class PST_GenericDateMetaCharAtom : public PST_Base
{
public:
    PST_GenericDateMetaCharAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_GENERICDATEMETACHARATOM_H
