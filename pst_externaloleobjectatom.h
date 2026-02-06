#ifndef PST_EXTERNALOLEOBJECTATOM_H
#define PST_EXTERNALOLEOBJECTATOM_H

#include "pst_base.h"

class PST_ExternalOleObjectAtom : public PST_Base
{
public:
    PST_ExternalOleObjectAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_EXTERNALOLEOBJECTATOM_H
