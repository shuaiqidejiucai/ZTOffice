#ifndef PST_PROGTAGS_H
#define PST_PROGTAGS_H

#include "pst_base.h"
#include "pst_progbinarytag.h"

class PST_ProgTags : public PST_Base
{
public:
    PST_ProgTags(const QByteArray& srcData);

    QList<PST_ProgBinaryTag> progBinTagList;
};

#endif // PST_PROGTAGS_H
