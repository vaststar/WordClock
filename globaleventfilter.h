#ifndef GLOBALEVENTFILTER_H
#define GLOBALEVENTFILTER_H

#include <QObject>
#include <QAbstractNativeEventFilter>

class GlobalEventFilter : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit GlobalEventFilter(QObject *parent = nullptr);
public:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result)override;
public:
    void startFilter();
    void stopFilter();
private:
    void InitTimer();
signals:
    void LesuireTime(int);
private:
    class DataPrivate;
    DataPrivate *_p;
};

#endif // GLOBALEVENTFILTER_H
