#ifndef PST_CLIENTTEXTBOX_H
#define PST_CLIENTTEXTBOX_H

#include "pst_base.h"
#include "pst_textheaderatom.h"
#include "pst_textcharsatom.h"
#include "pst_textspecialinfoatom.h"
#include "pst_textruleratom.h"
#include "pst_slidenumbermetacharatom.h"

class PST_ClientTextBox : public PST_Base
{
public:
    PST_ClientTextBox(const QByteArray& srcData);

    PST_TextHeaderAtom txtHeaderAtom;
    PST_TextCharsAtom txtCharsAtom;
    PST_TextSpecialInfoAtom txtSpecialInfoAtom;
    PST_TextRulerAtom txtRulerAtom;
    PST_SlideNumberMetaCharAtom slideNumMCAtom;

};

#endif // PST_CLIENTTEXTBOX_H
