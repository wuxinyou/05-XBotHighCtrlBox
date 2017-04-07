/****************************************************************************
** Meta object code from reading C++ file 'modle_2d.h'
**
** Created: Fri Dec 21 11:06:30 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/modle_2d.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modle_2d.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Modle_2d[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      23,    9,    9,    9, 0x0a,
      39,    9,    9,    9, 0x0a,
      55,    9,    9,    9, 0x0a,
      71,    9,    9,    9, 0x0a,
      87,    9,    9,    9, 0x0a,
     103,    9,    9,    9, 0x0a,
     119,    9,    9,    9, 0x0a,
     135,    9,    9,    9, 0x0a,
     151,    9,    9,    9, 0x0a,
     167,    9,    9,    9, 0x0a,
     184,    9,    9,    9, 0x0a,
     205,    9,  201,    9, 0x0a,
     218,    9,  201,    9, 0x0a,
     231,    9,  201,    9, 0x0a,
     244,    9,  201,    9, 0x0a,
     257,    9,  201,    9, 0x0a,
     270,    9,  201,    9, 0x0a,
     283,    9,  201,    9, 0x0a,
     296,    9,  201,    9, 0x0a,
     309,    9,  201,    9, 0x0a,
     322,    9,  201,    9, 0x0a,
     336,    9,  201,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Modle_2d[] = {
    "Modle_2d\0\0setDis(bool)\0setValue_1(int)\0"
    "setValue_2(int)\0setValue_3(int)\0"
    "setValue_4(int)\0setValue_5(int)\0"
    "setValue_6(int)\0setValue_7(int)\0"
    "setValue_8(int)\0setValue_9(int)\0"
    "setValue_10(int)\0setValue_11(int)\0int\0"
    "getValue_1()\0getValue_2()\0getValue_3()\0"
    "getValue_4()\0getValue_5()\0getValue_6()\0"
    "getValue_7()\0getValue_8()\0getValue_9()\0"
    "getValue_10()\0getValue_11()\0"
};

const QMetaObject Modle_2d::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Modle_2d,
      qt_meta_data_Modle_2d, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Modle_2d::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Modle_2d::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Modle_2d::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Modle_2d))
        return static_cast<void*>(const_cast< Modle_2d*>(this));
    return QWidget::qt_metacast(_clname);
}

int Modle_2d::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setDis((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: setValue_1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: setValue_2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setValue_3((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setValue_4((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: setValue_5((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: setValue_6((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: setValue_7((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: setValue_8((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: setValue_9((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: setValue_10((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: setValue_11((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: { int _r = getValue_1();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 13: { int _r = getValue_2();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: { int _r = getValue_3();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 15: { int _r = getValue_4();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 16: { int _r = getValue_5();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 17: { int _r = getValue_6();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 18: { int _r = getValue_7();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 19: { int _r = getValue_8();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 20: { int _r = getValue_9();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 21: { int _r = getValue_10();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 22: { int _r = getValue_11();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
