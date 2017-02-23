/****************************************************************************
** Meta object code from reading C++ file 'model_1.h'
**
** Created: Mon Feb 18 09:40:02 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/model_1.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'model_1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mymodel_1[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   10,   11,   10, 0x0a,
      41,   35,   10,   10, 0x0a,
      56,   35,   10,   10, 0x0a,
      72,   35,   10,   10, 0x0a,
      89,   35,   10,   10, 0x0a,
     106,   35,   10,   10, 0x0a,
     124,   35,   10,   10, 0x0a,
     142,   35,   10,   10, 0x0a,
     161,   35,   10,   10, 0x0a,
     177,   35,   10,   10, 0x0a,
     202,   35,   10,   10, 0x0a,
     225,  223,   10,   10, 0x0a,
     249,  247,   10,   10, 0x0a,
     275,  270,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mymodel_1[] = {
    "mymodel_1\0\0double\0getfocalLength()\0"
    "angle\0dabiPitch(int)\0dabiRotate(int)\0"
    "xiaobiPitch(int)\0yuntaiPitch(int)\0"
    "yuntaiRotate(int)\0shouwanPitch(int)\0"
    "shouwanRotate(int)\0zhibiPitch(int)\0"
    "qianjinxiangjiPitch(int)\0shouzhuaMediate(int)\0"
    "x\0updateview_xz(double)\0y\0"
    "updateview_y(double)\0size\0updatesize(double)\0"
};

const QMetaObject mymodel_1::staticMetaObject = {
    { &GLViewWidget::staticMetaObject, qt_meta_stringdata_mymodel_1,
      qt_meta_data_mymodel_1, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mymodel_1::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mymodel_1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mymodel_1::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mymodel_1))
        return static_cast<void*>(const_cast< mymodel_1*>(this));
    return GLViewWidget::qt_metacast(_clname);
}

int mymodel_1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GLViewWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { double _r = getfocalLength();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 1: dabiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: dabiRotate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: xiaobiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: yuntaiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: yuntaiRotate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: shouwanPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: shouwanRotate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: zhibiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: qianjinxiangjiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: shouzhuaMediate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: updateview_xz((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: updateview_y((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: updatesize((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
