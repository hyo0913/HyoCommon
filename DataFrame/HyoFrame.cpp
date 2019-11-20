#include "HyoFrame.h"
#include "qendian.h"
#include "QString"

HyoFrame::HyoFrame() :
    m_idx(0)
{

}

HyoFrame::HyoFrame(const QByteArray &src) :
    m_data(src),
    m_idx(0)
{

}

HyoFrame::HyoFrame(const char *data, int size) :
    m_data(data, size),
    m_idx(0)
{
}

HyoFrame::~HyoFrame()
{

}

bool HyoFrame::checkSize(int size) const
{
    bool result = false;

    if( m_idx + size <= m_data.size() ) result = true;

    return result;
}

quint8 HyoFrame::readU1() const
{
    quint8 val = 0;

    if( checkSize(sizeof(quint8)) )
    {
        val = qToLittleEndian(*reinterpret_cast<const quint8*>(m_data.data()+m_idx));
        m_idx += sizeof(quint8);
    }

    return val;
}

quint16 HyoFrame::readU2(bool isLittleEndian) const
{
    quint16 val = 0;

    if( checkSize(sizeof(quint16)) )
    {
        if( isLittleEndian ) {
            val = qToLittleEndian(*reinterpret_cast<const quint16*>(m_data.data()+m_idx));
        } else {
            val = qToBigEndian(*reinterpret_cast<const quint16*>(m_data.data()+m_idx));
        }
        m_idx += sizeof(quint16);
    }

    return val;
}

quint32 HyoFrame::readU4(bool isLittleEndian) const
{
    quint32 val = 0;

    if( checkSize(sizeof(quint32)) )
    {
        if( isLittleEndian ) {
            val = qToLittleEndian(*reinterpret_cast<const quint32*>(m_data.data()+m_idx));
        } else {
            val = qToBigEndian(*reinterpret_cast<const quint32*>(m_data.data()+m_idx));
        }
        m_idx += sizeof(quint32);
    }

    return val;
}

quint64 HyoFrame::readU8(bool isLittleEndian) const
{
    quint64 val = 0;

    if( checkSize(sizeof(quint64)) )
    {
        if( isLittleEndian ) {
            val = qToLittleEndian(*reinterpret_cast<const quint64*>(m_data.data()+m_idx));
        } else {
            val = qToBigEndian(*reinterpret_cast<const quint64*>(m_data.data()+m_idx));
        }
        m_idx += sizeof(quint64);
    }

    return val;
}

void HyoFrame::readBuf(char *dst, int size) const
{
    memset(dst, 0, static_cast<uint>(size));

    if( checkSize(size) )
    {
        memcpy(dst, m_data.data()+m_idx, static_cast<uint>(size));
        m_idx += size;
    }
}

void HyoFrame::writeU1(const quint8 val)
{
    int dataSize = sizeof(quint8);

    if( m_idx+dataSize > m_data.size() ) {
        m_data.resize(m_idx+dataSize);
    }

    m_data.data()[m_idx] = static_cast<char>(val);
    m_idx += dataSize;
}

void HyoFrame::writeU2(const quint16 val, bool isLittleEndian)
{
    int dataSize = sizeof(quint16);

    if( m_idx+dataSize > m_data.size() ) {
        m_data.resize(m_idx+dataSize);
    }

    if( isLittleEndian ) {
        qToLittleEndian(val, reinterpret_cast<uchar*>(m_data.data()+m_idx));
    } else {
        qToBigEndian(val, reinterpret_cast<uchar*>(m_data.data()+m_idx));
    }
    m_idx += dataSize;
}

void HyoFrame::writeU4(const quint32 val, bool isLittleEndian)
{
    int dataSize = sizeof(quint32);

    if( m_idx+dataSize > m_data.size() ) {
        m_data.resize(m_idx+dataSize);
    }

    if( isLittleEndian ) {
        qToLittleEndian(val, reinterpret_cast<uchar*>(m_data.data()+m_idx));
    } else {
        qToBigEndian(val, reinterpret_cast<uchar*>(m_data.data()+m_idx));
    }
    m_idx += dataSize;
}

void HyoFrame::writeU8(const quint64 val, bool isLittleEndian)
{
    int dataSize = sizeof(quint64);

    if( m_idx+dataSize > m_data.size() ) {
        m_data.resize(m_idx+dataSize);
    }

    if( isLittleEndian ) {
        qToLittleEndian(val, reinterpret_cast<uchar*>(m_data.data()+m_idx));
    } else {
        qToBigEndian(val, reinterpret_cast<uchar*>(m_data.data()+m_idx));
    }
    m_idx += dataSize;
}

void HyoFrame::writeBuf(const char *src, int size)
{
    if( m_idx+size > m_data.size() ) {
        m_data.resize(m_idx+size);
    }

    memcpy(m_data.data()+m_idx, src, static_cast<size_t>(size));
    m_idx += size;
}

void HyoFrame::writeBuf(const uchar *src, int size)
{
    if( m_idx+size > m_data.size() ) {
        m_data.resize(m_idx+size);
    }

    memcpy(m_data.data()+m_idx, src, static_cast<size_t>(size));
    m_idx += size;
}

void HyoFrame::writeStreamAsciiToBin(const HyoFrame *src)
{
    if( src == NULL ) return;

    bool ok = false;
    const char* srcBuf = src->data();
    quint8 temp = 0;

    if( src->size() % 2 ) return;
    for( int i = 0; i < src->size(); i+=2 )
    {
        temp = static_cast<quint8>(QString::fromLatin1(&srcBuf[i], 2).toUShort(&ok, 16));
        if( !ok ) break;

        this->writeU1(temp);
    }
}

void HyoFrame::writeStreamBinToAscii(const HyoFrame *src)
{
    if( src == NULL ) return;

    const char* srcBuf = src->data();
    QString temp;

    for( int i = 0; i < src->size(); i++ )
    {
        temp.sprintf("%02X", static_cast<uchar>(srcBuf[i]));
        m_data.append(temp);
    }

    m_idx += src->size()*2;
}

quint8 HyoFrame::calLRC(const char *data, int size)
{
    quint8 ret = 0;
    char temp = 0;

    for( int i = 0; i < size; i ++ )
    {
        temp += data[i];
    }

    ret = static_cast<quint8>(-temp);

    return ret;
}

HyoFrame& HyoFrame::operator=(const HyoFrame &other)
{
    m_data.clear();
    m_idx = 0;

    m_data = other.m_data;

    return *this;
}

HyoFrame& HyoFrame::operator=(const QByteArray &data)
{
    m_data.clear();
    m_idx = 0;

    m_data = data;

    return *this;
}

HyoFrame &HyoFrame::operator+=(const HyoFrame &other)
{
    m_data.append(other.m_data);
    m_idx = m_data.size();

    return *this;
}

HyoFrame &HyoFrame::operator+=(const QByteArray &data)
{
    m_data.append(data);
    m_idx = m_data.size();

    return *this;
}

HyoFrame &HyoFrame::operator+=(const char *data)
{
    m_data.append(data);
    m_idx = m_data.size();

    return *this;
}
