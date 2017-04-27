/****************************************************************************
** Meta object code from reading C++ file 'model.h'
**
** Created: Mon Apr 8 10:40:43 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/model.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mymodel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,    8,    9,    8, 0x0a,
      39,   33,    8,    8, 0x0a,
      57,   33,    8,    8, 0x0a,
      72,   33,    8,    8, 0x0a,
      88,   33,    8,    8, 0x0a,
     105,   33,    8,    8, 0x0a,
     122,   33,    8,    8, 0x0a,
     140,   33,    8,    8, 0x0a,
     158,   33,    8,    8, 0x0a,
     177,   33,    8,    8, 0x0a,
     193,   33,    8,    8, 0x0a,
     218,   33,    8,    8, 0x0a,
     241,  239,    8,    8, 0x0a,
     265,  263,    8,    8, 0x0a,
     291,  286,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mymodel[] = {
    "mymodel\0\0double\0getfocalLength()\0angle\0"
    "luopanRotate(int)\0dabiPitch(int)\0"
    "dabiRotate(int)\0xiaobiPitch(int)\0"
    "yuntaiPitch(int)\0yuntaiRotate(int)\0"
    "shouwanPitch(int)\0shouwanRotate(int)\0"
    "zhibiPitch(int)\0qianjinxiangjiPitch(int)\0"
    "shouzhuaMediate(int)\0x\0updateview_xz(double)\0"
    "y\0updateview_y(double)\0size\0"
    "updatesize(double)\0"
};

const QMetaObject mymodel::staticMetaObject = {
    { &GLViewWidget::staticMetaObject, qt_meta_stringdata_mymodel,
      qt_meta_data_mymodel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mymodel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mymodel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mymodel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mymodel))
        return static_cast<void*>(const_cast< mymodel*>(this));
    return GLViewWidget::qt_metacast(_clname);
}

int mymodel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GLViewWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { double _r = getfocalLength();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 1: luopanRotate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: dabiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: dabiRotate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: xiaobiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: yuntaiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: yuntaiRotate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: shouwanPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: shouwanRotate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: zhibiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: qianjinxiangjiPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: shouzhuaMediate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: updateview_xz((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: updateview_y((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: updatesize((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
