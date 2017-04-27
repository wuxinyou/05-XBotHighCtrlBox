/****************************************************************************
** Meta object code from reading C++ file 'counter.h'
**
** Created: Sun Dec 18 02:14:46 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/counter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'counter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Counter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       2,   29, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      23,    8,    8,    8, 0x0a,
      38,    8,    8,    8, 0x0a,

 // properties: name, type, flags
      65,   61, 0x02095103,
      71,   61, 0x02095103,

       0        // eod
};

static const char qt_meta_stringdata_Counter[] = {
    "Counter\0\0setValue(int)\0setDigits(int)\0"
    "setDigitsFile(QString)\0int\0value\0"
    "digits\0"
};

const QMetaObject Counter::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Counter,
      qt_meta_data_Counter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Counter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Counter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Counter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Counter))
        return static_cast<void*>(const_cast< Counter*>(this));
    return QWidget::qt_metacast(_clname);
}

int Counter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setDigits((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: setDigitsFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = value(); break;
        case 1: *reinterpret_cast< int*>(_v) = digits(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setValue(*reinterpret_cast< int*>(_v)); break;
        case 1: setDigits(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
