#include "connection.hpp"


int Connection::penWidth()
{
    return m_penWidth;
}

void Connection::setPenWidth(PenType p_penType)
{
    switch(p_penType)
    {
    case NORMAL:
        m_penWidth = Connection::m_penNormalWidth;
        break;

    case MOUSE_OVER:
        m_penWidth = Connection::m_penMouseOverWidth;
        break;
    }
}

QPoint Connection::endPos()
{
    return m_endPos;
}

void Connection::setEndPos(QPoint endPos)
{
    m_endPos = endPos;
}

QPoint Connection::startPos()
{
    return m_startPos;
}

void Connection::setStartPos(QPoint startPos)
{
    m_startPos = startPos;
}
Connection::Connection(QPoint p_startPos, QPoint p_endPos)
{
    m_startPos = p_startPos;
    m_endPos = p_endPos;
    m_penWidth = Connection::m_penNormalWidth;
}

Connection::~Connection()
{

}

bool Connection::contains(QPointF p_pos)
{
    QRect rect(m_startPos, m_endPos);
    double m = (double)rect.height() / (double)rect.width();
    double b = m_startPos.y() - m * startPos().x(); // m * x + b = y <=> b = y - m * x
    if(p_pos.x() >= rect.x() && p_pos.x() <= rect.x() + rect.width())
    {
        double result = m * p_pos.x() + b;
        if(p_pos.y() >= result - m_penWidth && p_pos.y() <= result + m_penWidth)
            return true;
    }
    return false;
}

