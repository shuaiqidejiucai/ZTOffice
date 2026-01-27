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
    PST_List(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser() override;

    QList<QSharedPointer<PST_NormalViewSetInfo> > normalViewSetInfoList;
    QList<QSharedPointer<PST_NotesTextViewInfo> > notesTxtViewInfoList;
    QList<QSharedPointer<PST_SlideViewInfo> > slideViewInfoList;
    QList<QSharedPointer<PST_ProgTags> > progTagsList;
};

#endif // PST_LIST_H
