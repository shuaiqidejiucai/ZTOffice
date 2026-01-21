#ifndef PST_LIST_H
#define PST_LIST_H

#include "pst_base.h"
#include "pst_normalviewsetinfo.h"
#include "pst_notestextviewinfo.h"
#include "pst_slideviewinfo.h"
#include "pst_progtags.h"

class PST_List : public PST_Base
{
public:
    PST_List(const QByteArray& srcData);

    QList<PST_NormalViewSetInfo> normalViewSetInfo;
    QList<PST_NotesTextViewInfo> notesTxtViewInfo;
    QList<PST_SlideViewInfo> slideViewInfo;
    QList<PST_ProgTags> progTags;
};

#endif // PST_LIST_H
