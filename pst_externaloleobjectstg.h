#ifndef PST_EXTERNALOLEOBJECTSTG_H
#define PST_EXTERNALOLEOBJECTSTG_H

#include "pst_base.h"

class PST_ExternaloleObjectStg : public PST_Base
{
public:
    PST_ExternaloleObjectStg(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch * pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_EXTERNALOLEOBJECTSTG_H
