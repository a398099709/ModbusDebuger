#ifndef HEX_THREAD_H
#define HEX_THREAD_H
#include <QThread>
#include <QString>
#include "hex_data_struct.h"
#include "file_deal.h"
class hex_thread:public QThread
{
    Q_OBJECT
public:
    explicit hex_thread(QObject* parent  = 0);
    ~hex_thread();
    void set_path(QString path);
    QThread workerThread;
protected :
        QString m_file_path;
        hex_data_struct m_hex_data;

public slots:
        void sig_startThread(void);
signals:
        void sig_deal(QString path);
};

#endif // HEX_THREAD_H
