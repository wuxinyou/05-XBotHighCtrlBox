/****************************************************************************
** Meta object code from reading C++ file 'qjoy.h'
**
** Created: Fri Dec 23 16:59:03 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/qjoy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qjoy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Qjoy[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x08,
      23,    5,    5,    5, 0x08,
      33,    5,    5,    5, 0x08,
      47,    5,   43,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Qjoy[] = {
    "Qjoy\0\0showMsg(QString)\0openJoy()\0"
    "joyMove()\0int\0calcPos(uint)\0"
};

const QMetaObject Qjoy::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Qjoy,
      qt_meta_data_Qjoy, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Qjoy::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Qjoy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Qjoy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Qjoy))
        return static_cast<void*>(const_cast< Qjoy*>(this));
    if (!strcmp(_clname, "Ui::qjoy"))
        return static_cast< Ui::qjoy*>(const_cast< Qjoy*>(this));
    return QWidget::qt_metacast(_clname);
}

int Qjoy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: openJoy(); break;
        case 2: joyMove(); break;
        case 3: { int _r = calcPos((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
