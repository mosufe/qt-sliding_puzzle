#include "resources.h"

DigitalTimer::DigitalTimer(uint digits): QLCDNumber(digits)
{
    setSegmentStyle(Filled);

    this->time = QTime(0,0,0,0);
    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalTimer::showTime);
    this->timer->start(1000);
    showTime();
}

void DigitalTimer::showTime()
{
    time = time.addSecs(1);
    QString text = time.toString("mm:ss");
    display(text);
}

void DigitalTimer::stopTimer(){
    timer->stop();
    emit getTime(this->time);
}

QTime DigitalTimer::getFinalTime(){
    return this->time;
}
