#ifndef DATASRECEIVETHREAD_H
#define DATASRECEIVETHREAD_H
#include <QThread>
#include "hex_data_struct.h"
class AbstractModbusDevice;
class DataBuffer;
class DatasReceiveThread : public QThread
{
    Q_OBJECT
public:
    explicit DatasReceiveThread(QObject *parent = 0);
    ~DatasReceiveThread();

    void setModbusDevice(AbstractModbusDevice* pDevice);
    void setDataBuffer(DataBuffer *pBuf);

protected:
    void run();
private:
    char* m_buf;
    int n_maxSize;
    AbstractModbusDevice* m_pModbusDevice;
    //定义数据缓存区实例指针
    DataBuffer *m_pDataBuf;
    hex_data_struct m_hex_data;

public:
    bool m_bRunning;
    int m_nTimeoutMS;
};


#endif // DATASRECEIVETHREAD_H
