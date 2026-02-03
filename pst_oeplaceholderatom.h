#ifndef PST_OEPLACEHOLDERATOM_H
#define PST_OEPLACEHOLDERATOM_H

#include "pst_base.h"

class PST_OEPlaceHolderAtom : public PST_Base
{
public:
    PST_OEPlaceHolderAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;
    virtual void clearParserData()override;
    virtual int priority()override;

    quint32 PlacementID = 0;
    quint8 PlaceholderID = 0;
    quint8 Size = 0;
    quint16 Unused = 0;
};

#endif // PST_OEPLACEHOLDERATOM_H
