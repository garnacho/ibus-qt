#ifndef __Q_IBUS_COMPONENT_H_
#define __Q_IBUS_COMPONENT_H_

#include <QFile>
#include <QDebug>
#include <QVector>
#include <QProcess>
#include <QXmlStreamWriter>
#include <QtXml/QDomNode>
#include "qibusserializable.h"
#include "qibusenginedesc.h"
#include "qibusobservedpath.h"

namespace IBus {

class Component;
typedef Pointer<Component> ComponentPointer;

class Component : public Serializable
{
    Q_OBJECT;

public:
    Component () {}
    Component (QString name,
               QString desc,
               QString vers,
               QString lics,
               QString auth,
               QString hmpg,
               QString exec,
               QString textdomain
               ):
               m_name(name),
               m_description(desc),
               m_version(vers),
               m_license(lics),
               m_author(auth),
               m_homepage(hmpg),
               m_exec(exec),
               m_textdomain(textdomain)
    {}

    virtual ~Component ()
    {}

public:
    virtual bool serialize (QDBusArgument &argument) const;
    virtual bool deserialize (const QDBusArgument &argument);

    void output (QString & output) const;
    bool parseXmlNode (const QDomNode & node);
    bool parseEngines (QDomNode node);
    bool parseObservedPaths (const QDomNode & node);

    const ComponentPointer newComponentFromFile (const QString & filename) const;

    void addObservedPath (const QString & filename);
    void addEngine (const EngineDescPointer edp);

    QVector<ObservedPathPointer> getObservedPathVec () const;
    const QVector<EngineDescPointer> & getEnginesVec () const;

    bool start (bool verbose) const;
    bool stop () const;
    bool isRunning () const;
    bool isComponentModified () const;
    const ComponentPointer getComponentFromEngine (EngineDescPointer edp) const;

private:
    const QDomDocument * parseXmlFile (const QString & filename) const;

private:
    QString m_name;
    QString m_description;
    QString m_version;
    QString m_license;
    QString m_author;
    QString m_homepage;
    QString m_exec;
    QString m_textdomain;

    QVector<ObservedPathPointer>    m_observedPaths;
    QVector<EngineDescPointer>      m_engines;

    uint    m_pid;

    IBUS_SERIALIZABLE
};

};

#endif
