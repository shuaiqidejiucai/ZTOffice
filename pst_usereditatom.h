#ifndef PST_USEREDITATOM_H
#define PST_USEREDITATOM_H

#include "pst_base.h"

class PST_UserEditAtom : public PST_Base
{
public:
    PST_UserEditAtom(const QByteArray& srcData, const ST_Variable& var);
};

#endif // PST_USEREDITATOM_H
