/****************************************************************************
** Meta object code from reading C++ file 'TestClient.h'
**
** Created: Thu May 13 13:52:58 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RunSeppRun/TestClient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TestClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TestClient[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      34,   11,   11,   11, 0x08,
      54,   11,   11,   11, 0x08,
      75,   11,   11,   11, 0x08,
      99,   11,   11,   11, 0x08,
     121,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TestClient[] = {
    "TestClient\0\0testSendHelloPacket()\0"
    "testSendAckPacket()\0testSendAck2Packet()\0"
    "testSendLevelIDPacket()\0testSendReadyPacket()\0"
    "testSendKeyInputPacket()\0"
};

const QMetaObject TestClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TestClient,
      qt_meta_data_TestClient, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TestClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TestClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TestClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestClient))
        return static_cast<void*>(const_cast< TestClient*>(this));
    return QObject::qt_metacast(_clname);
}

int TestClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: testSendHelloPacket(); break;
        case 1: testSendAckPacket(); break;
        case 2: testSendAck2Packet(); break;
        case 3: testSendLevelIDPacket(); break;
        case 4: testSendReadyPacket(); break;
        case 5: testSendKeyInputPacket(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
