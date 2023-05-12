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
        void sig_startThread(void);

public slots:
        
signals:
        void sig_deal_path(QString path);
        void sig_deal_file(void);
};

#endif // HEX_THREAD_H
