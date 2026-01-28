#include "powerpointbinarydocument.h"

PowerPointBinaryDocument::PowerPointBinaryDocument(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PowerPointBinaryDocument::parser()
{
    m_isParser = true;
    ST_Variable stVar;
    quint32 pos = ST_SP(stVar);
    do
    {
        if (!physicalStruct(pos, m_srcData, stVar))
        {
            return -1;
        }
        switch (ST_TP(stVar))
        {
        case RT_UserEditAtom:
        {
            userEditAtomPtr = QSharedPointer<PST_UserEditAtom>::create(m_srcData, stVar);
        }
        break;
        case RT_PersistDirectoryAtom:
        {
            persistDirectoryAtomPtr = QSharedPointer<PST_PersistDirectoryAtom>::create(m_srcData, stVar);
        }
        break;
        case RT_Document:
        {
            documentPtr = QSharedPointer<PST_Document>::create(m_srcData, stVar);
        }
        break;
        case RT_MainMaster:
        {
            QSharedPointer<PST_MainMaster> mainMasterPtr(new PST_MainMaster(m_srcData, stVar));
            mainMasterList.append(mainMasterPtr);
        }
        break;
        case RT_Notes:
        {
            QSharedPointer<PST_Notes> notesPtr(new PST_Notes(m_srcData, stVar));
            notesList.append(notesPtr);
        }
        break;
        case RT_Handout:
        {
            QSharedPointer<PST_Handout> handoutPtr(new PST_Handout(m_srcData, stVar));
            handoutList.append(handoutPtr);
        }
        break;
        case RT_Slide:
        {
            QSharedPointer<PST_Slide> slidePtr(new PST_Slide(m_srcData, stVar));
            slideList.append(slidePtr);
        }
        break;
        case RT_ExternalOleObjectStg:
        {
            QSharedPointer<PST_ExternaloleObjectStg> exOleObjPtr(new PST_ExternaloleObjectStg(m_srcData, stVar));
            exOleObjStringList.append(exOleObjPtr);
        }
        break;
        }
        pos = ST_EP(stVar);
    } while (pos < ST_EP(stVar));
	return 0;
}
