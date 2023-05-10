#include "hex_thread.h"
#include <QDebug>
#include <QFile>
hex_thread::hex_thread(QObject *parent) :QThread(parent)
{
     file_deal *do_file_deal = new file_deal;
     do_file_deal->moveToThread(&workerThread);
     connect(&workerThread, &QThread::finished, do_file_deal, &QObject::deleteLater);
     connect(this, &hex_thread::sig_deal, do_file_deal, &file_deal::file_deal_data);
     //connect(do_file_deal, &file_deal::resultReady, this, &hex_thread::handleResults);
     
}
hex_thread::~hex_thread()
{

}
// void hex_thread::run()
// {
//     qDebug()<<"hex thread"<<m_file_path;
//     QFile hexfile(m_file_path);

//     if(hexfile.open(QIODevice::ReadOnly))
//     {
//          qDebug()<<"file open true";
//          while(!hexfile.atEnd())
//          {
//              QByteArray array = QByteArray::fromHex(hexfile.readLine());//从hex文件中读取一行
//              ReadHexLineData(&m_hex_data,array);//将一行数据解读到HexDataStr结构体
//              HexToBin(&m_hex_data);//,out);//将解读后的数据写入bin文件
//          }
//          hexfile.close();//关闭文件
//     }

// }
void hex_thread::set_path(QString path)
{
    m_file_path = path;
}
// void hex_thread::sig_deal(QString path)
// {
//     ;
// }
void hex_thread::sig_startThread(void)
{
    workerThread.start();
}