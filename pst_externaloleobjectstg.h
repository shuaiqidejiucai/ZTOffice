#ifndef PST_EXTERNALOLEOBJECTSTG_H
#define PST_EXTERNALOLEOBJECTSTG_H

#include "pst_base.h"

class PST_ExternaloleObjectStg : public PST_Base
{
public:
    PST_ExternaloleObjectStg(const QByteArray& srcData, const ST_Variable& var);
};

#endif // PST_EXTERNALOLEOBJECTSTG_H
