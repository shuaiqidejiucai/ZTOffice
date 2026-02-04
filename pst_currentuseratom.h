#ifndef PST_CURRENTUSERATOM_H
#define PST_CURRENTUSERATOM_H

#include "pst_base.h"
class PST_CurrentUserAtom : public PST_Base
{
public:
    PST_CurrentUserAtom(const QByteArray& byteArry, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr)override;

    virtual void clearParserData()override;

    virtual int priority()override;
};

#endif // PST_CURRENTUSERATOM_H
