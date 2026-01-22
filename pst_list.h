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

    QList<QSharedPointer<PST_NormalViewSetInfo> > normalViewSetInfo;
    QList<QSharedPointer<PST_NotesTextViewInfo> > notesTxtViewInfo;
    QList<QSharedPointer<PST_SlideViewInfo> > slideViewInfo;
    QList<QSharedPointer<PST_ProgTags> > progTags;
};

#endif // PST_LIST_H
