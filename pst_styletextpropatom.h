#ifndef PST_STYLETEXTPROPATOM_H
#define PST_STYLETEXTPROPATOM_H

#include "pst_base.h"

class PST_StyleTextPropAtom : public PST_Base
{
public:
    PST_StyleTextPropAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser() override;
    virtual void clearParserData()override;
};

#endif // PST_STYLETEXTPROPATOM_H
