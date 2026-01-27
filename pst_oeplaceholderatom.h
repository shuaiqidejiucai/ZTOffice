#ifndef PST_OEPLACEHOLDERATOM_H
#define PST_OEPLACEHOLDERATOM_H

#include "pst_base.h"

class PST_OEPlaceHolderAtom : public PST_Base
{
public:
    PST_OEPlaceHolderAtom(const QByteArray& srcData, const ST_Variable& var);

    quint32 PlacementID;
    quint8 PlaceholderID;
    quint8 Size;
    quint16 Unused;
};

#endif // PST_OEPLACEHOLDERATOM_H
