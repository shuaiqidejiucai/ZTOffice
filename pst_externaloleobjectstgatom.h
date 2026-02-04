#ifndef PST_EXTERNALOLEOBJECTSTGATOM_H
#define PST_EXTERNALOLEOBJECTSTGATOM_H

#include "pst_base.h"

class PST_ExternalOleObjectStgAtom : public PST_Base
{
public:
    PST_ExternalOleObjectStgAtom(const QByteArray& srcData, const ST_Variable& var);
    virtual int parser(PSTSearch* pSearchPtr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_EXTERNALOLEOBJECTSTGATOM_H
