#ifndef HYOFRAME_H
#define HYOFRAME_H

#include <QByteArray>

class HyoFrame
{
private:
    QByteArray m_data;
    mutable int m_idx;

    bool checkSize(int size) const;

public:
    explicit HyoFrame();
    explicit HyoFrame(const QByteArray &src);
    explicit HyoFrame(const char *data, int size);
    ~HyoFrame();

    inline void clear() { m_data.clear(); m_idx = 0; }

    inline int size() const { return m_data.size(); }
    inline int index() const { return m_idx; }
    inline void setIndex(int idx) const { m_idx = idx; }

    inline const char* data() const { return m_data.data(); }
    inline const QByteArray& toByteArray() const { return m_data; }

    quint8 readU1() const;
    quint16 readU2(bool isLittleEndian = false) const;
    quint32 readU4(bool isLittleEndian = false) const;
    quint64 readU8(bool isLittleEndian = false) const;
    void readBuf(char *dst, int size) const;

    void writeU1(const quint8 val);
    void writeU2(const quint16 val, bool isLittleEndian = false);
    void writeU2(const quint16 *val, int count, bool isLittleEndian = false);
    void writeU4(const quint32 val, bool isLittleEndian = false);
    void writeU4(const quint32 *val, int count, bool isLittleEndian = false);
    void writeU8(const quint64 val, bool isLittleEndian = false);
    void writeU8(const quint64 *val, int count, bool isLittleEndian = false);
    void writeBuf(const char *src, int size);
    void writeBuf(const uchar *src, int size);
    void writeBuf(const QByteArray &data);
    void append(const QByteArray &data);

    void writeStreamAsciiToBin(const HyoFrame *src);
    void writeStreamBinToAscii(const HyoFrame *src);

    HyoFrame& operator=(const HyoFrame &other);
    HyoFrame& operator=(const QByteArray &data);
    HyoFrame& operator+=(const HyoFrame &other);
    HyoFrame& operator+=(const QByteArray &data);
    HyoFrame& operator+=(const char *data);

    static quint8 calLRC(const char *data, int size);
};

#endif // HYOFRAME_H
