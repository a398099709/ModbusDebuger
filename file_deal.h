#ifndef FILE_DEAL_H
#define FILE_DEAL_H
#include <QObject>
#include <QDebug>
#include <QFile>
#include "hex_data_struct.h"
class file_deal : public QObject //,public hex_data_struct
{
    Q_OBJECT
public:
    explicit file_deal(QObject *parent = nullptr);
    QFile hexfile;
signals:
public slots:
    void solt_read_file(void);
    void file_deal_data(void);
    void get_open_file_path(QString path);
private :
    QString m_file_path;
    char Data[8];
    //hex_data_struct file_hex_data;
    bool FileExist;
    bool m_file_read;
    hex_data_struct::HexFormatForLine m_hex_data;
    hex_data_struct m_data_struct;
    //hex_data_struct::
};

#endif // FILE_DEAL_H
