#ifndef PST_EXTERNALOLEOBJECTSTGATOM_H
#define PST_EXTERNALOLEOBJECTSTGATOM_H

#include "pst_base.h"

class PST_ExternalOleObjectStgAtom : public PST_Base
{
public:
    PST_ExternalOleObjectStgAtom(const QByteArray& srcData, const ST_Variable& var);

};

#endif // PST_EXTERNALOLEOBJECTSTGATOM_H
