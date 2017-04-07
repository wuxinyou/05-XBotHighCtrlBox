/****************************************************************************
** Meta object code from reading C++ file 'signalshow.h'
**
** Created: Tue Jul 24 16:24:05 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/signalshow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'signalshow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SignalShow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SignalShow[] = {
    "SignalShow\0\0flag\0setwiredflag(bool)\0"
};

const QMetaObject SignalShow::staticMetaObject = {
    { &AbstractMeter::staticMetaObject, qt_meta_stringdata_SignalShow,
      qt_meta_data_SignalShow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SignalShow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SignalShow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SignalShow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SignalShow))
        return static_cast<void*>(const_cast< SignalShow*>(this));
    return AbstractMeter::qt_metacast(_clname);
}

int SignalShow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractMeter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setwiredflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
