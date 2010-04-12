/****************************************************************************
** Meta object code from reading C++ file 'cannonfield.h'
**
** Created: Wed Apr 7 23:56:18 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cannonfield.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cannonfield.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CannonField[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      22,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   40,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CannonField[] = {
    "CannonField\0\0newAngle\0angleChanged(int)\0"
    "angle\0setAngle(int)\0"
};

const QMetaObject CannonField::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CannonField,
      qt_meta_data_CannonField, 0 }
};

const QMetaObject *CannonField::metaObject() const
{
    return &staticMetaObject;
}

void *CannonField::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CannonField))
        return static_cast<void*>(const_cast< CannonField*>(this));
    return QWidget::qt_metacast(_clname);
}

int CannonField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: angleChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setAngle((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CannonField::angleChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
