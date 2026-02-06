#ifndef PST_LIST_H
#define PST_LIST_H

#include "pst_base.h"

class PST_NormalViewSetInfo;
class PST_NotesTextViewInfo;
class PST_SlideViewInfo;
class PST_ProgTags;
class PST_List : public PST_Base
{
public:
    PST_List(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QList<QSharedPointer<PST_NormalViewSetInfo> > normalViewSetInfoList;
    QList<QSharedPointer<PST_NotesTextViewInfo> > notesTxtViewInfoList;
    QList<QSharedPointer<PST_SlideViewInfo> > slideViewInfoList;
    QList<QSharedPointer<PST_ProgTags> > progTagsList;
};

#endif // PST_LIST_H
