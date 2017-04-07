/****************************************************************************
** Meta object code from reading C++ file 'ctrsize.h'
**
** Created: Wed Dec 5 16:15:35 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/ctrsize.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ctrsize.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CtrSize[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      29,    8,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CtrSize[] = {
    "CtrSize\0\0sizeflagchange(int)\0sendx(int)\0"
};

const QMetaObject CtrSize::staticMetaObject = {
    { &AbstractMeter::staticMetaObject, qt_meta_stringdata_CtrSize,
      qt_meta_data_CtrSize, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CtrSize::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CtrSize::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CtrSize::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CtrSize))
        return static_cast<void*>(const_cast< CtrSize*>(this));
    return AbstractMeter::qt_metacast(_clname);
}

int CtrSize::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractMeter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sizeflagchange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: sendx((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CtrSize::sizeflagchange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CtrSize::sendx(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
