#ifndef HEX_DATA_STRUCT_H
#define HEX_DATA_STRUCT_H

#include <QObject>
#include <QDebug>
class hex_data_struct : public QObject
{
    Q_OBJECT
public:
    typedef struct
    {
        unsigned char datalen;//数据字节
        unsigned short addr;//地址域
        unsigned char datatype;//类型
        unsigned char databuf[16];//数据记录
        unsigned char checkout;//校验和
    }HexFormatForLine ;

public:
    explicit hex_data_struct(QObject *parent = nullptr);
    char hex_data_struct::HexToBin(HexFormatForLine* ba);
    bool hex_data_struct::ReadHexLineData(HexFormatForLine* out,const QByteArray & ba);
protected:
       HexFormatForLine m_hex_data_struct;
signals:

};

#endif // HEX_DATA_STRUCT_H
