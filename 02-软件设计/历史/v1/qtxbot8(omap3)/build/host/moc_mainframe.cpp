/****************************************************************************
** Meta object code from reading C++ file 'mainframe.h'
**
** Created: Tue Dec 25 17:41:05 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/mainframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Mainframe[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      33,   10,   10,   10, 0x08,
      56,   10,   10,   10, 0x08,
      67,   10,   10,   10, 0x08,
      87,   10,   10,   10, 0x08,
     101,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Mainframe[] = {
    "Mainframe\0\0readyRead(QByteArray)\0"
    "disposejoy(QByteArray)\0hidemenu()\0"
    "changmodelsize(int)\0sendcommand()\0"
    "showmyself()\0"
};

const QMetaObject Mainframe::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Mainframe,
      qt_meta_data_Mainframe, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Mainframe::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Mainframe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Mainframe::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Mainframe))
        return static_cast<void*>(const_cast< Mainframe*>(this));
    if (!strcmp(_clname, "Ui::mainframe"))
        return static_cast< Ui::mainframe*>(const_cast< Mainframe*>(this));
    return QDialog::qt_metacast(_clname);
}

int Mainframe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: readyRead((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: disposejoy((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: hidemenu(); break;
        case 3: changmodelsize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: sendcommand(); break;
        case 5: showmyself(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
