#ifndef PST_EXTERNALOBJECTLISTATOM_H
#define PST_EXTERNALOBJECTLISTATOM_H
#include "pst_base.h"
class PST_ExternalObjectListAtom : public PST_Base
{
public:
    PST_ExternalObjectListAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser();
};

#endif // PST_EXTERNALOBJECTLISTATOM_H
