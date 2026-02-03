#include "pst_clienttextbox.h"

PST_ClientTextBox::PST_ClientTextBox(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_ClientTextBox::parser()
{
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return Error_FailedType;
		}
		switch (ST_TP(stVar))
		{
		case RT_TextHeaderAtom:
		{
			txtHeaderAtom = QSharedPointer<PST_TextHeaderAtom>::create(m_srcData, stVar);
			addChildNodePtr(txtHeaderAtom);
		}
		break;
		case RT_TextCharsAtom:
		{
			txtCharsAtom = QSharedPointer<PST_TextCharsAtom>::create(m_srcData, stVar);
			addChildNodePtr(txtCharsAtom);
		}
			break;
		case RT_MasterTextPropAtom:
		{
			masterTextPropAtom = QSharedPointer<PST_MasterTextPropAtom>::create(m_srcData, stVar);
			addChildNodePtr(masterTextPropAtom);
		}
			break;
		case RT_TextSpecialInfoAtom:
		{
			txtSpecialInfoAtom = QSharedPointer<PST_TextSpecialInfoAtom>::create(m_srcData, stVar);
			addChildNodePtr(txtSpecialInfoAtom);
		}
			break;
		case RT_StyleTextPropAtom:
		{
			styleTextPropAtom = QSharedPointer<PST_StyleTextPropAtom>::create(m_srcData, stVar);
			addChildNodePtr(styleTextPropAtom);
		}
		break;
		case RT_GenericDateMetaCharAtom:
		{
			genericDateMetaCharAtom = QSharedPointer<PST_GenericDateMetaCharAtom>::create(m_srcData, stVar);
			addChildNodePtr(genericDateMetaCharAtom);
		}
			break;
		case RT_TextRulerAtom:
		{
			txtRulerAtom = QSharedPointer<PST_TextRulerAtom>::create(m_srcData, stVar);
			addChildNodePtr(txtRulerAtom);
		}
			break;
		case RT_SlideNumberMetaCharAtom:
		{
			slideNumMCAtom = QSharedPointer<PST_SlideNumberMetaCharAtom>::create(m_srcData, stVar);
			addChildNodePtr(slideNumMCAtom);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_ClientTextBox::clearParserData()
{
	txtHeaderAtom.clear();
	txtCharsAtom.clear();
	masterTextPropAtom.clear();
	txtSpecialInfoAtom.clear();
	styleTextPropAtom.clear();
	genericDateMetaCharAtom.clear();
	txtRulerAtom.clear();
	slideNumMCAtom.clear();
}

int PST_ClientTextBox::priority()
{
	return 0;
}
