#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <iostream>
#include <QPoint>
#include <QRect>

class Connection
{

private:
    QPoint m_startPos;
    QPoint m_endPos;
    int m_penWidth;
    static constexpr int m_penMouseOverWidth = 5;
    static constexpr int m_penNormalWidth = 3;

public:
    enum PenType
    {
        NORMAL,
        MOUSE_OVER
    };

    Connection(QPoint p_startPos, QPoint p_endPos);
    ~Connection();
    bool contains(QPointF p_pos);
    int penWidth();
    void setPenWidth(PenType p_penType);
    QPoint endPos();
    void setEndPos(QPoint endPos);
    QPoint startPos();
    void setStartPos(QPoint startPos);
};

#endif // CONNECTION_HPP
