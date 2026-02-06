#include "powerpointbinarydocument.h"
#include "pstsearch.h"
#include "pst_currentuseratom.h"
#include "pst_usereditatom.h"
#include "pst_persistdirectoryatom.h"
#include "pst_document.h"
#include "pst_mainmaster.h"
#include "pst_notes.h"
#include "pst_handout.h"
#include "pst_slide.h"
#include "pst_externaloleobjectstg.h"
PowerPointBinaryDocument::PowerPointBinaryDocument(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData,var)
{

}

int PowerPointBinaryDocument::parser(PSTSearch* pSearchPtr)
{
    ST_Variable stVar;
    quint32 pos = ST_SP(stVar);
    do
    {
        if (!physicalStruct(pos, m_srcData, stVar))
        {
            return Error_FailedType;
        }
        switch (ST_TP(stVar))
        {
        case RT_UserEditAtom:
        {
            userEditAtomPtr = QSharedPointer<PST_UserEditAtom>::create(m_srcData, stVar);
            addChildNodePtr(userEditAtomPtr);
            if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, userEditAtomPtr);
        }
        break;
        case RT_PersistDirectoryAtom:
        {
            persistDirectoryAtomPtr = QSharedPointer<PST_PersistDirectoryAtom>::create(m_srcData, stVar);
            addChildNodePtr(persistDirectoryAtomPtr);
            if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, persistDirectoryAtomPtr);
        }
        break;
        case RT_Document:
        {
            documentPtr = QSharedPointer<PST_Document>::create(m_srcData, stVar);
            addChildNodePtr(documentPtr);
            if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, documentPtr);
        }
        break;
        case RT_MainMaster:
        {
            QSharedPointer<PST_MainMaster> mainMasterPtr(new PST_MainMaster(m_srcData, stVar));
            mainMasterList.append(mainMasterPtr);
            addChildNodePtr(mainMasterPtr);
            if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, mainMasterPtr);
        }
        break;
        case RT_Notes:
        {
            QSharedPointer<PST_Notes> notesPtr(new PST_Notes(m_srcData, stVar));
            notesList.append(notesPtr);
            addChildNodePtr(notesPtr);
            if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, notesPtr);
        }
        break;
        case RT_Handout:
        {
            QSharedPointer<PST_Handout> handoutPtr(new PST_Handout(m_srcData, stVar));
            handoutList.append(handoutPtr);
            addChildNodePtr(handoutPtr);
            if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, handoutPtr);
        }
        break;
        case RT_Slide:
        {
            QSharedPointer<PST_Slide> slidePtr(new PST_Slide(m_srcData, stVar));
            slideList.append(slidePtr);
            addChildNodePtr(slidePtr);
            if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, slidePtr);
        }
        break;
        case RT_ExternalOleObjectStg:
        {
            QSharedPointer<PST_ExternaloleObjectStg> exOleObjPtr(new PST_ExternaloleObjectStg(m_srcData, stVar));
            exOleObjStringList.append(exOleObjPtr);
            addChildNodePtr(exOleObjPtr);
            if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, exOleObjPtr);
        }
        break;
        default:
            break;
        }
        pos = ST_EP(stVar);
    } while (pos < ST_EP(stVar));
	return Error_SuccessType;
}

void PowerPointBinaryDocument::clearParserData()
{
    currentUserAtom.clear();
    userEditAtomPtr.clear();
    persistDirectoryAtomPtr.clear();
    documentPtr.clear();
    mainMasterList.clear();
    notesList.clear();
    handoutList.clear();
    slideList.clear();
    exOleObjStringList.clear();
}

int PowerPointBinaryDocument::priority()
{
    return 0;
}
