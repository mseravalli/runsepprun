/****************************************************************************
** Meta object code from reading C++ file 'TestLevel.h'
**
** Created: Thu May 13 17:33:01 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RunServerRun/TestLevel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TestLevel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TestLevel[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      23,   10,   10,   10, 0x08,
      34,   10,   10,   10, 0x08,
      52,   10,   10,   10, 0x08,
      79,   10,   10,   10, 0x08,
     100,   10,   10,   10, 0x08,
     127,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TestLevel[] = {
    "TestLevel\0\0loadLevel()\0parseXML()\0"
    "testNoCollision()\0testEnvironmentCollision()\0"
    "testEnemyCollision()\0testCollectableCollision()\0"
    "testImmediateDeathCollision()\0"
};

const QMetaObject TestLevel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TestLevel,
      qt_meta_data_TestLevel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TestLevel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TestLevel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TestLevel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestLevel))
        return static_cast<void*>(const_cast< TestLevel*>(this));
    return QObject::qt_metacast(_clname);
}

int TestLevel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loadLevel(); break;
        case 1: parseXML(); break;
        case 2: testNoCollision(); break;
        case 3: testEnvironmentCollision(); break;
        case 4: testEnemyCollision(); break;
        case 5: testCollectableCollision(); break;
        case 6: testImmediateDeathCollision(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
