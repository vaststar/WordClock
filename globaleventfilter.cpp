#include "globaleventfilter.h"

#include <atomic>
#include <thread>
#include <Windows.h>
#include <QTimer>
#include <QDebug>

static std::atomic<int> lesuireTime(0);
class GlobalEventFilter::DataPrivate
{
public:
    DataPrivate()
        :timer(nullptr)
        ,alreadyInstalled(false)
    {

    }
public:
    QTimer *timer;
    HHOOK mousehook;
    HHOOK keyhook;
    bool alreadyInstalled;
};

GlobalEventFilter::GlobalEventFilter(QObject *parent)
    : QObject(parent)
    ,_p(new DataPrivate())
{
    InitTimer();
}

bool GlobalEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
    {
        MSG * pMsg = reinterpret_cast<MSG *>(message);

        if (pMsg->message == WM_KEYDOWN)
        {
            lesuireTime.fetch_and(0);
        }
    }
    return false;
}

LRESULT CALLBACK mymouse(int nCode, WPARAM wParam, LPARAM lParam)
{
    lesuireTime.fetch_and(0);
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
void GlobalEventFilter::startFilter()
{
    if(_p->alreadyInstalled) return;
    _p->mousehook  = SetWindowsHookEx(WH_MOUSE_LL, mymouse, 0, 0);
    _p->keyhook    = SetWindowsHookEx(WH_KEYBOARD_LL, mymouse, 0, 0);
    _p->alreadyInstalled = true;
    _p->timer->start(1000);
}

void GlobalEventFilter::stopFilter()
{
    if(!_p->alreadyInstalled) return;
    UnhookWindowsHookEx(_p->mousehook);
    UnhookWindowsHookEx(_p->keyhook);
    _p->alreadyInstalled = false;
    _p->timer->stop();
}

void GlobalEventFilter::InitTimer()
{
    _p->timer = new QTimer(this);
    connect(_p->timer,&QTimer::timeout,[this](){
        emit LesuireTime(lesuireTime.fetch_add(1));
    });
}
