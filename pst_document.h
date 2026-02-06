#ifndef PST_DOCUMENT_H
#define PST_DOCUMENT_H

#include "pst_base.h"

class PST_DocumentAtom;
class PST_ExObjList;
class PST_Environment;
class PST_PPDrawingGroup;
class PST_SlideListWithText;
class PST_List;
class PST_HeadersFooters;
class PST_RoundTripCustomTableStyles12;
class PST_EndDocumentAtom;

class PST_Document : public PST_Base
{
public:
    PST_Document(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QSharedPointer<PST_DocumentAtom> documentAtomPtr;
    QList<QSharedPointer<PST_ExObjList> > exObjListObjList;
    QList<QSharedPointer<PST_Environment> > envmentList;
    QList<QSharedPointer<PST_PPDrawingGroup> > ppdwGroupList;
    QList<QSharedPointer<PST_SlideListWithText> > slideListWithTxtList;
    QList<QSharedPointer<PST_List> > PSTList;
    QList<QSharedPointer<PST_HeadersFooters> > headersFootersList;
    QList<QSharedPointer<PST_RoundTripCustomTableStyles12> > roundTripTableStyleList;
    QSharedPointer<PST_EndDocumentAtom> endDocumentAtom;
};

#endif // PST_DOCUMENT_H
