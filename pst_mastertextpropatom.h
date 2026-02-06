#ifndef PST_MASTERTEXTPROPATOM_H
#define PST_MASTERTEXTPROPATOM_H

#include "pst_base.h"

class PST_MasterTextPropAtom : public PST_Base
{
public:
    PST_MasterTextPropAtom(const QByteArray& srcData, const ST_Variable& var);
    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_MASTERTEXTPROPATOM_H
