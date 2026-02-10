#ifndef PST_BASE_H
#define PST_BASE_H
#include "global.h"
#include "zttools.h"
class PSTSearch;
class PSTParser_EXPORT PST_Base : public QEnableSharedFromThis<PST_Base>
{
public:
    PST_Base(const QByteArray& srcData, const ST_Variable& var, PSTSearch * pSeachptr = nullptr);

    int parserData(PSTSearch* pSeachptr = nullptr);

    void clearData();

    virtual bool addChildNodePtr(const QSharedPointer<PST_Base>& childPtr);

    virtual void clearTreeData();
protected:
    virtual int parser(PSTSearch* pSeachptr) = 0;

    virtual int priority() = 0;//”≈œ»º∂

    virtual void clearParserData() = 0;

protected:
    const ST_Variable m_STVar;
    const QByteArray& m_srcData;
    bool m_isParser;
private:
    QWeakPointer<PST_Base> m_parentWeakPtr;
    QList<QWeakPointer<PST_Base> > m_childNodeWeakPtrList;
};

#endif // PST_BASE_H
