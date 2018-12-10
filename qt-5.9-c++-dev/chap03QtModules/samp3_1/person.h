#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("author", "Murphy")
    Q_CLASSINFO("company", "orange")
    Q_CLASSINFO("version", "1.0.0")

    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString name MEMBER m_name)
    Q_PROPERTY(int score MEMBER m_score)

private:
    int m_age = 10;
    QString m_name;
    int m_score = 97;

public:
    explicit Person(QString fName, QObject *parent = nullptr);
    int age();
    void setAge(int value);
    void incAge();

signals:
    void ageChanged(int value);

public slots:
};

#endif // PERSON_H




