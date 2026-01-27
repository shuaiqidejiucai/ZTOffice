#ifndef PST_EXTERNALOBJECTREFATOM_H
#define PST_EXTERNALOBJECTREFATOM_H

#include "pst_base.h"

class PST_ExternalObjectRefAtom : public PST_Base
{
public:
    PST_ExternalObjectRefAtom(const QByteArray& srcData, const ST_Variable& var);


};

#endif // PST_EXTERNALOBJECTREFATOM_H
