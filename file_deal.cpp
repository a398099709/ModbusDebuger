#include "file_deal.h"
#include <QTimer>
file_deal::file_deal(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this) ;
    connect(timer, SIGNAL(timeout()), this, SLOT(solt_read_file()));
    
}
 void file_deal::file_deal_data(void)
 {
     //qDebug()<<"hex thread"<<m_file_path;
    qDebug()<<"FileExist:"<<FileExist;
    if(FileExist)
    {
        qDebug()<<"file open true";
        timer->start(100);
        //  while(!hexfile.atEnd())
        //  {
        //     if(m_file_read)
        //     {
        //         qDebug()<<"file loop deal";
        //         QByteArray array = QByteArray::fromHex(hexfile.readLine());//从hex文件中读取一行
        //         m_data_struct.ReadHexLineData(&m_hex_data,array);//将一行数据解读到HexDataStr结构体
        //         m_data_struct.HexToBin(&m_hex_data);//,out);//将解读后的数据写入bin文件

        //         m_file_read=0;
        //     }
        //     else
        //     {
        //         //qDebug()<<"file loop error";
        //         return;
        //     }
        //     //QThread::msleep(100);

        //  }
        //  hexfile.close();//关闭文件
        // qDebug()<<"file read finish";
    }
    ;
 }

void file_deal::get_open_file_path(QString path)
{
    m_file_path  = path;
    qDebug()<<"file_deal_data_path"<<m_file_path;
    hexfile.setFileName(m_file_path);
    //QFile(m_file_path);
    if(hexfile.open(QIODevice::ReadOnly))
    {
        FileExist=1;
    }
    else
    {
        FileExist=0;
    }
}
void file_deal::solt_read_file(void)
{
     qDebug()<<"timer solt";
        m_file_read=1;
        if(!hexfile.atEnd())
         {
            if(m_file_read)
            {
                qDebug()<<"file loop deal";
                QByteArray array = QByteArray::fromHex(hexfile.readLine());//从hex文件中读取一行
                m_data_struct.ReadHexLineData(&m_hex_data,array);//将一行数据解读到HexDataStr结构体
                m_data_struct.HexToBin(&m_hex_data);//,out);//将解读后的数据写入bin文件

                m_file_read=0;
            }
            else
            {
                //qDebug()<<"file loop error";
                return;
            }
            //QThread::msleep(100);

         }
         else
         {
            hexfile.close();//关闭文件
            qDebug()<<"file read finish";
         }
         
}
