#include "hex_data_struct.h"

hex_data_struct::hex_data_struct(QObject *parent) : QObject(parent)
{

}

//读取一行数据然后解析成结构体
bool hex_data_struct::ReadHexLineData(HexFormatForLine* out,const QByteArray & ba)//false: 校验错误 true：校验成功
{
    unsigned char i,checkoutCal=0;


      //计算校验值
       for(i=0;i < ba.size()-1;i++){
          checkoutCal += (unsigned char)ba.at(i);
       }
       checkoutCal = 0x100-checkoutCal;
       //获取个部分域的值
       out->datalen =(unsigned char)ba.at(0);
       out->addr = ((unsigned char)ba.at(1)<<8)|(unsigned char)ba.at(2);
       out->datatype = (unsigned char)ba.at(3);
       memset(out->databuf,0,sizeof(out->databuf));
       for(i = 0;i<out->datalen;i++){
          out->databuf[i] = (unsigned char)ba.at(4+i);
       }
       out->checkout = (unsigned char)ba.at(4+i);
  #if  0 //调试时打开
       qDebug("datalen=%X",out->datalen);
       qDebug("addr=%X",out->addr);
       qDebug("datatype=%X",out->datatype);
       qDebug("checkout=%X",out->checkout);
       qDebug("checkoutCal=%X",checkoutCal);
  #endif
      //比较读取的校验值和计算的校验值是否一致
      if(checkoutCal == out->checkout){
          return true;
      }
      return false;
 }

#if 1
//假设stm32 使用hex转bin文件只使用了hex数据  因为hex是带地址 bin不带 纯二进制
char hex_data_struct::HexToBin(HexFormatForLine* ba)//,QDataStream & out)//return 0: ok  1:hex文件结束 2：hex文件有误
{
    static unsigned int ExStageAddr = 0x00;//扩展段地址
    static unsigned int ExLineAddr = 0x00;//扩展线性地址
    static unsigned int absoluteAddrLocal = 0x00;//本地记录绝对地址
    unsigned int absoluteAddrCurrent = 0x00;//计算当前记录的绝对地址
    unsigned int Bytesskipped = 0;//被跳过的字节数
    char i=0;
   // qDebug()<<"你好";
    switch(ba->datatype)
    {
        for(i=0;i<ba->datalen;i++)
        {
             qDebug()<<ba->databuf[i];
        }
        qDebug()<<"data";
    }
    return 0;
}

#else

//假设stm32 使用hex转bin文件只使用了hex数据  因为hex是带地址 bin不带 纯二进制
char hex_data_struct::HexToBin(HexFormatForLine* ba)//,QDataStream & out)//return 0: ok  1:hex文件结束 2：hex文件有误
{
    static unsigned int ExStageAddr = 0x00;//扩展段地址
    static unsigned int ExLineAddr = 0x00;//扩展线性地址
    static unsigned int absoluteAddrLocal = 0x00;//本地记录绝对地址
    unsigned int absoluteAddrCurrent = 0x00;//计算当前记录的绝对地址
    unsigned int Bytesskipped = 0;//被跳过的字节数
   // qDebug()<<"你好";
    switch(ba->datatype)
    {
        case 0x00://数据记录
                        //计算出当前记录的绝对地址
            if(ExStageAddr != 0)
            {
                absoluteAddrCurrent = (ba->addr+ExStageAddr);
                if(ba->datalen>8)
                {
                    for(int i=0;i<8;i++)
                    {
                        psend.Data[i] = ba->databuf[i];

                    }
                 psend.ID=0x18ffff01;
                 psend.DataLen=8;
                 psend.SendType=0;
                   // psend.TimeFlag
                   // psend.TimeStamp
                 psend.ExternFlag=1;
                 psend.RemoteFlag=0;
              //  Transmit(nDeviceType,nDeviceInd,nCANInd,&psend,8);
           //     printf("%x",psend.Data);
                  //  qDebug()<<("%x",psend.Data[0]);
                }
                 QThread::msleep(10);
                if((8<ba->datalen)&&(ba->datalen<=16))
                {
                    for(int i=8;i<ba->datalen;i++)
                    {
                        psend.Data[i] = ba->databuf[i];

                    }
                    psend.ID=0x18ffff02;
                    psend.DataLen=ba->datalen-8;
                    psend.SendType=0;
                   // psend.TimeFlag
                   // psend.TimeStamp
                    psend.ExternFlag=1;
                    psend.RemoteFlag=0;
                  //  Transmit(nDeviceType,nDeviceInd,nCANInd,&psend,8);
                }
                 QThread::msleep(5);
                if(ba->datalen<=8)
                {
                    for(int i=0;i<8;i++)
                    {
                        psend.Data[i] = ba->databuf[i];

                    }
                     psend.ID=0x18ffff03;
                     psend.DataLen=ba->datalen;
                     psend.SendType=0;
                    // psend.TimeFlag
                    // psend.TimeStamp
                     psend.ExternFlag=1;
                     psend.RemoteFlag=0;
                 //    Transmit(nDeviceType,nDeviceInd,nCANInd,&psend,8);
                  //  qDebug()<<("%x",psend.Data[0]);

                }

            }



            else if(ExLineAddr != 0)
            {
                absoluteAddrCurrent = (ba->addr|ExLineAddr);
                absoluteAddrCurrent = (ba->addr+ExStageAddr);

               // psend.ID=0x021a2b3c;
                if(ba->datalen>8)
                {
                    for(int i=0;i<8;i++)
                    {
                        psend.Data[i] = ba->databuf[i];

                    }
                 psend.ID=0x18ffff01;
                 psend.DataLen=8;
                 psend.SendType=0;
                   // psend.TimeFlag
                   // psend.TimeStamp
                 psend.ExternFlag=1;
                 psend.RemoteFlag=0;
              dw =Transmit(nDeviceType,nDeviceInd,nCANInd,&psend,psend.DataLen);
                QThread::msleep(5);
              //  qDebug()<<dw;
                cnt=cnt+ba->datalen;

               // cnt++;

              //  printf("%x",psend.Data[0]);
                  //  qDebug()<<("%x",psend.Data[0]);
                }

                if(8<ba->datalen&&ba->datalen<=16)
                {
                    int t=0;
                    for(int i=8;i<ba->datalen;i++)
                    {

                        psend.Data[t] = ba->databuf[i];
                        t++;
                    }
                    psend.ID=0x18ffff01;
                    psend.DataLen=ba->datalen-8;
                    psend.SendType=0;
                   // psend.TimeFlag
                   // psend.TimeStamp
                    psend.ExternFlag=1;
                    psend.RemoteFlag=0;
                    dw = Transmit(nDeviceType,nDeviceInd,nCANInd,&psend,psend.DataLen);
                 //   qDebug()<<dw;
                //    cnt=cnt+ba->datalen;
                  //  cnt++;
                }
                QThread::msleep(5);
                if(ba->datalen<=8)
                {
                    for(int i=0;i<ba->datalen;i++)
                    {
                        psend.Data[i] = ba->databuf[i];

                    }
                     psend.ID=0x18ffff01;
                     psend.DataLen=ba->datalen;
                     psend.SendType=0;
                    // psend.TimeFlag
                    // psend.TimeStamp
                     psend.ExternFlag=1;
                     psend.RemoteFlag=0;
                     dw = Transmit(nDeviceType,nDeviceInd,nCANInd,&psend, psend.DataLen);
                  //   qDebug()<<dw;
                     cnt=cnt+ba->datalen;
                  //   cnt++;

                  //  qDebug()<<("%x",psend.Data[0]);
                    QThread::msleep(5);
                }

            }else
            {
                absoluteAddrCurrent = ba->addr;
            }
            //hex文件第一条数据记录时，将本地绝对地址absoluteAddrLocal同步等于当前记录的绝对地址absoluteAddrCurrent
            qDebug()<<cnt;
            if(absoluteAddrLocal == 0)
            {
                absoluteAddrLocal = absoluteAddrCurrent;
            }
        //    =ba->databuf;
            Bytesskipped = absoluteAddrCurrent-absoluteAddrLocal;//比较当前记录的绝对地址absoluteAddrCurrent和本地的绝对地址absoluteAddrLocal是否有偏差
           // Transmit(nDeviceType,nDeviceInd,nCANInd,,ba->datalen);
        break;
        case 0x01://文件结束记录
            return 1;
        break;
        case 0x02://扩展段地址记录
            ExStageAddr = (ba->databuf[0]<<8|ba->databuf[1])<<2;
            ExLineAddr = 0x00;
            return 0;//return ok
        break;
        case 0x04://扩展线性地址记录
            ExLineAddr = (ba->databuf[0]<<8|ba->databuf[1])<<16;
            ExStageAddr = 0x00;
            return 0;//return ok
        break;
        default:
            return 2;
        break;
    }

    for(unsigned int i = 0;i < Bytesskipped;i++)
    {//被跳过的地址，填充0
  //     out <<(unsigned char)0x00;
    }
   if(Bytesskipped!=0)
    {
   //    qDebug() <<Bytesskipped;
    }
    absoluteAddrLocal += Bytesskipped;//本地绝对地址absoluteAddrLocal累加

    for(unsigned int i = 0;i < ba->datalen;i++)
    {
        //out <<ba->databuf[i];
    }

    absoluteAddrLocal += ba->datalen;//本地绝对地址absoluteAddrLocal累加

    return 0;//return ok
}

#endif





