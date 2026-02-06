#ifndef PST_CLIENTTEXTBOX_H
#define PST_CLIENTTEXTBOX_H

#include "pst_base.h"

class PST_TextHeaderAtom;
class PST_TextCharsAtom;
class PST_MasterTextPropAtom;
class PST_TextSpecialInfoAtom;
class PST_StyleTextPropAtom;
class PST_GenericDateMetaCharAtom;
class PST_TextRulerAtom;
class PST_SlideNumberMetaCharAtom;
class PST_ClientTextBox : public PST_Base
{
public:
    PST_ClientTextBox(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QSharedPointer<PST_TextHeaderAtom> txtHeaderAtom;
    QSharedPointer<PST_TextCharsAtom> txtCharsAtom;
    QSharedPointer<PST_MasterTextPropAtom> masterTextPropAtom;
    QSharedPointer<PST_TextSpecialInfoAtom> txtSpecialInfoAtom;
    QSharedPointer<PST_StyleTextPropAtom> styleTextPropAtom;
    QSharedPointer<PST_GenericDateMetaCharAtom> genericDateMetaCharAtom;
    QSharedPointer<PST_TextRulerAtom> txtRulerAtom;
    QSharedPointer<PST_SlideNumberMetaCharAtom> slideNumMCAtom;

};

#endif // PST_CLIENTTEXTBOX_H
