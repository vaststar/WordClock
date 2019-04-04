#ifndef CLOCKVIEW_H
#define CLOCKVIEW_H

#include <QGraphicsView>

class clockView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit clockView(QWidget *parent = nullptr);
    ~clockView();
private slots:
    void updateTime();
private:
    void initScene();
    void initClock();
private:
    class DataPrivate;
    DataPrivate *_p;
};

#endif // CLOCKVIEW_H
