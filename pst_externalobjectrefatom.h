#ifndef PST_EXTERNALOBJECTREFATOM_H
#define PST_EXTERNALOBJECTREFATOM_H

#include "pst_base.h"

class PST_ExternalObjectRefAtom : public PST_Base
{
public:
    PST_ExternalObjectRefAtom(const QByteArray& srcData, const ST_Variable& var);
    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_EXTERNALOBJECTREFATOM_H
