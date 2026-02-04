#ifndef PST_CLIENTTEXTBOX_H
#define PST_CLIENTTEXTBOX_H

#include "pst_base.h"
#include "pst_textheaderatom.h"
#include "pst_textcharsatom.h"
#include "pst_textspecialinfoatom.h"
#include "pst_textruleratom.h"
#include "pst_slidenumbermetacharatom.h"
#include "pst_mastertextpropatom.h"
#include "pst_styletextpropatom.h"
#include "pst_genericdatemetacharatom.h"
class PST_ClientTextBox : public PST_Base
{
public:
    PST_ClientTextBox(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr)override;
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
