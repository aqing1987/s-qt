#include "person.h"


Person::Person(QString fName, QObject *parent): QObject(parent)
{
    m_name = fName;
}

int Person::age()
{
    return m_age;
}

void Person::setAge(int value)
{
    m_age = value;
    emit ageChanged(m_age);
}

void Person::incAge()
{
    ++m_age;
    emit ageChanged(m_age);
}

