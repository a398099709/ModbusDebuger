#include "file_deal.h"

file_deal::file_deal(QObject *parent) : QObject(parent)
{

}
 void file_deal::file_deal_data(void)
 {
     //qDebug()<<"hex thread"<<m_file_path;
    qDebug()<<"FileExist:"<<FileExist;
    if(FileExist)
    {
         qDebug()<<"file open true";
         while(!hexfile.atEnd())
         {
             qDebug()<<"file loop deal";
             QByteArray array = QByteArray::fromHex(hexfile.readLine());//从hex文件中读取一行
             m_data_struct.ReadHexLineData(&m_hex_data,array);//将一行数据解读到HexDataStr结构体
             m_data_struct.HexToBin(&m_hex_data);//,out);//将解读后的数据写入bin文件
         }
         hexfile.close();//关闭文件
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
