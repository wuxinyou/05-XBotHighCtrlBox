/****************************************************************************
** Meta object code from reading C++ file 'mainframe.h'
**
** Created: Mon Jun 24 15:59:06 2013
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
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      33,   10,   10,   10, 0x08,
      56,   10,   10,   10, 0x08,
      76,   10,   10,   10, 0x08,
      90,   10,   10,   10, 0x08,
      98,   10,   10,   10, 0x08,
     106,   10,   10,   10, 0x08,
     114,   10,   10,   10, 0x08,
     122,   10,   10,   10, 0x08,
     130,   10,   10,   10, 0x08,
     138,   10,   10,   10, 0x08,
     146,   10,   10,   10, 0x08,
     154,   10,   10,   10, 0x08,
     162,   10,   10,   10, 0x08,
     170,   10,   10,   10, 0x08,
     178,   10,   10,   10, 0x08,
     186,   10,   10,   10, 0x08,
     194,   10,   10,   10, 0x08,
     202,   10,   10,   10, 0x08,
     210,   10,   10,   10, 0x08,
     222,   10,   10,   10, 0x08,
     231,   10,   10,   10, 0x08,
     240,   10,   10,   10, 0x08,
     249,   10,   10,   10, 0x08,
     258,   10,   10,   10, 0x08,
     269,   10,   10,   10, 0x08,
     281,   10,   10,   10, 0x08,
     298,   10,   10,   10, 0x08,
     310,   10,   10,   10, 0x08,
     322,   10,   10,   10, 0x08,
     333,   10,   10,   10, 0x08,
     341,   10,   10,   10, 0x08,
     349,   10,   10,   10, 0x08,
     357,   10,   10,   10, 0x08,
     365,   10,   10,   10, 0x08,
     373,   10,   10,   10, 0x08,
     381,   10,   10,   10, 0x08,
     389,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Mainframe[] = {
    "Mainframe\0\0readyRead(QByteArray)\0"
    "disposejoy(QByteArray)\0changmodelsize(int)\0"
    "sendcommand()\0setM1()\0setM2()\0setM3()\0"
    "setM4()\0setM5()\0zb_tq()\0zb_zd()\0zb_sp()\0"
    "zb_sq()\0zb_wz()\0sb_qg()\0sb_qz()\0sb_sq()\0"
    "sb_qs()\0sb_bz()\0zmControl()\0setCH1()\0"
    "setCH2()\0setCH3()\0setCH4()\0setCHAll()\0"
    "setCHFull()\0changeVideo(int)\0asgChange()\0"
    "rsgChange()\0jjChange()\0xb_fy()\0sw_fy()\0"
    "xj_fy()\0zb_fy()\0db_fy()\0db_xz()\0sz_kh()\0"
    "sz_xz()\0"
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
        case 2: changmodelsize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: sendcommand(); break;
        case 4: setM1(); break;
        case 5: setM2(); break;
        case 6: setM3(); break;
        case 7: setM4(); break;
        case 8: setM5(); break;
        case 9: zb_tq(); break;
        case 10: zb_zd(); break;
        case 11: zb_sp(); break;
        case 12: zb_sq(); break;
        case 13: zb_wz(); break;
        case 14: sb_qg(); break;
        case 15: sb_qz(); break;
        case 16: sb_sq(); break;
        case 17: sb_qs(); break;
        case 18: sb_bz(); break;
        case 19: zmControl(); break;
        case 20: setCH1(); break;
        case 21: setCH2(); break;
        case 22: setCH3(); break;
        case 23: setCH4(); break;
        case 24: setCHAll(); break;
        case 25: setCHFull(); break;
        case 26: changeVideo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: asgChange(); break;
        case 28: rsgChange(); break;
        case 29: jjChange(); break;
        case 30: xb_fy(); break;
        case 31: sw_fy(); break;
        case 32: xj_fy(); break;
        case 33: zb_fy(); break;
        case 34: db_fy(); break;
        case 35: db_xz(); break;
        case 36: sz_kh(); break;
        case 37: sz_xz(); break;
        default: ;
        }
        _id -= 38;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
