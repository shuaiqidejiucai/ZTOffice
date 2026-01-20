#ifndef PST_CSTRING_H
#define PST_CSTRING_H

#include "pst_base.h"

class PST_CString : public PST_Base
{
public:
    PST_CString(const QByteArray& srcData);
};

#endif // PST_CSTRING_H
