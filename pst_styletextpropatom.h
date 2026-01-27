#ifndef PST_STYLETEXTPROPATOM_H
#define PST_STYLETEXTPROPATOM_H

#include "pst_base.h"

class PST_StyleTextPropAtom : public PST_Base
{
public:
    PST_StyleTextPropAtom(const QByteArray& srcData, const ST_Variable& var);
};

#endif // PST_STYLETEXTPROPATOM_H
