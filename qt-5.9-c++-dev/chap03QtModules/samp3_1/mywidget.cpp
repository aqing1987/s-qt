#include <QMetaProperty>

#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    boy = new Person("Jack");
    boy->setProperty("score", 95);
    boy->setProperty("age", 10);
    boy->setProperty("sex", "Boy"); // dynamic property
    connect(boy, &Person::ageChanged, this, &MyWidget::on_ageChanged);

    girl = new Person("Murphy");
    girl->setProperty("score", 100);
    girl->setProperty("age", 1);
    girl->setProperty("sex", "Girl"); // dynamic property
    connect(girl, &Person::ageChanged, this, &MyWidget::on_ageChanged);

    // dynamic property
    ui->spinBoxBoy->setProperty("isBoy", true);
    ui->spinBoxGirl->setProperty("isBoy", false);

    connect(ui->spinBoxBoy, SIGNAL(valueChanged(int)), this, SLOT(on_spin_valueChanged(int)));
    connect(ui->spinBoxGirl, SIGNAL(valueChanged(int)), this, SLOT(on_spin_valueChanged(int)));
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_btnBoyInc_clicked()
{
    boy->incAge();
}

void MyWidget::on_btnGirlInc_clicked()
{
    girl->incAge();
}

void MyWidget::on_btnClassInfo_clicked()
{
    const QMetaObject *meta = boy->metaObject();
    ui->textEdit->clear();

    ui->textEdit->append("object info\n");
    ui->textEdit->append(QString("class name: %1").arg(meta->className()));

    ui->textEdit->append("property");
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) {
        const char* propName = meta->property(i).name();
        ui->textEdit->append(QString("property name =%1, property value = %2").arg(propName).arg(boy->property(propName).toString()));
    }

    ui->textEdit->append("");
    ui->textEdit->append("classInfo");
    for (int i = meta->classInfoOffset(); i < meta->classInfoCount(); ++i) {
        QMetaClassInfo classInfo = meta->classInfo(i);
        ui->textEdit->append(QString("Name=%1, value=%2").arg(classInfo.name()).arg(classInfo.value()));
    }
}

void MyWidget::on_btnClear_clicked()
{
    ui->textEdit->clear();
}

void MyWidget::on_ageChanged(int value)
{
    // response Person's ageChanged() signal
    Q_UNUSED(value);
    Person *aPerson = qobject_cast<Person *>(sender());
    QString name = aPerson->property("name").toString();
    QString sex = aPerson->property("sex").toString();
    int age = aPerson->age();
    ui->textEdit->append(name + "," + sex + QString::asprintf(", age=%d", age));
}

void MyWidget::on_spin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    QSpinBox *spinBox = qobject_cast<QSpinBox *>(sender());
    if (spinBox->property("isBoy").toBool())
        boy->setAge(spinBox->value());
    else
        girl->setAge(spinBox->value());
}
